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
	//��ʼ������
	virtual bool init();
	//��̬�������ڴ���sceneʵ��,Ϊ����appdelegate����
	static Scene *palyNewGame();
	//�����¼�
	void Touches();
	//Gamelayer���ƶ�������
	Point yidong;
	//CREATE_FUNC���ܹ����ٽ���һ��Ĭ�ϵ�create�������������������ص���һ������Ķ��󣬲����Զ�������init��autorelease����
    CREATE_FUNC(GameScene);
	//ͬ���������������ֱ�Ӷ���Ĭ�ϵ�get/set����
 
  //  CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    //CC_SYNTHESIZE(OptionLayer*, _optionLayer, OptionLayer);
};

#endif
