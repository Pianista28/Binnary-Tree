#include "CTree.h"
#include<iostream>
using namespace std;


CTree::CTree()
{
	pc_root = NULL;
}

CTree::CTree(CNode *root, CNode *left, CNode *right)
{
	pc_root = root;
	pc_root->pc_leftChild = left;
	pc_root->pc_rightChild = right;
}



CTree::CTree(CNode *root)
{
	pc_root = root;
	pc_root->pc_leftChild = NULL;
	pc_root->pc_rightChild = NULL;
}

CTree::CTree(CNode * pcRoot, bool ifCopy)//new
{

}

CTree::~CTree()
{
	if(pc_root != NULL) delete pc_root;
	
}




CNode * CTree::sGetRoot()
{
	return this->pc_root;
}

string CTree::sGetErrors()
{
	string sErrors = "";
	for (int i = 0; i < vs_errors.size(); i++)
		sErrors += vs_errors[i] +" ";
	return sErrors;
}

string CTree::sDisplay()
{
	return pc_root->s_value;
}

int CTree::iCountExpression(CNode * root)
{
	if (root->isLeaf()) return atoi(root->s_value.c_str());
	else if (root->s_value == "+") return iCountExpression(root->pc_leftChild) + iCountExpression(root->pc_rightChild);
	else if (root->s_value == "/") return iCountExpression(root->pc_leftChild) / iCountExpression(root->pc_rightChild);
	else if (root->s_value == "*") return iCountExpression(root->pc_leftChild) * iCountExpression(root->pc_rightChild);
	else if (root->s_value == "~") return iCountExpression(root->pc_leftChild) * -1;
	else if (root->s_value == "-") return iCountExpression(root->pc_leftChild) - iCountExpression(root->pc_rightChild);

}

vector<string> CTree::getErrorsVector()
{
	return vs_errors;
}

void CTree::vRepairTree(CNode * root)
{
	if (root != NULL)
	{
		if (bIsOperator(root->s_value))
		{

			if (root->pc_leftChild == NULL)
			{
				vs_errors.push_back(sStringOfInt(root->i_pos) +" dla " + root->sGetValue());
				root->pc_leftChild = new CNode("1");
			}
			if (root->pc_rightChild == NULL && !(root->s_value == "~"))
			{
				
				vs_errors.push_back(sStringOfInt(root->i_pos) +" dla" + root->sGetValue());
				root->pc_rightChild = new CNode("1");
			}
			vRepairTree(root->pc_leftChild);
			vRepairTree(root->pc_rightChild);
		}

	}
}

void CTree::vCheckLackOperator(CNode * p_root)
{
	if (stack.size() != 1)
	{
		
		CTree* cTempTree = stack.top();
		stack.pop();
		vs_errors.push_back("u" + sStringOfInt(stack.top()->pc_root->i_pos));
		stack.push(cTempTree);
		
	}
}

string CTree::sStringOfInt(int value)
{
	ostringstream ss;
	ss << value;
	string str = ss.str();
	return str;
}


bool CTree::bBuildTree(vector<string>& stringVector, vector<CNode*> & inputVariablesVector)
{
	int iStackSize = 0;

	for (int iInputPosition = 0; iInputPosition < stringVector.size(); iInputPosition++)
	{
		
		string sElement = stringVector[iInputPosition];
		//cout << sElement << endl<<endl;//dla testu
		if (!bIsOperator(sElement))
		{
			CTree *pAddedNode = new CTree(new CNode(sElement, iInputPosition));
			stack.push(pAddedNode);
			iStackSize++;
			if (!bIsNumber(sElement))
			{
				inputVariablesVector.push_back(pAddedNode->pc_root);
			}
		}
		else
		{
			if (iStackSize == 0)
			{
				stack.push(new CTree(new CNode(sElement, iInputPosition)));
				iStackSize++;
			}
			if (iStackSize == 1 || (iStackSize >=2 && sElement == "~")) //bo "~" jako jedyny operator jest jednoargumentowy
			{
				CTree * pAddedNode = new CTree(new CNode(sElement, iInputPosition), stack.top()->pc_root, NULL);
				stack.pop();
				stack.push(pAddedNode);
			}
			if (iStackSize >= 2)
			{	
				CNode * p_tempRight;
				p_tempRight = stack.top()->pc_root;
				stack.pop();

				CNode * p_tempLeft;
				p_tempLeft = stack.top()->pc_root;
				stack.pop();

				CTree *pAddedNode = new CTree(new CNode(sElement, iInputPosition), p_tempLeft,p_tempRight);
				stack.push(pAddedNode);
				iStackSize--;
			}
		}
	}
	pc_root = stack.top()->pc_root;
	return true;
}

bool CTree::bIsOperator(string sElement)
{
	return sElement == "/" || sElement == "+" || sElement == "-" || sElement == "~" || sElement == "*";
}

bool CTree::bIsNumber(string sElement)
{
	return sElement.find_first_not_of(DIGITS) == string::npos;
}


void CTree::vInOrder(CNode * root)
{
	s_inOrder += "(";
	if (root->pc_leftChild != NULL)
		vInOrder(root->pc_leftChild);
	s_inOrder +=  root->sGetValue()  ;
	if (root->pc_rightChild != NULL)
		vInOrder(root->pc_rightChild);
	s_inOrder += ")";

}

string CTree::sDisplayInOrder()
{
	s_inOrder = "";
	vInOrder(this->pc_root);
	return s_inOrder;
}

void CTree::newRoot(CNode * newRoot)
{

	if (newRoot != NULL)
	{
		bool ifContains;
		bTreeContains(newRoot, this->pc_root, ifContains);
		if (ifContains)
		{
			CNode* pcTemp = new CNode(newRoot);
			delete this->pc_root;
			this->pc_root = pcTemp;
		}
	}
}

void CTree::bTreeContains(CNode * newRoot, CNode * currentRoot, bool &contains  )
{
	if (newRoot != NULL && currentRoot != NULL)
	{
		if (newRoot == currentRoot)
			contains = true;
		else
		{
			bTreeContains(newRoot, currentRoot->pc_leftChild,contains);
			bTreeContains(newRoot, currentRoot->pc_rightChild,contains);
		}
	}
}


