#ifndef __HERO_AI_H__
#define __HERO_AI_H__
#include "MTGame.h"
using namespace cocos2d;

class ditNode;
//英雄类ai
class HeroAI :public cocos2d::Object
	
{

public:
	HeroAI(void);
	~HeroAI(void);
	bool init();
	//ai的状态
	//AITag aiTag;
	
	void start();
	//静态方法，用于创建
	static HeroAI *createHeroAI();
	//A*算法
	void findRoute();
	//迭代个数组出来
	void vecPathArray(ditNode* d);
	//算法节点方法
	ditNode* newDituNode(ditNode* p,Point p1);
	//重写hero的moveto方法
	void heroMoveTo();
	//回调方法
	void onMoveToDone(Node *_Target);
};
#endif

