#include "Enemy.h"
using namespace cocos2d;
//怪物的创建、移动方法
//12
//大量一样的Sprite渲染时使用SpriteBatchNode提高效率,但是只能在同一层
//伤害是5,固定值
//血量是20,固定值
Enemy::Enemy(void)
{
	//单类里面的,所以hero也成了单类了
	//sGlobal->Enemy=this;
}

Enemy::~Enemy(void)
{
}

//静态方法，用于创建,加入内存池
Enemy* Enemy::enemyWithLayer(){
	Enemy *_Ret=new Enemy();
	//调用init方法
	if(_Ret&&_Ret->init()){
		//将实例放入自动池，由系统控制他的生命周期
		_Ret->autorelease();
		return _Ret;
	}
	CC_SAFE_DELETE(_Ret);
	return NULL;
}

//初始化方法
bool Enemy::init()
{
	bool ret = false;
	do{
		//血量默认是20
		xue=20;

		//设置开始帧的图像
		Sprite *_enemySprit = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_1.png"));     
		//第5层,tag为1
		this->addChild(_enemySprit,5,1);  //this->setPosition(Point(90,30));  
		
		//播放动画,通过调用动画管理器
		//this->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));

		//血条
		//角色血条(空血框)
		Sprite *pBloodKongSp = CCSprite::create("sliderTrack.png");
		pBloodKongSp->setPosition(Point(0, _enemySprit->getContentSize().height*0.5));
		//绑到人物精灵上
		this->addChild(pBloodKongSp,1,2);
		//红色的图
		Sprite *pBloodMan = CCSprite::create("sliderTrack1.png");

		//创建用于表示人物当前血量的进度条
		ProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodMan);
		//设置为条形
		pBloodProGress->setType(kCCProgressTimerTypeBar);
		//设置起始点为条形左下方
		pBloodProGress->setMidpoint(Point(0,0));
		//设置为水平方向
		pBloodProGress->setBarChangeRate(Point(1, 0));
		//设置初始进度为满血
		pBloodProGress->setPercentage(100.0f);
		//设置位置，与上面的空血框重叠，且居于其上
		pBloodProGress->setPosition(Point(0, _enemySprit->getContentSize().height*0.5));
		this->addChild(pBloodProGress,3,3);
		
		//创建表示选中的光环
		Sprite *xuanZhong =Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("4_1.png"));     
		xuanZhong->setPosition(Point(0, -_enemySprit->getContentSize().height*0.45));
		xuanZhong->setVisible(false);
		//绑到人物精灵上,第1层,tag为4
		this->addChild(xuanZhong,1,4);

		auto label = LabelTTF::create("-5","Arial", 18);
		label->setColor(Color3B(255,0,0));
		label->setPosition(Point(0, _enemySprit->getContentSize().height*0.7));
		label->setVisible(false);
		//绑到人物精灵上,第1层,tag为5
		this->addChild(label,1,5);

		//状态设置为不移动
		isHeroMoving = false;
		ret = true;
	} while (0);
    return ret;
}

 
//向指定方向移动,因为是持续不断地移动所以用MoveBy
void Enemy::move(HeroDirection direction){
	//是否在移动状态
	if (isHeroMoving)
		return;
	famgx=direction;
	//移动的距离
	Point moveByPosition;
	//根据方向计算移动的距离
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
	//计算目标坐标，用当前勇士坐标加上移动距离
	targetPosition = this->getPosition()+moveByPosition;
	
	//调用checkCollision检测碰撞类型，如果是墙壁、怪物、门，则只需要设置勇士的朝向
	CollisionType collisionType =sGlobal->gameLayer->checkCollision(targetPosition,pEnemy);
	if (collisionType == kWall || collisionType == kEnemy || collisionType == kDoor || collisionType == kNPC)
	{
		setFaceDirection(this,(HeroDirection)direction);
		return;
	}
	//heroSprite仅播放行走动画
	//heroSprite->runAction(sAnimationMgr->createAnimate(direction));
	//主体进行位移，结束时调用onMoveDone方法
	
	//把方向信息传递给onMoveDone方法
	Action *action = Sequence::create(MoveBy::create(0.25, moveByPosition),CallFuncN::create(CC_CALLBACK_1(Enemy::onMoveDone,this)), NULL);
	//移动的tag为1
	action->setTag(1);
	
	
	this->runAction(action);
	isHeroMoving = true;

}
//移动完成后回调函数
void Enemy::onMoveDone(Node *_Target){
	isHeroMoving = false;
	//将保存的方向传入
	move(famgx);
	//_Target->stopAllActions();
}
//设置怪物方向
void Enemy::setFaceDirection(Enemy* enemy,HeroDirection direction){

	//设置显示帧
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
