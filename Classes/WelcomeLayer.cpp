#include "WelcomeLayer.h"
#include "CCEventListenerTouch.h"
//#include "ui/CocosGUI.h"  
//#include "ui/UICheckBox.h"
//使用命名空间
using namespace ui;
using namespace cocos2d;
//欢迎layer
//用户数据"backmusic",1播放背景音乐,"backmusic",2不播放
//"yinliang",percent音乐音量
WelcomeLayer::WelcomeLayer(void)
{

}
WelcomeLayer::~WelcomeLayer(void)
{

}
//初始化方法
bool WelcomeLayer::init()
{

	bool ret = false;

	do {
		CC_BREAK_IF(!Layer::init());

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		//新游戏按钮
		auto newItem = MenuItemImage::create("1.png", "1.png", CC_CALLBACK_1(WelcomeLayer::menuNewCallback,this));
		//设置位置
		newItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2+5);
		// create menu, it's an autorelease object
		auto menu1 = Menu::create(newItem, NULL);
		menu1->setPosition(Point::ZERO);
		this->addChild(menu1, 1);

		//关于
		auto aboutItem = MenuItemImage::create("4.png", "4.png", CC_CALLBACK_1(WelcomeLayer::menuAboutCallback,this));
		//设置位置
		aboutItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-25);
		// create menu, it's an autorelease object
		auto menu2 = Menu::create(aboutItem, NULL);
		menu2->setPosition(Point::ZERO);
		this->addChild(menu2, 1);

		//设置
		auto setItem = MenuItemImage::create("2.png", "2.png", CC_CALLBACK_1(WelcomeLayer::menuSetCallback,this));
		//设置位置
		setItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-55);
		// create menu, it's an autorelease object
		auto menu3 = Menu::create(setItem, NULL);
		menu3->setPosition(Point::ZERO);
		this->addChild(menu3, 1);

		//退出按钮
		auto closeItem = MenuItemImage::create("3.png","3.png",CC_CALLBACK_1(WelcomeLayer::menuCloseCallback,this));
		closeItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-85);
		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu, 1);

		// 设置背景
		auto sprite = Sprite::create("beij.png");
		// position the sprite on the center of the screen
		sprite->setPosition(Point(visibleSize / 2) + origin);
		// add the sprite as a child to this layer
		this->addChild(sprite);

		//将_menuLayer加入sesne
		//this->addChild(_menuLayer,5,1);


		ret = true;
	} while(0);

	return ret;
}


