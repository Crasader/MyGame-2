#pragma once
#include <string>
#include <map>
#include "TCPClient.h"
#include "TCPRequest.h"
#include <deque>
USING_NS_CC;
using namespace std;

const int g_popRadio = 45;				//����Ƶ��

//����ͨ����
class NetworkManger
{
public:
	static NetworkManger* getInstance();
	virtual ~NetworkManger();
	static void destroyInstance();

	void shutDownNetwork();
	void startNetwork();

	//���͸�������ȡ���ص�����Ϊ���߳��޷�����UI
	bool SendRequest(const S_ZZ_WechatLoginReq& requestData);
	bool SendRequest(const S_ZZ_RoleLoginReq& requestData);
	bool SendRequest(const S_ZZ_ReconnectReq& requestData);
	//bool SendRequest(const S_ZZ_CreatePlayerReq& requestData);
	bool SendRequest(const S_ZZ_GetPlayerInfoReq& requestData);
	bool SendRequest(const S_ZZ_CreateRoomReq& requestData);
	bool SendRequest(const S_ZZ_JoinRoomReq& requestData);
	bool SendRequest(const S_ZZ_SearchZhanjiReq& requestData);
	bool SendRequest(const S_ZZ_QuitRoomReq& requestData);
	bool SendRequest(const S_ZZ_ReadyPlayReq& requestData);
	//bool SendRequest(const S_ZZ_FaPaiReq& requestData);
	bool SendRequest(const S_ZZ_SuanNiuTanPaiReq& requestData);
	bool SendRequest(const S_ZZ_QuickChatReq& requestData);
	//bool SendRequest(const S_ZZ_SuanNiuReq& requestData);
	bool SendRequest(const S_ZZ_WechatOrderReq& requestData);
	bool SendRequest(const S_ZZ_QiangZhuangReq& requestData);
	bool SendRequest(const S_ZZ_YaZhuReq& requestData);
	bool SendRequest(const S_ZZ_VoiceChatReq& requestData);
	bool SendRequest(const S_ZZ_InviteReq& requestData);
	bool SendRequest(const S_ZZ_TextChatReq& requestData);
	bool SendRequest(const S_ZZ_KeepaliveReq& requestData);
	bool SendRequest(const S_ZZ_CheckUpdateReq& requestData);

	//��Ϣ�������
	bool ackQueueIsEmpty();						//��Ϣ�����Ƿ�Ϊ��
	void pushACKQueue(void* data, int size);	//���
	void popACKQueue();							//����
	unsigned short getQueueFrontACKCmd();				//��ö�ͷ����Э���
	void* getQueueFrontACKBinaryData();			//��ö�ͷ���Ķ���������
private:
	NetworkManger();
	bool _SendRequest(void* requestData, int size);
private:
	//ACK��Ӧ����Ϣ����
	class CACKResponseQueue
	{
	public:
		void pushACKResponse(void* responseData, int size);		//��Ӧ��Ϣ���
		bool isEmpty();											//�п�
		void popACKResponse();									//����
		S_ACKResponse* getFrontFromQueue();						//��ö�ͷ����
	protected:
	private:
		deque<S_ACKResponse*> m_queue;							//��Ϣ����
	};

	CACKResponseQueue m_ackQueue;			//ack��Ϣ���У��������̻߳��ack��Ӧ��Ϣ�������Ⱦ
	static NetworkManger* m_pInstance;
	CTCPClient* m_tcpClient;

};


