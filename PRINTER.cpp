

#include "PRINTER.h"

using namespace std;

void Printer::SetName(string& inputName)
{
	name = inputName;
}

const string& Printer::GetName()
{
	return name;
}

void Printer::SetSerial(string& serial)
{
	serialNumber = serial;
}

const string& Printer::GetSerial()
{
	return serialNumber;
}

void Printer::SetCurrTask(string& taskName)
{
	currTask = taskName;
}

const string& Printer::GetCurrTask()
{
	return currTask;
}

void Printer::SetWorkspace(string& currSpace)
{
	currWorkspace = currSpace;
}

const string& Printer::GetWorkspace()
{
	return currWorkspace;
}

void Printer::SetCurrProduct(string& productName)
{
	currProduct = productName;
}

string& Printer::GetCurrProduct()
{
	return currProduct;
}

void Printer::SetCurrColorStyle(string& colorStyle)
{
	currColorStyle = colorStyle;
}

string& Printer::GetCurrColorStyle()
{
	return currColorStyle;
}

void Printer::SetCurrUser(string& userName)
{
	currUser = userName;
}

const string& Printer::GetCurrUser()
{
	return currUser;
}

void Printer::SetFilamentStatus(string& status)
{
	filamentStatus = status;
}

const string& Printer::GetFilamentStatus()
{
	return filamentStatus;
}

void Printer::SetIsFunctional(int& functional)
{
	if (functional == 0)
	{
		isFunctional = false;
	}
	
	else if (functional == 1)
	{
		isFunctional = true;
	}
}

const bool& Printer::GetIsFunctional()
{
	return isFunctional;
}

