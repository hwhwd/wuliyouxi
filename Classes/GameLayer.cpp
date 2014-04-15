
#include "GameLayer.h"
using namespace cocos2d;
//�������layer������������
//��������ʾ��ͼ����������ı任�����������\��ײ���
//10
//��Դ�������ccConfo.h�е�CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL��,���Ƶ�ͼ�к�ɫ�ӷ�
//��Ļ�����ǵ�ͼ�����һ��
//����z��,ʵ��˳�����,�ڵ�,���Ƿ���,�����˸���ֵ1000��ȥ
//������ѧͷ�ļ�,Ϊ�˿���#include<math.h>
//����8������
//�̶��˺���5
//����ٶ�150
//����50
//hero���Ӵ�С,90,50
//��ͼ�����С��16,16
//��ͼê��0.4,0.76
GameLayer::GameLayer(void)
{
	//���������,����gameLayerҲ���˵�����
	sGlobal->gameLayer=this;
}

GameLayer::~GameLayer(void)
{
	//������ж�ʱ��
	this->unscheduleAllSelectors();
}

//��ʼ�����������������ͼ
bool GameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
			//��Ļ��С
		auto visibleSize = Director::getInstance()->getVisibleSize();


		//��ʼ����ͼ
		_map = TMXTiledMap::create("ditu.tmx");
		//����Ӣ�۳�ʼλ��
		_map->setAnchorPoint(Point(0.4,0.76));
		_map->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
		//��ͼ��С
		//Size  s = _map->getContentSize();
		//CCLOG("dituSize: %f, %f", s.width,s.height);
		//��ͼ���������
		auto& children = _map->getChildren();
		SpriteBatchNode* child = NULL;
		for(const auto &node : children) {
			child = static_cast<SpriteBatchNode*>(node);
			child->getTexture()->setAntiAliasTexParameters();
		}
		
		//��ʼ����ͼ�еĲ�
		//floorLayer=_map->getLayer("floor");//�ײ�
		wallLayer=_map->getLayer("shitou");//ǽ��
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
			//���ò��ܹ���
				Sprite *child1=wallLayer->getTileAt(Point(i,e));
				//child1->setAnchorPoint(Point(0.0f,0.0f));
				
				child1->setPhysicsBody(ballBody);
				CCLOG("gdgdffhf %d,%d",i,e);
				
				}
			}
		}
		//����ê��
		
		this->addChild(_map);
	


	
		//����һ������,���ӷ�ΧΪ�˶���Χ
		//auto origin = Director::getInstance()->getVisibleOrigin();
		auto edgeSp = Sprite::create();
		auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		edgeSp->setPhysicsBody(boundBody); 
		this->addChild(edgeSp); 
		edgeSp->setTag(0);
		//this->setAccelerometerEnabled(true);



		//����hero��ķ���
		Hero *_hero=Hero::heroWithLayer();
		auto ballBody = PhysicsBody::createBox(Size(_hero->getChildByTag(1)->getContentSize().width/2,_hero->getChildByTag(1)->getContentSize().height/1.3));
		//CCLOG("hero�Ĵ�С %f,%f", _hero->getContentSize().width, _hero->getContentSize().height);
		//���ò��ܹ���
		ballBody->setRotationEnable(false);
		//����ٶ���60
		ballBody->setVelocityLimit(150);
		//����Ϊ0
		ballBody->getShape(0)->setRestitution(0);
		//Ħ����Ϊ0
		ballBody->getShape(0)->setFriction(0);
		//��������
		//ballBody->setMass(100.0);
		_hero->setPhysicsBody(ballBody);
		this->addChild(_hero,12,99);
		_hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2)); 



		//�����ӵ�����
		sGlobal->_bullets =Array::create();
		sGlobal->_bullets->retain();


		//��������,������ӽ�ȥ
		sGlobal->_enemys = Array::createWithCapacity(8);
		sGlobal->_enemys->retain();
		for (int i = 0; i < 8; i++) {
			Enemy *_enemy = Enemy::enemyWithLayer();
			// ����ķŵ���ͼ����
			_enemy->setPosition(Point(CCRANDOM_0_1() *550+250, CCRANDOM_0_1() * 500+30));
			//���Ŷ����������
			_enemy->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(CCRANDOM_0_1() *4+5)));
			//_enemy->idle();
			sGlobal->_enemys->addObject(_enemy);
			//����z��
			//_enemy->setLocalZOrder(_enemy->getPositionY());
			//�����ͼ,tag��i
			this->addChild(_enemy,12,i);
		}
		//����������
		SpriteBatchNode* BatchNode = CCSpriteBatchNode::create("sliderThumb.png", 70);
		this->addChild(BatchNode,3,100);
		//sGlobal->_enemys->getObjectAtIndex(1)->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(eUp)));
		//ÿ֡���õ�ͼ�ƶ�����
		schedule(schedule_selector(GameLayer::update2));
		//��ײ���
		schedule(schedule_selector(GameLayer::update1),0.1f);
		ret = true;
	} while(0);

	return ret;
}

