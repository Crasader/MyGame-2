#include "PopupLayer.h"

#include "ui/UIScale9Sprite.h"
#include "ui/UICheckBox.h"
#include "ui/CocosGUI.h"
using namespace ui;
PopupLayer::PopupLayer() :
	m__pMenu(NULL)
	, m_contentPadding(0)
	, m_contentPaddingTop(0)
	, m_callbackListener(NULL)
	, m_callback(NULL)
	, m__sfBackGround(NULL)
	, m__s9BackGround(NULL)
	, m__ltContentText(NULL)
	, m__ltTitle(NULL)
{

}

PopupLayer::~PopupLayer() {
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}
PopupLayer* layer;
bool PopupLayer::init() {
	if (!LayerColor::init()) {
		return false;
	}
	// ��ʼ����Ҫ�� Menu
	Menu* menu = Menu::create();
	menu->setPosition(ccp(0, 0));
	setMenuButton(menu);

	//add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setColor(ccc3(0, 0, 0));
	setOpacity(128);

	return true;
}

bool PopupLayer::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void PopupLayer::onTouchMoved(Touch *touch, Event *event) {

}

void PopupLayer::onTouchEnded(Touch* touch, Event* event) {

}

PopupLayer* PopupLayer::create(const char* backgroundImage, Size dialogSize) {

	layer = PopupLayer::create();

	//	layer->setSpriteBackGround(Sprite::create(backgroundImage));
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));

	layer->m_dialogContentSize = dialogSize;

	return layer;
}

void PopupLayer::setTitle(const char* title, int fontsize /* = 20 */) {
	LabelTTF* label = LabelTTF::create(title, "", fontsize);
	setLabelTitle(label);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop) {
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun) {
	m_callbackListener = target;
	m_callback = callfun;
}

bool PopupLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */) {

	auto size = Director::getInstance()->getWinSize();
	auto center = Point(size.width / 2, size.height / 2);

	// ����ͼƬ�˵���ť
	auto item = MenuItemImage::create(
		normalImage,
		selectedImage,
		CC_CALLBACK_1(PopupLayer::buttonCallBack, this));
	item->setTag(tag);
	item->setPosition(center);

	// �������˵��������λ��
	Size itemSize = item->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 2));
	item->addChild(ttf);


	getMenuButton()->addChild(item);

	return true;
}
bool PopupLayer::addListView(/*const char* normalImage, const char* selectedImage, const char* title, int tag  = 0 */) {

	Size size = Size(200, 50);
	auto popupSize = Director::getInstance()->getWinSize();
	auto center = Point(popupSize.width / 2, popupSize.height / 2);
	auto lv = ListView::create();
	// ����ͼƬ�˵���ť
	lv->setDirection(ui::ScrollView::Direction::VERTICAL);
	lv->setBounceEnabled(true);
	lv->setBackGroundImage("bg.jpg");//����ͼƬΪ�Ź����ʽ����ʵ�ͺ�9ͼһ����˼��ֻ�ǰ�׿��Ҫ�Լ����������������������  
	lv->setBackGroundImageScale9Enabled(true);
	lv->setContentSize(Size(200, 150));
	lv->setAnchorPoint(Point(0.5, 0.5));
	lv->setPosition(center);
	char* _image[15] = { "CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png",
		"CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png",
		"nCloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png" };
	this->addChild(lv,10);
	
	for (int i = 0; i < 15; ++i)
	{
		auto image = ImageView::create(_image[i]);

		image->setPosition(Point(image->getContentSize().width / 2, size.height / 2));

		auto bt = Button::create("joinRoom_normal.png", "joinRoom_press.png");

		bt->setScale9Enabled(true);

		bt->setContentSize(Size(size.width / 2, size.height / 2));

		bt->setPosition(Point(size.width - bt->getContentSize().width / 2, size.height / 2));

		bt->setTitleText(_image[i]);

		//itme�Ĳ���  
		auto layout = Layout::create();

		layout->setBackGroundImageScale9Enabled(true);

		layout->setBackGroundImage("bg.jpg");

		layout->setContentSize(size);

		layout->addChild(bt);
		layout->addChild(image);

		lv->addChild(layout);

	}

	lv->setItemsMargin(10);
	return true;
}
void PopupLayer::selectedItemEvent(cocos2d::Ref *pSender, ListViewEventType type)
{

	switch (type) {
	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
	{
		ListView* listView = static_cast<ListView*>(pSender);

		log("%ld", listView->getCurSelectedIndex());
	}
	break;


	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
	{
		ListView* listView = static_cast<ListView*>(pSender);

		log("%ld", listView->getCurSelectedIndex());
	}
	break;
	default:
		break;
	}
}
bool PopupLayer::addCheckBox(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */) {

	auto size = Director::getInstance()->getWinSize();
	auto center = Point(size.width / 2, size.height / 2);

	// ����ͼƬ�˵���ť
		CheckBox* checkBox = CheckBox::create();
	checkBox->setTouchEnabled(true);
	checkBox->loadTextures("CheckBox_UnSelect.png",
		"CheckBox_Select.png",
		"CheckBox_UnSelect.png",
		"CheckBox_UnSelect.png",
		"CheckBox_UnSelect.png");
	checkBox->setPosition(Point(center));

	checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(PopupLayer::selectedEvent));
	//getMenuButton()->addWidget(checkBox);
	if(checkBox!=nullptr)
	layer->addChild(checkBox,10);
	checkBox->setTag(0);
	//m_pUiLayer->addWidget(checkBox);
	/*
	checkBox->setPosition(center);

	// �������˵��������λ��
	Size itemSize = checkBox->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 2));
	checkBox->addChild(ttf);*/


	

	return true;
}
void PopupLayer::selectedEvent(Object* pSender, CheckBoxEventType type)
{
	switch (type) {
	case cocos2d::ui::CHECKBOX_STATE_EVENT_SELECTED:
		
		break;
	case ui::CHECKBOX_STATE_EVENT_UNSELECTED:
		
		break;
	default:
		break;
	}

}
void PopupLayer::buttonCallBack(Ref* pSender) {
	Node* node = dynamic_cast<Node*>(pSender);
	//CCLog("��====PopupLayer::buttonCallBack====��touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener) {
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParent();
}

