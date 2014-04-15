#ifndef __DIT_NODE_H__
#define __DIT_NODE_H__
#include "MTGame.h"
using namespace cocos2d;
//英雄类ai
class ditNode :public cocos2d::Object
	
{

public:
	ditNode(void);
	~ditNode(void);
	//bool init();
	//ai的状态
	//AITag aiTag;
	int x;
	int y;
	int nH;//总共走了几步
	int nG;//估算目标还有几步
	ditNode* pParent;//父节点

	static ditNode* createDitNode();
};
#endif

