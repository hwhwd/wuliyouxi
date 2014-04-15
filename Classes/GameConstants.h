#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__
//公用常量

//勇士行走方向
typedef enum{
	kDown=0,//向下走
	kLeft=1,//向左
	kRight=2,//向右
	kUp=3,//向上
	kNormal,
}HeroDirection;

//碰撞类型
typedef enum{
	kNone=1,//无碰撞
	kWall,//墙壁
	kEnemy,//敌人
	kDoor,
	kNPC,
}CollisionType;

//动画模板键值
typedef enum{
	aDown=0,//向下走
	aLeft=1,//向左
	aRight=2,//向右
	aUp=3,//向上
	aFight=4,//战斗
	//怪
	eDown=5,//向下走
	eLeft=6,//向左
	eRight=7,//向右
	eUp=8,//向上

	bullet=9,//子弹
}AnimationKey;


//碰撞检测时的东西
typedef enum{
	pNone=0,//无碰撞
	pEnemy=1,//敌人
	pHero=2,
	pBullet=3,//子弹
}CollisionThing;
//AI状态
typedef enum{
	aiNone=0,//手动控制
	aiFite=1,//战斗
	aiMove=2,//行走
	//pBullet=3,//子弹
}AITag;

#endif

