
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "MTGame.h"


//���������ռ�
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;
//������,����һ��scene������layer
//����������
//�����Ƿ�ҪԤ������
//������С�޷�ʹ��
  
WelcomeScene::WelcomeScene(void){
	//����
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
    //���뱳������
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
		//SimpleAudioEngine::getInstance()->playBackgroundMusic("Backmusic.wav",true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Backmusic.wav", true);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(UserDefault::getInstance()->getIntegerForKey("yinliang",50)/100.0f);
	}
	


	WelcomeLayer *_menuLayer=WelcomeLayer::create();

    //��_menuLayer����sesne
	this->addChild(_menuLayer,5,1);
    return true;
}


Scene *WelcomeScene::palyWelcomeScene(){
	Scene *scene=NULL;
	do{
	//�汾�޸ĺ��
	scene=WelcomeScene::create();
	CC_BREAK_IF(!scene);

	}while(0);
	return scene;
}
