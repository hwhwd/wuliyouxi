#include "HeroAI.h"
using namespace cocos2d;
using namespace std;
//Ӣ��AI
//��ֱ�������ƶ�,�����ײ����·,����·�ĺ������ƶ�
//�������ֱ���ܴ���,�����ӵ�������..�Ͳ�����
//��ͼ55��,30��
//�����ӵ����,��ȥ��7����
//����ϵ�任���鹫ʽ(ԭʼy�Ƿ���)
//ʹ��batchnode����־���һ��ɾ��sGlobal->gameLayer->addChild(BatchNode,1,100);



// Ѱ·��·������  
shared_ptr<Vector<ditNode*>> vecPath=make_shared<Vector<ditNode*>>(); 
// close��
shared_ptr<Vector<ditNode*>> vecClose=make_shared<Vector<ditNode*>>();  
// open��
shared_ptr<Vector<ditNode*>> vecOpen=make_shared<Vector<ditNode*>>();  
//��С��ֵ,��ʱ���nh+ng
//int min=0;

//���࿪ʼ

HeroAI::HeroAI(void)
{
	//���������,����heroҲ���˵�����
	sGlobal->_heroAI=this;
	//aiTag=aiNone;
}

HeroAI::~HeroAI(void)
{
}
//�������������Զ�����
HeroAI *HeroAI::createHeroAI(){
	HeroAI *_heroAI=new HeroAI();
	//����init����
	if(_heroAI&&_heroAI->init()){
		//��ʵ�������Զ��أ���ϵͳ����������������
		_heroAI->autorelease();
		return _heroAI;
	}
	CC_SAFE_DELETE(_heroAI);
	return NULL;
}

//��ʼ������
bool HeroAI::init()
{
	bool ret = false;
	//mgx=kDown;
	do{
		//aiTag=aiNone;
		ret = true;
	} while (0);
	return ret;
}

void HeroAI::start(){

	//���AIû��������״̬
	if(sGlobal->heroAITag==aiNone){
		//log("******");
		sGlobal->heroAITag=aiFite;
		sGlobal->hero->heroFight();
		//this->findRoute();
	}
}

