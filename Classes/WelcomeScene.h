#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__
#include "MTGame.h"
using namespace ui;
using namespace cocos2d;
//���������ռ�
//using namespace CocosDenshion;
//�̳�sense

class WelcomeScene : public cocos2d::Scene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	//����scene
	Scene *palyWelcomeScene();
    
	WelcomeScene(void);
    
   ~WelcomeScene(void);
    // implement the "static node()" method manually
    CREATE_FUNC(WelcomeScene);
};

#endif