//������������,�����հ�scene
Scene* GameLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	//����ģʽָ����
	sGlobal->physicScene=scene;
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//��������
	Vect gravity(0.0f, -50.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();

	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	// return the scene
	return scene;
}


//tilemap��cocos2d����ת��
Point GameLayer::tileCoordForPosition(Point position){
	//����2��������,Ҳ��֪��Ϊɶ
	//int x = position.x /( _map->getTileSize().width);
	//���鹫ʽ...
	int x = (int)(position.x /15.6+0.5);
	//log("zuobianx = %f, y = %f",_map->getTileSize().width,_map->getTileSize().height);
	int y = (((_map->getMapSize().height) * (_map->getTileSize().height-1)) - position.y*2) / _map->getTileSize().height;
	//int y = (480 - position.y) /32;
	//log("zuobianx = %f, y = %f",_map->getMapSize().height,_map->getTileSize().height);

	return Point(x, y);
}
//�ӵ�ͼ���굽ϵͳ����
Point GameLayer::positionForTileCoord(Point tileCoord){
	Point pos =  Point((tileCoord.x * _map->getTileSize().width),
		((_map->getMapSize().height - tileCoord.y - 1) * _map->getTileSize().height));
	return pos;
}
//tilemap�Ķ����ʼ������
//void GameLayer::extraInit(){
//}
//���������
//void GameLayer::enableAnitiAlisForEachLayer(cocos2d::TMXTiledMap *_map){
//	//����
//	Vector<Node*> _ChildArray=_map->getChildren();
//	//Node *_object=NULL;
//	SpriteBatchNode *_child=NULL;
//	//_map->getChildren����ֵ��һ��ccarry����
//	for(auto sp:_ChildArray){
//		_child=(SpriteBatchNode*)sp;
//		if(!_child)
//			break;
//		//���������
//		_child->getTexture()->setAntiAliasTexParameters();
//	}
//}
TMXLayer* GameLayer::getWallLayer()
{
	return wallLayer;
}


