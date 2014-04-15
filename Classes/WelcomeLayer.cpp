#include "WelcomeLayer.h"
#include "CCEventListenerTouch.h"
//#include "ui/CocosGUI.h"  
//#include "ui/UICheckBox.h"
//ʹ�������ռ�
using namespace ui;
using namespace cocos2d;
//��ӭlayer
//�û�����"backmusic",1���ű�������,"backmusic",2������
//"yinliang",percent��������
WelcomeLayer::WelcomeLayer(void)
{

}
WelcomeLayer::~WelcomeLayer(void)
{

}
//��ʼ������
bool WelcomeLayer::init()
{

	bool ret = false;

	do {
		CC_BREAK_IF(!Layer::init());

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		//����Ϸ��ť
		auto newItem = MenuItemImage::create("1.png", "1.png", CC_CALLBACK_1(WelcomeLayer::menuNewCallback,this));
		//����λ��
		newItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2+5);
		// create menu, it's an autorelease object
		auto menu1 = Menu::create(newItem, NULL);
		menu1->setPosition(Point::ZERO);
		this->addChild(menu1, 1);

		//����
		auto aboutItem = MenuItemImage::create("4.png", "4.png", CC_CALLBACK_1(WelcomeLayer::menuAboutCallback,this));
		//����λ��
		aboutItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-25);
		// create menu, it's an autorelease object
		auto menu2 = Menu::create(aboutItem, NULL);
		menu2->setPosition(Point::ZERO);
		this->addChild(menu2, 1);

		//����
		auto setItem = MenuItemImage::create("2.png", "2.png", CC_CALLBACK_1(WelcomeLayer::menuSetCallback,this));
		//����λ��
		setItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-55);
		// create menu, it's an autorelease object
		auto menu3 = Menu::create(setItem, NULL);
		menu3->setPosition(Point::ZERO);
		this->addChild(menu3, 1);

		//�˳���ť
		auto closeItem = MenuItemImage::create("3.png","3.png",CC_CALLBACK_1(WelcomeLayer::menuCloseCallback,this));
		closeItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-85);
		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu, 1);

		// ���ñ���
		auto sprite = Sprite::create("beij.png");
		// position the sprite on the center of the screen
		sprite->setPosition(Point(visibleSize / 2) + origin);
		// add the sprite as a child to this layer
		this->addChild(sprite);

		//��_menuLayer����sesne
		//this->addChild(_menuLayer,5,1);


		ret = true;
	} while(0);

	return ret;
}


