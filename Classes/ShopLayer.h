#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include <string>

USING_NS_CC;
using namespace ui;

class ShopLayer : public cocos2d::Layer
{
public:
	ShopLayer(unsigned long long playerID, int diamond, int money, int number = 0);
	~ShopLayer();
	static Scene* createScene(unsigned long long playerID,int diamond, int money, int number = 0);
	//static cocos2d::Scene* createScene(String str);
	virtual bool init();
	//CREATE_FUNC(ShopLayer);
	static ShopLayer* create(unsigned long long playerID, int diamond, int money, int number = 0);
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	//virtual void onEnter(int number);

private:
	bool initBackground();
	bool initButtons();			//�̳�ͼ�ꡢ���ذ�ť��ʼ��
	bool initMenuBar();			//����ʼ��������
	bool initTopMenuBar();		//������ʼ��������
	bool initShow();			//��ʼ����ʾ��
	bool initDiamondLayer();	//��ʼ����ʯ��
	bool initCoinLayer();		//��ʼ����Ҳ�
	void tapBarMenuPressed(Ref *pSender);
	//void onEnter();
	//bool initNotice();

	LayerMultiplex* layers;		//����
	LayerMultiplex* topLayers;	//������
	Menu* tabBarItems;			//����˵�
	Menu* tabBarTopItems;		//������˵�
	Layer* layerDiamond;		//��ʯ��
	Layer* layerCoin;			//��Ҳ�
	MenuItemSprite* buyDiamond;		//������ʯ����
	MenuItemSprite* buyCoin;		//�����Ҿ���
	ccColor3B colBegan;				//��ʯ����Ҿ������ɫ

	LabelTTF* m_lblDiamond01;
	LabelTTF* m_lblDiamond02;
	LabelTTF* m_lblDiamond03;
	LabelTTF* m_lblDiamond04;
	LabelTTF* m_lblDiamond05;
	LabelTTF* m_lblDiamond06;

	LabelTTF* m_lblCoin01;
	LabelTTF* m_lblCoin02;
	LabelTTF* m_lblCoin03;
	LabelTTF* m_lblCoin04;
	LabelTTF* m_lblCoin05;
	LabelTTF* m_lblCoin06;

	Button* s_buyDiamond01Btn;
	Button* s_buyDiamond02Btn;
	Button* s_buyDiamond03Btn;
	Button* s_buyDiamond04Btn;
	Button* s_buyDiamond05Btn;
	Button* s_buyDiamond06Btn;

	Button* s_buyCoin01Btn;
	Button* s_buyCoin02Btn;
	Button* s_buyCoin03Btn;
	Button* s_buyCoin04Btn;
	Button* s_buyCoin05Btn;
	Button* s_buyCoin06Btn;

	int m_number;
	unsigned long long m_playerID;
	int m_diamond;
	int m_money;
};

