#pragma once
#include "cocos2d.h"
#include <vector>
#include "NiuPoker.h"
#include "SiteManager.h"
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
	
private:
	bool createPokers();
	NiuPoker* selectPoker(int huaSe, int num);
	/** �����ƶ����� */
	void MovePk(NiuPlayer* play, NiuPoker* pk);				
private:
	__Array* m_arrPokers;				//52����

	Node* m_pParent;
	SiteManager* m_pSitManager;
};