void WelcomeLayer::menuCloseCallback(Object* sender)
{
	//���Ű�ť��Ч
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
//����Ϸ
void WelcomeLayer::menuNewCallback(Object* sender)
{
	//Director::getInstance()->end();
	//���Ű�ť��Ч
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	// ����Ϸsense
	Director::getInstance()->pushScene( GameScene::palyNewGame());
	//LoadingLayer *layer=LoadingLayer::create();
	//����scene;
	//sGlobal->welcomeScene->addChild(layer);
	//ɾ���Լ�
	//this->removeFromParentAndCleanup(true);

}
//��ʾ������Ļ�Ļص�����
void  WelcomeLayer::menuAboutCallback(Object* sender)
{
	//��ȡ�û�����,���Ű�ť��Ч
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//�½�һ��layer
	Layer *_aboutLayer=Layer::create();
	// ���ñ���
	auto sprite = Sprite::create("beij1.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize / 2) + origin);
	// add the sprite as a child to this layer
	_aboutLayer->addChild(sprite);

	//��������,����"��ΰ����ʾ����"
	auto label = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom"))->getCString(), "Arial", 30);
	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 80));
	// add the label as a child to this layer
	_aboutLayer->addChild(label, 1);

	//��������
	auto label1 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom1"))->getCString(), "Arial", 15);
	//����ê��
	label1->setAnchorPoint(Point(0,0));
	label1->setPosition(Point(origin.x + visibleSize.width/9, origin.y + visibleSize.height - 130));
	// add the label as a child to this layer
	_aboutLayer->addChild(label1, 1);

	//��������
	auto label2 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom2"))->getCString(), "Arial", 15);
	//����ê��
	label2->setAnchorPoint(Point(0,0));
	label2->setPosition(Point(origin.x + visibleSize.width/9, origin.y + visibleSize.height - 160));
	// add the label as a child to this layer
	_aboutLayer->addChild(label2, 1);

	//��������
	auto label3 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom3"))->getCString(), "Arial", 15);
	//����ê��
	label3->setAnchorPoint(Point(0,0));
	label3->setPosition(Point(origin.x + visibleSize.width/9, origin.y + visibleSize.height-190));
	// add the label as a child to this layer
	_aboutLayer->addChild(label3, 1);

	//���ذ�ť
	auto closeItem = MenuItemImage::create("5.png","5.png",CC_CALLBACK_1(WelcomeLayer::menuAboutReturnCallback,this));
	closeItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-85);
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	_aboutLayer->addChild(menu, 1);

	//��layer����scene,tag����Ϊ2
	sGlobal->welcomeScene->addChild(_aboutLayer,10,2);
	//�رյ�һ��,��ֹ��������(��Ȼ������)
	sGlobal->welcomeScene->removeChildByTag(1);

	//CCDirector::sharedDirector()->getEventDispatcher() ->addTargetedDelegate(this, numeric_limits <int> ::min() , true);

}
//���õĻص�����
void  WelcomeLayer::menuSetCallback(Object* sender)
{

	//���Ű�ť��Ч
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//�½�һ��layer
	Layer *_setLayer=Layer::create();

	// ���ñ���
	auto sprite = Sprite::create("beij1.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize / 2) + origin);
	// add the sprite as a child to this layer
	_setLayer->addChild(sprite);

	Dictionary *chnStrings= Dictionary::createWithContentsOfFile("cstring.xml");
	//->objectForKey("name"))->getCString()

	//��������
	ui::Text* alert = ui::Text::create();
	alert->setText(((CCString*)chnStrings->objectForKey("beijyy"))->getCString());
	//��������
	//alert->setFontName("Marker Felt");
	alert->setFontSize(20);
	alert->setColor(Color3B(159, 168, 176));
	alert->setPosition(Point(visibleSize.width / 2.0-alert->getSize().width * 1.5f, visibleSize.height / 2.0f + alert->getSize().height * 1.75f));
	_setLayer->addChild(alert);  


	//��������
	ui::Text* alert1 = ui::Text::create();
	alert1->setText(((String*)chnStrings->objectForKey("yinxiaokg"))->getCString());
	//��������
	//alert->setFontName("Marker Felt");
	alert1->setFontSize(20);
	alert1->setColor(Color3B(159, 168, 176));
	alert1->setPosition(Point(visibleSize.width / 2.0-alert->getSize().width * 1.5f, visibleSize.height / 2.0f ));
	_setLayer->addChild(alert1);  

	ui::Text* alert2 = ui::Text::create();
	alert2->setText(((String*)chnStrings->objectForKey("yinliangdx"))->getCString());
	//��������
	// alert1->setFontName("Marker Felt");
	alert2->setFontSize(20);
	alert2->setColor(Color3B(159, 168, 176));
	alert2->setPosition(Point(visibleSize.width / 2.0-alert->getSize().width * 1.5f, visibleSize.height / 2.0f- alert->getSize().height * 1.75f));
	_setLayer->addChild(alert2);  

	// �������ֿ���
	CheckBox* checkBox = CheckBox::create();
	checkBox->setTouchEnabled(true);
	//δѡ��,����,ѡ��,����,������
	checkBox->loadTextures("fuxuan2.png", "fuxuan2.png", "fuxuan1.png", "fuxuan1.png","fuxuan1.png");
	//����û�����,Ĭ���ǿ�
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
		checkBox->setSelectedState(true);
	}else{
		checkBox->setSelectedState(false);
	}
	//log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("backmusic",0));
	checkBox->setPosition(Point(visibleSize.width / 2.0, visibleSize.height / 2.0f + alert->getSize().height * 1.75f));
	checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(WelcomeLayer::selectedEvent));
	_setLayer->addChild(checkBox);

	// ��Ч����
	CheckBox* checkBox1 = CheckBox::create();
	checkBox1->setTouchEnabled(true);
	//δѡ��,����,ѡ��,����,������
	checkBox1->loadTextures("fuxuan2.png", "fuxuan2.png", "fuxuan1.png", "fuxuan1.png","fuxuan1.png");
	//����û�����,Ĭ���ǿ�
	if(sGlobal->effect){
		checkBox1->setSelectedState(true);
	}else{
		checkBox1->setSelectedState(false);
	}
	//log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("backmusic",0));
	checkBox1->setPosition(Point(visibleSize.width / 2.0, visibleSize.height / 2.0f ));
	checkBox1->addEventListenerCheckBox(this, checkboxselectedeventselector(WelcomeLayer::selectedEvent1));
	_setLayer->addChild(checkBox1);


	// Create the slider
	Slider* slider = Slider::create();
	slider->setTouchEnabled(true);
	slider->loadBarTexture("sliderTrack.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress.png");
	slider->setPosition(Point(visibleSize.width / 2.0, visibleSize.height / 2.0f-alert->getSize().height * 1.75f));
	//����Ĭ��Ϊ50,��ʾʱ���û����ݶ�ȡ
	slider->setPercent(UserDefault::getInstance()->getIntegerForKey("yinliang",50));
	slider->addEventListenerSlider(this, sliderpercentchangedselector(WelcomeLayer::sliderEvent));
	_setLayer->addChild(slider);


	//���ذ�ť
	auto closeItem = MenuItemImage::create("5.png","5.png",CC_CALLBACK_1(WelcomeLayer::menuSetReturnCallback,this));
	closeItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-85);
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	_setLayer->addChild(menu, 1);

	//��layer����scene,tag����Ϊ3
	sGlobal->welcomeScene->addChild(_setLayer,10,3);
	//�رյ�һ��,��ֹ��������(��Ȼ������)
	sGlobal->welcomeScene->removeChildByTag(1);


	//Layer *_setLayer=Layer::create();
	//addChild(m_pLayer);

	// auto uiLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cc_1.json");  
	// UILayout* m_pLayout = dynamic_cast<UILayout*>(cocostudio::GUIReader::shareReader()->widgetFromJsonFile("cc_1.json"));
	//_setLayer->addWidget(m_pLayout);
	///
	//��layer����scene,tag����Ϊ2
	//this->addChild(uiLayer,10,2);

}

