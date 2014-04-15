#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);

Global::Global(void)
{
	effect=UserDefault::getInstance()->getBoolForKey("effectmusic",true);
	xuanz=false;
	//选中的目标tag;
	xuanzTag=-1;
	heroAITag=aiNone;
}

Global::~Global(void)
{
	gameLayer = NULL;
	hero = NULL;
	optionLayer = NULL;
	gameScene = NULL;
	welcomeScene=NULL;
	_enemys=NULL;
	_bullets=NULL;
	_heroAI=NULL;
	effect=NULL;
	//screenSize = Director::getInstance()->getWinSize();
	xuanz=NULL;
	//选中的目标tag;
	xuanzTag=NULL;
	heroAITag=aiNone;
	physicScene=NULL;
	//yidong=Point(0,0);
	//chnStrings =NULL;  
}