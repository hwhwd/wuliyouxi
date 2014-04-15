
#include "GameLayer.h"
using namespace cocos2d;
//仅在这个layer里有物理引擎
//画布，显示地图、各种坐标的变换、开启抗锯齿\碰撞检测
//10
//在源代码改了ccConfo.h中的CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL宏,改善地图有黑色接缝
//屏幕坐标是地图坐标的一半
//加入z轴,实现顺序添加,遮挡,但是反的,引入了个大值1000减去
//加了数学头文件,为了开方#include<math.h>
//加入8个怪物
//固定伤害是5
//最高速度150
//重力50
//hero盒子大小,90,50
//地图方块大小是16,16
//地图锚点0.4,0.76
GameLayer::GameLayer(void)
{
	//单类里面的,所以gameLayer也成了单类了
	sGlobal->gameLayer=this;
}

GameLayer::~GameLayer(void)
{
	//清除所有定时器
	this->unscheduleAllSelectors();
}

//初始化方法，包括载入地图
bool GameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
			//屏幕大小
		auto visibleSize = Director::getInstance()->getVisibleSize();


		//初始化地图
		_map = TMXTiledMap::create("ditu.tmx");
		//决定英雄初始位置
		_map->setAnchorPoint(Point(0.4,0.76));
		_map->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
		//地图大小
		//Size  s = _map->getContentSize();
		//CCLOG("dituSize: %f, %f", s.width,s.height);
		//地图开启抗锯齿
		auto& children = _map->getChildren();
		SpriteBatchNode* child = NULL;
		for(const auto &node : children) {
			child = static_cast<SpriteBatchNode*>(node);
			child->getTexture()->setAntiAliasTexParameters();
		}
		
		//初始化地图中的层
		//floorLayer=_map->getLayer("floor");//底层
		wallLayer=_map->getLayer("shitou");//墙壁
		Size  s = _map->getMapSize();
		unsigned int gid=0;
		for (int i = 0; i < s.width; i++)
		{
			for (int e = 0; e < s.height; e++)
			{
				//CCLOG("********************");
				gid = wallLayer->tileGIDAt(Point(i,e));
				if(gid>0){
				
				auto ballBody = PhysicsBody::createEdgeBox(Size( 16,16));
			//设置不能滚动
				Sprite *child1=wallLayer->getTileAt(Point(i,e));
				//child1->setAnchorPoint(Point(0.0f,0.0f));
				
				child1->setPhysicsBody(ballBody);
				CCLOG("gdgdffhf %d,%d",i,e);
				
				}
			}
		}
		//设置锚点
		
		this->addChild(_map);
	


	
		//创建一个刚体,可视范围为运动范围
		//auto origin = Director::getInstance()->getVisibleOrigin();
		auto edgeSp = Sprite::create();
		auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		edgeSp->setPhysicsBody(boundBody); 
		this->addChild(edgeSp); 
		edgeSp->setTag(0);
		//this->setAccelerometerEnabled(true);



		//调用hero类的方法
		Hero *_hero=Hero::heroWithLayer();
		auto ballBody = PhysicsBody::createBox(Size(_hero->getChildByTag(1)->getContentSize().width/2,_hero->getChildByTag(1)->getContentSize().height/1.3));
		//CCLOG("hero的大小 %f,%f", _hero->getContentSize().width, _hero->getContentSize().height);
		//设置不能滚动
		ballBody->setRotationEnable(false);
		//最高速度是60
		ballBody->setVelocityLimit(150);
		//弹性为0
		ballBody->getShape(0)->setRestitution(0);
		//摩擦力为0
		ballBody->getShape(0)->setFriction(0);
		//设置质量
		//ballBody->setMass(100.0);
		_hero->setPhysicsBody(ballBody);
		this->addChild(_hero,12,99);
		_hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2)); 



		//建立子弹数组
		sGlobal->_bullets =Array::create();
		sGlobal->_bullets->retain();


		//建立数组,将怪物加进去
		sGlobal->_enemys = Array::createWithCapacity(8);
		sGlobal->_enemys->retain();
		for (int i = 0; i < 8; i++) {
			Enemy *_enemy = Enemy::enemyWithLayer();
			// 随机的放到地图的右
			_enemy->setPosition(Point(CCRANDOM_0_1() *550+250, CCRANDOM_0_1() * 500+30));
			//播放动画随机方向
			_enemy->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(CCRANDOM_0_1() *4+5)));
			//_enemy->idle();
			sGlobal->_enemys->addObject(_enemy);
			//加入z轴
			//_enemy->setLocalZOrder(_enemy->getPositionY());
			//加入地图,tag是i
			this->addChild(_enemy,12,i);
		}
		//动画管理器
		SpriteBatchNode* BatchNode = CCSpriteBatchNode::create("sliderThumb.png", 70);
		this->addChild(BatchNode,3,100);
		//sGlobal->_enemys->getObjectAtIndex(1)->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eUp)));
		//每帧调用地图移动方法
		schedule(schedule_selector(GameLayer::update2));
		//碰撞检测
		schedule(schedule_selector(GameLayer::update1),0.1f);
		ret = true;
	} while(0);

	return ret;
}

