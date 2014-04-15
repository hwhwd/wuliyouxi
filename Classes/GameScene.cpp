
#include "GameScene.h"

//场景类
//
//触摸监听,应该在这里
//
//无多点触摸
//无触摸时move方法



//是否是方向键响应了,为了给onTouchEnded选择,如果是触摸其他地方结束,就不需要设置hero的方向和停止动画
bool xiangy=false;
//Gamelayer层移动的坐标


GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}
//初始化
bool GameScene::init()
{
	//参数
	bool ret = false;
	do {
		CC_BREAK_IF(!Scene::init());

		//获得多点触摸许可
		//setTouchEnabled(true);

		//初始化AI
		sGlobal->_heroAI= HeroAI::createHeroAI();
		//背景渐变层
		auto layer1 = LayerGradient::create(Color4B(187,255,255,255), Color4B(139,131,120,255));
		 addChild(layer1, 0, 1);

		// 游戏层初始化
		//GameLayer *_gameLayer = GameLayer::create();
		Scene * _gameLayer=GameLayer::createScene();
		this->addChild(_gameLayer, 10);

		OptionLayer *_optionLayer=OptionLayer::create();
		//控制层在上面
		this->addChild(_optionLayer,15);
		//调用触摸方法
		Touches();

		ret = true;
	} while (0);

	return ret;
}
//创建一个新的scene实例
Scene *GameScene::palyNewGame(){
	GameScene *scene=NULL;
	do{
		//版本修改后的
		scene=GameScene::create();
		CC_BREAK_IF(!scene);

	}while(0);
	return scene;
}


