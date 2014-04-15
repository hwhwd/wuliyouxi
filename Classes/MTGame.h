#ifndef __MTGAME_H__
#define __MTGAME_H__
//公用头文件
//框架
#include "cocos2d.h"
//外部项,画的gui
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h" 
#include "ui/UICheckBox.h"
//常量
#include "GameConstants.h"
//游戏场景
#include "GameScene.h"
//画布，包括地图、各种坐标的变换、开启抗锯齿
//10
#include "GameLayer.h"
//英雄类、碰撞检测,移动方法
//12
#include "Hero.h"
//怪物类、碰撞检测,移动方法
//12
#include "Enemy.h"
//英雄AI
#include "HeroAI.h"
//用于ai的类
#include "ditNode.h"

//控制层,触摸控制
//15
#include "OptionLayer.h"
//单类模板
#include "Singleton.h"
//单类保存全局都能访问的变量
#include "Global.h"
//单类动画管理器,预先加载文件,创建所有动画播放模板
#include "AnimationManager.h"
//欢迎场景,设置,关于在此中
#include "WelcomeScene.h"
//欢迎layer,为了触摸事件才独立的
#include "WelcomeLayer.h"
//音乐
#include "SimpleAudioEngine.h"

#endif

