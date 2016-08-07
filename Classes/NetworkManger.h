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
	NetworkManger(const string& url = string("https://www.baidu.com"));
	virtual ~NetworkManger();

	//��������--������ɫ
	//callback = �ص�
	void SendRequest_CreateUser(const ccHttpRequestCallback& callback);
	//��������--��ȡ��ɫ��Ϣ
	//userID=�û�id
	//callback=�ص�
	void SendRequest_GetUserInfo(unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--��������
	//callback=�ص�
	void SendRequest_CreateRoom(const ccHttpRequestCallback& callback);
	//��������--���뷿��
	//roomID=����ID
	//callback=�ص�
	void SendRequest_JoinRoom(int roomID, const ccHttpRequestCallback& callback);
	//��������--ս����ѯ
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_SearchGains(unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--�˳�����
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_QuitRoom(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--׼��
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_Ready(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--����
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_GetPoker(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--̯��
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_ShowPoker(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--��ʯ��ֵ
	//num=�������ʯ����
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_AddDiamond(unsigned long long userID, int num, const ccHttpRequestCallback& callback);
	//��������--����
	//roomID=����ID
	//userID=�û�ID
	//callback=�ص�
	void SendRequest_QiangZhuang(int roomID, unsigned long long userID, const ccHttpRequestCallback& callback);
	//��������--��ע
	//roomID=����ID
	//userID=�û�ID
	//num=��ע����
	//callback=�ص�
	void SendRequest_Bet(int roomID, unsigned long long userID, int num, const ccHttpRequestCallback& callback);

private:
	string m_strBaseUrl;
};