void WelcomeLayer::menuCloseCallback(Object* sender)
{
	//播放按钮音效
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
//新游戏
void WelcomeLayer::menuNewCallback(Object* sender)
{
	//Director::getInstance()->end();
	//播放按钮音效
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	// 打开游戏sense
	Director::getInstance()->pushScene( GameScene::palyNewGame());
	//LoadingLayer *layer=LoadingLayer::create();
	//加入scene;
	//sGlobal->welcomeScene->addChild(layer);
	//删除自己
	//this->removeFromParentAndCleanup(true);

}
//显示关于屏幕的回调函数
void  WelcomeLayer::menuAboutCallback(Object* sender)
{
	//读取用户设置,播放按钮音效
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//新建一个layer
	Layer *_aboutLayer=Layer::create();
	// 设置背景
	auto sprite = Sprite::create("beij1.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize / 2) + origin);
	// add the sprite as a child to this layer
	_aboutLayer->addChild(sprite);

	//设置文字,标题"黄伟的演示程序"
	auto label = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom"))->getCString(), "Arial", 30);
	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 80));
	// add the label as a child to this layer
	_aboutLayer->addChild(label, 1);

	//设置文字
	auto label1 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom1"))->getCString(), "Arial", 15);
	//设置锚点
	label1->setAnchorPoint(Point(0,0));
	label1->setPosition(Point(origin.x + visibleSize.width/9, origin.y + visibleSize.height - 130));
	// add the label as a child to this layer
	_aboutLayer->addChild(label1, 1);

	//设置文字
	auto label2 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom2"))->getCString(), "Arial", 15);
	//设置锚点
	label2->setAnchorPoint(Point(0,0));
	label2->setPosition(Point(origin.x + visibleSize.width/9, origin.y + visibleSize.height - 160));
	// add the label as a child to this layer
	_aboutLayer->addChild(label2, 1);

	//设置文字
	auto label3 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("shuom3"))->getCString(), "Arial", 15);
	//设置锚点
	label3->setAnchorPoint(Point(0,0));
	label3->setPosition(Point(origin.x + visibleSize.width/9, origin.y + visibleSize.height-190));
	// add the label as a child to this layer
	_aboutLayer->addChild(label3, 1);

	//返回按钮
	auto closeItem = MenuItemImage::create("5.png","5.png",CC_CALLBACK_1(WelcomeLayer::menuAboutReturnCallback,this));
	closeItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-85);
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	_aboutLayer->addChild(menu, 1);

	//将layer加入scene,tag设置为2
	sGlobal->welcomeScene->addChild(_aboutLayer,10,2);
	//关闭第一屏,防止触摸按到(虽然看不见)
	sGlobal->welcomeScene->removeChildByTag(1);

	//CCDirector::sharedDirector()->getEventDispatcher() ->addTargetedDelegate(this, numeric_limits <int> ::min() , true);

}
//设置的回调函数
void  WelcomeLayer::menuSetCallback(Object* sender)
{

	//播放按钮音效
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//新建一个layer
	Layer *_setLayer=Layer::create();

	// 设置背景
	auto sprite = Sprite::create("beij1.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize / 2) + origin);
	// add the sprite as a child to this layer
	_setLayer->addChild(sprite);

	Dictionary *chnStrings= Dictionary::createWithContentsOfFile("cstring.xml");
	//->objectForKey("name"))->getCString()

	//设置文字
	ui::Text* alert = ui::Text::create();
	alert->setText(((CCString*)chnStrings->objectForKey("beijyy"))->getCString());
	//设置字体
	//alert->setFontName("Marker Felt");
	alert->setFontSize(20);
	alert->setColor(Color3B(159, 168, 176));
	alert->setPosition(Point(visibleSize.width / 2.0-alert->getSize().width * 1.5f, visibleSize.height / 2.0f + alert->getSize().height * 1.75f));
	_setLayer->addChild(alert);  


	//设置文字
	ui::Text* alert1 = ui::Text::create();
	alert1->setText(((String*)chnStrings->objectForKey("yinxiaokg"))->getCString());
	//设置字体
	//alert->setFontName("Marker Felt");
	alert1->setFontSize(20);
	alert1->setColor(Color3B(159, 168, 176));
	alert1->setPosition(Point(visibleSize.width / 2.0-alert->getSize().width * 1.5f, visibleSize.height / 2.0f ));
	_setLayer->addChild(alert1);  

	ui::Text* alert2 = ui::Text::create();
	alert2->setText(((String*)chnStrings->objectForKey("yinliangdx"))->getCString());
	//设置字体
	// alert1->setFontName("Marker Felt");
	alert2->setFontSize(20);
	alert2->setColor(Color3B(159, 168, 176));
	alert2->setPosition(Point(visibleSize.width / 2.0-alert->getSize().width * 1.5f, visibleSize.height / 2.0f- alert->getSize().height * 1.75f));
	_setLayer->addChild(alert2);  

	// 背景音乐开关
	CheckBox* checkBox = CheckBox::create();
	checkBox->setTouchEnabled(true);
	//未选择,过程,选择,过程,不可用
	checkBox->loadTextures("fuxuan2.png", "fuxuan2.png", "fuxuan1.png", "fuxuan1.png","fuxuan1.png");
	//获得用户数据,默认是开
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
		checkBox->setSelectedState(true);
	}else{
		checkBox->setSelectedState(false);
	}
	//log("%d",UserDefault::sharedUserDefault()->getIntegerForKey("backmusic",0));
	checkBox->setPosition(Point(visibleSize.width / 2.0, visibleSize.height / 2.0f + alert->getSize().height * 1.75f));
	checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(WelcomeLayer::selectedEvent));
	_setLayer->addChild(checkBox);

	// 音效开关
	CheckBox* checkBox1 = CheckBox::create();
	checkBox1->setTouchEnabled(true);
	//未选择,过程,选择,过程,不可用
	checkBox1->loadTextures("fuxuan2.png", "fuxuan2.png", "fuxuan1.png", "fuxuan1.png","fuxuan1.png");
	//获得用户数据,默认是开
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
	//设置默认为50,显示时从用户数据读取
	slider->setPercent(UserDefault::getInstance()->getIntegerForKey("yinliang",50));
	slider->addEventListenerSlider(this, sliderpercentchangedselector(WelcomeLayer::sliderEvent));
	_setLayer->addChild(slider);


	//返回按钮
	auto closeItem = MenuItemImage::create("5.png","5.png",CC_CALLBACK_1(WelcomeLayer::menuSetReturnCallback,this));
	closeItem->setPosition((origin.x + Point (visibleSize).x/2) ,origin.y+Point (visibleSize).y/2-85);
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	_setLayer->addChild(menu, 1);

	//将layer加入scene,tag设置为3
	sGlobal->welcomeScene->addChild(_setLayer,10,3);
	//关闭第一屏,防止触摸按到(虽然看不见)
	sGlobal->welcomeScene->removeChildByTag(1);


	//Layer *_setLayer=Layer::create();
	//addChild(m_pLayer);

	// auto uiLayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cc_1.json");  
	// UILayout* m_pLayout = dynamic_cast<UILayout*>(cocostudio::GUIReader::shareReader()->widgetFromJsonFile("cc_1.json"));
	//_setLayer->addWidget(m_pLayout);
	///
	//将layer加入scene,tag设置为2
	//this->addChild(uiLayer,10,2);

}

//关于返回的回调函数
void  WelcomeLayer::menuAboutReturnCallback(Object* sender)
{

	//播放按钮音效
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	//根据tag删除layer
	sGlobal->welcomeScene->removeChildByTag(2);

	//新建第一屏幕
	WelcomeLayer *_menuLayer=WelcomeLayer::create();
	//将_menuLayer加入sesne
	sGlobal->welcomeScene->addChild(_menuLayer,5,1);
}

//设置返回的回调函数
void  WelcomeLayer::menuSetReturnCallback(Object* sender)
{
	//播放按钮音效
	if(sGlobal->effect){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("BtnB.wav");
	}
	//根据tag删除layer
	sGlobal->welcomeScene->removeChildByTag(3);

	WelcomeLayer *_menuLayer=WelcomeLayer::create();
	//将_menuLayer加入sesne
	sGlobal->welcomeScene->addChild(_menuLayer,5,1);

}


//设置里背景音乐复选框函数
void WelcomeLayer::selectedEvent(Object* pSender,CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		// _displayValueLabel->setText(String::createWithFormat("Selected")->getCString());
		//设置用户数据

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

//设置里音效复选框函数
void WelcomeLayer::selectedEvent1(Object* pSender,CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		// _displayValueLabel->setText(String::createWithFormat("Selected")->getCString());
		//设置用户数据
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




//设置里音量滑动
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
