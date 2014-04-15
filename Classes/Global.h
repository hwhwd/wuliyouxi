#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "MTGame.h"
//���ౣ��ȫ�ֶ��ܷ��ʵı���
using namespace cocos2d;

class GameScene;
class GameLayer;
class Hero;
class HeroAI;
class OptionLayer;
class WelcomeScene;
//class CCScene;

class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);

	GameScene *gameScene;
	//��Ϸ��ͼ��
	GameLayer *gameLayer;
	OptionLayer *optionLayer;
	//��ӭ����
	WelcomeScene *welcomeScene;
	//��ʿ
	Hero *hero;
	//��������
	Array *_enemys;
	//�ӵ�������
	Array *_bullets;
	//ai
	HeroAI *_heroAI;

	//Ŀ���ͼ�Ĳ���
	int currentLevel;
	//��ʿ���ֵ���ʼλ��
	Point heroSpawnTileCoord;
	//��Ч����
	bool effect;
	//�Ƿ���ѡ�е�Ŀ��
	bool xuanz;
	//ѡ�е�Ŀ��tag;
	int xuanzTag;
	//AI״̬
	AITag heroAITag;
	Scene* physicScene;

	//��Ļ�ߴ�
	//Size screenSize;
	//Gamelayer���ƶ�������
	//Point yidong;
	//��ȡxml��
	//Dictionary *chnStrings;
};

#define sGlobal Global::instance()

#endif