#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "MTGame.h"
#include<math.h>
using namespace cocos2d;
//画布，包括地图和碰撞检测
class GameLayer :public cocos2d::Layer
	
{

public:
	GameLayer(void);
	~GameLayer(void);
	virtual bool init();
    CREATE_FUNC(GameLayer);

	//物理世界
	Sprite* _ball;
    PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world){ m_world = world; };
	//创造空白物理scene
	static cocos2d::Scene* createScene();
	//tilemap和cocos2d坐标转换
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point position);
	//移动场景方法
	void setSceneScrollPosition(Point position);
	//开启抗锯齿
	//void enableAnitiAlisForEachLayer(cocos2d::TMXTiledMap *_map);
	//每帧调用一次
	void update2(float dt);
	//0.1秒调用一次
	void update1(float dt);
	//碰撞检测,需要检测的点,什么来检测的
	CollisionType checkCollision(Point point,CollisionThing key);
	//加入子弹
	void addBullet(Point heroPosition,Point enemyPosition);
	//子弹消失后调用的方法
	void onMoveDone(Node *_Target);
	//子弹消失动画后调用的方法
	void onBulletAnimateDone(Node *_Target);
	//子弹撞到敌人
	void bulletEnemy(Point point);
	//子弹撞到敌人的回调方法
	void onBulletEnemyDone(Node *_Target);
	//怪物死亡方法
	void onEnemyDie(Point point);
	//怪物死亡回调方法
	void onEnemyDieDone(Node *_Target);
	//获得墙壁图层
	TMXLayer*  getWallLayer();
	//地图
	cocos2d::TMXTiledMap *_map;
//私有的变量
private:
	
   
   //地图底层
   TMXLayer *floorLayer;
   //地图墙层
   TMXLayer  *wallLayer;
  // protected:
//	Hero *_hero;
   
};
#endif

