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
	SiteManager(Node* parent,int currentPlayerID);
	virtual ~SiteManager();

	//����Ҹ�λ������
	bool joinSite(int playerID, string playerName, int diamond, int money);
	//�뿪��λ
	bool leaveSite(int playerID);
	//���ñ���
	bool setMultiple(int playerID, int multiple);
	//��ʾ����
	bool showMultiple(int playerID, bool isShow = true);
	//����ׯ��
	bool showZhuangJia(int playerID);
	//��ʾţ
	bool showNiu(int playerID, int niuIndex);
	//��������ţ
	void hideAllNiu();
	//��ʾ׼��
	bool showReady(int playerID, bool isShow = true);
	//��ǰ�����������
	int currentPlayerCount() const;
	//��ʾ������Ϣ
	void showChatMessage(int playerID, string strMessage, float timeThreshold = 3.0f);

private:
	//��Һ�ͷ��λ����Ϣ
	struct PlayerAndProfilePos
	{
		Point playerPos;
		Point profilePos;
		Point niuPos;
		Point bubblePos;
		int profileType;		//0Ϊˮƽ��1Ϊ��ֱ
	};

private:
	array<NiuPlayer*,5> m_inRoomPlayer;
	array<PlayerAndProfilePos,5> m_playerProfileInfo;			//λ����Ϣ
	array<IUserProfileUIInGame*,5> m_pUserProfileVecs;			//ͷ��UI����0���ǵ�ǰ���ͷ��
	array<int,5> m_playerInRoom;								//������Ŀ�λ��0��ʾû������1��ʾ������
	array<int, 5> m_inRoomPlayerID;				//0Ϊ������
	array<Sprite*,5> m_playerNiu;
	map<int, string> m_niuIndex2JPGPath;

	int m_currentPlayerID;						//�Լ���ID

	Node* m_pParent;

	friend class PorkerManager;
	mutex m_lock;
};

