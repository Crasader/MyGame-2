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
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond,const int coin) = 0;
	~UserProfileUI();
protected:
	string m_strPlayerName;			//�û��ǳ�
	int m_nCoin;					//�������
	int m_nDiamond;					//��ʯ����
	LabelTTF* m_lblDiamond;			//��ʯ����label
	LabelTTF* m_lblCoin;			//�������label
	Sprite* m_spHead;				//ͷ����
	Sprite* m_spFrame;				//����
	LabelTTF* m_lblPlayerName;		//�û��ǳ�label
	Node* m_pParent;				//���ڵ�
	Sprite* m_spCoin;				//��Ҿ���
	Sprite* m_spDianmond;			//��ʯ����
};

//�����û�ͷ��UI��������Ϸ��
class VerticalUserProfileUI : public UserProfileUI
{
public:
	VerticalUserProfileUI(Node* pParent);
	VerticalUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
};

//�����û�ͷ��UI��������Ϸ��
class HerizelUserProfileUI: public UserProfileUI
{
public:
	HerizelUserProfileUI(Node* pParent);
	HerizelUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
protected:
private:
};

class UserProfileUIInMainScene : public HerizelUserProfileUI
{
public:
	UserProfileUIInMainScene(Node* pParent);
	UserProfileUIInMainScene(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	void onAddBtnTouch(Ref *pSender, Widget::TouchEventType type);
private:
	Sprite* m_spRoundRect;
	Sprite* m_spRoundRect2;
	Button* m_btnAddDiamond;
	Button* m_btnAddCoin;
	Sprite* m_spDianmond;			//��ʯ����

};

