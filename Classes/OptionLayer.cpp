#include "OptionLayer.h"
#include <math.h>
//û�ж�㴥��,û���϶�����
//�������λ��
Point	fangx=Point(80,80);

OptionLayer::OptionLayer(void)
{
	//����ʵ��ָ���Լ�
	sGlobal->optionLayer=this;
}


OptionLayer::~OptionLayer(void)
{
}

bool OptionLayer::init()
{
	//ע���׼�����¼�
	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);

	bool ret = false;
	do{
		//��ö�㴥�����
		setTouchEnabled(true);
		//��ÿ��������С
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		//�������ذ�ť
		auto closeItem = MenuItemImage::create("back.png","back.png",CC_CALLBACK_1(OptionLayer::menuCloseCallback,this));
		//λ��
		closeItem->setPosition(origin + Point(visibleSize) - Point(closeItem->getContentSize() / 2));
		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Point::ZERO);
		//��Ҫ��ͬһ��,���򲻽��ܴ�����
		this->addChild(menu, 3,1);


		//���������
		_fangxiang=Sprite::create("btn_normal.png");
		//�������ĵ�Ϊ������
		//_fangxiang->setAnchorPoint(ccp(0, 0));
		//����ê��
		_fangxiang->setPosition(fangx);
		//����Ϊ��͸��
		_fangxiang->setOpacity(150);
		this->addChild(_fangxiang,3,2);


		//ѡ����ʾ
		Sprite *xuanzhong=Sprite::create("biankuang.png");
		xuanzhong->setPosition((origin +Point(visibleSize) - Point(xuanzhong->getContentSize()/2)).x,(Point(visibleSize)/2 ).y);
		xuanzhong->setVisible(false);
		this->addChild(xuanzhong,1,3);

		//ѡ�еĹ�
		Enemy *enemy=Enemy::enemyWithLayer();
		enemy->setPosition((origin +Point(visibleSize) - Point(xuanzhong->getContentSize()/2)).x,(Point(visibleSize)/2 ).y);
		//���Ŷ���
		enemy->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(6)));
		//�⻷��ʾ
		enemy->getChildByTag(4)->setVisible(true);
		enemy->setVisible(false);
		this->addChild(enemy,3,4);

		//�����켣
		Sprite *guiji=Sprite::create("BUSYBACK.PNG");
		guiji->setVisible(false);
		this->addChild(guiji,3,5);

		//�Զ�Ѱ·ָʾ
		//��������
		auto label1 = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("AIing"))->getCString(), "Arial", 15);
		label1->setPosition(Point(origin.x + visibleSize.width/2, origin.y + label1->getContentSize().height));
		label1->setVisible(false);
		this->addChild(label1,3,6);

		ret = true;
	}while (0);
	//���ô�������
	//Touches();
	return ret;
}
//�ر���Ϸ
void OptionLayer::menuCloseCallback(Object* sender)
{
	//���Ű�ť��Ч
	if(sGlobal->effect){
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/BtnB.wav");
	}
	// �򿪻�ӭsense
	Director::getInstance()->pushScene(WelcomeScene::create());
}
