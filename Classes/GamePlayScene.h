#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DebugSimpleServer.h"
#include "TimeLayer.h"
#include "SettingMenuInPlaying.h"
class NiuPoker;
class NiuPlayer;
USING_NS_CC;
using namespace ui;

class GamePlayScene : public cocos2d::Layer
{
public:
	GamePlayScene();
	~GamePlayScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GamePlayScene);

	//virtual void onExit();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
private:
	bool initBackground();
	bool initButtons();
	bool initPlayerProfile();
	/** ��ʼ�������Ϣ */
	bool initPlayer();
	/** ����һ���� */
	NiuPoker* selectPoker(int huaSe, int num);
	/** ����һ���˿��� */
	bool createPokers();
	/** ϴ�� */
	bool xiPai();
	/** ���� */
	void SendPk();
	/** �����ƶ����� */
	void MovePk(NiuPlayer* play, NiuPoker* pk);

	void func(Node* pSender, void* pData);
private:
	TimeLayer* m_timeLayer;
	Button* m_startGameBtn;
	SettingMenuInPlaying *m_btnSetting;

	bool m_bReady;
	/** ���е��� */
	__Array* m_arrPokers;
	/** ��� */
	CC_SYNTHESIZE(NiuPlayer*, m_player, Player);
	/** ����� */
	NiuPlayer* m_playerRight;
	/** ����϶� */
	NiuPlayer* m_playerTopRight;
	/** �����һ */
	NiuPlayer* m_playerTopLeft;
	/** ����� */
	NiuPlayer* m_playerLeft;
	/** ������� */
	Point playerDiZhuLablePt;
	/** �����һ���� */
	Point playerOneLablePt;
	/** ����϶����� */
	Point playerTwoLablePt;
	/** ����������� */
	Point playerThreeLablePt;
	/** �Ƿ����� */
	bool m_isSend;
	/** �ѷ����ڼ����� */
	int m_iSendPk;
	/** ��ǰ״̬ 0������״̬  */
	int m_iState;
};


#endif // __GAMESCENE_SCENE_H__
