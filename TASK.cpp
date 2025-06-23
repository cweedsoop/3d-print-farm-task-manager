

#include "TASK.h"
#include <string>

using namespace std;

void Task::SetTaskName(string& inputName)
{
	taskName = inputName;
}

const string& Task::GetTaskName()
{
	return taskName;
}

void Task::SetUser(string& userName)
{
	taskUser = userName;
}

const string& Task::GetUser()
{
	return taskUser;
}

void Task::SetStatus(string& inputStatus)
{
	status = inputStatus;
}

const string& Task::GetStatus()
{
	return status;
}

void Task::SetCurrProduct(Product& inputProduct)
{
	currProduct = inputProduct;
}

Product& Task::GetCurrProduct()
{
	return currProduct;
}


void Task::AddPrinter(string& printerName)
{
	assignedPrinters.push_back(printerName);
}

void Task::LoadPrinters(vector<string>& dataVec)
{
	assignedPrinters = dataVec;
}

void Task::GetPrinterList(vector<string>& dataVec)
{
	dataVec = assignedPrinters;
}

int Task::ErasePrinterList()
{
	assignedPrinters.resize(0);
	return 0;
}