void HeroAI::findRoute(){
	//������־��ֹ����ε���,ʧ��
	//sGlobal->heroAITag!=aiMove;
	//[1].������������
	//log("*******************");
	vecPath->clear();
	vecOpen->clear();
	vecClose->clear();
	//[2].��ǽ\��\hero������浽close����
	//������ǽ��λ�ô浽close����
	//��ͼx��55��
	for (int i = 0; i < 55; i++)
	{
		//��ͼy��30��
		for (int r = 0; r < 30; r++)
		{
			//���Point(i,r)��wallͼ���Ƿ�Ϊ0
			int targetTileGID = sGlobal->gameLayer->getWallLayer()->getTileGIDAt(Point(i,r));
			//id��Ϊ0ʯǽ
			if (targetTileGID) {
				ditNode *d=ditNode::createDitNode();
				d->x=i;
				d->y=r;
				//�������
				vecClose->pushBack(d);
			}
		}
	}
	//��ֵ�����,���Ǳ�ѡ�еĹֵ����겻��
	for(int i=0;i<sGlobal->_enemys->count();++i){
		//��û��ѡ��
		if (i!=sGlobal->xuanzTag)
		{
			Node *enemy=(Node*)sGlobal->_enemys->getObjectAtIndex(i);
			//���gameLayer������
			Point p2=sGlobal->gameLayer->tileCoordForPosition(sGlobal->optionLayer->convertToWorldSpace(enemy->getPosition()));
			ditNode *d10=ditNode::createDitNode();
			d10->x=p2.x;
			d10->y=p2.y;
			//�������
			vecClose->pushBack(d10);
			//����ҲҪ�������
			ditNode *d11=ditNode::createDitNode();
			d11->x=p2.x+1;
			d11->y=p2.y;
			vecClose->pushBack(d11);
			ditNode *d12=ditNode::createDitNode();
			d12->x=p2.x+1;
			d12->y=p2.y+1;
			vecClose->pushBack(d12);
			ditNode *d13=ditNode::createDitNode();
			d13->x=p2.x;
			d13->y=p2.y+1;
			vecClose->pushBack(d13);
			ditNode *d14=ditNode::createDitNode();
			d14->x=p2.x-1;
			d14->y=p2.y;
			vecClose->pushBack(d14);
			ditNode *d15=ditNode::createDitNode();
			d15->x=p2.x-1;
			d15->y=p2.y-1;
			vecClose->pushBack(d15);
			ditNode *d16=ditNode::createDitNode();
			d16->x=p2.x;
			d16->y=p2.y-1;
			vecClose->pushBack(d16);
			ditNode *d17=ditNode::createDitNode();
			d17->x=p2.x+1;
			d17->y=p2.y-1;
			vecClose->pushBack(d17);
			ditNode *d18=ditNode::createDitNode();
			d18->x=p2.x-1;
			d18->y=p2.y+1;
			vecClose->pushBack(d18);

		}
	}
	//��hero��λ�ô��ȥ
	Point p3=sGlobal->gameLayer->tileCoordForPosition(sGlobal->optionLayer->convertToWorldSpace(sGlobal->hero->getPosition()));
	ditNode *d=ditNode::createDitNode();
	d->x=p3.x;
	d->y=p3.y;
	//�������,ͳһ�ڷ����м������и���
	//vecClose->pushBack(d);

	//[3].��ʼִ��
	//��һ���ڵ�ֻ�������������ĸ�����,��б���п��ܱ���ס
	//��hero�ڵ�����ĸ��ڵ����vecOpen��
	//Ŀ��ֵ
	Point p1=sGlobal->gameLayer->tileCoordForPosition(sGlobal->optionLayer->convertToWorldSpace(((Node*)sGlobal->_enemys->getObjectAtIndex(sGlobal->xuanzTag ))->getPosition()));
	//Point p2=Point(p1.x,30-p1.y);
	//���÷����ɹ���,�����õ���·�����������

	ditNode * d5=newDituNode(d, p1);

	//��Ŀ���ĸ��ڵ��������������,
	vecPathArray(d5);
	//����һ����ʱ����
	//shared_ptr<Vector<Point>> _temporary1=make_shared<Vector<Point>>(); 
	//��·����ʾ��������,���¿�ʼʱҪȥ��,�任״̬ҲҪȥ��
	//sGlobal->gameLayer->removeChildByTag(97);

	ditNode *d6=ditNode::createDitNode();
	for (ssize_t iter =0; iter != vecPath->size() ; ++iter)
	{
		d6=	vecPath->at(iter);
		Sprite *sp=Sprite::createWithTexture(((SpriteBatchNode* )sGlobal->gameLayer->getChildByTag(100))->getTexture());
		//����ϵ�任
		sp->setPosition(Point(d6->x*16-16,(28-d6->y)*16));
		((SpriteBatchNode* )sGlobal->gameLayer->getChildByTag(100))->addChild(sp);
	}
	//sGlobal->gameLayer->addChild(BatchNode,1,100);
	//�Զ�Ѱ·�⼸����
	sGlobal->optionLayer->getChildByTag(6)->setVisible(true);


	//ȥ������Ҫ������
	if (vecPath->size()>10)
	{
		vecPath->erase(6);
		vecPath->erase(5);
		vecPath->erase(4);
		vecPath->erase(3);
		vecPath->erase(2);
		vecPath->erase(1);
		vecPath->erase(0);
	}else{
		this->heroMoveTo();
		return;
	}
	//����һ����ʱ����
	shared_ptr<Vector<ditNode*>> _temporary1=make_shared<Vector<ditNode*>>(); 
	ditNode *d7=ditNode::createDitNode();
	ditNode *d8=ditNode::createDitNode();
	ditNode *d9=ditNode::createDitNode();
	for (ssize_t iter =2; iter != vecPath->size() ; ++iter)
	{
		d7=	vecPath->at(iter-2);
		d8=	vecPath->at(iter-1);
		d9=	vecPath->at(iter);
		if ((d7->x==d8->x&&d9->x==d8->x)||(d7->y==d8->y&&d9->y==d8->y))
		{
			_temporary1->pushBack(d8);
		}
	}
	//ɾ����ʱ�����ڵ�����
	if (!_temporary1->empty())
	{
		for (ssize_t iter =2; iter != _temporary1->size() ; ++iter)
		{
			vecPath->eraseObject(_temporary1->at(iter));
		}
	}
	//����moveto�����ط���
	this->heroMoveTo();
	//�����ô�ַ���
	//sGlobal->hero->heroFight();
}
//��һ���ڵ�,�ֳ��ĸ��ڵ�,���ұȽ����е�open��,��С�Ľڵ㷵��
ditNode* HeroAI::newDituNode(ditNode* d,Point p1){
	//��ʱ��,���ڴ洢Ԫ��
	shared_ptr<Vector<ditNode*>> _temporary=make_shared<Vector<ditNode*>>(); 
	//���ڴ洢Ҫɾ��Ԫ��
	shared_ptr<Vector<ditNode*>> _temporary2=make_shared<Vector<ditNode*>>(); 
	//log("ddddd  %d   %d",d->x,d->y);


	do
	{
		//�������������Χ�ĸ������ж��Ƿ�Ϸ�
		ditNode *d1=ditNode::createDitNode();
		d1->x=d->x+1;
		d1->y=d->y;
		d1->nH=d->nH+1;
		d1->nG=abs(d1->x-p1.x)+abs(d1->y-p1.y);
		d1->pParent=d;

		//����㳬����Χ,���Ϸ�,�븸�ڵ���ͬҲ���Ϸ�
		if (d1->x>0&&d1->x<55&&d1->y>0&&d1->y<30)
		{
			//�Ϸ��߼�����ʱ��
			_temporary->pushBack(d1);
			//����ﵽ�յ㷵��
			if(d1->nG==0){
				return d1;
			}
		}
		ditNode *d2=ditNode::createDitNode();
		d2->x=d->x-1;
		d2->y=d->y;
		d2->nH=d->nH+1;
		d2->nG=abs(d2->x-p1.x)+abs(d2->y-p1.y);
		d2->pParent=d;
		if (d2->x>0&&d2->x<55&&d2->y>0&&d2->y<30)
		{
			//�Ϸ��߼�����ʱ��
			_temporary->pushBack(d2);
			//����ﵽ�յ㷵��
			if(d2->nG==0){
				return d2;
			}
		}
		ditNode *d3=ditNode::createDitNode();
		d3->x=d->x;
		d3->y=d->y+1;
		d3->nH=d->nH+1;
		d3->nG=abs(d3->x-p1.x)+abs(d3->y-p1.y);
		d3->pParent=d;
		if (d3->x>0&&d3->x<55&&d3->y>0&&d3->y<30)
		{
			//�Ϸ��߼�����ʱ��
			_temporary->pushBack(d3);
			//����ﵽ�յ㷵��
			if(d3->nG==0){
				return d3;
			}
		}
		ditNode *d4=ditNode::createDitNode();
		d4->x=d->x;
		d4->y=d->y-1;
		d4->nH=d->nH+1;
		d4->nG=abs(d4->x-p1.x)+abs(d4->y-p1.y);
		d4->pParent=d;
		if (d4->x>0&&d4->x<55&&d4->y>0&&d4->y<30)
		{
			//�Ϸ��߼�����ʱ��
			_temporary->pushBack(d4);
			//����ﵽ�յ㷵��
			if(d4->nG==0){
				return d4;
			}
		}

		//���ڵ����close��,��open��ɾ��
		vecClose->pushBack(d);
		vecOpen->eraseObject(d);
		//log("11111111111111111");
		//������ʱ��,��close��


		//������ʱ��
		ditNode  *ditnod1;
		for (ssize_t iter =0; iter != _temporary->size() ; ++iter)
		{
			ditnod1= _temporary->at(iter);

			//����close��
			ditNode  *ditnod2;
			for (ssize_t iter1 =0; iter1 != vecClose->size() ; ++iter1)
			{
				//��������о�ɾ����ʱ�����
				ditnod2= vecClose->at(iter1);
				if (ditnod2->x==ditnod1->x&&ditnod2->y==ditnod1->y)
				{
					//���뵽��2��ȥɾ,����ֱ��ɾ����
					_temporary2->pushBack(ditnod1);
				}
			}
		}

		//���ݱ�2ɾ����ʱ��
		if(!_temporary2->empty()){
			ditNode  *ditnod1;
			for (ssize_t iter =0; iter != _temporary2->size() ; ++iter)
			{
				ditnod1= _temporary2->at(iter);
				_temporary->eraseObject(ditnod1);
			}
		}
		//��ʼ����2
		_temporary2->clear();
		//��open��Ƚ�,��ͬ�Ļ��ͼ���open��
		if (!_temporary->empty())
		{
			//������ʱ��
			ditNode  *ditnod1;
			for (ssize_t iter =0; iter != _temporary->size() ; ++iter)
			{
				ditnod1= _temporary->at(iter);
				//����open��
				ditNode  *ditnod2;
				for (ssize_t iter =0; iter != vecOpen->size() ; ++iter)
				{
					//��������оͱȽ�nh,���ĸ��ڵ�,ɾ��ԭ�ڵ�
					ditnod2= vecOpen->at(iter);
					if (ditnod2->x==ditnod1->x&&ditnod2->y==ditnod1->y)
					{
						_temporary2->pushBack(ditnod2);
						if((ditnod2->nH)>(ditnod1->nH)){
							//ɾ��ԭ�ڵ�
							//vecOpen->eraseObject(ditnod2);
						}else{
							//���ĸ��ڵ�,ɾ��ԭ�ڵ�
							ditnod1->nH=ditnod2->nH;
							ditnod1->pParent=ditnod2->pParent;
							//vecOpen->eraseObject(ditnod2);
						}
					}
				}
				//����open��
				vecOpen->pushBack(ditnod1);

				//log("***%d   %d",ditnod1->x,ditnod1->y);
			}
		}

		//���ݱ�2ɾ��open��
		if(!_temporary2->empty()){
			ditNode  *ditnod1;
			for (ssize_t iter =0; iter != _temporary2->size() ; ++iter)
			{
				ditnod1= _temporary2->at(iter);
				vecOpen->eraseObject(ditnod1);
			}
		}
		///log("33333333333333");
		//��������open��,ȡng+nh��С���Ǹ��ڵ�
		ditNode  *ditnod3=NULL;
		ditNode  *ditnod4=NULL;
		for (ssize_t iter =0; iter != vecOpen->size() ; ++iter){
			ditnod4= vecOpen->at(iter);
			if (iter==0)
			{
				ditnod3=ditnod4;
			}
			if ((ditnod4->nG+ditnod4->nH)<(ditnod3->nG+ditnod3->nH))
			{
				ditnod3=ditnod4;
			}
		}
		//��ִֵ����һ��
		d=ditnod3;
		_temporary->clear();
		_temporary2->clear();
	} while (true);
}