//������ʿ��ǰλ����Ϣ���������ƶ�����Ӧλ��,ÿ֡����,��Ҫ�Ż�
void GameLayer::setSceneScrollPosition(Point position)
{
	//��ȡ��Ļ�ߴ�
	Size screenSize = Director::getInstance()->getWinSize();
	//log("%f",screenSize.height);
	//ȡ��ʿ��ǰx�������Ļ�е�x�����ֵ�������ʿ��xֵ�ϴ�������
	float x = MAX(position.x, screenSize.width / 2.0f);
	float y = MAX(position.y, screenSize.height / 2.0f);
	//��ͼ�ܿ�ȴ�����Ļ��ȵ�ʱ����п��ܹ���
	//log("%f   %f",screenSize.height,_map->getMapSize().height);
	if (_map->getMapSize().width*16 >screenSize.width)
	{
		//���������������벻�ܳ�����ͼ�ܿ��ȥ��Ļ���1/2
		//Ϊ��ȥ���ڱ���
		//x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width)/2- screenSize.width / 2.0f);
		x = MIN(x, (_map->getMapSize().width * (_map->getTileSize().width-2))/2- screenSize.width / 2.0f);
	}
	if (_map->getMapSize().height*16 > screenSize.height)
	{
		y = MIN(y, (_map->getMapSize().height * (_map->getTileSize().height-2))/2 
			-screenSize.height / 2.0f);
	}
	//��ʿ��ʵ��λ��
	//Point heroPosition = ccp(x, y);
	//ccp����
	Point heroPosition = Point(x, y);
	//��Ļ�е�λ��
	Point screenCenter = Point(screenSize.width/2.0f,screenSize.height/2.0f);

	//ֱ�Ӽ���
	Point scrollPosition = screenCenter-heroPosition;
	//���ƶ����뱣��������ı�����

	//�������ƶ�����Ӧλ��
	//sGlobal->physicScene->setPosition(scrollPosition);
	//�������෴....��Ҳ��֪��Ϊɶ
	setPosition(scrollPosition);
	CCLog("scene position: %f,%f", scrollPosition.x, scrollPosition.y);
}
//ÿִ֡��,��������
void GameLayer::update2(float dt)
{
	//�����ʿ��������״̬������Ҫ���³���λ��\����zֵ\����AI
	if (sGlobal->hero->isHeroMoving)
	{
		//���µ�ͼ��λ��
		setSceneScrollPosition(sGlobal->hero->getPosition());
	}
}


//0.1��ִ��һ��,/����z��/��ײ���
void GameLayer::update1(float dt){
	//�����ʿ��������״̬������Ҫ���³���λ��\����zֵ\����AI
	if (sGlobal->hero->isHeroMoving)
	{
		//����zֵ,ת������,�����ֺ���ʿ
		Node *_sprite=this->getChildByTag(99);
		//ͳһ���ڲ������ϵ�����y,���Ƿ�����Ҫ��һ����ֵ��ȥ
		_sprite->setZOrder(1000-sGlobal->optionLayer->convertToWorldSpace(_sprite->getPosition()).y);
		//���鲻����..Ҫ��forech
		CCObject* pObject = NULL; 
		CCARRAY_FOREACH(sGlobal->_enemys,pObject){
			_sprite=(Node*)pObject;
			this->reorderChild(_sprite,1000-sGlobal->optionLayer->convertToWorldSpace(_sprite->getPosition()).y);
		}

	}

	//���û���ӵ�����Ҫ�ӵ���ײ���
	if(sGlobal->_bullets->count()!=0){
		//log("****************");
		CCObject* pObject = NULL; 
		Node *node=Node::create();
		CCARRAY_FOREACH(sGlobal->_bullets,pObject){
			node=(Node*)pObject;
			CollisionType collisionType = checkCollision(node->getPosition(),pBullet);
			//����ǽ,��ʱ��������
			if (collisionType == kWall || collisionType == kEnemy)
			{
				//ֹͣ���ж���
				node->stopActionByTag(1);
				//��������,���ñ�ը��������(�½�һ������)
				bulletEnemy(node->getPosition());
				//�Ƴ�����
				sGlobal->_bullets->removeObject(node);
				node->removeFromParentAndCleanup(true);
			}
		}
	}
	//Aiʱ����ײ���
	if (sGlobal->hero->isHeroMoving&&sGlobal->heroAITag!=aiNone)
	{
		//���hero��Ҫ�ƶ�ȥ�ĵ�
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
		//Ҫ�ƶ����ĵ�
		Point point=sGlobal->hero->getPosition()+moveByPosition;
		CollisionType collisionType = checkCollision(point,pHero);
		//�����ǽ���߹�
		if (collisionType == kWall || collisionType == kEnemy){

			if (sGlobal->hero->isHeroMoving)
			{
				//���ñ�ʾ,����ִֻ��һ��
				sGlobal->hero->isHeroMoving=false;
				//ֹͣ���ж���
				sGlobal->hero->stopAllActions();
				sGlobal->hero->getChildByTag(1)->stopAllActions();
				//����A*��·����
				sGlobal->_heroAI->findRoute();
				//log("**********************");
			}
		}
	}


}


