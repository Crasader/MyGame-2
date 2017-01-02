#pragma once

#include <cocos2d.h>
#include <thread>
#include "NetworkPackage.h"
#include "TCPRequest.h"
USING_NS_CC;
#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif

#ifndef CHECKF
#define CHECKF(x) \
	do \
				{ \
	if (!(x)) { \
		log("%s%s%s%s","CHECKF", #x, __FILE__, __LINE__); \
	return 0; \
					} \
				} while (0)
#endif

const string g_strServerIP = "120.24.180.25"/*"127.0.0.1"*/;
const int g_nServerPort = 333/*9999*/;

const string g_mdzzStrServerName = "huanan01.csbhnt.cn";
const int g_mdzzServerPort = 9998;


#define _MAX_MSGSIZE (1000 * 1024)		// �ݶ�һ����Ϣ���Ϊ1000k
#define BLOCKSECONDS	30			// ��ȡ��������ʱ��
#define INBUFSIZE	(1000*1024)		//	����ߴ�������汨�����  �������ݵĻ���
#define OUTBUFSIZE	(1000*1024)		// ����ߴ�������汨������� �������ݵĻ���

class CTCPClient {
public:
	CTCPClient(void);
	~CTCPClient();

	bool sendTCPRequset(CTCPRequest* request);
	bool	Create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	void	Destroy(void);
	bool isConnected();
private:
	void   ReconnectServer();
	void	NetworkThreadFunc();					//��������IO���̺߳���
	void	ReconnectFunc();						//�����̺߳���
	bool	Flush(void);
	bool	Check(void);
	bool	isWantedCMD(short& cmd);
	bool	isRecvCompelete(unsigned int& nPackageLen);
	SOCKET	GetSocket(void) const { return m_sockClient; }
	bool	ReceiveMsg();
	bool	SendMsg(void* pBuf, int nSize);
	int	recvFromSock(void);		// �������ж�ȡ�����ܶ������
	bool    hasError();			// �Ƿ�������ע�⣬�첽ģʽδ��ɷǴ���
	void    closeSocket();
	SOCKET	m_sockClient;

	// �������ݻ���
	unsigned char	*m_bufOutput;	// ���Ż�Ϊָ������
	int		m_nOutbufLen;

	unsigned char	*m_bufInput;
	int		m_nInbufLen;
	unsigned int		m_nInbufStart;				//��ͷ

	CTCPRequest* m_pRequest;
	mutex m_requestMutex;
	bool m_flag;
	float m_fTimeEscaped;							//��ʱ
};
