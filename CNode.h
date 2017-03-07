#pragma once
#include<string>
//#include "Menu.h"
//#include  "CNode.h"
#define DIGITS "0123456789"
using namespace std;

class CNode
{
	
	private:
		CNode *pc_leftChild;
		CNode *pc_rightChild;
		string s_value;
		int i_pos;
		


	public:
		friend class CTree;
		bool CNode::isLeaf();
		~CNode();
		CNode(string sValue);
		CNode(string sValue, int iPosition);
		string sGetValue();
		void vSetValue(string sValue);

		CNode(CNode* pcToCopy);
};