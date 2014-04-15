
#include "GameScene.h"

//������
//
//��������,Ӧ��������
//
//�޶�㴥��
//�޴���ʱmove����



//�Ƿ��Ƿ������Ӧ��,Ϊ�˸�onTouchEndedѡ��,����Ǵ��������ط�����,�Ͳ���Ҫ����hero�ķ����ֹͣ����
bool xiangy=false;
//Gamelayer���ƶ�������


GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}
//��ʼ��
bool GameScene::init()
{
	//����
	bool ret = false;
	do {
		CC_BREAK_IF(!Scene::init());

		//��ö�㴥�����
		//setTouchEnabled(true);

		//��ʼ��AI
		sGlobal->_heroAI= HeroAI::createHeroAI();
		//���������
		auto layer1 = LayerGradient::create(Color4B(187,255,255,255), Color4B(139,131,120,255));
		 addChild(layer1, 0, 1);

		// ��Ϸ���ʼ��
		//GameLayer *_gameLayer = GameLayer::create();
		Scene * _gameLayer=GameLayer::createScene();
		this->addChild(_gameLayer, 10);

		OptionLayer *_optionLayer=OptionLayer::create();
		//���Ʋ�������
		this->addChild(_optionLayer,15);
		//���ô�������
		Touches();

		ret = true;
	} while (0);

	return ret;
}
//����һ���µ�sceneʵ��
Scene *GameScene::palyNewGame(){
	GameScene *scene=NULL;
	do{
		//�汾�޸ĺ��
		scene=GameScene::create();
		CC_BREAK_IF(!scene);

	}while(0);
	return scene;
}


