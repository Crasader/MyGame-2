//
//  NiuPlayer.hpp
//  BullPoker
//
//  Created by �¶�÷ on 16/7/25.
//
//

#ifndef NiuPlayer_h
#define NiuPlayer_h

#include <stdio.h>
#include "cocos2d.h"
#include "GamePlayScene.h"

USING_NS_CC;

/** ������� */
enum PlayerType
{
	/** ����Լ� */
	PlayerType_Me,
	/** �ұ���� */
	PlayerType_Right,
	/** �ϲ��ұ���� */
	PlayerType_TopRight,
	/** �ϲ������� */
	PlayerType_TopLeft,
	/** ������ */
	PlayerType_Left
};

class NiuPlayer : public Object
{
public:
	NiuPlayer();
	~NiuPlayer();
	void updatePkWeiZhi();

private:
	CC_SYNTHESIZE(__Array*, m_arrPk, ArrPk);
	CC_SYNTHESIZE(Point, m_point, Point);
	CC_SYNTHESIZE(PlayerType, m_iPlayerClass, PlayerClass);
};
#endif /* NiuPlayer_h */
