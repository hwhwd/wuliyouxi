#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "MTGame.h"
using namespace cocos2d;


class GameScene :
	public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);
	//初始化方法
	virtual bool init();
	//静态方法用于创建scene实例,为了让appdelegate调用
	static Scene *palyNewGame();
	//触摸事件
	void Touches();
	//Gamelayer层移动的坐标
	Point yidong;
	//CREATE_FUNC宏能够快速建立一个默认的create方法，不带参数，返回的是一个该类的对象，并且自动调用了init和autorelease方法
    CREATE_FUNC(GameScene);
	//同样定义变量，并且直接定义默认的get/set方法
 
  //  CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    //CC_SYNTHESIZE(OptionLayer*, _optionLayer, OptionLayer);
};

#endif
