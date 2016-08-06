#pragma once
#include "cocos2d.h"
#include "toolFunctions.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"   

using namespace CocosDenshion;

using namespace cocos2d;
using namespace ui;

class ChatLayer :public LayerColor
{
public:
	ChatLayer();
	virtual ~ChatLayer();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(ChatLayer);

	//��ʼ������
	bool initChatBG();
	//���������
	bool createListView(const vector<pair<string, string>> quickMessage);

	void selectedItemEvent(cocos2d::Ref *pSender, ListViewEventType type);

	//��ʼ������
	bool initTitle();
	//��ʼ����ť
	bool initButton();
	//���������
	bool initEditBox();

	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);

	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(EditBox *editBox);


protected:
	Sprite* m_pFrameSprtie;							//��Ϣ����

private:
	ListView* lv;

};