//���������������
void HeroAI::vecPathArray(ditNode* d){
	//��������
	vecPath->pushBack(d);

	//���û����ʼ��,�����Լ�
	if(d->nH>1){
		vecPathArray(d->pParent);
	}

}

void HeroAI::heroMoveTo(){
	//����Ӣ���ƶ�״̬
	sGlobal->hero->isHeroMoving=true;
	//���Ҫ�ƶ����ĵ�d6->x*16-16,(28-d6->y)*16
	Point xiaos=Point(vecPath->back()->x*16-16,(29-vecPath->back()->y)*16);
	Point chazhi=xiaos-sGlobal->hero->getPosition();
	float time=sqrt(chazhi.x*chazhi.x+chazhi.y*chazhi.y)*0.25/8;
	Action *action = Sequence::create(MoveTo::create(time, xiaos),CallFuncN::create(CC_CALLBACK_1(HeroAI::onMoveToDone,this)), NULL);
	action->setTag(2);
	sGlobal->hero->runAction(action);

	//���Ŷ��������
	if (abs(chazhi.x)>abs(chazhi.y)) {
		if((chazhi.x)>0){
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
			//���÷���
			sGlobal->hero->famgx=kRight;
		}else{
			//���
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aLeft))); 
			sGlobal->hero->famgx=kLeft;
		}
	} else {
		if((chazhi.y)>0){
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aUp))); 
			sGlobal->hero->famgx=kUp;
		}else{

			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aDown)));  
			sGlobal->hero->famgx=kDown;
		}
	}

}

void HeroAI::onMoveToDone(Node *_Target){
	//���÷���ֹͣ����
	sGlobal->hero->getChildByTag(1)->stopAllActions();
	//�ı��ƶ�״̬
	sGlobal->hero->isHeroMoving=false;
	//������鲻Ϊ��,ɾ�����һ��,�ٴ�move
	if (vecPath->size()>1 )
	{
		//ɾ�����һ��
		vecPath->erase(vecPath->end()-1);
		heroMoveTo();
	}else{
		//ִ�й�������
		sGlobal->hero->heroFight();
		vecPath->clear();
	}
}