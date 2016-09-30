#pragma once
#include <string>
#include <map>
#include "network/HttpClient.h"
#include "TCPClient.h"
#include "TCPRequest.h"
USING_NS_CC;
using namespace network;
using namespace std;

//����ͨ����
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	//��������--������ɫ
	//callback = �ص�
	void SendRequest_CreateUser(const S_CreatePlayerReq& requestData, const TCPResponseCallback& responseCallback);
	
private:
	static NetworkManger* m_pInstance;
	NetworkManger();
	void SendRequest(void* requestData, int size, const TCPResponseCallback& responseCallback);

};


