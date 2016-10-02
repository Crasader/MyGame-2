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

const string g_strServerIP = /*"120.24.180.25"*/"127.0.0.1";
const int g_nServerPort = /*333*/9999;
#define _MAX_MSGSIZE 16 * 1024		// �ݶ�һ����Ϣ���Ϊ16k
#define BLOCKSECONDS	30			// ��ȡ��������ʱ��
#define INBUFSIZE	(64*1024)		//	����ߴ�������汨�����  �������ݵĻ���
#define OUTBUFSIZE	(8*1024)		// ����ߴ�������汨������� �������ݵĻ��棬��������8Kʱ��FLUSHֻ��ҪSENDһ��

class CTCPClient {
public:
	static CTCPClient *getInstance();
	static void destroyInstance();

	bool sendTCPRequset(CTCPRequest* request);
	

private:
	CTCPClient(void);
	bool	Create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	void	NetworkThreadFunc();					//��������IO���̺߳���
	bool	Flush(void);
	bool	Check(void);
	void	Destroy(void);
	SOCKET	GetSocket(void) const { return m_sockClient; }
	bool	ReceiveMsg(void* pBuf, int& nSize);
	bool	SendMsg(void* pBuf, int nSize);
	int	recvFromSock(void);		// �������ж�ȡ�����ܶ������
	bool    hasError();			// �Ƿ�������ע�⣬�첽ģʽδ��ɷǴ���
	void    closeSocket();

	SOCKET	m_sockClient;

	// �������ݻ���
	char	m_bufOutput[OUTBUFSIZE];	//? ���Ż�Ϊָ������
	int		m_nOutbufLen;

	// ���λ�����
	char	m_bufInput[INBUFSIZE];
	int		m_nInbufLen;
	int		m_nInbufStart;				// INBUFʹ��ѭ��ʽ���У��ñ���Ϊ������㣬0 - (SIZE-1)

	static CTCPClient* m_pTCPClient;
	CTCPRequest* m_pRequest;
	mutex m_requestMutex;
};
