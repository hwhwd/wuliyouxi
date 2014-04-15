#include "AppDelegate.h"

#include <vector>
#include <string>

#include "AppMacros.h"
#include "WelcomeScene.h"

USING_NS_CC;
using namespace std;
//动画管理器应该在loading里载入
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	//游戏结束后释放动画管理器
	sAnimationMgr->release();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
	
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }

    director->setOpenGLView(glview);

    // Set the design resolution
   #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
	#else
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	#endif

	Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
	//if (frameSize.height > mediumResource.size.height)
	//{
      //  searchPath.push_back(largeResource.directory);

        //director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	//}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    //else
		
		if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
        director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
        searchPath.push_back(smallResource.directory);

        director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
    //设置资源文件夹,通过前面的分辨率,适应不同图片
    // set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);
	//显示帧数
    // turn on display FPS
    director->setDisplayStats(true);
	//设置帧数
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	
	//初始化动画管理器
	sAnimationMgr->initAnimationMap();
	
	
    // create a scene. it's an autorelease object
	//此处调用自己的返回scene方法
    
	auto scene =WelcomeScene::create();
	
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
