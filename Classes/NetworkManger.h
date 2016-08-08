#pragma once
#include <string>
#include <map>
#include "network/HttpClient.h"
USING_NS_CC;
using namespace network;
using namespace std;

//����ͨ����
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	void SetBaseURL(const string& url);
	//��������--������ɫ
	//callback = �ص�
	void SendRequest_CreateUser(ccHttpRequestCallback callback);
	//��������--��ȡ��ɫ��Ϣ
	//userID=�û�id
	//callback=�ص�
	void SendRequest_GetUserInfo(unsigned long long userID, ccHttpRequestCallback callback);
	//��������--��������
	//callback=�ص�
	void SendRequest_CreateRoom(ccHttpRequestCallback callback);
	//��������--���뷿��
	//roomID=����ID
	//callback=�ص�
	void SendRequest_JoinRoom(int roomID, ccHttpRequestCallback callback);
	//��������--ս����ѯ
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_SearchGains(unsigned long long userID, ccHttpRequestCallback callback);
	//��������--�˳�����
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_QuitRoom(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//��������--׼��
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_Ready(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//��������--����
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_GetPoker(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//��������--̯��
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_ShowPoker(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//��������--��ʯ��ֵ
	//num=�������ʯ����
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_AddDiamond(unsigned long long userID, int num,  ccHttpRequestCallback callback);
	//��������--����
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_QiangZhuang(int roomID, unsigned long long userID, ccHttpRequestCallback callback);
	//��������--��ע
	//roomID=����ID
	//userID=�û�ID
	//num=��ע����
	//callback=�ص�
	void SendRequest_Bet(int roomID, unsigned long long userID, int num,  ccHttpRequestCallback callback);
private:
	static NetworkManger* m_pInstance;
	NetworkManger(const string& url = string("https://www.baidu.com"));
	void SendRequest(ccHttpRequestCallback, const char* requestData = NULL);
private:
	string m_strBaseUrl;

};


