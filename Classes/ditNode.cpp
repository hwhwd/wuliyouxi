#include "ditNode.h"
using namespace cocos2d;
//using namespace std;




//����һ���࣬����Ѱ·�����У���¼ÿ�����ӵ���Ϣ,����:���˶��ٲ�,Ԥ�ڶ��ٲ�,���ڵ���ɶ
//Vector��֧�ּ̳���object����


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

//���࿪ʼ