//加入物理引擎,创建空白scene
Scene* GameLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	//单例模式指向他
	sGlobal->physicScene=scene;
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//设置重力
	Vect gravity(0.0f, -50.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();

	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	// return the scene
	return scene;
}


//tilemap和cocos2d坐标转换
Point GameLayer::tileCoordForPosition(Point position){
	//乘以2就正常了,也不知道为啥
	//int x = position.x /( _map->getTileSize().width);
	//经验公式...
	int x = (int)(position.x /15.6+0.5);
	//log("zuobianx = %f, y = %f",_map->getTileSize().width,_map->getTileSize().height);
	int y = (((_map->getMapSize().height) * (_map->getTileSize().height-1)) - position.y*2) / _map->getTileSize().height;
	//int y = (480 - position.y) /32;
	//log("zuobianx = %f, y = %f",_map->getMapSize().height,_map->getTileSize().height);

	return Point(x, y);
}
//从地图坐标到系统坐标
Point GameLayer::positionForTileCoord(Point tileCoord){
	Point pos =  Point((tileCoord.x * _map->getTileSize().width),
		((_map->getMapSize().height - tileCoord.y - 1) * _map->getTileSize().height));
	return pos;
}
//tilemap的额外初始化方法
//void GameLayer::extraInit(){
//}
//开启抗锯齿
//void GameLayer::enableAnitiAlisForEachLayer(cocos2d::TMXTiledMap *_map){
//	//出错
//	Vector<Node*> _ChildArray=_map->getChildren();
//	//Node *_object=NULL;
//	SpriteBatchNode *_child=NULL;
//	//_map->getChildren返回值是一个ccarry对象
//	for(auto sp:_ChildArray){
//		_child=(SpriteBatchNode*)sp;
//		if(!_child)
//			break;
//		//开启抗锯齿
//		_child->getTexture()->setAntiAliasTexParameters();
//	}
//}
TMXLayer* GameLayer::getWallLayer()
{
	return wallLayer;
}


//传入勇士当前位置信息，将场景移动到相应位置,每帧调用,需要优化
void GameLayer::setSceneScrollPosition(Point position)
{
	//获取屏幕尺寸
	Size screenSize = Director::getInstance()->getWinSize();
	//log("%f",screenSize.height);
	//取勇士当前x坐标和屏幕中点x的最大值，如果勇士的x值较大，则会滚动
	float x = MAX(position.x, screenSize.width / 2.0f);
	float y = MAX(position.y, screenSize.height / 2.0f);
	//地图总宽度大于屏幕宽度的时候才有可能滚动
	//log("%f   %f",screenSize.height,_map->getMapSize().height);
	if (_map->getMapSize().width*16 >screenSize.width)
	{
		//场景滚动的最大距离不能超过地图总宽减去屏幕宽的1/2
		//为了去掉黑边拉
		//x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width)/2- screenSize.width / 2.0f);
		x = MIN(x, (_map->getMapSize().width * (_map->getTileSize().width-2))/2- screenSize.width / 2.0f);
	}
	if (_map->getMapSize().height*16 > screenSize.height)
	{
		y = MIN(y, (_map->getMapSize().height * (_map->getTileSize().height-2))/2 
			-screenSize.height / 2.0f);
	}
	//勇士的实际位置
	//Point heroPosition = ccp(x, y);
	//ccp弃用
	Point heroPosition = Point(x, y);
	//屏幕中点位置
	Point screenCenter = Point(screenSize.width/2.0f,screenSize.height/2.0f);

	//直接减了
	Point scrollPosition = screenCenter-heroPosition;
	//将移动距离保存进公共的变量里

	//将场景移动到相应位置
	//sGlobal->physicScene->setPosition(scrollPosition);
	//和上面相反....我也不知道为啥
	setPosition(scrollPosition);
	CCLog("scene position: %f,%f", scrollPosition.x, scrollPosition.y);
}
//每帧执行,场景更新
void GameLayer::update2(float dt)
{
	//如果勇士不在行走状态，不需要更新场景位置\设置z值\智能AI
	if (sGlobal->hero->isHeroMoving)
	{
		//更新第图层位置
		setSceneScrollPosition(sGlobal->hero->getPosition());
	}
}


