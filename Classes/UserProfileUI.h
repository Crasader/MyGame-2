#pragma once
#include <string>
#include "cocos2d.h"
#include "toolFunctions.h"
#include "ui/CocosGUI.h" 
using namespace std;
USING_NS_CC;
using namespace ui;

//����
class UserProfileUI:public Ref
{
public:
	UserProfileUI(Node* pParent);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond,const int coin) = 0;
	virtual ~UserProfileUI();
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

//������Ϸ�е�ͷ��ӿ�
class IUserProfileUIInGame : public UserProfileUI
{
public:
	IUserProfileUIInGame(Node* pParent) :UserProfileUI(pParent),m_spBankerFrame(0), m_lblMultiple(0){}
	bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin){ return true; }
	virtual bool setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin, const int multiple) = 0;
	virtual void showMultiple(bool isShow = true) = 0;												//��ʾ����
	virtual void showBanker(bool isShow = true) = 0;													//��ʾׯ�ҿ�
	virtual ~IUserProfileUIInGame(){}
protected:
	Sprite* m_spBankerFrame;
	LabelTTF* m_lblMultiple;
};

//�����û�ͷ��UI��������Ϸ��
class VerticalUserProfileUI : public IUserProfileUIInGame
{
public:
	static IUserProfileUIInGame* create(Node* pParent);
	VerticalUserProfileUI(Node* pParent);
	//VerticalUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin){ return true; }
	virtual bool setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin, const int multiple);
	virtual void showMultiple(bool isShow = true);													//��ʾ����
	virtual void showBanker(bool isShow = true);													//��ʾׯ�ҿ�
};

//�����û�ͷ��UI��������Ϸ��
class HerizelUserProfileUI : public IUserProfileUIInGame
{
public:
	static IUserProfileUIInGame* create(Node* pParent);
	HerizelUserProfileUI(Node* pParent);
	//HerizelUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin){ return true; }
	virtual bool setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin, const int multiple);
	virtual void showMultiple(bool isShow = true);												//��ʾ����
	virtual void showBanker(bool isShow = true);													//��ʾׯ�ҿ�
};

class UserProfileUIInMainScene : public UserProfileUI
{
public:
	static UserProfileUI* create(Node* pParent);
	UserProfileUIInMainScene(Node* pParent);
	UserProfileUIInMainScene(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	void onAddBtnTouch(Ref *pSender, Widget::TouchEventType type);
	virtual ~UserProfileUIInMainScene();
private:
	Sprite* m_spRoundRect;
	Sprite* m_spRoundRect2;
	Button* m_btnAddDiamond;
	Button* m_btnAddCoin;
	Sprite* m_spDianmond;			//��ʯ����

};

