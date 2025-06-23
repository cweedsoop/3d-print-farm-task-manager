#pragma once

#include <iostream>
#include <string>
#include "PRODUCT.h"
#include "MYUTILITIES.h"

using namespace std;

class Printer
{
public:
	void SetName(string& inputName);

	const string& GetName();

	void SetSerial(string& serial);

	const string& GetSerial();

	void SetCurrTask(string& taskName);

	const string& GetCurrTask();

	void SetWorkspace(string& currSpace);

	const string& GetWorkspace();

	void SetCurrProduct(string& productName);

	string& GetCurrProduct();

	void SetCurrColorStyle(string& colorStyle);

	string& GetCurrColorStyle();
		
	void SetCurrUser(string& userName);

	const string& GetCurrUser();

	void SetFilamentStatus(string& status);

	const string& GetFilamentStatus();

	void SetIsFunctional(int& functional);

	const bool& GetIsFunctional();

private:
	string name;
	string serialNumber;
	string currWorkspace; //In current implementation this is the workspace of the assigning task. 
												//Printers can currently be managed across multiple workspaces 
	string currTask;
	string currProduct;	
	string currColorStyle;
	string currUser;
	string filamentStatus = "full"; //full, medium, low, empty
	bool isFunctional = true; //stored as 0 for false, 1 for true
};

template<typename T, typename U>
int PrinterEditPrompt(T& fieldname, U& data) //Uses function template
{
	U tempData;

	cout << "Enter the " << fieldname << ": " << endl << endl;

	while (true)
	{
		tempData = GetlineEX();
		RemoveEndingWhitespace(tempData);

		if (tempData.size() == 0)
		{
			cout << fieldname << " cannot be empty. Please reenter: " << endl << endl;
			continue;
		}
		break;
	}

	RemoveStartingWhitespace(tempData);
	WhitespaceCleanup(tempData);

	data = tempData;

	return 0;
}

//a line is stored between entries for readability
