#include "AnimationManager.h"

DECLARE_SINGLETON_MEMBER(AnimationManager);
//����������,Ԥ�ȼ����ļ�,�������ж�������ģ��
AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	//CCDirector���Լ����AnimationCache
	//CCAnimationCache::purgeSharedAnimationCache();
}

bool AnimationManager::initAnimationMap()
{

	// ��� plist�ļ�������  
	// cache->addSpriteFramesWithFile("01.plist");  
	SpriteFrameCache *cache=SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("01.plist");  
	// ���������������֡����  
	//SpriteBatchNode *batchNode = SpriteBatchNode::create("01.png");  

	char temp[20];
	sprintf(temp, "%d", aDown);
	//������ʿ�����ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kDown), temp);
	sprintf(temp, "%d", aRight);
	//������ʿ�����ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kRight), temp);
	sprintf(temp, "%d", aLeft);
	//������ʿ�����ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kLeft), temp);
	sprintf(temp, "%d", aUp);
	//������ʿ�����ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createHeroMovingAnimationByDirection(kUp), temp);
	//����ս������
	//sprintf(temp, "%d", aFight);
	//AnimationCache::sharedAnimationCache()->addAnimation(createFightAnimation(), temp);

	sprintf(temp, "%d", eDown);
	//���ع��������ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kDown), temp);
	sprintf(temp, "%d", eRight);
	//���ع��������ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kRight), temp);
	sprintf(temp, "%d", eLeft);
	//���ع��������ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kLeft), temp);
	sprintf(temp, "%d", eUp);
	//���ع��������ߵĶ���
	AnimationCache::sharedAnimationCache()->addAnimation(createEnemyMovingAnimationByDirection(kUp), temp);
	sprintf(temp, "%d", bullet);
	//�ӵ���ը
	AnimationCache::sharedAnimationCache()->addAnimation(createBulletAnimation(), temp);

	//����NPC����
	//AnimationCache::sharedAnimationCache()->addAnimation(createNPCAnimation(), "npc0");
	return true;
}
//��ʿ���߶����ķ���
Animation* AnimationManager::createHeroMovingAnimationByDirection(HeroDirection direction)
{

	//�������ļ�����..���²��Ƕ���
	Animation *animation = Animation::create();  
	int i=4*direction+1;
	int a=i+3;
	for (i; i<=a; i++) {  
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("%d.png",i)->getCString());  
		animation->addSpriteFrame(frame);  

	}  
	//���ż��ʱ��
	animation->setDelayPerUnit(0.2);  
	//ɾ�������еĶ���
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	return animation;
}
//�������߶���
Animation* AnimationManager::createEnemyMovingAnimationByDirection(HeroDirection direction)
{
	//�������ļ�����..���²��Ƕ���
	Animation *animation = Animation::create();  
	int i=4*direction+1;
	int a=i+3;
	for (i; i<=a; i++) {  
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("2_%d.png",i)->getCString());  
		animation->addSpriteFrame(frame);  

	}  
	//���ż��ʱ��
	animation->setDelayPerUnit(0.2);  
	//ɾ�������еĶ���
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	return animation;
}
//�ӵ���ըģ��
Animation* AnimationManager::createBulletAnimation(){
	Animation *animation = Animation::create();  
	int i=5;
	int a=i+3;
	for (i; i<=a; i++) {  
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("4_%d.png",i)->getCString());  
		animation->addSpriteFrame(frame);  

	}  
	//���ż��ʱ��
	animation->setDelayPerUnit(0.1);  
	//ɾ�������еĶ���
	//SpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	return animation;



}
//����ս������ģ��
Animation* AnimationManager::createFightAnimation()
{
	//����ÿ֡�����
	Animation *animation = Animation::create(); 


	return animation;
}
//����NPC�Ķ���ģ��
Animation* AnimationManager::createNPCAnimation()
{

	Animation *animation = Animation::create(); 
	//0.05f��ʾÿ֡������ļ��


	return animation;
}

//��ȡָ������ģ��
Animation* AnimationManager::getAnimation(int key)
{
	char temp[20];
	sprintf(temp, "%d", key);
	return AnimationCache::getInstance()->animationByName(temp);
}

//��ȡһ��ָ������ģ���ʵ��
Animate* AnimationManager::createAnimate(int key)
{
	//��ȡָ������ģ��
	Animation* anim = getAnimation(key);
	if(anim)
	{
		//���ݶ���ģ������һ������ʵ��
		return cocos2d::Animate::create(anim);
	}
	return NULL;
}

//��ȡһ��ָ������ģ���ʵ��,��һ��������
Animate* AnimationManager::createAnimate(const char* key)
{
	//��ȡָ������ģ��
	//Animation* anim = AnimationCache::sharedAnimationCache()->animationByName(key);
	Animation* anim = AnimationCache::getInstance()->animationByName(key);
	if(anim)
	{
		//���ݶ���ģ������һ������ʵ��
		return cocos2d::Animate::create(anim);
	}
	return NULL;
}

