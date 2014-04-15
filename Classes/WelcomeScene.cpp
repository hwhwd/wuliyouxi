
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "MTGame.h"


//音乐命名空间
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;
//场景类,是用一个scene管理多个layer
//文字是乱码
//音乐是否要预先载入
//声音大小无法使用
  
WelcomeScene::WelcomeScene(void){
	//单类
	sGlobal->welcomeScene=this;
}
    
WelcomeScene::~WelcomeScene(void){}
	
// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    //加入背景音乐
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
		//SimpleAudioEngine::getInstance()->playBackgroundMusic("Backmusic.wav",true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Backmusic.wav", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(UserDefault::getInstance()->getIntegerForKey("yinliang",50)/100.0f);
	}
	


	WelcomeLayer *_menuLayer=WelcomeLayer::create();

    //将_menuLayer加入sesne
	this->addChild(_menuLayer,5,1);
    return true;
}


Scene *WelcomeScene::palyWelcomeScene(){
	Scene *scene=NULL;
	do{
	//版本修改后的
	scene=WelcomeScene::create();
	CC_BREAK_IF(!scene);

	}while(0);
	return scene;
}
