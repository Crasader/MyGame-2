#include "ShopLayer.h"
#include "toolFunctions.h"
#include "MainScene.h"

USING_NS_CC;


ShopLayer::ShopLayer()
{
}


ShopLayer::~ShopLayer()
{
}

Scene* ShopLayer::createScene()
{
	auto scene = Scene::create();
	auto shopLayer = ShopLayer::create();
	scene->addChild(shopLayer);
	return scene;
}

//��ʼ������
bool ShopLayer::init()
{
	CCLayer::init();
	scheduleUpdate();
	if (!initBackground()) return false;
}

//��ʼ������
bool ShopLayer::initBackground()
{
	CCSprite* bk = CCSprite::create("shop\\shopbg.png");
	bk->setScale(2, 1);
	if (!bk)
	{
		return false;
	}
	this->addChild(bk, 0);
	bk->setAnchorPoint(ccp(0, 0));
	return true;
}