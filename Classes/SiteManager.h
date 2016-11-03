#pragma once
#include "Global.h"
#include "cocos2d.h"
#include "UserProfileUI.h"
#include "NiuPlayer.h"
#include <vector>
#include <mutex>
#include <array>
using namespace std;
USING_NS_CC;

class PorkerManager;

//������Ϸ�е������λ
class SiteManager
{
public:
	SiteManager(Node* parent,unsigned long long currentPlayerID);
	virtual ~SiteManager();

	//����Ҹ�λ������
	bool joinSite(unsigned long long playerID, string playerName, int diamond, int money);
	//�뿪��λ
	bool leaveSite(unsigned long long playerID);
	//���ñ���
	bool setMultiple(unsigned long long playerID, int multiple);
	//��ʾ����
	bool showMultiple(unsigned long long playerID,bool isShow = true);
	//����ׯ��
	bool showZhuangJia(unsigned long long playerID);
	//��ʾ׼��
	bool showReady(unsigned long long playerID, bool isShow = true);


private:
	//��Һ�ͷ��λ����Ϣ
	struct PlayerAndProfilePos
	{
		Point playerPos;
		Point profilePos;
		int profileType;		//0Ϊˮƽ��1Ϊ��ֱ
	};

private:
	array<NiuPlayer*,5> m_inRoomPlayer;
	array<PlayerAndProfilePos,5> m_playerProfileInfo;			//λ����Ϣ
	array<IUserProfileUIInGame*,5> m_pUserProfileVecs;			//ͷ��UI����0���ǵ�ǰ���ͷ��
	array<int,5> m_playerInRoom;									//������Ŀ�λ��0��ʾû������1��ʾ������
	array<unsigned long long,5> m_inRoomPlayerID;				//0Ϊ������

	unsigned long long m_currentPlayerID;						//�Լ���ID

	Node* m_pParent;

	friend class PorkerManager;
	mutex m_lock;
};

