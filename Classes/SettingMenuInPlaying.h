#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;


class SettingMenuInPlaying:public Ref
{
public:
	SettingMenuInPlaying(Node* parent);
	SettingMenuInPlaying(Node* parent,Vec2 pos);				//posΪui����
	void setPos(Vec2 pos);						//posΪui����
	virtual ~SettingMenuInPlaying();	
	void onOptionsTouch(Ref* pSender, Widget::TouchEventType evnet);
	void onBtnsTouch(Ref* pSender, Widget::TouchEventType evnet);
	void quitRoomCallback(Node* node);
private:
	bool init(Node* parent);
	enum BtnStatus
	{
		NORMAL,
		NORMAL2EXPAND,
		EXPAND,
		EXPAND2NORMAL
	} m_btnStatus;
	Sprite* m_spFrame;
	Sprite* m_spDropdownFrame;
	Button* m_btnSetting;				//����
	Button* m_btnQuitRoom;				//�뿪����
	Button* m_btnDestoryRoom;			//��ɢ����
	Button* m_btnOptions;				//ѡ��
	Node* m_pParent;
};

