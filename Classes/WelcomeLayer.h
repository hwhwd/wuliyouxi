#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__
#include "MTGame.h"
//#include "gui/UICheckBox.h"
using namespace ui;
using namespace cocos2d;
//������������ͼ����ײ���
class WelcomeLayer :public cocos2d::Layer
	
{

public:
	WelcomeLayer(void);
	~WelcomeLayer(void);
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	 // �˳�
    void menuCloseCallback(Object* sender);
	//����Ϸ
	void  menuNewCallback(Object* sender);
	//����
	void  menuAboutCallback(Object* sender);
	//����
	void  menuSetCallback(Object* sender);
	//����
	void  menuAboutReturnCallback(Object* sender);
	//���÷���
	void  menuSetReturnCallback(Object* sender);
	//��ѡ��
	void selectedEvent(Object* pSender,CheckBoxEventType type);
	void selectedEvent1(Object* pSender,CheckBoxEventType type);
	//����
	void sliderEvent(Object *pSender, SliderEventType type);
//˽�еı���
private:
	
   
  
   
};
#endif

