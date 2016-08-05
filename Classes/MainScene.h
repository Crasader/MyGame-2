#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "UserProfileUI.h"
USING_NS_CC;
using namespace ui;

//��¼������˵�����
class MainScene :public Layer
{
public:
	MainScene();
	static Scene* scene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	virtual void onEnter();
	virtual void onExit();
	virtual ~MainScene();
	static void onBtnTouch(Ref *pSender, Widget::TouchEventType type);		
	void update(float delta);
	void buttonCallback(CCNode* pSender);
private:
	bool initBackground();
	bool initButtons();
	bool initNotice();
	bool initPlayerProfile();					
	void flushNoticeLabel(float delta);			//�ػ湫��

private:
	LabelTTF* m_pNoticeLabel;
	UserProfileUI* m_pUser;
	Sprite* m_spRoundRectInNotice;		
};



