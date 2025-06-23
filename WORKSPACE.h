#pragma once

#include <string>
#include <vector>
#include "PRODUCT.h"
#include "PRINTER.h"
#include "TASK.h"

using namespace std;

class Workspace
{
public:	
	void SetName(string& name);

	const string& GetName();

	int AddProduct(string& productName);

	int AddPrinter(string& printerSerial);

	int AddTask(Task& inputTask);

	int AddUser(string& inputUser);

	void LoadProductList(vector<string>& inputList);

	void LoadPrinterList(vector<string>& inputList);

	void LoadTaskList(vector<Task>& inputList);

	void LoadUserList(vector<string>& inputList);

	void GetProductList(vector<string>& inputList);

	void GetPrinterList(vector<string>& inputList);

	void GetTaskList(vector<Task>& inputList);

	void GetUserList(vector<string>& inputList);



private:
	string workspaceName;
	vector<string> productList;
	vector<string> printerList;	
	vector<Task> taskList;
	vector<string> userList;
};


template<typename T>
int WriteToWorkspaceDataFile(string& filename, vector<T>& dataVec)
{
	ofstream printerFileWrite;
	int count = 0;

	printerFileWrite.open(filename);

	if (!printerFileWrite.is_open())
	{
		cout << "Unable to open data file" << endl;
		return -1;
	}

	count = dataVec.size();
	printerFileWrite << count << endl;

	for (int i = 0; i < count; ++i)
	{
		printerFileWrite << dataVec.at(i) << endl;
	}

	printerFileWrite.close();
	return 0;
}


//tasklist file format:
//count
//taskname
//taskuser
//status
//product name
//product ID
//number of colors and styles
//color/style list
//currColor
//number of filament types needed
//filament types needed
//number of assigned printers
//printers serial number list
//space between tasks