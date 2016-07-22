#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "User.h"
USING_NS_CC;
using namespace ui;

//��¼������˵�����
class MainScene :public Layer
{
public:
	MainScene();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	virtual void onEnter();
	virtual void onExit();
	virtual ~MainScene();
	static void onBtnTouch(Ref *pSender, Widget::TouchEventType type);		
	void update(float delta);

private:
	bool initBackground();
	bool initButtons();
	bool initNotice();
	bool initPlayerProfile();					
	void flushNoticeLabel(float delta);			//�ػ湫��

private:
	LabelTTF* m_pNoticeLabel;
	User* m_pUser;
};



