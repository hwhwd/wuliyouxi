#include "Hero.h"
using namespace cocos2d;
//Ӣ�� �ƶ�����
//12
//����һ����Sprite��Ⱦʱʹ��SpriteBatchNode���Ч��,����ֻ����ͬһ��
//Ѫ����Ĭ��75%
//moveto�ƶ�tagΪ2,moveby�ƶ�tagΪ1
Hero::Hero(void)
{
	//���������,����heroҲ���˵�����
	sGlobal->hero=this;
}

Hero::~Hero(void)
{
}

//��̬���������ڴ���,�����ڴ��
Hero* Hero::heroWithLayer(){
	Hero *_Ret=new Hero();
	//����init����
	if(_Ret&&_Ret->init()){
		//��ʵ�������Զ��أ���ϵͳ����������������
		_Ret->autorelease();
		return _Ret;
	}
	CC_SAFE_DELETE(_Ret);
	return NULL;
}

//��ʼ������
bool Hero::init()
{
	bool ret = false;
	//mgx=kDown;
	do{
		///CC_BREAK_IF(Node::init());�˾��ָ��..
		//���ÿ�ʼ֡��ͼ��
		_HeroSprit = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));   
		//�趨λ��
		_HeroSprit->setPosition(Point(0,0));  
		//��һ���ǲ�,�ڶ�����tag��ǩ 
		this->addChild(_HeroSprit,1,1);  
		this->setPosition(Point(30,30));  
		//״̬����Ϊ���ƶ�
		isHeroMoving = false;
		//���Ŷ���,ͨ�����ö���������
		//this->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
	
		//Ѫ��
		//��ɫѪ��(��Ѫ��)
		Sprite *pBloodKongSp = CCSprite::create("sliderTrack.png");
		pBloodKongSp->setPosition(Point(0, _HeroSprit->getContentSize().height*0.6));
		//�����ﾫ����
		this->addChild(pBloodKongSp,1,2);


		//��ɫ��ͼ
		Sprite *pBloodMan = CCSprite::create("sliderTrack1.png");
		//�������ڱ�ʾ���ﵱǰѪ���Ľ�����
		ProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodMan);
		//����Ϊ����
		pBloodProGress->setType(kCCProgressTimerTypeBar);
		//������ʼ��Ϊ�������·�
		pBloodProGress->setMidpoint(Point(0,0));
		//����Ϊˮƽ����
		pBloodProGress->setBarChangeRate(Point(1, 0));
		//���ó�ʼ����Ϊ��Ѫ
		pBloodProGress->setPercentage(75.0f);
		//����λ�ã�������Ŀ�Ѫ���ص����Ҿ�������
		pBloodProGress->setPosition(Point(0, _HeroSprit->getContentSize().height*0.6));
		this->addChild(pBloodProGress,1,3);

		//Ӣ������
		auto label = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("name"))->getCString(), "Arial", 10);
		//������ɫ
		label->setColor(Color3B(0,0,238));
		label->setPosition(Point(0, _HeroSprit->getContentSize().height*0.8));
		this->addChild(label,1,4);

		ret = true;
	} while (0);
	return ret;
}


//��ָ�������ƶ�,��Ϊ�ǳ������ϵ��ƶ�������MoveBy
void Hero::move(HeroDirection direction){
	//�Ƿ����ƶ�״̬
	if (isHeroMoving)
		return;
	famgx=direction;
	//�ƶ��ľ���
	Point moveByPosition;
	//���ݷ�������ƶ��ľ���
	switch (direction)
	{
	case kDown:
		moveByPosition = Point(0, -8);
		break;
	case kLeft:
		moveByPosition = Point(-8, 0);
		break;
	case kRight:
		moveByPosition = Point(8, 0);
		break;
	case kUp:
		moveByPosition = Point(0, 8);
		break;
	}
	//����Ŀ�����꣬�õ�ǰ��ʿ��������ƶ�����
	targetPosition = this->getPosition()+moveByPosition;

	//����checkCollision�����ײ���ͣ������ǽ�ڡ�����ţ���ֻ��Ҫ������ʿ�ĳ���
	CollisionType collisionType =sGlobal->gameLayer->checkCollision(targetPosition,pHero);
	if (collisionType == kWall || collisionType == kEnemy || collisionType == kDoor || collisionType == kNPC)
	{

		setFaceDirection((HeroDirection)direction);
		return;
	}
	//heroSprite���������߶���
	//heroSprite->runAction(sAnimationMgr->createAnimate(direction));
	//�������λ�ƣ�����ʱ����onMoveDone����

	//�ѷ�����Ϣ���ݸ�onMoveDone����MoveBy::create(ʱ��, Ŀ���)
	Action *action = Sequence::create(MoveBy::create(0.25, moveByPosition),CallFuncN::create(CC_CALLBACK_1(Hero::onMoveDone,this)), NULL);
	//�ƶ���tagΪ1
	action->setTag(1);
	//Action *action = Sequence::create(MoveBy::create(1, targetPosition));
	//����z��
	//this->setLocalZOrder(targetPosition.y);
	//log("y=%f",targetPosition.y);
	this->runAction(action);
	isHeroMoving = true;

}
//�ƶ���ɺ�ص�����
void Hero::onMoveDone(Node *_Target){
	isHeroMoving = false;
	//������ķ�����
	move(famgx);
	//_Target->stopAllActions();
}
//������ʿ����
void Hero::setFaceDirection(HeroDirection direction){

	//������ʾ֡
	switch (direction)
	{
	case kDown:
		_HeroSprit->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
		break;
	case kLeft:
		_HeroSprit->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
		break;
	case kRight:
		_HeroSprit->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("9.png"));
		break;
	case kUp:
		_HeroSprit->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("13.png"));
		break;
	default:
		break;
	}
}