//������Ӧ����
void GameScene::Touches(){
	// ����һ���¼������� OneByOne Ϊ���㴥��
	auto listener1 = EventListenerTouchOneByOne::create();
	// �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
	listener1->setSwallowTouches(true);
	//��ʼ����¼�,��������falseʱ,������ִ��һ��Ŀ������һ��,���Ի�����Ŀ�������,ͨ����һ������������в�ĵ��
	//��Ϊ�ҰѼ����¼�ָ����layer,���Եõ������������layer��,���ڰ�ť��˵ûɶ����,����ֻ������true;
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		//do{
		// ��ȡ�¼����󶨵Ķ���,������˰�ť�Ļ��ͺ�����,���ڰ󶨵���layer
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//CCLOG("ceshi");
		// ��ȡ��ǰ�����������԰�ť��λ��opgl����
		Point p = target->convertToNodeSpace(touch->getLocation());
		//��ӡ��������Ļ����
		//log("DIANJIx = %f, y = %f",p.x,p.y);


		//������ť
		//ͨ��ѡ�б�����ж���ʾ�İ�ť�Ƿ����,������ڵĻ��ٵ���͹���
		if(sGlobal->xuanz){
			//����ľ�������
			Rect rect=sGlobal->optionLayer->getChildByTag(3)->getBoundingBox();
			//�����������Ŀ��������
			if( rect.containsPoint(p)){
				//log("********************");
				//�����ӵ�����,����Ӣ�������ѡ�й�������
				//sGlobal->gameLayer->addBullet(sGlobal->hero->getPosition(),sGlobal->optionLayer->convertToWorldSpace(((Node*)(sGlobal->_enemys->getObjectAtIndex (sGlobal->xuanzTag)))->getPosition()));
				//sGlobal->hero->heroFight();
				sGlobal->_heroAI->start();
				return true;
			}
		}

		// �����
		//�������Ƿ��ڿ��Ʋ㷽�������Ӧ��Χ��
		//if(p.x<(pianyi.x+40)&&p.x>(pianyi.x-40)&&p.y<(pianyi.y+40)&&p.y>(pianyi.y-40)){
		if(sGlobal->optionLayer->getChildByTag(2)->getBoundingBox().containsPoint(p)){
			//���ô�����λ�úͿɼ�
			sGlobal->optionLayer->getChildByTag(5)->setPosition(p);
			sGlobal->optionLayer->getChildByTag(5)->setVisible(true);

			//��÷������λ��
			Point pianyi=sGlobal->optionLayer->getChildByTag(2)->getPosition();
			// �������ڿ��Ƶ��ұ߻��ұ�
			if (abs(p.x-pianyi.x)>abs(p.y-pianyi.y)) {
				if((p.x-pianyi.x)>0){
					//�ұ�
					//log("YOUBIANx = %f, y = %f",p.x,p.y);
					//sGlobal->hero->setPosition(Point(30,30));
					//sGlobal->hero->retain();
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));

					sGlobal->hero->move(kRight);
				}else{
					//���
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aLeft))); 
					sGlobal->hero->move(kLeft);
				}
			} else {
				if((p.y-pianyi.y)>0){
					//�ϱ�
					// log("shangbian = %f, y = %f",p.x,p.y);
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aUp))); 
					sGlobal->hero->move(kUp);
				}else{
					//�±�
					//log("xiabian = %f, y = %f",p.x,p.y);
					sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aDown)));  
					sGlobal->hero->move(kDown);
				}
			}
			//��Ӧ֮�������
			xiangy=true;
			//����true,�Ͳ��������´���
			return true;
		}
		//�Ƚ�ѡ�л�����Ϊ���ɼ�
		sGlobal->optionLayer->getChildByTag(3)->setVisible(false);
		sGlobal->optionLayer->getChildByTag(4)->setVisible(false);
		//����ѡ�б��
		sGlobal->xuanz=false;
		//����ai״̬
		sGlobal->heroAITag=aiNone;
		//ȥ���Զ�Ѱ·���
		sGlobal->optionLayer->getChildByTag(6)->setVisible(false);
		
		sGlobal->gameLayer->getChildByTag(100)->removeAllChildren();
		
		//ֹͣ���ж���
		sGlobal->hero->stopAllActions();
		sGlobal->hero->getChildByTag(1)->stopAllActions();
		//sGlobal->_heroAI->setAITag(aiNone);
		//����Ŀ����
		if(sGlobal->xuanzTag>-1){
		//��ѡ�����������һ�ε�Ŀ��
			((Node *)(sGlobal->_enemys ->getObjectAtIndex (sGlobal->xuanzTag)))->getChildByTag(4)->setVisible(false);
			sGlobal->xuanzTag=-1;
		}

		
		//��������Ӣ�ۺ͹�,�Ƿ���������,������arry����,
		//sGlobal->_enemys;
		for (unsigned int i = 0; i <sGlobal->_enemys->count(); ++i) 
		{
			Enemy* enemy=(Enemy*)sGlobal->_enemys->objectAtIndex(i);
			//Rect rect = Rect(enemy->getPosition.x-enemy->getContentSize().width/2, enemy->getPosition.y-enemy->getContentSize().height/2,enemy->getPosition.x+enemy->getContentSize().width/2,enemy->getPosition.y+enemy->getContentSize().height/2);
			//log("xiabian = %f, y = %f",enemy->getPositionX(),enemy->getPositionY());
			// enemy->getPosition;
			//if((enemy->getPositionX()-enemy->getChildByTag(1)->getContentSize().width/2)>p.x&&(enemy->getPositionX()+enemy->getChildByTag(1)->getContentSize().width/2)<p.x&&(enemy->getPositionY()+enemy->getChildByTag(1)->getContentSize().height/2)>p.y&&(enemy->getPositionY()-enemy->getChildByTag(1)->getContentSize().height/2)<p.y)
			
			//������ϵ������������ϵ;
			Point dian=sGlobal->gameLayer->convertToWorldSpace (Point(enemy->getPositionX(),enemy->getPositionY()));
			if((dian.x-30)<p.x&&(dian.x+30)>p.x&&(dian.y-40)<p.y&&(dian.y+40)>p.y)
			{
				//log("zhixingle************************************");
				enemy->getChildByTag(4)->setVisible(true);
				//����ѡ�л���ɼ�
				sGlobal->optionLayer->getChildByTag(3)->setVisible(true);
				sGlobal->optionLayer->getChildByTag(4)->setVisible(true);
				//����ѡ�б��
				sGlobal->xuanz=true;
				//����ѡ��tag
				sGlobal->xuanzTag=i;
				//����ѡ�л����Ѫ��
				((ProgressTimer *)sGlobal->optionLayer->getChildByTag(4)->getChildByTag(3))->setPercentage((float)((Enemy*)enemy)->xue*5);
				//return true;
			}
		}
		return true;
	};

	//��������
	listener1->onTouchMoved = [](Touch* touch, Event* event){  
		// ��ȡ�¼����󶨵� target 
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		// ��ȡ��ǰ�����������԰�ť��λ������
		Point p = target->convertToNodeSpace(touch->getLocation());

		// �����Χ�жϼ��,����ֻ��Ӧ������
		if(sGlobal->optionLayer->getChildByTag(2)->getBoundingBox().containsPoint(p)){
			//���ô�����λ��
			sGlobal->optionLayer->getChildByTag(5)->setPosition(p);
			//��÷������λ��
			Point pianyi=sGlobal->optionLayer->getChildByTag(2)->getPosition();
			// �������ڿ��Ƶ��ұ߻��ұ�
			if (abs(p.x-pianyi.x)>abs(p.y-pianyi.y)) {
				if((p.x-pianyi.x)>0){
					if(sGlobal->hero->famgx!=kRight){
						//ֹͣ���ж���
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//�ƶ���tagΪ1,ֹͣ�ƶ�����
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
						//��ʼ�µĶ���
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
						sGlobal->hero->move(kRight);
					}
					
				}else{
					//���
					if(sGlobal->hero->famgx!=kLeft){
						//ֹͣ���ж���
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//�ƶ���tagΪ1,ֹͣ�ƶ�����
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aLeft))); 
						sGlobal->hero->move(kLeft);
					}
				}
			} else {
				if((p.y-pianyi.y)>0){
					//�ϱ�
					if(sGlobal->hero->famgx!=kUp){
						//ֹͣ���ж���
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//�ƶ���tagΪ1,ֹͣ�ƶ�����
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
					// log("shangbian = %f, y = %f",p.x,p.y);
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aUp))); 
						sGlobal->hero->move(kUp);
					}
				}else{
					//�±�
					if(sGlobal->hero->famgx!=kDown){
						//ֹͣ���ж���
						sGlobal->hero->getChildByTag(1)->stopAllActions();
						//�ƶ���tagΪ1,ֹͣ�ƶ�����
						sGlobal->hero->stopActionByTag(1);
						sGlobal->hero->isHeroMoving=false;
						sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aDown)));  
						sGlobal->hero->move(kDown);
					}
				}
			}
		}
	};  

	//����ֹͣ
	listener1->onTouchEnded = [=](Touch* touch, Event* event){  
		//�������opeionlayer����Ӧ��,����Ҫ����hero
		if(xiangy){
			//ֹͣ���ж���
			sGlobal->hero->getChildByTag(1)->stopAllActions();
			//�ƶ���tagΪ1,ֹͣ�ƶ�����
			sGlobal->hero->stopActionByTag(1);
			sGlobal->hero->isHeroMoving=false;
			//�������ĳ���
			sGlobal->hero->setFaceDirection(sGlobal->hero->famgx);
			//�����㲻�ɼ�
			sGlobal->optionLayer->getChildByTag(5)->setVisible(false);
		}

		//�κ�����³�ʼ��
		xiangy=false;
	};  

	//����¼����������¼��ַ���,�����
	//SceneGraphPriority���Զ�������ʾ�����ַ�,��FixedPriority ��Ҫ�ֶ�ָ��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sGlobal->optionLayer);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),sGlobal->gameLayer);

}