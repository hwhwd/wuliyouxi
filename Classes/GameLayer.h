#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "MTGame.h"
#include<math.h>
using namespace cocos2d;
//������������ͼ����ײ���
class GameLayer :public cocos2d::Layer
	
{

public:
	GameLayer(void);
	~GameLayer(void);
	virtual bool init();
    CREATE_FUNC(GameLayer);

	//��������
	Sprite* _ball;
    PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world){ m_world = world; };
	//����հ�����scene
	static cocos2d::Scene* createScene();
	//tilemap��cocos2d����ת��
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point position);
	//�ƶ���������
	void setSceneScrollPosition(Point position);
	//���������
	//void enableAnitiAlisForEachLayer(cocos2d::TMXTiledMap *_map);
	//ÿ֡����һ��
	void update2(float dt);
	//0.1�����һ��
	void update1(float dt);
	//��ײ���,��Ҫ���ĵ�,ʲô������
	CollisionType checkCollision(Point point,CollisionThing key);
	//�����ӵ�
	void addBullet(Point heroPosition,Point enemyPosition);
	//�ӵ���ʧ����õķ���
	void onMoveDone(Node *_Target);
	//�ӵ���ʧ��������õķ���
	void onBulletAnimateDone(Node *_Target);
	//�ӵ�ײ������
	void bulletEnemy(Point point);
	//�ӵ�ײ�����˵Ļص�����
	void onBulletEnemyDone(Node *_Target);
	//������������
	void onEnemyDie(Point point);
	//���������ص�����
	void onEnemyDieDone(Node *_Target);
	//���ǽ��ͼ��
	TMXLayer*  getWallLayer();
	//��ͼ
	cocos2d::TMXTiledMap *_map;
//˽�еı���
private:
	
   
   //��ͼ�ײ�
   TMXLayer *floorLayer;
   //��ͼǽ��
   TMXLayer  *wallLayer;
  // protected:
//	Hero *_hero;
   
};
#endif

