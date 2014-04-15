#include "ditNode.h"
using namespace cocos2d;
//using namespace std;




//定义一个类，用于寻路过程中，记录每个格子的信息,包括:走了多少步,预期多少步,父节点是啥
//Vector仅支持继承自object的类


ditNode::ditNode()
{
	x=0;y=0;nH = 0; nG = 0; pParent = NULL;
}

ditNode::~ditNode()
{
}  
ditNode* ditNode::createDitNode(){
	ditNode* _ct=new ditNode();
	return _ct;
}

//主类开始
