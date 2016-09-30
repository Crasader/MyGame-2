#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "GameSocket.h"
USING_NS_CC;


void LoginScene::onCreateUserResponse(void* responseData)
{
	log("in response!");
}

Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CCSprite* sprite1 = CCSprite::create("login/logo.png");
	sprite1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(sprite1,1);
	CCSprite* sprite2 = CCSprite::create("login/login_bg_dianzhui.png");
	sprite2->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(sprite2, 1);
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"login/login_normal.png",
		"login/login_pressed.png",
		CC_CALLBACK_1(LoginScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1,"login_button");

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label


	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("login/login_bg.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	S_CreatePlayerReq s;
	
	NetworkManger::getInstance()->SendRequest_CreateUser(s, CC_CALLBACK_1(LoginScene::onCreateUserResponse,this));
	
	return true;
}
void LoginScene::loading() {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vector<SpriteFrame*> spriteFrameVec;
	auto spriteFrameCache = SpriteFrameCache::getInstance();

	char path[256] = { 0 };
	for (int i = 1; i <= 3; ++i)
	{
		sprintf(path, "login/loading0%d.png", i);

		// 331x212��ͼƬ�Ĵ�С��ò������ֱ���趨�ǲ��õģ����ǻ������ṩ�������
		// Ӧ�ø����Rect�����ṩһ��Ĭ�ϲ�����Ĭ�ϼ�������ͼƬ
		SpriteFrame *pSpriteFrame = SpriteFrame::create(path, Rect(0, 0, 113, 27));

		// ����SpriteFrameCache��
		spriteFrameCache->addSpriteFrame(pSpriteFrame, path);
		spriteFrameVec.pushBack(pSpriteFrame);
	}

	// 0.1�Ǹ����������趨�������趨��Ĭ��ֵ������κ�ֵ������㲻�趨���������޷�����Animate����
	// Cocos2d-x�Ŀӻ����ٰ�����λ�������
	auto animation = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
	AnimationCache::getInstance()->addAnimation(animation, "login");
	//animation->setLoops(1);
	// ����1��ֱ�Ӽ��ض�Ӧ��ͼƬΪ����
	auto sprite = Sprite::create("login/loading01.png");

	// ����2����SpriteFrameCache�и������ֻ�ö�Ӧ�ľ���֡��������
	//sprite->setSpriteFrame(spriteFrameCache->getSpriteFrameByName("..\\Resources\\dogs\\1.png"));

	// ����3����Animation�л�ö�Ӧ��֡���ٽ�������
	//sprite->setDisplayFrameWithAnimationName("dogs", 0);
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + sprite->getContentSize().height / 2));
	this->addChild(sprite, 5, 5);
	//auto scene = Director::getInstance()->getRunningScene();
	//auto layer = this->getChildByTag(5);
	//auto dog1 = layer->getChildByTag(5);

	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("login"));
	auto repeat = RepeatForever::create(animate);
	sprite->runAction(repeat);
}

void LoginScene::menuCloseCallback(Ref* pSender)
{
	//auto scene = Director::getInstance()->getRunningScene();
	auto item = this->getChildByName("login_button");
	item->setVisible(false);
	loading();

	CCTransitionScene * reScene = NULL;
	CCScene * s = MainScene::scene();
	float t = 1.2f;

	//    CCTransitionJumpZoom
	//    ���ã� ����һ�������Ĺ��ɶ���
	//    ����1�����ɶ�����ʱ��
	//    ����2���л���Ŀ�곡���Ķ���
	    reScene = CCTransitionJumpZoom ::create(t , s);
	   CCDirector::sharedDirector()->replaceScene(reScene);

	//auto director = Director::getInstance();
	//auto scene = MainScene::scene();

	// run

	//director->runWithScene(scene);

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
