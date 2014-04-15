#include "Hero.h"
using namespace cocos2d;
//英雄 移动方法
//12
//大量一样的Sprite渲染时使用SpriteBatchNode提高效率,但是只能在同一层
//血量是默认75%
//moveto移动tag为2,moveby移动tag为1
Hero::Hero(void)
{
	//单类里面的,所以hero也成了单类了
	sGlobal->hero=this;
}

Hero::~Hero(void)
{
}

//静态方法，用于创建,加入内存池
Hero* Hero::heroWithLayer(){
	Hero *_Ret=new Hero();
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
bool Hero::init()
{
	bool ret = false;
	//mgx=kDown;
	do{
		///CC_BREAK_IF(Node::init());此句空指针..
		//设置开始帧的图像
		_HeroSprit = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));   
		//设定位置
		_HeroSprit->setPosition(Point(0,0));  
		//第一个是层,第二个是tag标签 
		this->addChild(_HeroSprit,1,1);  
		this->setPosition(Point(30,30));  
		//状态设置为不移动
		isHeroMoving = false;
		//播放动画,通过调用动画管理器
		//this->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
	
		//血条
		//角色血条(空血框)
		Sprite *pBloodKongSp = CCSprite::create("sliderTrack.png");
		pBloodKongSp->setPosition(Point(0, _HeroSprit->getContentSize().height*0.6));
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
		pBloodProGress->setPercentage(75.0f);
		//设置位置，与上面的空血框重叠，且居于其上
		pBloodProGress->setPosition(Point(0, _HeroSprit->getContentSize().height*0.6));
		this->addChild(pBloodProGress,1,3);

		//英雄名字
		auto label = LabelTTF::create(((CCString*) Dictionary::createWithContentsOfFile("cstring.xml")->objectForKey("name"))->getCString(), "Arial", 10);
		//设置颜色
		label->setColor(Color3B(0,0,238));
		label->setPosition(Point(0, _HeroSprit->getContentSize().height*0.8));
		this->addChild(label,1,4);

		ret = true;
	} while (0);
	return ret;
}


//向指定方向移动,因为是持续不断地移动所以用MoveBy
void Hero::move(HeroDirection direction){
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
	CollisionType collisionType =sGlobal->gameLayer->checkCollision(targetPosition,pHero);
	if (collisionType == kWall || collisionType == kEnemy || collisionType == kDoor || collisionType == kNPC)
	{

		setFaceDirection((HeroDirection)direction);
		return;
	}
	//heroSprite仅播放行走动画
	//heroSprite->runAction(sAnimationMgr->createAnimate(direction));
	//主体进行位移，结束时调用onMoveDone方法

	//把方向信息传递给onMoveDone方法MoveBy::create(时间, 目标点)
	Action *action = Sequence::create(MoveBy::create(0.25, moveByPosition),CallFuncN::create(CC_CALLBACK_1(Hero::onMoveDone,this)), NULL);
	//移动的tag为1
	action->setTag(1);
	//Action *action = Sequence::create(MoveBy::create(1, targetPosition));
	//设置z轴
	//this->setLocalZOrder(targetPosition.y);
	//log("y=%f",targetPosition.y);
	this->runAction(action);
	isHeroMoving = true;

}
//移动完成后回调函数
void Hero::onMoveDone(Node *_Target){
	isHeroMoving = false;
	//将保存的方向传入
	move(famgx);
	//_Target->stopAllActions();
}
//设置勇士方向
void Hero::setFaceDirection(HeroDirection direction){

	//设置显示帧
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



//勇士战斗方法,内含判断距离方法
void Hero::heroFight(){
	Point phero=sGlobal->hero->getPosition();
	Point penemy=((Node *)(sGlobal->_enemys->getObjectAtIndex(sGlobal->xuanzTag)))->getPosition();
	Point juli=penemy-phero;
	//如果目标在射程内
	if ((juli.x*juli.x+juli.y*juli.y)<20000)
	{
		sGlobal->gameLayer->addBullet(sGlobal->hero->getPosition(),sGlobal->optionLayer->convertToWorldSpace(((Node*)(sGlobal->_enemys->getObjectAtIndex (sGlobal->xuanzTag)))->getPosition()));
		//设置ai状态
		sGlobal->heroAITag=aiNone;
		//把自动寻路标志去掉
		sGlobal->gameLayer->getChildByTag(100)->removeAllChildren();
		//sGlobal->gameLayer->getChildByTag(100)->removeFromParentAndCleanup(true);
		sGlobal->optionLayer->getChildByTag(6)->setVisible(false);
		//sGlobal->_heroAI->setAITag(aiNone);
		return;
	}else{
		//计算需要移动到的坐标点
		float offX = phero.x - penemy.x;
		float offY = phero.y - penemy.y;
		//this->addChild(_projectile,15,88);
		//方向的比值
		float ratio = (float)offY / (float)offX;
		//目标点是
		//设置子弹最大距离是100像素,已知直角三角形的斜边和俩边长之比,则目标的x为
		//又得考虑负数的情况
		//为了防bug将值小一点,也就是勇士要比极限射程更靠近怪
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
		//子弹消失的点
		Point xiaos= Point(realX,realY);

		//调用moveto方法
		heroMoveTo(xiaos);
		//然后再调用它自己
	}

}
//勇士moveto方法,无障碍的前提下直接走过去
void Hero::heroMoveTo(Point xiaos){
	//设置英雄移动状态
	isHeroMoving=true;
	//点的差值
	Point chazhi=xiaos-sGlobal->hero->getPosition();
	float time=sqrt(chazhi.x*chazhi.x+chazhi.y*chazhi.y)*0.25/8;
	Action *action = Sequence::create(MoveTo::create(time, xiaos),CallFuncN::create(CC_CALLBACK_1(Hero::onMoveToDone,this)), NULL);
	action->setTag(2);
	this->runAction(action);

	//播放动画神马的
	if (abs(chazhi.x)>abs(chazhi.y)) {
		if((chazhi.x)>0){
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
		}else{
			//左边
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
	//调用方法停止动画
	this->getChildByTag(1)->stopAllActions();
	//改变移动状态
	isHeroMoving=false;
	//移动完成后调用攻击方法
	heroFight();
}