//触摸响应方法
void GameScene::Touches(){
	// 创建一个事件监听器 OneByOne 为单点触摸
	auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener1->setSwallowTouches(true);
	//开始点击事件,当他返回false时,就重新执行一次目标是下一个,可以获得相对目标的坐标,通过它一个方法获得所有层的点击
	//因为我把监听事件指向了layer,所以得到的坐标是相对layer的,对于按钮来说没啥意义,所以只返回了true;
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		//do{
		// 获取事件所绑定的对象,如果绑定了按钮的话就好用了,现在绑定的是layer
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//CCLOG("ceshi");
		// 获取当前点击点所在相对按钮的位置opgl坐标
		Point p = target->convertToNodeSpace(touch->getLocation());
		//打印触摸的屏幕坐标
		//log("DIANJIx = %f, y = %f",p.x,p.y);


		//攻击按钮
		//通过选中标记来判断显示的按钮是否存在,如果存在的话再点击就攻击
		if(sGlobal->xuanz){
			//怪物的矩形区域
			Rect rect=sGlobal->optionLayer->getChildByTag(3)->getBoundingBox();
			//如果触摸点在目标区域内
			if( rect.containsPoint(p)){
				//log("********************");
				//调用子弹方法,传入英雄坐标和选中怪物坐标
				//sGlobal->gameLayer->addBullet(sGlobal->hero->getPosition(),sGlobal->optionLayer->convertToWorldSpace(((Node*)(sGlobal->_enemys->getObjectAtIndex (sGlobal->xuanzTag)))->getPosition()));
				//sGlobal->hero->heroFight();
				sGlobal->_heroAI->start();
				return true;
			}
		}

		// 方向键
		//触摸点是否在控制层方向键的响应范围内
		//if(p.x<(pianyi.x+40)&&p.x>(pianyi.x-40)&&p.y<(pianyi.y+40)&&p.y>(pianyi.y-40)){
		if(sGlobal->optionLayer->getChildByTag(2)->getBoundingBox().containsPoint(p)){
			//设置触摸点位置和可见
			sGlobal->optionLayer->getChildByTag(5)->setPosition(p);
			sGlobal->optionLayer->getChildByTag(5)->setVisible(true);

			//获得方向键的位置
			Point pianyi=sGlobal->optionLayer->getChildByTag(2)->getPosition();
			// 触摸点在控制点右边或右边
			if (abs(p.x-pianyi.x)>abs(p.y-pianyi.y)) {
				if((p.x-pianyi.x)>0){
					//右边
					//log("YOUBIANx = %f, y = %f",p.x,p.y);
					//sGlobal->hero->setPosition(Point(30,30));
					//sGlobal->hero->retain();
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));

					sGlobal->hero->move(kRight);
				}else{
					//左边
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aLeft))); 
					sGlobal->hero->move(kLeft);
				}
			} else {
				if((p.y-pianyi.y)>0){
					//上边
					// log("shangbian = %f, y = %f",p.x,p.y);
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aUp))); 
					sGlobal->hero->move(kUp);
				}else{
					//下边
					//log("xiabian = %f, y = %f",p.x,p.y);
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aDown)));  
					sGlobal->hero->move(kDown);
				}
			}
			//响应之后做标记
			xiangy=true;
			//返回true,就不会再往下传了
			return true;
		}
		//先将选中画面设为不可见
		sGlobal->optionLayer->getChildByTag(3)->setVisible(false);
		sGlobal->optionLayer->getChildByTag(4)->setVisible(false);
		//重置选中标记
		sGlobal->xuanz=false;
		//重置ai状态
		sGlobal->heroAITag=aiNone;
		//去掉自动寻路标记
		sGlobal->optionLayer->getChildByTag(6)->setVisible(false);
		
		sGlobal->gameLayer->getChildByTag(100)->removeAllChildren();
		
		//停止所有动作
		sGlobal->hero->stopAllActions();
		sGlobal->hero->getChildByTag(1)->stopAllActions();
		//sGlobal->_heroAI->setAITag(aiNone);
		//重置目标标记
		if(sGlobal->xuanzTag>-1){
		//被选中则先清除上一次的目标
			((Node *)(sGlobal->_enemys ->getObjectAtIndex (sGlobal->xuanzTag)))->getChildByTag(4)->setVisible(false);
			sGlobal->xuanzTag=-1;
		}

		
		//遍历所有英雄和怪,是否触摸到了他,可以用arry遍历,
		//sGlobal->_enemys;
		for (unsigned int i = 0; i <sGlobal->_enemys->count(); ++i) 
		{
			Enemy* enemy=(Enemy*)sGlobal->_enemys->objectAtIndex(i);
			//Rect rect = Rect(enemy->getPosition.x-enemy->getContentSize().width/2, enemy->getPosition.y-enemy->getContentSize().height/2,enemy->getPosition.x+enemy->getContentSize().width/2,enemy->getPosition.y+enemy->getContentSize().height/2);
			//log("xiabian = %f, y = %f",enemy->getPositionX(),enemy->getPositionY());
			// enemy->getPosition;
			//if((enemy->getPositionX()-enemy->getChildByTag(1)->getContentSize().width/2)>p.x&&(enemy->getPositionX()+enemy->getChildByTag(1)->getContentSize().width/2)<p.x&&(enemy->getPositionY()+enemy->getChildByTag(1)->getContentSize().height/2)>p.y&&(enemy->getPositionY()-enemy->getChildByTag(1)->getContentSize().height/2)<p.y)
			
			//将坐标系换到世界坐标系;
			Point dian=sGlobal->gameLayer->convertToWorldSpace (Point(enemy->getPositionX(),enemy->getPositionY()));
			if((dian.x-30)<p.x&&(dian.x+30)>p.x&&(dian.y-40)<p.y&&(dian.y+40)>p.y)
			{
				//log("zhixingle************************************");
				enemy->getChildByTag(4)->setVisible(true);
				//设置选中画面可见
				sGlobal->optionLayer->getChildByTag(3)->setVisible(true);
				sGlobal->optionLayer->getChildByTag(4)->setVisible(true);
				//保存选中标记
				sGlobal->xuanz=true;
				//保存选中tag
				sGlobal->xuanzTag=i;
				//更改选中画面的血量
				((ProgressTimer *)sGlobal->optionLayer->getChildByTag(4)->getChildByTag(3))->setPercentage((float)((Enemy*)enemy)->xue*5);
				//return true;
			}
		}
		return true;
	};

	//触摸滑动
	listener1->onTouchMoved = [](Touch* touch, Event* event){  
		// 获取事件所绑定的 target 
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		// 获取当前点击点所在相对按钮的位置坐标
		Point p = target->convertToNodeSpace(touch->getLocation());

		// 点击范围判断检测,滑动只响应方向盘
		if(sGlobal->optionLayer->getChildByTag(2)->getBoundingBox().containsPoint(p)){
			//设置触摸点位置
			sGlobal->optionLayer->getChildByTag(5)->setPosition(p);
			//获得方向键的位置
			Point pianyi=sGlobal->optionLayer->getChildByTag(2)->getPosition();
			// 触摸点在控制点右边或右边
			if (abs(p.x-pianyi.x)>abs(p.y-pianyi.y)) {
				if((p.x-pianyi.x)>0){
					if(sGlobal->hero->famgx!=kRight){
						//停止所有动画
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//移动的tag为1,停止移动动作
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
						//开始新的动画
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
						sGlobal->hero->move(kRight);
					}
					
				}else{
					//左边
					if(sGlobal->hero->famgx!=kLeft){
						//停止所有动画
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//移动的tag为1,停止移动动作
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aLeft))); 
						sGlobal->hero->move(kLeft);
					}
				}
			} else {
				if((p.y-pianyi.y)>0){
					//上边
					if(sGlobal->hero->famgx!=kUp){
						//停止所有动画
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//移动的tag为1,停止移动动作
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
					// log("shangbian = %f, y = %f",p.x,p.y);
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aUp))); 
						sGlobal->hero->move(kUp);
					}
				}else{
					//下边
					if(sGlobal->hero->famgx!=kDown){
						//停止所有动画
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//移动的tag为1,停止移动动作
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aDown)));  
						sGlobal->hero->move(kDown);
					}
				}
			}
		}
	};  

	//触摸停止
	listener1->onTouchEnded = [=](Touch* touch, Event* event){  
		//如果不是opeionlayer层响应的,不需要操作hero
		if(xiangy){
			//停止所有动画
			sGlobal->hero->getChildByTag(1)->stopAllActions();
			//移动的tag为1,停止移动动作
			sGlobal->hero->stopActionByTag(1);
			sGlobal->hero->isHeroMoving=false;
			//设置最后的朝向
			sGlobal->hero->setFaceDirection(sGlobal->hero->famgx);
			//触摸点不可见
			sGlobal->optionLayer->getChildByTag(5)->setVisible(false);
		}

		//任何情况下初始化
		xiangy=false;
	};  

	//添加事件监听器到事件分发器,方向键
	//SceneGraphPriority会自动根据显示层来分发,而FixedPriority 需要手动指定
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sGlobal->optionLayer);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),sGlobal->gameLayer);

}