//0.1秒执行一次,/设置z轴/碰撞检测
void GameLayer::update1(float dt){
	//如果勇士不在行走状态，不需要更新场景位置\设置z值\智能AI
	if (sGlobal->hero->isHeroMoving)
	{
		//设置z值,转换坐标,包括怪和勇士
		Node *_sprite=this->getChildByTag(99);
		//统一的在操作层上的坐标y,但是反的需要用一个大值减去
		_sprite->setZOrder(1000-sGlobal->optionLayer->convertToWorldSpace(_sprite->getPosition()).y);
		//数组不定长..要用forech
		CCObject* pObject = NULL; 
		CCARRAY_FOREACH(sGlobal->_enemys,pObject){
			_sprite=(Node*)pObject;
			this->reorderChild(_sprite,1000-sGlobal->optionLayer->convertToWorldSpace(_sprite->getPosition()).y);
		}

	}

	//如果没有子弹则不需要子弹碰撞检测
	if(sGlobal->_bullets->count()!=0){
		//log("****************");
		CCObject* pObject = NULL; 
		Node *node=Node::create();
		CCARRAY_FOREACH(sGlobal->_bullets,pObject){
			node=(Node*)pObject;
			CollisionType collisionType = checkCollision(node->getPosition(),pBullet);
			//碰到墙,怪时触发动作
			if (collisionType == kWall || collisionType == kEnemy)
			{
				//停止所有动作
				node->stopActionByTag(1);
				//传出坐标,调用爆炸动画方法(新建一个精灵)
				bulletEnemy(node->getPosition());
				//移除精灵
				sGlobal->_bullets->removeObject(node);
				node->removeFromParentAndCleanup(true);
			}
		}
	}
	//Ai时的碰撞检测
	if (sGlobal->hero->isHeroMoving&&sGlobal->heroAITag!=aiNone)
	{
		//获得hero将要移动去的点
		Point moveByPosition;
		switch (sGlobal->hero->famgx)
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
		//要移动到的点
		Point point=sGlobal->hero->getPosition()+moveByPosition;
		CollisionType collisionType = checkCollision(point,pHero);
		//如果是墙或者怪
		if (collisionType == kWall || collisionType == kEnemy){

			if (sGlobal->hero->isHeroMoving)
			{
				//做好标示,让他只执行一次
				sGlobal->hero->isHeroMoving=false;
				//停止所有动画
				sGlobal->hero->stopAllActions();
				sGlobal->hero->getChildByTag(1)->stopAllActions();
				//调用A*找路方法
				sGlobal->_heroAI->findRoute();
				//log("**********************");
			}
		}
	}


}