//���ڷ��صĻص�����
void  WelcomeLayer::menuAboutReturnCallback(Object* sender)
{

	//���Ű�ť��Ч
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	//����tagɾ��layer
	sGlobal->welcomeScene->removeChildByTag(2);

	//�½���һ��Ļ
	WelcomeLayer *_menuLayer=WelcomeLayer::create();
	//��_menuLayer����sesne
	sGlobal->welcomeScene->addChild(_menuLayer,5,1);
}

//���÷��صĻص�����
void  WelcomeLayer::menuSetReturnCallback(Object* sender)
{
	//���Ű�ť��Ч
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	//����tagɾ��layer
	sGlobal->welcomeScene->removeChildByTag(3);

	WelcomeLayer *_menuLayer=WelcomeLayer::create();
	//��_menuLayer����sesne
	sGlobal->welcomeScene->addChild(_menuLayer,5,1);

}


//�����ﱳ�����ָ�ѡ����
void WelcomeLayer::selectedEvent(Object* pSender,CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		// _displayValueLabel->setText(String::createWithFormat("Selected")->getCString());
		//�����û�����

		UserDefault::getInstance()->setIntegerForKey("backmusic",1);
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/Backmusic.mp3", true);
		break;

	case CHECKBOX_STATE_EVENT_UNSELECTED:
		// _displayValueLabel->setText(String::createWithFormat("Unselected")->getCString());

		UserDefault::getInstance()->setIntegerForKey("backmusic",2);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic( false);

		break;
	default:
		break;
	}

}

//��������Ч��ѡ����
void WelcomeLayer::selectedEvent1(Object* pSender,CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		// _displayValueLabel->setText(String::createWithFormat("Selected")->getCString());
		//�����û�����
		UserDefault::getInstance()->setBoolForKey("effectmusic",true);
		sGlobal->effect=true;
		break;

	case CHECKBOX_STATE_EVENT_UNSELECTED:
		// _displayValueLabel->setText(String::createWithFormat("Unselected")->getCString());
		sGlobal->effect=false;
		UserDefault::getInstance()->setBoolForKey("effectmusic",false);


		break;
	default:
		break;
	}

}




//��������������
void WelcomeLayer::sliderEvent(Object *pSender, SliderEventType type)
{
	if (type == SLIDER_PERCENTCHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		UserDefault::getInstance()->setIntegerForKey("yinliang",percent);
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent/100.0f);
		//_displayValueLabel->setText(String::createWithFormat("Percent %d", percent)->getCString());
	}
}
