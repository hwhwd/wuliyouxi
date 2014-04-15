#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "MTGame.h"
//单类保存全局都能访问的变量
using namespace cocos2d;

class GameScene;
class GameLayer;
class Hero;
class HeroAI;
class OptionLayer;
class WelcomeScene;
//class CCScene;

class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);

	GameScene *gameScene;
	//游戏主图层
	GameLayer *gameLayer;
	OptionLayer *optionLayer;
	//欢迎场景
	WelcomeScene *welcomeScene;
	//勇士
	Hero *hero;
	//怪物数组
	Array *_enemys;
	//子弹的数组
	Array *_bullets;
	//ai
	HeroAI *_heroAI;

	//目标地图的层数
	int currentLevel;
	//勇士出现的起始位置
	Point heroSpawnTileCoord;
	//音效开关
	bool effect;
	//是否有选中的目标
	bool xuanz;
	//选中的目标tag;
	int xuanzTag;
	//AI状态
	AITag heroAITag;
	Scene* physicScene;

	//屏幕尺寸
	//Size screenSize;
	//Gamelayer层移动的坐标
	//Point yidong;
	//读取xml的
	//Dictionary *chnStrings;
};

#define sGlobal Global::instance()

#endif