#ifndef __OPTION_LAYER_H__
#define __OPTION_LAYER_H__
#include "MTGame.h"
using namespace cocos2d;
//���Ʋ�
//15
class OptionLayer :
	public cocos2d::Layer
{
public:
	OptionLayer(void);
	~OptionLayer(void);
	virtual bool init();
	//�رհ�ť�ر���Ϸ����
	void menuCloseCallback(Object* sender);
	
	 // ���ص������¼���������
    //void TouchesBegan(cocos2d::Set *ts, cocos2d::Event *e);
    //void TouchesMoved(cocos2d::Set *ts, cocos2d::Event *e);
    //void TouchesEnded(cocos2d::Set *ts, cocos2d::Event *e);
	//������Ӧ�ķ���
	//void Touches();
    CREATE_FUNC(OptionLayer);
	//�������λ��
	//Point fangx;
	Sprite *_fangxiang;
};
#endif
