#pragma once
#include <string>
#include <map>
#include "TCPClient.h"
#include "TCPRequest.h"
#include <deque>
USING_NS_CC;
using namespace std;

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
	bool SendRequest_Login(const S_LoginReq& requestData);
	bool SendRequest_CreateUser(const S_CreatePlayerReq& requestData);
	bool SendRequest_GetPlayerInfo(const S_GetPlayerInfoReq& requestData);
	bool SendRequest_CreateRoom(const S_CreateRoomReq& requestData);
	bool SendRequest_JoinRoom(const S_JoinRoomReq& requestData);
	bool SendRequest_SearchZhanji(const S_SearchZhanjiReq& requestData);
	bool SendRequest_QuitRoom(const S_QuitRoomReq& requestData);
	bool SendRequest_ReadyPlay(const S_ReadyPlayReq& requestData);
	bool SendRequest_FaPai(const S_FaPaiReq& requestData);
	bool SendRequest_TanPai(const S_TanPaiReq& requestData);
	bool SendRequest_BuyDiamond(const S_BuyDiamondReq& requestData);
	bool SendRequest_QiangZhuang(const S_QiangZhuangReq& requestData);
	bool SendRequest_YaZhu(const S_YaZhuReq& requestData);

	//��Ϣ�������
	bool ackQueueIsEmpty();						//��Ϣ�����Ƿ�Ϊ��
	void pushACKQueue(void* data, int size);	//���
	void popACKQueue();							//����
	short getQueueFrontACKCmd();				//��ö�ͷ����Э���
	void* getQueueFrontACKBinaryData();			//��ö�ͷ���Ķ���������
private:
	NetworkManger();
	bool SendRequest(void* requestData, int size/*, const TCPResponseCallback& responseCallback*/);
private:
	//ACK��Ӧ����Ϣ����
	class CACKResponseQueue
	{
	public:
		void pushACKResponse(void* responseData, int size);		//��Ӧ��Ϣ���
		bool isEmpty();											//�п�
		void popACKResponse();									//����
		S_ACKResponse getFrontFromQueue();						//��ö�ͷ����
	protected:
	private:
		deque<S_ACKResponse> m_queue;							//��Ϣ����
	};

	CACKResponseQueue m_ackQueue;			//ack��Ϣ���У��������̻߳��ack��Ӧ��Ϣ�������Ⱦ
	static NetworkManger* m_pInstance;
	CTCPClient* m_tcpClient;
	

};


