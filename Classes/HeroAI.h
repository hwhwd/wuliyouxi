#ifndef __HERO_AI_H__
#define __HERO_AI_H__
#include "MTGame.h"
using namespace cocos2d;

class ditNode;
//Ӣ����ai
class HeroAI :public cocos2d::Object
	
{

public:
	HeroAI(void);
	~HeroAI(void);
	bool init();
	//ai��״̬
	//AITag aiTag;
	
	void start();
	//��̬���������ڴ���
	static HeroAI *createHeroAI();
	//A*�㷨
	void findRoute();
	//�������������
	void vecPathArray(ditNode* d);
	//�㷨�ڵ㷽��
	ditNode* newDituNode(ditNode* p,Point p1);
	//��дhero��moveto����
	void heroMoveTo();
	//�ص�����
	void onMoveToDone(Node *_Target);
};
#endif

