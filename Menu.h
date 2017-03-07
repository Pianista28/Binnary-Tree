#pragma once

#include "CNode.h"
#include "CTree.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


class CMenu
{
	private:
		
		CTree *pc_tree;
		bool isCreated;
		bool bAreVariablesSet;
		vector<CNode*> inputVariables; // przechowuje zmienne
	public:
		
		
		~CMenu();
		int iIntegerCorrectInput();
		void vInterface();
		void vShowErrors();
		void vShowVariables();
		bool bVContains(vector<string> vwektor,string element);
		void vSetVariablesValue();
		string iStringOfInt(int value);
		string sGetIpout();
		bool bCorrectChars(string sInput);
		void vRepairInput(string & sInput, vector<string> & correctVector);
		bool isOperand(char cElement);
};
