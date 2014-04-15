#ifndef __HERO_H__
#define __HERO_H__
#include "MTGame.h"
using namespace cocos2d;
//Ӣ����12
class Hero :public cocos2d::Node
	
{

public:
	Hero(void);
	~Hero(void);
	//��̬���������ڴ���
	static Hero *heroWithLayer();
    //��ʼ��
	bool init();
	//��ָ�������ƶ�һ��
	void move(HeroDirection direction);
	//�ƶ���ɺ�ص�����
	void onMoveDone(Node *_Target);
	//������ʿ����
	void setFaceDirection(HeroDirection direction);
	//�����ײ
	//CollisionType checkCollision(Point heroPosition);
	//ս������
	void heroFight();
	//�ƶ�������
	void heroMoveTo(Point xiaos);
	
	//moveto�Ļص�����
	void onMoveToDone(Node *_Target);

	//������ʿ�ľ���
	Sprite *_HeroSprit;
	//�Ƿ����ƶ�״̬
	bool isHeroMoving;
	//����Ŀ������
	Point targetPosition;
	//����hero����
	HeroDirection famgx;
	//��ʱ����Ŀ���Tilemap����
	//Point targetTileCoord;
	
};
#endif

