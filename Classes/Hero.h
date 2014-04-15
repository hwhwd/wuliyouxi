#ifndef __HERO_H__
#define __HERO_H__
#include "MTGame.h"
using namespace cocos2d;
//英雄类12
class Hero :public cocos2d::Node
	
{

public:
	Hero(void);
	~Hero(void);
	//静态方法，用于创建
	static Hero *heroWithLayer();
    //初始化
	bool init();
	//向指定方向移动一格
	void move(HeroDirection direction);
	//移动完成后回调函数
	void onMoveDone(Node *_Target);
	//设置勇士方向
	void setFaceDirection(HeroDirection direction);
	//检测碰撞
	//CollisionType checkCollision(Point heroPosition);
	//战斗方法
	void heroFight();
	//移动到方法
	void heroMoveTo(Point xiaos);
	
	//moveto的回调方法
	void onMoveToDone(Node *_Target);

	//变量勇士的精灵
	Sprite *_HeroSprit;
	//是否在移动状态
	bool isHeroMoving;
	//保存目标坐标
	Point targetPosition;
	//保存hero方向
	HeroDirection famgx;
	//临时保存目标的Tilemap坐标
	//Point targetTileCoord;
	
};
#endif

