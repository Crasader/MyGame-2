#pragma once
#include <string>
#include "cocos2d.h"
#include "toolFunctions.h"
using namespace std;
USING_NS_CC;

class User
{
public:
	User();
	User(int x, int y, const string name, const string level);
	bool setProfile(int x, int y, const string name, const string level);
	Sprite* getHeadSprite();
	LabelTTF* getPlayerName();
	LabelTTF* getLevel();
	~User();
protected:
	string m_strPlayerName;			//�û��ǳ�
	string m_strLevel;				//�û��ȼ�
	Sprite* m_spOutline;			//�߿���
	Sprite* m_spHead;				//ͷ����
	LabelTTF* m_lblPlayerName;		//�û��ǳ�label
	LabelTTF* m_lblLevel;			//�ȼ�label
	int m_nExp;						//����ֵ
};