void PopupLayer::onEnter() {
	LayerColor::onEnter();

	Size winSize = CCDirector::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	//	Size contentSize ;
	// �趨�ò�����������ʱ����
	//���û������ ContentSize ����ô��ȡ�ķ����ǣ����ڴ�С�봫��ͼƬһ����
	// 	if (getContentSize().equals(this->getParent()->getContentSize())) {
	// 		getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	// 		this->addChild(getSpriteBackGround(), 0, 0);
	// 		contentSize = getSpriteBackGround()->getTexture()->getContentSize();
	// 	} else {
	// 		Scale9Sprite *background = getSprite9BackGround();
	// 		background->setContentSize(getContentSize());
	// 		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	// 		this->addChild(background, 0, 0);
	// 		contentSize = getContentSize();
	// 	}
	//��ӱ���ͼƬ
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(m_dialogContentSize);
	background->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);

	// ����Ч��
	Action* popupLayer = Sequence::create(
		ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.2, 1.05),
		ScaleTo::create(0.2, 0.95),
		ScaleTo::create(0.1, 1.0),
		CallFunc::create(CC_CALLBACK_0(PopupLayer::backgroundFinish, this)),
		NULL
	);
	background->runAction(popupLayer);



}

void PopupLayer::backgroundFinish() {

	Size winSize = CCDirector::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	// ��Ӱ�ť����������λ��
	this->addChild(getMenuButton());
	float btnWidth = m_dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

	Vector<Node*> vector = getMenuButton()->getChildren();
	Ref* pObj = NULL;
	int i = 0;
	for (Node* pObj : vector) {
		Node* node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(winSize.width / 2 - m_dialogContentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - m_dialogContentSize.height / 3));
		i++;
	}

	// ��ʾ�Ի������
	if (getLabelTitle()) {
		getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, m_dialogContentSize.height / 2 - 35.0f)));
		this->addChild(getLabelTitle());
	}

	// ��ʾ�ı�����
	if (getLabelContentText()) {
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		ltf->setDimensions(CCSizeMake(m_dialogContentSize.width - m_contentPadding * 2, m_dialogContentSize.height - m_contentPaddingTop));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}
}



void PopupLayer::onExit() {

	//CCLog("popup on exit.");
	CCLayerColor::onExit();
}
