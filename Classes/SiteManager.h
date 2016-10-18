#pragma once
#include "Global.h"
#include "cocos2d.h"
#include "UserProfileUI.h"
#include "NiuPlayer.h"
#include <vector>
using namespace std;
USING_NS_CC;


//������Ϸ�е������λ
class SiteManager
{
public:
	SiteManager(Node* parent);
	virtual ~SiteManager();

	//����Ҹ�λ������
	bool joinSite(unsigned long long playerID, string playerName, int diamond, int money);
	//�뿪��λ
	bool leaveSite(unsigned long long playerID);
	//���ñ���
	bool setMultiple(unsigned long long playerID);
	//����ׯ��
	bool setZhuangJia(unsigned long long playerID);

private:
	struct PlayerAndProfilePos
	{
		Point playerPos;
		Point profilePos;
		int profileType;		//0Ϊˮƽ��1Ϊ��ֱ
	};

private:
	vector<NiuPlayer*> m_inRoomPlayer;
	vector<PlayerAndProfilePos> m_playerProfileInfo;			//λ����Ϣ
	vector<IUserProfileUIInGame*> m_pUserProfileVecs;			//ͷ��UI����0���ǵ�ǰ���ͷ��
	vector<int> m_playerInRoom;									//������Ŀ�λ��0��ʾû������1��ʾ������
	vector<unsigned long long> m_inRoomPlayerID;				//0Ϊ������
	
	Node* m_pParent;
};

