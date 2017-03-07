#include "CNode.h"


CNode::CNode(std::string value)
{
	this->pc_leftChild = NULL;
	this->pc_rightChild = NULL;
	this->s_value = value;
}

CNode::CNode(std::string value, int pos)
{
	this->pc_leftChild = NULL;
	this->pc_rightChild = NULL;
	this->s_value = value;
	this->i_pos = pos;
}

string CNode::sGetValue()
{
	return s_value;
}

void CNode::vSetValue(string sValue)
{
	s_value = sValue;
}

CNode::CNode(CNode * pcToCopy)//new
{
	s_value = pcToCopy->sGetValue();
	pc_leftChild = new CNode(pcToCopy->pc_leftChild);
	pc_rightChild = new CNode(pcToCopy->pc_rightChild);
}

bool CNode::isLeaf()
{
	return pc_leftChild == NULL && pc_rightChild == NULL;
}

CNode::~CNode()
{
	if (pc_leftChild != NULL) delete pc_leftChild;
	if(pc_rightChild != NULL) delete pc_rightChild;
}

