#include "HeroAI.h"
using namespace cocos2d;
using namespace std;
//英雄AI
//先直接往过移动,如果碰撞再找路,在找路的后期再移动
//如果近到直接能打了,但是子弹被挡了..就不行了
//地图55宽,30高
//根据子弹射程,舍去了7个点
//坐标系变换经验公式(原始y是反的)
//使用batchnode做标志点好一次删除sGlobal->gameLayer->addChild(BatchNode,1,100);



// 寻路的路径数组  
shared_ptr<Vector<ditNode*>> vecPath=make_shared<Vector<ditNode*>>(); 
// close表
shared_ptr<Vector<ditNode*>> vecClose=make_shared<Vector<ditNode*>>();  
// open表
shared_ptr<Vector<ditNode*>> vecOpen=make_shared<Vector<ditNode*>>();  
//最小的值,临时存放nh+ng
//int min=0;

//主类开始

HeroAI::HeroAI(void)
{
	//单类里面的,所以hero也成了单类了
	sGlobal->_heroAI=this;
	//aiTag=aiNone;
}

HeroAI::~HeroAI(void)
{
}
//创建方法并且自动管理
HeroAI *HeroAI::createHeroAI(){
	HeroAI *_heroAI=new HeroAI();
	//调用init方法
	if(_heroAI&&_heroAI->init()){
		//将实例放入自动池，由系统控制他的生命周期
		_heroAI->autorelease();
		return _heroAI;
	}
	CC_SAFE_DELETE(_heroAI);
	return NULL;
}

//初始化方法
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

	//如果AI没有在运行状态
	if(sGlobal->heroAITag==aiNone){
		//log("******");
		sGlobal->heroAITag=aiFite;
		sGlobal->hero->heroFight();
		//this->findRoute();
	}
}

