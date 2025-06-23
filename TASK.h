#pragma once

#include <string>
#include <vector>
#include "PRODUCT.h"
#include "PRINTER.h"
#include "USER.h"

using namespace std;

class Task
{
public:

	void SetTaskName(string& inputName);

	const string& GetTaskName();

	void SetUser(string& userName);

	const string& GetUser();

	void SetStatus(string& inputStatus);

	const string& GetStatus();

	void SetCurrProduct(Product& inputProduct);

	Product& GetCurrProduct();

	void AddPrinter(string& printerName);

	void LoadPrinters(vector<string>& dataVec);

	void GetPrinterList(vector<string>& dataVec);

	int ErasePrinterList();	


private:
	string taskName;
	string taskUser;
	string status = "Ongoing"; //ongoing and finished. Eventually include queued status once scheduling is implemented
	Product currProduct;
	vector<string> assignedPrinters;
};