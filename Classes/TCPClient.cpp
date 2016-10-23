#include "TCPClient.h"
#include "NetworkManger.h"

CTCPClient::CTCPClient()
{
	m_flag = false;
	m_pRequest = nullptr;
	// ��ʼ��
	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
	m_sockClient = INVALID_SOCKET;

	//�������߳�
	thread t(&CTCPClient::NetworkThreadFunc, this);
	t.detach();
}

CTCPClient::~CTCPClient()
{
	Destroy();
	m_flag = true;
	while (m_flag)
	{
	}
}

void CTCPClient::NetworkThreadFunc()
{
	m_requestMutex.lock();
	if (!Create(g_strServerIP.c_str(), g_nServerPort, BLOCKSECONDS, true))
	{
		log("connect server error!");
		m_requestMutex.unlock();
		return;
	}
	m_requestMutex.unlock();
	while (1)
	{
		m_requestMutex.lock();
		if (/*m_pRequest && */m_sockClient != INVALID_SOCKET)
		{
			char buf[g_nMaxRequsetDataSize];
			memset(buf, 0, g_nMaxRequsetDataSize);
			int rcvSize = g_nMaxRequsetDataSize;
			if (ReceiveMsg(buf, rcvSize))
			{
				//����Ϣ�������ack
				NetworkManger::getInstance()->pushACKQueue(buf, rcvSize);
				m_pRequest = nullptr;
			}
			else
			{
#ifdef WIN32
				int err = WSAGetLastError();
#else
				int err = errno;
#endif
				log("errno = %d", err);
			}
		}
		if (m_sockClient == INVALID_SOCKET)
		{
			m_requestMutex.unlock();
			m_flag = false;
			return;
		}
		m_requestMutex.unlock();
#ifdef _WIN32
		Sleep(30);
#else
		usleep(30*1000); // takes microseconds
#endif
	}
}

bool CTCPClient::sendTCPRequset(CTCPRequest* request)
{
	if (request == nullptr)
	{
		log("request is null in sendTCPRequest()!");
		return false;
	}
	if (!SendMsg(request->getRequestData(),request->getRequestDataLen()))
	{
		log("send msg error in sendTCPRequest()!");
		return false;
	}
	if (!Flush())
	{
		log("send error");
		return false;
	}
	m_pRequest = request;
	return true;
}

void CTCPClient::closeSocket()
{
#ifdef WIN32
	closesocket(m_sockClient);
	WSACleanup();
#else
	close(m_sockClient);
#endif
}

bool CTCPClient::Create(const char* pszServerIP, int nServerPort, int nBlockSec, bool bKeepAlive /*= FALSE*/)
{
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;
	// ������
	if (pszServerIP == 0 || strlen(pszServerIP) > 15) {
		return false;
	}

#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if (ret != 0) {
		return false;
	}
