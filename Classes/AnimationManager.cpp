#include "AnimationManager.h"

DECLARE_SINGLETON_MEMBER(AnimationManager);
//动画管理器,预先加载文件,创建所有动画播放模板
AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	//CCDirector会自己清除AnimationCache
	//CCAnimationCache::purgeSharedAnimationCache();
}

bool AnimationManager::initAnimationMap()
{

	// 添加 plist文件到缓存  
	// cache->addSpriteFramesWithFile("01.plist");  
	SpriteFrameCache *cache=SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("01.plist");  
	// 创建数组用来存放帧序列  
	//SpriteBatchNode *batchNode = SpriteBatchNode::create("01.png");  

	char temp[20];
	sprintf(temp, "%d", aDown);
	//加载勇士向下走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kDown), temp);
	sprintf(temp, "%d", aRight);
	//加载勇士向右走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kRight), temp);
	sprintf(temp, "%d", aLeft);
	//加载勇士向左走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kLeft), temp);
	sprintf(temp, "%d", aUp);
	//加载勇士向上走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kUp), temp);
	//加载战斗动画
	//sprintf(temp, "%d", aFight);
	//AnimationCache::sharedAnimationCache()->addAnimation(createFightAnimation(), temp);

	sprintf(temp, "%d", eDown);
	//加载怪物向下走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kDown), temp);
	sprintf(temp, "%d", eRight);
	//加载怪物向下走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kRight), temp);
	sprintf(temp, "%d", eLeft);
	//加载怪物向下走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kLeft), temp);
	sprintf(temp, "%d", eUp);
	//加载怪物向下走的动画
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kUp), temp);
	sprintf(temp, "%d", bullet);
	//子弹爆炸
	AnimationCache::sharedAnimationCache()->addAnimation(createBulletAnimation(), temp);

	//加载NPC动画
	//AnimationCache::sharedAnimationCache()->addAnimation(createNPCAnimation(), "npc0");
	return true;
}
//勇士行走动画的方法
Animation* AnimationManager::createHeroMovingAnimationByDirection(HeroDirection direction)
{

	//以上是文件缓存..以下才是动画
	Animation *animation = Animation::create();  
	int i=4*direction+1;
	int a=i+3;
	for (i; i<=a; i++) {  
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("%d.png",i)->getCString());  
		animation->addSpriteFrame(frame);  

	}  
	//播放间隔时间
	animation->setDelayPerUnit(0.2);  
	//删除缓存中的动画
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	return animation;
}
//怪物行走动画
Animation* AnimationManager::createEnemyMovingAnimationByDirection(HeroDirection direction)
{
	//以上是文件缓存..以下才是动画
	Animation *animation = Animation::create();  
	int i=4*direction+1;
	int a=i+3;
	for (i; i<=a; i++) {  
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("2_%d.png",i)->getCString());  
		animation->addSpriteFrame(frame);  

	}  
	//播放间隔时间
	animation->setDelayPerUnit(0.2);  
	//删除缓存中的动画
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	return animation;
}
//子弹爆炸模板
Animation* AnimationManager::createBulletAnimation(){
	Animation *animation = Animation::create();  
	int i=5;
	int a=i+3;
	for (i; i<=a; i++) {  
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("4_%d.png",i)->getCString());  
		animation->addSpriteFrame(frame);  

	}  
	//播放间隔时间
	animation->setDelayPerUnit(0.1);  
	//删除缓存中的动画
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	return animation;



}
//创建战斗动画模板
Animation* AnimationManager::createFightAnimation()
{
	//定义每帧的序号
	Animation *animation = Animation::create(); 


	return animation;
}
//创建NPC的动画模板
Animation* AnimationManager::createNPCAnimation()
{

	Animation *animation = Animation::create(); 
	//0.05f表示每帧动画间的间隔


	return animation;
}

//获取指定动画模版
Animation* AnimationManager::getAnimation(int key)
{
	char temp[20];
	sprintf(temp, "%d", key);
	return AnimationCache::getInstance()->animationByName(temp);
}

//获取一个指定动画模版的实例
Animate* AnimationManager::createAnimate(int key)
{
	//获取指定动画模版
	Animation* anim = getAnimation(key);
	if(anim)
	{
		//根据动画模版生成一个动画实例
		return cocos2d::Animate::create(anim);
	}
	return NULL;
}

//获取一个指定动画模版的实例,上一个的重载
Animate* AnimationManager::createAnimate(const char* key)
{
	//获取指定动画模版
	//Animation* anim = AnimationCache::sharedAnimationCache()->animationByName(key);
	Animation* anim = AnimationCache::getInstance()->animationByName(key);
	if(anim)
	{
		//根据动画模版生成一个动画实例
		return cocos2d::Animate::create(anim);
	}
	return NULL;
}

