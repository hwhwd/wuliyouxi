#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__
#include "MTGame.h"
//#include "gui/UICheckBox.h"
using namespace ui;
using namespace cocos2d;
//画布，包括地图和碰撞检测
class WelcomeLayer :public cocos2d::Layer
	
{

public:
	WelcomeLayer(void);
	~WelcomeLayer(void);
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	 // 退出
    void menuCloseCallback(Object* sender);
	//新游戏
	void  menuNewCallback(Object* sender);
	//关于
	void  menuAboutCallback(Object* sender);
	//设置
	void  menuSetCallback(Object* sender);
	//返回
	void  menuAboutReturnCallback(Object* sender);
	//设置返回
	void  menuSetReturnCallback(Object* sender);
	//复选框
	void selectedEvent(Object* pSender,CheckBoxEventType type);
	void selectedEvent1(Object* pSender,CheckBoxEventType type);
	//滑动
	void sliderEvent(Object *pSender, SliderEventType type);
//私有的变量
private:
	
   
  
   
};
#endif