//碰撞检测,传入任何一个坐标,检测是否有东西,key,1代表
CollisionType GameLayer::checkCollision(Point point,CollisionThing key){

	////墙和地图边界
	////cocos2d-x坐标转换为Tilemap坐标
	//Point  targetTileCoord = tileCoordForPosition(point);
	////log("zuobiao x = %f, y = %f ,ditu %f  ,  %f",heroPosition.x,heroPosition.y,targetTileCoord.x,targetTileCoord.y);
	////如果勇士坐标超过地图边界，返回kWall类型，阻止其移动
	//if (targetTileCoord.x >_map->getMapSize().width - 1 || targetTileCoord.y < 1 || targetTileCoord.y > _map->getMapSize().height - 1||targetTileCoord.x<1)
	//	return kWall;
	////获取墙壁层对应坐标的图块ID
	//int targetTileGID = getWallLayer()->getTileGIDAt(targetTileCoord);
	////如果图块ID不为0，表示有墙
	//if (targetTileGID) {
	//		CCLOG("*********************");
	//	//return kWall;
	//}
	////英雄的世界坐标
	////Point p1=sGlobal->optionLayer->convertToWorldSpace(heroPosition);

	////怪物
	////怪物的大小,不加判断,当数组空的时候,这个就保错了
	//Size s1;
	//if (sGlobal->_enemys->count()!=0)
	//{
	//	s1=((Node*)sGlobal->_enemys->getObjectAtIndex(0))->getChildByTag(1)->getContentSize();
	//}

	////获取怪物对应坐标
	////sGlobal->_enemys->count();
	//for(int i=0;i<sGlobal->_enemys->count();++i){
	//	//怪的临时对象
	//	Node *enemy=(Node*)sGlobal->_enemys->getObjectAtIndex(i);
	//	Point p2=sGlobal->optionLayer->convertToWorldSpace(enemy->getPosition());
	//	//攻击方法
	//	if(point.y<p2.y+s1.width/2&&point.y>p2.y-s1.width/2&&point.x<p2.x+s1.width/2&&point.x>p2.x-s1.width/2){
	//		//如果打来的是子弹是魔法伤害
	//		if (key==pBullet)
	//		{
	//			//淡出效果时间是1秒
	//			//显示打怪时的伤害值
	//			FiniteTimeAction* action =FadeOut::create(1);
	//			enemy->getChildByTag(5)->setVisible(true);
	//			enemy->getChildByTag(5)->runAction(action);
	//			//减少血显示,伤害的默认值是5,伤害固定是20
	//			((ProgressTimer *)enemy->getChildByTag(3))->setPercentage((float)(((Enemy*)enemy)->xue-5)*5);
	//			//((ProgressTimer *)enemy->getChildByTag(3))->setPercentage(75.0);
	//			((Enemy*)enemy)->xue=((Enemy*)enemy)->xue-5;

	//			//更改选中画面的血量
	//			((ProgressTimer *)sGlobal->optionLayer->getChildByTag(4)->getChildByTag(3))->setPercentage((float)((Enemy*)enemy)->xue*5);
	//			//log("aaa%d",((Enemy*)enemy)->xue);
	//			//怪物死亡
	//			if(((Enemy*)enemy)->xue<1){
	//				onEnemyDie(p2);
	//				sGlobal->_enemys->removeObject(enemy);
	//				//this->removeChildByTag(i);
	//				enemy->removeFromParentAndCleanup(true);
	//				//去掉选中标记
	//				sGlobal->xuanz=false;
	//				sGlobal->xuanzTag=-1;
	//			}

	//		}else if(key==pHero){
	//			//如果是英雄..是物理伤害


	//		}
	//		return kEnemy;
	//	}
		//进入怪的警戒范围,不返回值,因为不操作hero本身,开启AI
		//if (key==pHero)
		//{
		//	if(point.y<p2.y+s1.height*2&&point.y>p2.y-s1.height*2&&point.x<p2.x+s1.height*2&&point.x>p2.x-s1.height*2){
		//		//设置怪面对的方向
		//		//Point p3=p2-point;
		//		//if (p3.x>p3.y)
		//		//{
		//		//	if(p3.x>0){
		//		//		//((Enemy*)enemy)->Enemy::setFaceDirection(((Enemy*)enemy),kRight);
		//		//		((Enemy*)enemy)->getChildByTag(1)->stopAllActions();
		//		//		((Enemy*)enemy)->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eLeft)));
		//		//	}else{
		//		//		((Enemy*)enemy)->getChildByTag(1)->stopAllActions();
		//		//		((Enemy*)enemy)->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eRight)));
		//		//	}	
		//		//}else{
		//		//	if(p3.y>0){
		//		//		((Enemy*)enemy)->getChildByTag(1)->stopAllActions();
		//		//		((Enemy*)enemy)->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eDown)));
		//		//	}else{

		//		//		((Enemy*)enemy)->getChildByTag(1)->stopAllActions();
		//		//		((Enemy*)enemy)->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eUp)));
		//		//	}
		//		//}
		//		////log("****************");
		//		////警戒音效
		//		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/FiftyStun.wav");
		//	}
		//}
	//}

	//子弹和英雄不需要检测英雄
	if(key==pEnemy){
		//如果碰到英雄
		Rect rect=sGlobal->hero->getBoundingBox();
		if (rect.containsPoint(point))
		{
			return kNPC;
		}
	}
	//可以通行
	return kNone;


}
//加入子弹
void GameLayer::addBullet(Point heroPosition,Point enemyPosition){
	//创建精灵
	Sprite *_projectile =Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("4_3.png")); 
	//加入数组
	sGlobal->_bullets->addObject(_projectile);
	//设定初始位置
	_projectile->setPosition( heroPosition );
	//要飞去的路程
	float offX = enemyPosition.x - heroPosition.x;
	float offY = enemyPosition.y - heroPosition.y;
	this->addChild(_projectile,15,88);
	//方向的比值
	float ratio = (float)offY / (float)offX;
	//目标点是
	//设置子弹最大距离是100像素,已知直角三角形的斜边和俩边长之比,则目标的x为
	//又得考虑负数的情况
	float xis=sqrt(20000/(1+ratio*ratio));
	float realX=0;
	float realY=0;
	if(enemyPosition.x> heroPosition.x){
		realX =heroPosition.x+xis;
		realY=heroPosition.y+xis*ratio;
	}else{
		realX =heroPosition.x-xis;
		realY=heroPosition.y-xis*ratio;
	}
	//realY=heroPosition.y+xis*ratio;

	//子弹消失的点
	Point xiaos= Point(realX,realY);
	//log("x=%f  y=%f  e %f  e %f  h%f  h%f ",realX,realY,enemyPosition.x,enemyPosition.y,heroPosition.x,heroPosition.y);
	//开始移动
	Action *action = Sequence::create(MoveTo::create(0.5, xiaos),CallFuncN::create(CC_CALLBACK_1(GameLayer::onMoveDone,this)), NULL);
	//移动的tag为1
	action->setTag(1);

	_projectile->runAction(action);

}
//子弹移动完成之后需要调用爆炸的动画
void GameLayer::onMoveDone(Node *_Target){
	//执行动画,因为要回调方法所以不直接传
	//this->getChildByTag(88)->runAction(sAnimationMgr->createAnimate(bullet));
	Action *action = Sequence::create(sAnimationMgr->createAnimate(bullet),CallFuncN::create(CC_CALLBACK_1(GameLayer::onBulletAnimateDone,this)), NULL);
	_Target->runAction(action);

}
//爆炸动画执行完毕的回调方法,删除精灵
void GameLayer::onBulletAnimateDone(Node *_Target){
	//this->removeChildByTag(88);
	//数组内删除
	//_Target->setVisible(false);
	sGlobal->_bullets->removeObject(_Target);
	_Target->removeFromParentAndCleanup(true);
}
//子弹撞到墙或者敌人
void GameLayer::bulletEnemy(Point point){
	//新建一个精灵
	Sprite* node=Sprite::create();
	//设置位置
	node->setPosition(point);
	//加入
	this->addChild(node,101);
	Action *action = Sequence::create(sAnimationMgr->createAnimate(bullet),CallFuncN::create(CC_CALLBACK_1(GameLayer::onBulletEnemyDone,this)), NULL);
	node->runAction(action);

}
//子弹撞到墙或者敌人的回调方法
void GameLayer::onBulletEnemyDone(Node *_Target){
	//2种删除方法都错
	//this->removeChildByTag(88);

	//_Target->setVisible(false);

	//数组内删除
	sGlobal->_bullets->removeObject(_Target);
	_Target->removeFromParentAndCleanup(true);

}
//怪物死亡方法
void GameLayer::onEnemyDie(Point point){
	//新建一个精灵
	Sprite* node1=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_17.png"));   
	//设置位置
	node1->setPosition(point);
	//加入
	this->addChild(node1,102);
	//建立一个5秒淡出的方法
	Action *action = Sequence::create(FadeOut::create(5),CallFuncN::create(CC_CALLBACK_1(GameLayer::onEnemyDieDone,this)), NULL);
	node1->runAction(action);


}
void GameLayer::onEnemyDieDone(Node *_Target){
	//删除方法

	_Target->removeFromParentAndCleanup(true);

}
