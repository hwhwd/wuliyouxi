#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__
//���ó���

//��ʿ���߷���
typedef enum{
	kDown=0,//������
	kLeft=1,//����
	kRight=2,//����
	kUp=3,//����
	kNormal,
}HeroDirection;

//��ײ����
typedef enum{
	kNone=1,//����ײ
	kWall,//ǽ��
	kEnemy,//����
	kDoor,
	kNPC,
}CollisionType;

//����ģ���ֵ
typedef enum{
	aDown=0,//������
	aLeft=1,//����
	aRight=2,//����
	aUp=3,//����
	aFight=4,//ս��
	//��
	eDown=5,//������
	eLeft=6,//����
	eRight=7,//����
	eUp=8,//����

	bullet=9,//�ӵ�
}AnimationKey;


//��ײ���ʱ�Ķ���
typedef enum{
	pNone=0,//����ײ
	pEnemy=1,//����
	pHero=2,
	pBullet=3,//�ӵ�
}CollisionThing;
//AI״̬
typedef enum{
	aiNone=0,//�ֶ�����
	aiFite=1,//ս��
	aiMove=2,//����
	//pBullet=3,//�ӵ�
}AITag;

#endif

