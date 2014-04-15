#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "MTGame.h"
using namespace cocos2d;
//������
class Enemy :public cocos2d::Node
	
{

public:
	Enemy(void);
	~Enemy(void);
	//��̬���������ڴ���
	static Enemy *enemyWithLayer();
    //��ʼ��
	bool init();
	//��ָ�������ƶ�һ��
	void move(HeroDirection direction);
	//�ƶ���ɺ�ص�����
	void onMoveDone(Node *_Target);
	//���÷���
	void setFaceDirection(Enemy* enemy,HeroDirection direction);
	


	//������ʿ�ľ���
	Sprite *_enemySprit;
	//�Ƿ����ƶ�״̬
	bool isHeroMoving;
	//����Ŀ������
	Point targetPosition;
	//����enemy����
	HeroDirection famgx;
	//��ʱ����Ŀ���Tilemap����
	Point targetTileCoord;
	//Ѫ��
	int xue;
	
};
#endif

