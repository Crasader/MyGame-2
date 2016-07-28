#pragma once
#include <string>
#include "cocos2d.h"
#include "toolFunctions.h"
#include "ui/CocosGUI.h" 
using namespace std;
USING_NS_CC;
using namespace ui;

//����
class UserProfileUI
{
public:
	UserProfileUI(Node* pParent);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond) = 0;
	~UserProfileUI();
protected:
	string m_strPlayerName;			//�û��ǳ�
	int m_nDiamond;					//��ʯ����
	LabelTTF* m_lblDiamond;			//��ʯ����label
	Sprite* m_spHead;				//ͷ����
	Sprite* m_spFrame;				//����
	LabelTTF* m_lblPlayerName;		//�û��ǳ�label
	Node* m_pParent;				//���ڵ�
	Sprite* m_spDianmond;			//��ʯ����
};

//�����û�ͷ��UI��������Ϸ��
class VerticalUserProfileUI : public UserProfileUI
{
public:
	VerticalUserProfileUI(Node* pParent);
	VerticalUserProfileUI(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond);
};

//�����û�ͷ��UI��������Ϸ��
class HerizelUserProfileUI: public UserProfileUI
{
public:
	HerizelUserProfileUI(Node* pParent);
	HerizelUserProfileUI(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond);
protected:
private:
};

class UserProfileUIInMainScene : public HerizelUserProfileUI
{
public:
	UserProfileUIInMainScene(Node* pParent);
	UserProfileUIInMainScene(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond);
	void onAddDiamondTouch(Ref *pSender, Widget::TouchEventType type);
private:
	Sprite* m_spRoundRect;
	Button* m_btnAddDiamond;
};

