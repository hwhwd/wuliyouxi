#ifndef __DIT_NODE_H__
#define __DIT_NODE_H__
#include "MTGame.h"
using namespace cocos2d;
//Ӣ����ai
class ditNode :public cocos2d::Object
	
{

public:
	ditNode(void);
	~ditNode(void);
	//bool init();
	//ai��״̬
	//AITag aiTag;
	int x;
	int y;
	int nH;//�ܹ����˼���
	int nG;//����Ŀ�껹�м���
	ditNode* pParent;//���ڵ�

	static ditNode* createDitNode();
};
#endif

