

#include <string>

#include "WORKSPACE.h"

using namespace std;

void Workspace::SetName(string& name)
{
	workspaceName = name;
}

const string& Workspace::GetName()
{
	return workspaceName;
}

int Workspace::AddProduct(string& productName)
{
	productList.push_back(productName);
	return 0;
}

int Workspace::AddPrinter(string& printerSerial)
{
	printerList.push_back(printerSerial);
	return 0;
}

int Workspace::AddTask(Task& inputTask)
{
	taskList.push_back(inputTask);
	return 0;
}

int Workspace::AddUser(string& inputUser)
{
	userList.push_back(inputUser);
	return 0;
}


void Workspace::LoadProductList(vector<string>& inputList)
{
	productList = inputList;
}

void Workspace::LoadPrinterList(vector<string>& inputList)
{
	printerList = inputList;
}

void Workspace::LoadTaskList(vector<Task>& inputList)
{
	taskList = inputList;
}

void Workspace::LoadUserList(vector<string>& inputList)
{
	userList = inputList;
}


void Workspace::GetProductList(vector<string>& inputList)
{
	inputList = productList;
}

void Workspace::GetPrinterList(vector<string>& inputList)
{
	inputList = printerList;
}

void Workspace::GetTaskList(vector<Task>& inputList)
{
	inputList = taskList;
}

void Workspace::GetUserList(vector<string>& inputList)
{
	inputList = userList;
}