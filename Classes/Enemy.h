#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "MTGame.h"
using namespace cocos2d;
//敌人类
class Enemy :public cocos2d::Node
	
{

public:
	Enemy(void);
	~Enemy(void);
	//静态方法，用于创建
	static Enemy *enemyWithLayer();
    //初始化
	bool init();
	//向指定方向移动一格
	void move(HeroDirection direction);
	//移动完成后回调函数
	void onMoveDone(Node *_Target);
	//设置方向
	void setFaceDirection(Enemy* enemy,HeroDirection direction);
	


	//变量勇士的精灵
	Sprite *_enemySprit;
	//是否在移动状态
	bool isHeroMoving;
	//保存目标坐标
	Point targetPosition;
	//保存enemy方向
	HeroDirection famgx;
	//临时保存目标的Tilemap坐标
	Point targetTileCoord;
	//血量
	int xue;
	
};
#endif

