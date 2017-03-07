#include "Menu.h"
#define WPROWADZ 1
#define WYPISZ_WYRAZENIE 2
#define WYPISZ_ZMIENNE 3
#define WARTOSCI_ZMIENNYCH 4
#define OBLICZ 5
#define WYLACZ 6


CMenu::~CMenu()
{
	delete pc_tree;
}

int CMenu::iIntegerCorrectInput()
{

	int i_input;
	cin >> i_input;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		cout << "Podaj liczbê ponownie" << endl;
		cin >> i_input;
	}
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	return i_input;
}

void CMenu::vInterface()
{
	pc_tree = new CTree();
	cout << "1. Podaj wyrazenie w postaci postfiksowej" << endl;
	cout << "2. Wypisz wyrazenie w postaci infiksowej" << endl;
	cout << "3. Wypisz zmienne" << endl;
	cout << "4. Nadaj wartosci zmiennych" << endl;
	cout << "5. Oblicz wartosc wyrazenia" << endl;
	cout << "6. Wyjscie \n" << endl;

	int iOption = 0;

	while (iOption != 6)
	{
		cout << "Opcja numer: ";
		iOption = iIntegerCorrectInput();

		switch (iOption)
		{
		case WPROWADZ:
		{
			if (isCreated)
				cout << "Juz utworzyles drzewo" << endl;
			else
			{
				string sExpression = sGetIpout();
				vector <string> expressionVector;
				vRepairInput(sExpression, expressionVector);
				
				pc_tree->bBuildTree(expressionVector, inputVariables);
				pc_tree->vCheckLackOperator(pc_tree->sGetRoot());
				pc_tree->vRepairTree(pc_tree->sGetRoot());
				vShowErrors();
				
				isCreated = true;
			}
			break;
		}
		case WYPISZ_WYRAZENIE: 
		{
			if (isCreated)
				cout << pc_tree->sDisplayInOrder();
			else
				cout << "Najpierw podaj wyra¿enie" << endl;
			break;
		}
		case WYPISZ_ZMIENNE:
		{
			vShowVariables();
			break;
		}
		case WARTOSCI_ZMIENNYCH:
		{
			vSetVariablesValue();
			bAreVariablesSet = true;
			break;
		}
		case OBLICZ:
		{
			if (!isCreated)
				cout << "Najpierw podaj wyra¿enie " << endl;
			
			else if (!bAreVariablesSet)
				cout << "Najpierw zmienne" << endl;
			else
				cout << "Wartoœæ: " << pc_tree->iCountExpression(pc_tree->sGetRoot()) << endl;
			break;
		}
		case WYLACZ:
		{
			break;
		}
		}
	}


}

void CMenu::vShowErrors()
{
	for (int i = 0; i < pc_tree->getErrorsVector().size(); i++)
	{
		if (pc_tree->getErrorsVector()[i][0] == 'u')
			cout << LACK_OF_OPERATOR << " " << pc_tree->getErrorsVector()[i][1] << endl;
		else
			cout << LACK_OF_ARGUMENT << " " << pc_tree->getErrorsVector()[i] << endl;
	}
}

void CMenu::vShowVariables()
{
	vector <string> processed;

	for (int i = 0; i < inputVariables.size(); i++)
	{
		if (!bVContains(processed, inputVariables[i]->sGetValue()))
		{
			processed.push_back(inputVariables[i]->sGetValue());
			cout << "zmienna " << inputVariables[i]->sGetValue() << endl;
		}
	}

}

bool CMenu::bVContains(vector<string>vwektor, string element)
{
	for (int i = 0; i < vwektor.size(); i++)
	{
		if (vwektor[i] == element)
			return true;
	}
	return false;
}

void CMenu::vSetVariablesValue()
{
	vector <string> processed;

	if (inputVariables.empty())
		cout << "Nie ma zmiennych" << endl;
	else
	{
		for (int i = 0; i < inputVariables.size(); i++)
		{
			string sTempVariableValue = inputVariables[i]->sGetValue();
			if (!bVContains(processed, sTempVariableValue))
			{
				processed.push_back(sTempVariableValue);
				cout << "Podaj wartosc zmiennej " << sTempVariableValue;
				int iToSet = iIntegerCorrectInput();
				string sToSet = iStringOfInt(iToSet);
				for (int j = i; j < inputVariables.size(); j++)
					if (sTempVariableValue == inputVariables[j]->sGetValue())
					{
						inputVariables[j]->vSetValue(sToSet);
						processed.push_back(sToSet);
					}
			}
		}
	}
}

string CMenu::iStringOfInt(int value)
{
	ostringstream ss;
	ss << value;
	string str = ss.str();
	return str;
}

string CMenu::sGetIpout()
{
	cout << "Podaj wyrazenie" << endl;
	string sToReturn;
	do
	{
		getline(cin, sToReturn);
	} while (!bCorrectChars(sToReturn));
	
	return sToReturn;
}

bool CMenu::bCorrectChars(string sInput)
{
	for (int i = 0; i < sInput.size(); i++)
		if (sInput[i] < ' ' || (sInput[i]>' ' && sInput[i] < '(') || (sInput[i]>'+'&& sInput[i]<'/'&& sInput[i] != '-') || (sInput[i]>'9' && sInput[i]<'A') || (sInput[i]>'Z'&&sInput[i]<'a') || (sInput[i]>'z'&&sInput[i] != '~'))
			return false;
	return true;
}

void CMenu::vRepairInput(string & sInput, vector<string>& correctVector)
{

	int i = 0;
	while (i < sInput.length())
	{
		if (i < sInput.length() - 1)
		{
			if ((sInput[i] >= '0' && sInput[i] <= '9') && ((sInput[i + 1] >= 'A' && sInput[i + 1] <= 'Z') || (sInput[i + 1] >= 'a' && sInput[i + 1] <= 'z'))
				|| (sInput[i + 1] >= '0' && sInput[i + 1] <= '9') && ((sInput[i] >= 'A' && sInput[i] <= 'Z') || (sInput[i] >= 'a' && sInput[i] <= 'z')))
			{
				sInput.insert(i + 1, " ");
			}
		}
		if (i < sInput.length())
		{
			if (isOperand(sInput[i]) ) //sInput[i] == '+' || sInput[i] == '-' || sInput[i] == '*' || sInput[i] == '/' || sInput[i] == '~')
			{
				sInput.insert(i, " ");
				i++;
				i++;
				sInput.insert(i, " ");
				
			}
		}
		
		i++;
	}

	stringstream ss(sInput);
	string sElement;
	while (ss >> sElement)
	{
		correctVector.push_back(sElement);
	}
}

bool CMenu::isOperand(char cElement)
{
	return cElement == '/' || cElement == '+' || cElement == '-' || cElement == '~' || cElement == '*';
}

/*
if (sInput[i] == '+')
{
sInput.replace(i, 1, " + ");
i++;
}
else if (sInput[i] == '*')
{
sInput.replace(i, 1, " * ");
i++;
}
else if (sInput[i] == '/')
{
sInput.replace(i, 1, " / ");
i++;
}
else if (sInput[i] == '-')
{
sInput.replace(i, 1, " - ");
i++;
}
else if (sInput[i] == '~')
{
sInput.replace(i, 1, " ~ ");
i++;
}
*/


