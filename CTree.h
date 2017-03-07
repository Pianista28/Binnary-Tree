#pragma once
#include "Menu.h"
#include "CNode.h"
#include<vector>
#include <string>
#include <queue>
#include <stack>
#define PIERWSZY_ELEMENT 0
#define LACK_OF_ARGUMENT "brakuje argumentu dla operatora na pozycji "
#define LACK_OF_OPERATOR "brakuje operatora, utrata zawartoœci, od pozycja "
#include <sstream>
#include <cstdlib>
using namespace std;
class CTree
{
	private:
		
		
		string s_inOrder; //przechowuje wyra¿enie do wyœwietlenia
		stack<CTree*> stack; //stos do budowy drzewa
		vector <string> vs_errors;
		CNode *pc_root;

	public:
		
		CTree();
		CTree(CNode *pcRoot, CNode *pcLeft, CNode *pcRight);
		CTree(CNode *pcRoot);
		CTree(CNode *pcRoot, bool ifCopy);
		~CTree();
		
		CNode* sGetRoot();
		string sGetErrors();
		string sDisplay();
		int iCountExpression(CNode * pcRoot);
		vector<string> getErrorsVector();
		
		void vRepairTree(CNode* pcRoot);
		void vCheckLackOperator(CNode *pcRoot);
		string sStringOfInt(int value);
		
		bool bBuildTree(vector<string> & stringVector,vector<CNode*> & inputVariablesVector);

		bool bIsOperator(string sElement);
		bool bIsNumber(string sElement);
		void vInOrder(CNode * pcRoot);
		string sDisplayInOrder();
		bool contains;
		void newRoot(CNode* newRoot);//new
		void bTreeContains(CNode* newRoot, CNode* currentRoot, bool& contains); //new


		//int getValueR(CNode *root);
		//bool addNode(string sValue);
		//bool addNode(CNode *NewNode);
};