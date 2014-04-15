#include "Enemy.h"
using namespace cocos2d;
//����Ĵ������ƶ�����
//12
//����һ����Sprite��Ⱦʱʹ��SpriteBatchNode���Ч��,����ֻ����ͬһ��
//�˺���5,�̶�ֵ
//Ѫ����20,�̶�ֵ
Enemy::Enemy(void)
{
	//���������,����heroҲ���˵�����
	//sGlobal->Enemy=this;
}

Enemy::~Enemy(void)
{
}

//��̬���������ڴ���,�����ڴ��
Enemy* Enemy::enemyWithLayer(){
	Enemy *_Ret=new Enemy();
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
bool Enemy::init()
{
	bool ret = false;
	do{
		//Ѫ��Ĭ����20
		xue=20;

		//���ÿ�ʼ֡��ͼ��
		Sprite *_enemySprit = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_1.png"));     
		//��5��,tagΪ1
		this->addChild(_enemySprit,5,1);  //this->setPosition(Point(90,30));  
		
		//���Ŷ���,ͨ�����ö���������
		//this->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));

		//Ѫ��
		//��ɫѪ��(��Ѫ��)
		Sprite *pBloodKongSp = CCSprite::create("sliderTrack.png");
		pBloodKongSp->setPosition(Point(0, _enemySprit->getContentSize().height*0.5));
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
		pBloodProGress->setPercentage(100.0f);
		//����λ�ã�������Ŀ�Ѫ���ص����Ҿ�������
		pBloodProGress->setPosition(Point(0, _enemySprit->getContentSize().height*0.5));
		this->addChild(pBloodProGress,3,3);
		
		//������ʾѡ�еĹ⻷
		Sprite *xuanZhong =Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("4_1.png"));     
		xuanZhong->setPosition(Point(0, -_enemySprit->getContentSize().height*0.45));
		xuanZhong->setVisible(false);
		//�����ﾫ����,��1��,tagΪ4
		this->addChild(xuanZhong,1,4);

		auto label = LabelTTF::create("-5","Arial", 18);
		label->setColor(Color3B(255,0,0));
		label->setPosition(Point(0, _enemySprit->getContentSize().height*0.7));
		label->setVisible(false);
		//�����ﾫ����,��1��,tagΪ5
		this->addChild(label,1,5);

		//״̬����Ϊ���ƶ�
		isHeroMoving = false;
		ret = true;
	} while (0);
    return ret;
}

 
//��ָ�������ƶ�,��Ϊ�ǳ������ϵ��ƶ�������MoveBy
void Enemy::move(HeroDirection direction){
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
	CollisionType collisionType =sGlobal->gameLayer->checkCollision(targetPosition,pEnemy);
	if (collisionType == kWall || collisionType == kEnemy || collisionType == kDoor || collisionType == kNPC)
	{
		setFaceDirection(this,(HeroDirection)direction);
		return;
	}
	//heroSprite���������߶���
	//heroSprite->runAction(sAnimationMgr->createAnimate(direction));
	//�������λ�ƣ�����ʱ����onMoveDone����
	
	//�ѷ�����Ϣ���ݸ�onMoveDone����
	Action *action = Sequence::create(MoveBy::create(0.25, moveByPosition),CallFuncN::create(CC_CALLBACK_1(Enemy::onMoveDone,this)), NULL);
	//�ƶ���tagΪ1
	action->setTag(1);
	
	
	this->runAction(action);
	isHeroMoving = true;

}
//�ƶ���ɺ�ص�����
void Enemy::onMoveDone(Node *_Target){
	isHeroMoving = false;
	//������ķ�����
	move(famgx);
	//_Target->stopAllActions();
}
//���ù��﷽��
void Enemy::setFaceDirection(Enemy* enemy,HeroDirection direction){

	//������ʾ֡
	switch (direction)
	{
	case kDown:
		//enemy->getChildByTag(1)-> setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_1.png"));
		//enemy->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eDown)));
		break;
	case kLeft:
		//enemy->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_5.png"));
		break;
	case kRight:
		//enemy->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_9.png"));
		break;
	case kUp:
		//_enemySprit->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_13.png"));
		break;
	default:
		break;
	}


}