//��ײ���,�����κ�һ������,����Ƿ��ж���,key,1����
CollisionType GameLayer::checkCollision(Point point,CollisionThing key){

	////ǽ�͵�ͼ�߽�
	////cocos2d-x����ת��ΪTilemap����
	//Point  targetTileCoord = tileCoordForPosition(point);
	////log("zuobiao x = %f, y = %f ,ditu %f  ,  %f",heroPosition.x,heroPosition.y,targetTileCoord.x,targetTileCoord.y);
	////�����ʿ���곬����ͼ�߽磬����kWall���ͣ���ֹ���ƶ�
	//if (targetTileCoord.x >_map->getMapSize().width - 1 || targetTileCoord.y < 1 || targetTileCoord.y > _map->getMapSize().height - 1||targetTileCoord.x<1)
	//	return kWall;
	////��ȡǽ�ڲ��Ӧ�����ͼ��ID
	//int targetTileGID = getWallLayer()->getTileGIDAt(targetTileCoord);
	////���ͼ��ID��Ϊ0����ʾ��ǽ
	//if (targetTileGID) {
	//		CCLOG("*********************");
	//	//return kWall;
	//}
	////Ӣ�۵���������
	////Point p1=sGlobal->optionLayer->convertToWorldSpace(heroPosition);

	////����
	////����Ĵ�С,�����ж�,������յ�ʱ��,����ͱ�����
	//Size s1;
	//if (sGlobal->_enemys->count()!=0)
	//{
	//	s1=((Node*)sGlobal->_enemys->getObjectAtIndex(0))->getChildByTag(1)->getContentSize();
	//}

	////��ȡ�����Ӧ����
	////sGlobal->_enemys->count();
	//for(int i=0;i<sGlobal->_enemys->count();++i){
	//	//�ֵ���ʱ����
	//	Node *enemy=(Node*)sGlobal->_enemys->getObjectAtIndex(i);
	//	Point p2=sGlobal->optionLayer->convertToWorldSpace(enemy->getPosition());
	//	//��������
	//	if(point.y<p2.y+s1.width/2&&point.y>p2.y-s1.width/2&&point.x<p2.x+s1.width/2&&point.x>p2.x-s1.width/2){
	//		//������������ӵ���ħ���˺�
	//		if (key==pBullet)
	//		{
	//			//����Ч��ʱ����1��
	//			//��ʾ���ʱ���˺�ֵ
	//			FiniteTimeAction* action =FadeOut::create(1);
	//			enemy->getChildByTag(5)->setVisible(true);
	//			enemy->getChildByTag(5)->runAction(action);
	//			//����Ѫ��ʾ,�˺���Ĭ��ֵ��5,�˺��̶���20
	//			((ProgressTimer *)enemy->getChildByTag(3))->setPercentage((float)(((Enemy*)enemy)->xue-5)*5);
	//			//((ProgressTimer *)enemy->getChildByTag(3))->setPercentage(75.0);
	//			((Enemy*)enemy)->xue=((Enemy*)enemy)->xue-5;

	//			//����ѡ�л����Ѫ��
	//			((ProgressTimer *)sGlobal->optionLayer->getChildByTag(4)->getChildByTag(3))->setPercentage((float)((Enemy*)enemy)->xue*5);
	//			//log("aaa%d",((Enemy*)enemy)->xue);
	//			//��������
	//			if(((Enemy*)enemy)->xue<1){
	//				onEnemyDie(p2);
	//				sGlobal->_enemys->removeObject(enemy);
	//				//this->removeChildByTag(i);
	//				enemy->removeFromParentAndCleanup(true);
	//				//ȥ��ѡ�б��
	//				sGlobal->xuanz=false;
	//				sGlobal->xuanzTag=-1;
	//			}

	//		}else if(key==pHero){
	//			//�����Ӣ��..�������˺�


	//		}
	//		return kEnemy;
	//	}
		//����ֵľ��䷶Χ,������ֵ,��Ϊ������hero����,����AI
		//if (key==pHero)
		//{
		//	if(point.y<p2.y+s1.height*2&&point.y>p2.y-s1.height*2&&point.x<p2.x+s1.height*2&&point.x>p2.x-s1.height*2){
		//		//���ù���Եķ���
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
		//		////������Ч
		//		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/FiftyStun.wav");
		//	}
		//}
	//}

	//�ӵ���Ӣ�۲���Ҫ���Ӣ��
	if(key==pEnemy){
		//�������Ӣ��
		Rect rect=sGlobal->hero->getBoundingBox();
		if (rect.containsPoint(point))
		{
			return kNPC;
		}
	}
	//����ͨ��
	return kNone;


}
//�����ӵ�
void GameLayer::addBullet(Point heroPosition,Point enemyPosition){
	//��������
	Sprite *_projectile =Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("4_3.png")); 
	//��������
	sGlobal->_bullets->addObject(_projectile);
	//�趨��ʼλ��
	_projectile->setPosition( heroPosition );
	//Ҫ��ȥ��·��
	float offX = enemyPosition.x - heroPosition.x;
	float offY = enemyPosition.y - heroPosition.y;
	this->addChild(_projectile,15,88);
	//����ı�ֵ
	float ratio = (float)offY / (float)offX;
	//Ŀ�����
	//�����ӵ���������100����,��ֱ֪�������ε�б�ߺ����߳�֮��,��Ŀ���xΪ
	//�ֵÿ��Ǹ��������
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

	//�ӵ���ʧ�ĵ�
	Point xiaos= Point(realX,realY);
	//log("x=%f  y=%f  e %f  e %f  h%f  h%f ",realX,realY,enemyPosition.x,enemyPosition.y,heroPosition.x,heroPosition.y);
	//��ʼ�ƶ�
	Action *action = Sequence::create(MoveTo::create(0.5, xiaos),CallFuncN::create(CC_CALLBACK_1(GameLayer::onMoveDone,this)), NULL);
	//�ƶ���tagΪ1
	action->setTag(1);

	_projectile->runAction(action);

}
//�ӵ��ƶ����֮����Ҫ���ñ�ը�Ķ���
void GameLayer::onMoveDone(Node *_Target){
	//ִ�ж���,��ΪҪ�ص��������Բ�ֱ�Ӵ�
	//this->getChildByTag(88)->runAction(sAnimationMgr->createAnimate(bullet));
	Action *action = Sequence::create(sAnimationMgr->createAnimate(bullet),CallFuncN::create(CC_CALLBACK_1(GameLayer::onBulletAnimateDone,this)), NULL);
	_Target->runAction(action);

}
//��ը����ִ����ϵĻص�����,ɾ������
void GameLayer::onBulletAnimateDone(Node *_Target){
	//this->removeChildByTag(88);
	//������ɾ��
	//_Target->setVisible(false);
	sGlobal->_bullets->removeObject(_Target);
	_Target->removeFromParentAndCleanup(true);
}
//�ӵ�ײ��ǽ���ߵ���
void GameLayer::bulletEnemy(Point point){
	//�½�һ������
	Sprite* node=Sprite::create();
	//����λ��
	node->setPosition(point);
	//����
	this->addChild(node,101);
	Action *action = Sequence::create(sAnimationMgr->createAnimate(bullet),CallFuncN::create(CC_CALLBACK_1(GameLayer::onBulletEnemyDone,this)), NULL);
	node->runAction(action);

}
//�ӵ�ײ��ǽ���ߵ��˵Ļص�����
void GameLayer::onBulletEnemyDone(Node *_Target){
	//2��ɾ����������
	//this->removeChildByTag(88);

	//_Target->setVisible(false);

	//������ɾ��
	sGlobal->_bullets->removeObject(_Target);
	_Target->removeFromParentAndCleanup(true);

}
//������������
void GameLayer::onEnemyDie(Point point){
	//�½�һ������
	Sprite* node1=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("2_17.png"));   
	//����λ��
	node1->setPosition(point);
	//����
	this->addChild(node1,102);
	//����һ��5�뵭���ķ���
	Action *action = Sequence::create(FadeOut::create(5),CallFuncN::create(CC_CALLBACK_1(GameLayer::onEnemyDieDone,this)), NULL);
	node1->runAction(action);


}
void GameLayer::onEnemyDieDone(Node *_Target){
	//ɾ������

	_Target->removeFromParentAndCleanup(true);

}
