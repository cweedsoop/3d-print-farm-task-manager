#pragma once

#include <vector>
#include <string>

using namespace std;

class Product
{
public:
	//template <typename T>
	void SetName(string& inputName);

	string GetName();

	void SetProductID(int& ID);

	int GetProductID();

	void DisplayColorStyleList();

	void GetColorsStylesList(vector<string>& dataVec);

	int AddToColorStyleList(string& newStyle);

	int RemoveFromColorStyleList(int& entryNum);

	int EraseColorStyleList();

	void SetCurrColor(string& color);

	string GetCurrColor();

	void DisplayFilamentTypes();

	vector<string> GetFilamentTypes();

	int AddFilamentType(string newFilament);

	int RemoveFilamentType(int& entryNum);

	int EraseFilamentList();

	int DisplayFullProductInfo();

	int GetNumLines();

	int GetNumColorsStyles();

	int GetNumFilamentTypes();

private:
	string name;
	int productID = 0;
	vector<string> colorAndStyleList;
	string currColor = "null";
	vector<string> filamentTypesNeeded;
};

//File format:
//total count
//nextID
// 
//For each product:
//1. total number of lines occupied (7 + size of colorAndStyleList + size of filamentTypesNeeded
//2. name
//3. productID (NOT CHANGEABLE)
//4. number of colors and styles
//0. color/style list
//5. currColor (null outside of a task)
//6. number of filament types needed
//0. filamentTypesNeeded
//7. empty line for spacing