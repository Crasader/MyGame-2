#pragma once
#include "cocos2d.h"
#include <vector>
#include "NiuPoker.h"
#include "SiteManager.h"
#include <utility>
using namespace std;
USING_NS_CC;

//���-�˿�
struct S_PlayerPorker
{
	S_PlayerPorker() :playerID(0), vecPorkerIndex(5, -1){}
	unsigned long long playerID;			//���ID
	vector<int> vecPorkerIndex;				//��Ҷ�Ӧ��5����
};

class PorkerManager
{
public:
	PorkerManager(Node* parent,SiteManager* pSite);
	virtual ~PorkerManager();
	void SendPorker(const vector<S_PlayerPorker>& porkers);			//����
	void ShowAllPorkers();
	void EmptyAllPorkers();
	bool RunActions();												//���з��ƶ���������true��������ж�������
	vector<NiuPoker*> GetMePlayerPoker();							//������Ϸ��ME��ҵ�5����
	
private:
	bool createPokers();
	NiuPoker* selectPoker(int huaSe, int num);
	/** �����ƶ����� */
	void MovePk(NiuPlayer* play, NiuPoker* pk);				
private:

	class PokerAction:public Ref
	{
	public:
		void updatePokerPos(Node* pSender, void* pData);
	};
	__Array* m_arrPokers;				//52����
	Node* m_pParent;
	SiteManager* m_pSitManager;
	vector<pair<NiuPoker*, Sequence*> > m_poker2Actions;			//�˿˺Ͷ�����ӳ��
	int m_currentPokerActionIndex;
public:
    static vector<NiuPoker*> m_touchPokers;
};

vector<NiuPoker*> PorkerManager::m_touchPokers;

