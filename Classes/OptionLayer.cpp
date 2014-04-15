#include "OptionLayer.h"
#include <math.h>
//没有多点触摸,没有拖动手势
//方向键的位置
Point	fangx=Point(80,80);

OptionLayer::OptionLayer(void)
{
	//单类实现指定自己
	sGlobal->optionLayer=this;
}


OptionLayer::~OptionLayer(void)
{
}

bool OptionLayer::init()
{
	//注册标准触摸事件
	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);

	bool ret = false;
	do{
		//获得多点触摸许可
		setTouchEnabled(true);
		//获得可视区域大小
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		//创建返回按钮
		auto closeItem = MenuItemImage::create("back.png","back.png",CC_CALLBACK_1(OptionLayer::menuCloseCallback,this));
		//位置
		closeItem->setPosition(origin + Point(visibleSize) - Point(closeItem->getContentSize() / 2));
		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Point::ZERO);
		//需要在同一层,否则不接受触摸了
		this->addChild(menu, 3,1);


		//创建方向键
		_fangxiang=Sprite::create("btn_normal.png");
		//设置中心点为正中心
		//_fangxiang->setAnchorPoint(ccp(0, 0));
		//设置锚点
		_fangxiang->setPosition(fangx);
		//设置为半透明
		_fangxiang->setOpacity(150);
		this->addChild(_fangxiang,3,2);


		//选中显示
		Sprite *xuanzhong=Sprite::create("biankuang.png");
		xuanzhong->setPosition((origin +Point(visibleSize) - Point(xuanzhong->getContentSize()/2)).x,(Point(visibleSize)/2 ).y);
		xuanzhong->setVisible(false);
		this->addChild(xuanzhong,1,3);

		//选中的怪
		Enemy *enemy=Enemy::enemyWithLayer();
		enemy->setPosition((origin +Point(visibleSize) - Point(xuanzhong->getContentSize()/2)).x,(Point(visibleSize)/2 ).y);
		//播放动画
		enemy->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(6)));
		//光环显示
		enemy->getChildByTag(4)->setVisible(true);
		enemy->setVisible(false);
		this->addChild(enemy,3,4);

		//触摸轨迹
		Sprite *guiji=Sprite::create("BUSYBACK.PNG");
		guiji->setVisible(false);
		this->addChild(guiji,3,5);

		//自动寻路指示
		//设置文字
		auto label1 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("AIing"))->getCString(), "Arial", 15);
		label1->setPosition(Point(origin.x + visibleSize.width/2, origin.y + label1->getContentSize().height));
		label1->setVisible(false);
		this->addChild(label1,3,6);

		ret = true;
	}while (0);
	//调用触摸方法
	//Touches();
	return ret;
}
//关闭游戏
void OptionLayer::menuCloseCallback(Object* sender)
{
	//播放按钮音效
	if(sGlobal->effect){
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/BtnB.wav");
	}
	// 打开欢迎sense
	Director::getInstance()->pushScene(WelcomeScene::create());
}
