#ifndef __OPTION_LAYER_H__
#define __OPTION_LAYER_H__
#include "MTGame.h"
using namespace cocos2d;
//控制层
//15
class OptionLayer :
	public cocos2d::Layer
{
public:
	OptionLayer(void);
	~OptionLayer(void);
	virtual bool init();
	//关闭按钮关闭游戏方法
	void menuCloseCallback(Object* sender);
	
	 // 触控的三个事件函数重载
    //void TouchesBegan(cocos2d::Set *ts, cocos2d::Event *e);
    //void TouchesMoved(cocos2d::Set *ts, cocos2d::Event *e);
    //void TouchesEnded(cocos2d::Set *ts, cocos2d::Event *e);
	//触摸响应的方法
	//void Touches();
    CREATE_FUNC(OptionLayer);
	//方向键的位置
	//Point fangx;
	Sprite *_fangxiang;
};
#endif
