//
//  NiuPoker.hpp
//  BullPoker
//
//  Created by �¶�÷ on 16/7/25.
//
//

#ifndef NiuPoker_h
#define NiuPoker_h

#include "Global.h"
#include "cocos2d.h"
class GamePlayScene;
USING_NS_CC;
class  NiuPoker : public Sprite
{
public:
	NiuPoker();
	~NiuPoker();
	static NiuPoker* create();
	void showFront();//��ʾǰ��
	void showLast();//��ʾ����
    void showFront_small();
    void showLast_small();
	NiuPoker* copy();
	/** ��ӡ�˿��� */
	void printPoker();
	void setTouchPriority();
	bool upOrDownPoker(int& up);
	void setTouchable(bool isTouchable = true);
private:
	CC_SYNTHESIZE(bool, m_isSelect, Select);
	CC_SYNTHESIZE(GamePlayScene*, m_gameMain, GameMain);
	CC_SYNTHESIZE(int, m_huaSe, HuaSe);
	CC_SYNTHESIZE(int, m_num, Num);
	bool m_isTouchable;
};


#endif /* NiuPoker_h */