#endif

	// �������׽���
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sockClient == INVALID_SOCKET) {
		closeSocket();
		return false;
	}

	// ����SOCKETΪKEEPALIVE
	if (bKeepAlive)
	{
		int		optval = 1;
		if (setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)))
		{
			closeSocket();
			return false;
		}
	}


	unsigned long serveraddr = inet_addr(pszServerIP);
	if (serveraddr == INADDR_NONE)	// ���IP��ַ��ʽ����
	{
		closeSocket();
		return false;
	}

	sockaddr_in	addr_in;
	memset((void *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nServerPort);
	addr_in.sin_addr.s_addr = serveraddr;

	if (connect(m_sockClient, (sockaddr *)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
		if (hasError()) {
			closeSocket();
			return false;
		}
		else	// WSAWOLDBLOCK
		{
#ifdef WIN32
			DWORD nMode = 1;
			int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
			if (nRes == SOCKET_ERROR) {
				closeSocket();
				return false;
			}
#else
			// ����Ϊ��������ʽ
			fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
#endif
			timeval timeout;
			timeout.tv_sec = nBlockSec;
			timeout.tv_usec = 0;
			fd_set writeset, exceptset;
			FD_ZERO(&writeset);
			FD_ZERO(&exceptset);
			FD_SET(m_sockClient, &writeset);
			FD_SET(m_sockClient, &exceptset);

			int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
			if (ret == 0 || ret < 0) {
				closeSocket();
				return false;
			}
			else	// ret > 0
			{
				ret = FD_ISSET(m_sockClient, &exceptset);
				if (ret)		// or (!FD_ISSET(m_sockClient, &writeset)
				{
					closeSocket();
					return false;
				}
			}
		}
	}



	//struct linger so_linger;
	//so_linger.l_onoff = 1;
	//so_linger.l_linger = 500;
	//setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	return true;
}

bool CTCPClient::SendMsg(void* pBuf, int nSize)
{
	if (pBuf == 0 || nSize <= 0) {
		return false;
	}

	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	// ���ͨѶ��Ϣ������
	int packsize = 0;
	packsize = nSize;

	// ���BUF���
	if (m_nOutbufLen + nSize > OUTBUFSIZE) {
		// ��������OUTBUF�е����ݣ������OUTBUF��
		Flush();
		if (m_nOutbufLen + nSize > OUTBUFSIZE) {
			// ������
			return false;
		}
	}
	// ������ӵ�BUFβ
	memcpy(m_bufOutput + m_nOutbufLen, pBuf, nSize);
	m_nOutbufLen += nSize;
	return true;
}

bool CTCPClient::ReceiveMsg(void* pBuf, int& nSize)
{
	//������
	if (pBuf == NULL || nSize <= 0) {
		return false;
	}

	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	int rcvLen = recvFromSock();
	if (rcvLen <= 0)
	{
		return false;
	}
	// ���Ƴ�һ����Ϣ
	if (m_nInbufStart + rcvLen > INBUFSIZE) {
		// ���һ����Ϣ�лؾ�����������ڻ��λ�������ͷβ��
		// �ȿ������λ�����ĩβ������
		int copylen = INBUFSIZE - m_nInbufStart;
		memcpy(pBuf, m_bufInput + m_nInbufStart, copylen);

		// �ٿ������λ�����ͷ����ʣ�ಿ��
		memcpy((unsigned char *)pBuf + copylen, m_bufInput, rcvLen - copylen);
		nSize = rcvLen;
	}
	else {
		// ��Ϣû�лؾ�����һ�ο�����ȥ
		memcpy(pBuf, m_bufInput + m_nInbufStart, rcvLen);
		nSize = rcvLen;
	}
	// ���¼��㻷�λ�����ͷ��λ��
	m_nInbufStart = (m_nInbufStart + rcvLen) % INBUFSIZE;
	m_nInbufLen -= rcvLen;
	return true;
}

bool CTCPClient::isConnected()
{
	if (m_sockClient == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool CTCPClient::hasError()
{
#ifdef WIN32
	int err = WSAGetLastError();
	if (err != WSAEWOULDBLOCK) {
#else
	int err = errno;
	if (err != EINPROGRESS && err != EAGAIN) {
#endif
		return true;
	}

	return false;
}

// �������ж�ȡ�����ܶ�����ݣ�ʵ����������������ݵĵط�
int CTCPClient::recvFromSock(void)
{
	if (m_nInbufLen >= INBUFSIZE || m_sockClient == INVALID_SOCKET) {
		return 0 ;
	}

	// ���յ�һ������
	int	savelen, savepos;			// ����Ҫ����ĳ��Ⱥ�λ��
	if (m_nInbufStart + m_nInbufLen < INBUFSIZE)	{	// INBUF�е�ʣ��ռ��л���
		savelen = INBUFSIZE - (m_nInbufStart + m_nInbufLen);		// �󲿿ռ䳤�ȣ����������ݵĳ���
	}
	else {
		savelen = INBUFSIZE - m_nInbufLen;
	}

	// ���������ݵ�ĩβ
	savepos = (m_nInbufStart + m_nInbufLen) % INBUFSIZE;
	CHECKF(savepos + savelen <= INBUFSIZE);
	int inlen = recv(m_sockClient, (char*)m_bufInput + savepos, savelen, 0);
	if (inlen > 0) {
		// �н��յ�����
		m_nInbufLen += inlen;

		if (m_nInbufLen > INBUFSIZE) {
			return 0;
		}

		// ���յڶ�������(һ�ν���û����ɣ����յڶ�������)
		if (inlen == savelen && m_nInbufLen < INBUFSIZE) {
			int savelen = INBUFSIZE - m_nInbufLen;
			int savepos = (m_nInbufStart + m_nInbufLen) % INBUFSIZE;
			CHECKF(savepos + savelen <= INBUFSIZE);
			inlen = recv(m_sockClient, (char*)m_bufInput + savepos, savelen, 0);
			if (inlen > 0) {
				m_nInbufLen += inlen;
				if (m_nInbufLen > INBUFSIZE) {
					return 0;
				}
			}
			else if (inlen == 0) {
				return 0;
			}
			else {
				// �����ѶϿ����ߴ��󣨰���������
				if (hasError()) {
					return 0;
				}
			}
		}
	}
	else if (inlen == 0) {
		return 0;
	}
	else {
		// �����ѶϿ����ߴ��󣨰���������
		if (hasError()) {
			return 0;
		}
	}

	return inlen;
}

bool CTCPClient::Flush(void)		// ��� OUTBUF > SENDBUF ����Ҫ���SEND����
{
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	if (m_nOutbufLen <= 0) {
		return true;
	}

	// ����һ������
	int	outsize;
	outsize = send(m_sockClient, (char*)m_bufOutput, m_nOutbufLen, 0);
	if (outsize > 0) {
		// ɾ���ѷ��͵Ĳ���
		if (m_nOutbufLen - outsize > 0) {
			memcpy(m_bufOutput, m_bufOutput + outsize, m_nOutbufLen - outsize);
		}

		m_nOutbufLen -= outsize;

		if (m_nOutbufLen < 0) {
			return false;
		}
	}
	else {
		if (hasError()) {
			return false;
		}
	}

	return true;
}

bool CTCPClient::Check(void)
{
	// ���״̬
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	char buf[1];
	int	ret = recv(m_sockClient, buf, 1, MSG_PEEK);
	if (ret == 0) {
		return false;
	}
	else if (ret < 0) {
		if (hasError()) {
			return false;
		}
		else {	// ����
			return true;
		}
	}
	else {	// ������
		return true;
	}

	return true;
}

void CTCPClient::Destroy(void)
{
	// �ر�
	//struct linger so_linger;
	//so_linger.l_onoff = 1;
	//so_linger.l_linger = 500;
	//int ret = setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	closeSocket();

	m_sockClient = INVALID_SOCKET;
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;

	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
}

