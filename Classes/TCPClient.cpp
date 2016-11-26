#include "TCPClient.h"
#include "NetworkManger.h"

CTCPClient::CTCPClient()
{
	m_nInbufLen = 0;
	m_nOutbufLen = 0;
	m_nInbufStart = 0;
	m_flag = false;
	m_pRequest = nullptr;
	// ��ʼ��
	m_bufInput = new unsigned char[INBUFSIZE];
	m_bufOutput = new unsigned char[OUTBUFSIZE];
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
	if (!m_bufInput)
	{
		delete[] m_bufInput;
		m_bufInput = 0;
	}
	if (!m_bufOutput)
	{
		delete[] m_bufOutput;
		m_bufOutput = 0;
	}
}

bool CTCPClient::isWantedCMD(unsigned short& cmd)
{
	if (cmd == PP_DOUNIU_CHONGZHI_ACK || cmd == PP_DOUNIU_CREAT_ACCOUNT_ACK ||
		cmd == PP_DOUNIU_CREATE_ROOM_ACK || cmd == PP_DOUNIU_GET_ROLEINFO_ACK ||
		cmd == PP_DOUNIU_LOGIN_ACCOUNT_ACK || cmd == PP_DOUNIU_JOIN_ROOM_ACK ||
		cmd == PP_DOUNIU_SUANNIU_ACK || cmd == PP_DOUNIU_QUIT_ROOM_ACK ||
		cmd == PP_DOUNIU_READY_ACK || cmd == PP_DOUNIU_FAPAI_ACK ||
		cmd == PP_DOUNIU_SUANNIU_ACK || cmd == PP_DOUNIU_YAZHU_ACK ||
		cmd == PP_DOUNIU_QUIT_ROOM_ACK || cmd == PP_DOUNIU_VOICE_CHAT_ACK ||
		cmd == PP_DOUNIU_MEMBER_INFO_ACK || cmd == PP_DOUNIU_GAME_START_ACK ||
		cmd == PP_DOUNIU_GAME_OVER_ACK || cmd == PP_DOUNIU_TANPAI_ACK || cmd == PP_DOUNIU_QIANGZHUANG_ACK)
	{
		return true;
	}
	return false;
}

bool CTCPClient::isRecvCompelete(unsigned int& nPackageLen)
{
	static bool b = false;
	static unsigned int Len = 0;
	if (!b)
	{
		if (m_nInbufLen >= 6)
		{
			unsigned short cmd = 0;
			memcpy(&cmd, m_bufInput+m_nInbufStart, 2);
			cmd = ntohs(cmd);
			if (isWantedCMD(cmd))
			{
				if (cmd == PP_DOUNIU_VOICE_CHAT_ACK)
				{
					unsigned int packageLen = 0;
					memcpy(&packageLen, m_bufInput + m_nInbufStart + 2, 4);
					packageLen = ntohl(packageLen);
					if (packageLen <= m_nInbufLen)
					{
						b = false;
						Len = 0;
						nPackageLen = packageLen;
						return true;
					}
					Len = packageLen;
				}
				else
				{
					unsigned int packageLen = 0;
					memcpy(&packageLen, m_bufInput + m_nInbufStart + 2, 2);
					packageLen = ntohs(packageLen);
					if (packageLen <= m_nInbufLen)
					{
						b = false;
						Len = 0;
						nPackageLen = packageLen;
						return true;
					}
					Len = packageLen;
				}
				b = true;
			}
		}
		else if (m_nInbufLen >= 4)
		{
			unsigned short cmd = 0;
			memcpy(&cmd, m_bufInput+m_nInbufStart, 2);
			cmd = ntohs(cmd);
			if (isWantedCMD(cmd))
			{
				unsigned int packageLen = 0;
				memcpy(&packageLen, m_bufInput + 2, 2);
				packageLen = ntohs(packageLen);
				if (packageLen <= m_nInbufLen)
				{
					b = false;
					Len = 0;
					nPackageLen = packageLen;
					return true;
				}
				Len = packageLen;
				b = true;
			}
		}
	}
	else
	{
		if (Len <= m_nInbufLen)
		{
			b = false;
			Len = 0;
			nPackageLen = m_nInbufLen;
			return true;
		}
	}
	return false;
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
		if (m_sockClient != INVALID_SOCKET)
		{
			if (ReceiveMsg())
			{
				unsigned int packageLen = 0;
				if (isRecvCompelete(packageLen))
				{
					//����Ϣ�������ack
					NetworkManger::getInstance()->pushACKQueue(m_bufInput+m_nInbufStart, packageLen);
					m_pRequest = nullptr;
					if (packageLen == m_nInbufLen)
					{
						m_nInbufLen = 0;
					}
					else
						m_nInbufStart += packageLen;
				}
			}
			else
			{
#ifdef WIN32
				int err = WSAGetLastError();
				//if (err == 10053 || err == 0)
				//{
				//	log("will reconnecting server!");
				//	ReconnectServer();
				//}
#else
				int err = errno;
				//if (err == 60 || err == 0)
				//{
				//	log("will reconnecting server!");
				//	ReconnectServer();
				//}
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

	if (m_nOutbufLen+nSize > OUTBUFSIZE)
	{
		return false;
	}
	m_nOutbufLen += nSize;
	memcpy(m_bufOutput, pBuf, m_nOutbufLen);
	Flush();
	m_nOutbufLen = 0;
	return true;
}

bool CTCPClient::ReceiveMsg()
{
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	int rcvLen = recvFromSock();
 	if (rcvLen <= 0)
	{
		return false;
	}
	m_nInbufLen += rcvLen;
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

	int inlen = recv(m_sockClient, (char*)m_bufInput+m_nInbufLen, INBUFSIZE, 0);
	if (inlen <= 0)
	{
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
		return false;
	}

	// ����һ������
	int	outsize;
	outsize = send(m_sockClient, (char*)m_bufOutput, m_nOutbufLen, 0);
	if (outsize <= 0) 
	{
		int err = hasError();
#ifdef WIN32
		if (err == 10053)
		{
			log("will reconnecting server!");
			
		}
#else
		if (err == 60)
		{
			log("will reconnecting server!");
		}
#endif
		ReconnectServer();
		return false;
	}

	return true;
}

void CTCPClient::ReconnectFunc()
{
	Destroy();
	m_flag = true;
	while (m_flag);
	thread t(&CTCPClient::NetworkThreadFunc, this);
	t.detach();
}


void CTCPClient::ReconnectServer()
{
	//�������߳�
	thread t(&CTCPClient::ReconnectFunc, this);
	t.detach();
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
	closeSocket();

	m_sockClient = INVALID_SOCKET;
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;

	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
}

