#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "UserProfileUI.h"
#include "NetworkManger.h"
USING_NS_CC;
using namespace ui;

//��¼������˵�����
class MainScene :public Layer
{
public:
	MainScene(int playerID);
	static Scene* scene(int playerID);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual ~MainScene();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
	void buttonCallback(CCNode* pSender);
	int getDiamond() const;
	int getMoney() const;
	int getPlayerID() const;
private:
	bool initBackground();
	bool initButtons();
	bool initNotice();
	bool initPlayerProfile();					
	void flushNoticeLabel(float delta);			//�ػ湫��
	static MainScene* createMainScene(int  playerID);

private:
	LabelTTF* m_pNoticeLabel;
	UserProfileUI* m_pUser;
	Sprite* m_spRoundRectInNotice;		

	INT m_playerID;
	string m_strPlayerName;
	int m_currentDiamond;
	int m_currentMoney;
};