//��ʿս������,�ں��жϾ��뷽��
void Hero::heroFight(){
	Point phero=sGlobal->hero->getPosition();
	Point penemy=((Node *)(sGlobal->_enemys->getObjectAtIndex(sGlobal->xuanzTag)))->getPosition();
	Point juli=penemy-phero;
	//���Ŀ���������
	if ((juli.x*juli.x+juli.y*juli.y)<20000)
	{
		sGlobal->gameLayer->addBullet(sGlobal->hero->getPosition(),sGlobal->optionLayer->convertToWorldSpace(((Node*)(sGlobal->_enemys->getObjectAtIndex (sGlobal->xuanzTag)))->getPosition()));
		//����ai״̬
		sGlobal->heroAITag=aiNone;
		//���Զ�Ѱ·��־ȥ��
		sGlobal->gameLayer->getChildByTag(100)->removeAllChildren();
		//sGlobal->gameLayer->getChildByTag(100)->removeFromParentAndCleanup(true);
		sGlobal->optionLayer->getChildByTag(6)->setVisible(false);
		//sGlobal->_heroAI->setAITag(aiNone);
		return;
	}else{
		//������Ҫ�ƶ����������
		float offX = phero.x - penemy.x;
		float offY = phero.y - penemy.y;
		//this->addChild(_projectile,15,88);
		//����ı�ֵ
		float ratio = (float)offY / (float)offX;
		//Ŀ�����
		//�����ӵ���������100����,��ֱ֪�������ε�б�ߺ����߳�֮��,��Ŀ���xΪ
		//�ֵÿ��Ǹ��������
		//Ϊ�˷�bug��ֵСһ��,Ҳ������ʿҪ�ȼ�����̸�������
		float xis=sqrt(19000/(1+ratio*ratio));
		float realX=0;
		float realY=0;
		if(phero.x> penemy.x){
			realX =penemy.x+xis;
			realY=penemy.y+xis*ratio;
		}else{
			realX =penemy.x-xis;
			realY=penemy.y-xis*ratio;
		}
		//�ӵ���ʧ�ĵ�
		Point xiaos= Point(realX,realY);

		//����moveto����
		heroMoveTo(xiaos);
		//Ȼ���ٵ������Լ�
	}

}
//��ʿmoveto����,���ϰ���ǰ����ֱ���߹�ȥ
void Hero::heroMoveTo(Point xiaos){
	//����Ӣ���ƶ�״̬
	isHeroMoving=true;
	//��Ĳ�ֵ
	Point chazhi=xiaos-sGlobal->hero->getPosition();
	float time=sqrt(chazhi.x*chazhi.x+chazhi.y*chazhi.y)*0.25/8;
	Action *action = Sequence::create(MoveTo::create(time, xiaos),CallFuncN::create(CC_CALLBACK_1(Hero::onMoveToDone,this)), NULL);
	action->setTag(2);
	this->runAction(action);

	//���Ŷ��������
	if (abs(chazhi.x)>abs(chazhi.y)) {
		if((chazhi.x)>0){
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
		}else{
			//���
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aLeft))); 
		}
	} else {
		if((chazhi.y)>0){
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aUp))); 
		}else{

			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aDown)));  
		}
	}
	
}

void Hero::onMoveToDone(Node *_Target){
	//���÷���ֹͣ����
	this->getChildByTag(1)->stopAllActions();
	//�ı��ƶ�״̬
	isHeroMoving=false;
	//�ƶ���ɺ���ù�������
	heroFight();
}