void HeroAI::findRoute(){
	//创建标志防止被多次调用,失败
	//sGlobal->heroAITag!=aiMove;
	//[1].创建各种数组
	//log("*******************");
	vecPath->clear();
	vecOpen->clear();
	vecClose->clear();
	//[2].将墙\怪\hero的坐标存到close表里
	//将所有墙的位置存到close表里
	//地图x轴55个
	for (int i = 0; i < 55; i++)
	{
		//地图y轴30个
		for (int r = 0; r < 30; r++)
		{
			//检查Point(i,r)的wall图层是否为0
			int targetTileGID = sGlobal->gameLayer->getWallLayer()->getTileGIDAt(Point(i,r));
			//id不为0石墙
			if (targetTileGID) {
				ditNode *d=ditNode::createDitNode();
				d->x=i;
				d->y=r;
				//加入表中
				vecClose->pushBack(d);
			}
		}
	}
	//存怪的坐标,但是被选中的怪的坐标不存
	for(int i=0;i<sGlobal->_enemys->count();++i){
		//怪没被选中
		if (i!=sGlobal->xuanzTag)
		{
			Node *enemy=(Node*)sGlobal->_enemys->getObjectAtIndex(i);
			//相对gameLayer的坐标
			Point p2=sGlobal->gameLayer->tileCoordForPosition(sGlobal->optionLayer->convertToWorldSpace(enemy->getPosition()));
			ditNode *d10=ditNode::createDitNode();
			d10->x=p2.x;
			d10->y=p2.y;
			//加入表中
			vecClose->pushBack(d10);
			//四周也要加入表中
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
	//将hero的位置存进去
	Point p3=sGlobal->gameLayer->tileCoordForPosition(sGlobal->optionLayer->convertToWorldSpace(sGlobal->hero->getPosition()));
	ditNode *d=ditNode::createDitNode();
	d->x=p3.x;
	d->y=p3.y;
	//加入表中,统一在方法中加入所有父类
	//vecClose->pushBack(d);

	//[3].开始执行
	//从一个节点只能走上下左右四个方向,走斜线有可能被挡住
	//由hero节点算出四个节点加入vecOpen表
	//目标值
	Point p1=sGlobal->gameLayer->tileCoordForPosition(sGlobal->optionLayer->convertToWorldSpace(((Node*)sGlobal->_enemys->getObjectAtIndex(sGlobal->xuanzTag ))->getPosition()));
	//Point p2=Point(p1.x,30-p1.y);
	//调用方法成功了,将最后得到的路径保存进数组

	ditNode * d5=newDituNode(d, p1);

	//用目标点的父节点迭代出个数组来,
	vecPathArray(d5);
	//定义一个临时数组
	//shared_ptr<Vector<Point>> _temporary1=make_shared<Vector<Point>>(); 
	//把路径显示出来试试,重新开始时要去掉,变换状态也要去掉
	//sGlobal->gameLayer->removeChildByTag(97);

	ditNode *d6=ditNode::createDitNode();
	for (ssize_t iter =0; iter != vecPath->size() ; ++iter)
	{
		d6=	vecPath->at(iter);
		Sprite *sp=Sprite::createWithTexture(((SpriteBatchNode* )sGlobal->gameLayer->getChildByTag(100))->getTexture());
		//坐标系变换
		sp->setPosition(Point(d6->x*16-16,(28-d6->y)*16));
		((SpriteBatchNode* )sGlobal->gameLayer->getChildByTag(100))->addChild(sp);
	}
	//sGlobal->gameLayer->addChild(BatchNode,1,100);
	//自动寻路这几个字
	sGlobal->optionLayer->getChildByTag(6)->setVisible(true);


	//去除不必要的坐标
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
	//定义一个临时数组
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
	//删除临时数组内的所有
	if (!_temporary1->empty())
	{
		for (ssize_t iter =2; iter != _temporary1->size() ; ++iter)
		{
			vecPath->eraseObject(_temporary1->at(iter));
		}
	}
	//调用moveto的重载方法
	this->heroMoveTo();
	//最后调用打怪方法
	//sGlobal->hero->heroFight();
}
//由一个节点,分出四个节点,并且比较所有的open表,把小的节点返回
ditNode* HeroAI::newDituNode(ditNode* d,Point p1){
	//临时表,用于存储元素
	shared_ptr<Vector<ditNode*>> _temporary=make_shared<Vector<ditNode*>>(); 
	//用于存储要删的元素
	shared_ptr<Vector<ditNode*>> _temporary2=make_shared<Vector<ditNode*>>(); 
	//log("ddddd  %d   %d",d->x,d->y);


	do
	{
		//将传入坐标的周围四个坐标判断是否合法
		ditNode *d1=ditNode::createDitNode();
		d1->x=d->x+1;
		d1->y=d->y;
		d1->nH=d->nH+1;
		d1->nG=abs(d1->x-p1.x)+abs(d1->y-p1.y);
		d1->pParent=d;

		//如果点超出范围,不合法,与父节点相同也不合法
		if (d1->x>0&&d1->x<55&&d1->y>0&&d1->y<30)
		{
			//合法者加入临时表
			_temporary->pushBack(d1);
			//如果达到终点返回
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
			//合法者加入临时表
			_temporary->pushBack(d2);
			//如果达到终点返回
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
			//合法者加入临时表
			_temporary->pushBack(d3);
			//如果达到终点返回
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
			//合法者加入临时表
			_temporary->pushBack(d4);
			//如果达到终点返回
			if(d4->nG==0){
				return d4;
			}
		}

		//父节点加入close表,从open表删除
		vecClose->pushBack(d);
		vecOpen->eraseObject(d);
		//log("11111111111111111");
		//遍历临时表,和close表


		//遍历临时表
		ditNode  *ditnod1;
		for (ssize_t iter =0; iter != _temporary->size() ; ++iter)
		{
			ditnod1= _temporary->at(iter);

			//遍历close表
			ditNode  *ditnod2;
			for (ssize_t iter1 =0; iter1 != vecClose->size() ; ++iter1)
			{
				//如果表内有就删除临时表对象
				ditnod2= vecClose->at(iter1);
				if (ditnod2->x==ditnod1->x&&ditnod2->y==ditnod1->y)
				{
					//加入到表2出去删,这里直接删错了
					_temporary2->pushBack(ditnod1);
				}
			}
		}

		//根据表2删除临时表
		if(!_temporary2->empty()){
			ditNode  *ditnod1;
			for (ssize_t iter =0; iter != _temporary2->size() ; ++iter)
			{
				ditnod1= _temporary2->at(iter);
				_temporary->eraseObject(ditnod1);
			}
		}
		//初始化表2
		_temporary2->clear();
		//和open表比较,不同的话就加入open表
		if (!_temporary->empty())
		{
			//遍历临时表
			ditNode  *ditnod1;
			for (ssize_t iter =0; iter != _temporary->size() ; ++iter)
			{
				ditnod1= _temporary->at(iter);
				//遍历open表
				ditNode  *ditnod2;
				for (ssize_t iter =0; iter != vecOpen->size() ; ++iter)
				{
					//如果表内有就比较nh,更改父节点,删除原节点
					ditnod2= vecOpen->at(iter);
					if (ditnod2->x==ditnod1->x&&ditnod2->y==ditnod1->y)
					{
						_temporary2->pushBack(ditnod2);
						if((ditnod2->nH)>(ditnod1->nH)){
							//删除原节点
							//vecOpen->eraseObject(ditnod2);
						}else{
							//更改父节点,删除原节点
							ditnod1->nH=ditnod2->nH;
							ditnod1->pParent=ditnod2->pParent;
							//vecOpen->eraseObject(ditnod2);
						}
					}
				}
				//加入open表
				vecOpen->pushBack(ditnod1);

				//log("***%d   %d",ditnod1->x,ditnod1->y);
			}
		}

		//根据表2删除open表
		if(!_temporary2->empty()){
			ditNode  *ditnod1;
			for (ssize_t iter =0; iter != _temporary2->size() ; ++iter)
			{
				ditnod1= _temporary2->at(iter);
				vecOpen->eraseObject(ditnod1);
			}
		}
		///log("33333333333333");
		//遍历整个open表,取ng+nh最小的那个节点
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
		//赋值执行下一次
		d=ditnod3;
		_temporary->clear();
		_temporary2->clear();
	} while (true);
}

//最后迭代个数组出来
void HeroAI::vecPathArray(ditNode* d){
	//加入数组
	vecPath->pushBack(d);

	//如果没到起始点,调用自己
	if(d->nH>1){
		vecPathArray(d->pParent);
	}

}

void HeroAI::heroMoveTo(){
	//设置英雄移动状态
	sGlobal->hero->isHeroMoving=true;
	//获得要移动到的点d6->x*16-16,(28-d6->y)*16
	Point xiaos=Point(vecPath->back()->x*16-16,(29-vecPath->back()->y)*16);
	Point chazhi=xiaos-sGlobal->hero->getPosition();
	float time=sqrt(chazhi.x*chazhi.x+chazhi.y*chazhi.y)*0.25/8;
	Action *action = Sequence::create(MoveTo::create(time, xiaos),CallFuncN::create(CC_CALLBACK_1(HeroAI::onMoveToDone,this)), NULL);
	action->setTag(2);
	sGlobal->hero->runAction(action);

	//播放动画神马的
	if (abs(chazhi.x)>abs(chazhi.y)) {
		if((chazhi.x)>0){
			sGlobal->hero->getChildByTag(1)->runAction(CCRepeatForever::create(sAnimationMgr->createAnimate(aRight)));
			//设置方向
			sGlobal->hero->famgx=kRight;
		}else{
			//左边
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
	//调用方法停止动画
	sGlobal->hero->getChildByTag(1)->stopAllActions();
	//改变移动状态
	sGlobal->hero->isHeroMoving=false;
	//如果数组不为空,删除最后一个,再次move
	if (vecPath->size()>1 )
	{
		//删除最后一个
		vecPath->erase(vecPath->end()-1);
		heroMoveTo();
	}else{
		//执行攻击方法
		sGlobal->hero->heroFight();
		vecPath->clear();
	}
}