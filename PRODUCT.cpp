

#include <iostream>
#include <string>

#include "PRODUCT.h"

using namespace std;

//template <typename T>
void Product::SetName(string& inputName)
{
	name = inputName;
}

string Product::GetName()
{
	return name;
}

void Product::SetProductID(int& ID)
{
	productID = ID;
}

int Product::GetProductID()
{
	return productID;
}

void Product::DisplayColorStyleList()
{
	for (int i = 0; i < colorAndStyleList.size(); ++i)
	{		
		cout << i + 1 << ". " << colorAndStyleList.at(i) << endl;
	}
}


void Product::GetColorsStylesList(vector<string>& dataVec)
{
	dataVec = colorAndStyleList;
}


int Product::AddToColorStyleList(string& newStyle)
{
	colorAndStyleList.push_back(newStyle);
	return 0;
}

int Product::RemoveFromColorStyleList(int& entryNum)
{
	int entryIndex = 0;
	entryIndex = entryNum - 1;
	int lastIndex = 0;
	lastIndex = colorAndStyleList.size() - 1;

	colorAndStyleList.at(entryIndex) = colorAndStyleList.at(lastIndex);
	colorAndStyleList.pop_back();

	return 0;
}

int Product::EraseColorStyleList()
{
	colorAndStyleList.resize(0);
	return 0;
}

void Product::SetCurrColor(string& color)
{
	currColor = color;
}

string Product::GetCurrColor()
{
	return currColor;
}

void Product::DisplayFilamentTypes()
{
	for (int i = 0; i < filamentTypesNeeded.size(); ++i)
	{
		cout << i + 1 << ". " << filamentTypesNeeded.at(i);
	}
}

vector<string> Product::GetFilamentTypes()
{
	return filamentTypesNeeded;
}

int Product::AddFilamentType(string newFilament)
{
	filamentTypesNeeded.push_back(newFilament);

	return 0;
}

int Product::RemoveFilamentType(int& entryNum)
{
	int entryIndex = 0;
	entryIndex = entryNum - 1;
	int lastIndex = 0;
	lastIndex = filamentTypesNeeded.size() - 1;

	filamentTypesNeeded.at(entryIndex) = filamentTypesNeeded.at(lastIndex);
	filamentTypesNeeded.pop_back();

	return 0;
}

int Product::EraseFilamentList()
{
	filamentTypesNeeded.resize(0);
	return 0;
}

int Product::DisplayFullProductInfo()
{
	cout << name << endl;
	cout << "Product ID: " << productID << endl << endl;
	cout << "Available colors and styles:" << endl;

	for (int i = 0; i < colorAndStyleList.size(); ++i)
	{
		cout << "  " << i + 1 << ". " << colorAndStyleList.at(i) << endl;
	}

	cout << endl << "Current color/style: " << endl;
	cout << "  " << currColor << endl << endl;

	cout << "Filament types needed: " << endl;

	for (int i = 0; i < filamentTypesNeeded.size(); ++i)
	{
		cout << "  " << i + 1 << ". " << filamentTypesNeeded.at(i) << endl;
	}

	return 0;
}

int Product::GetNumLines()
{
	int num = 0;
	num = 7 + colorAndStyleList.size() + filamentTypesNeeded.size();
	return num;
}

int Product::GetNumColorsStyles()
{
	int num = 0;
	num = colorAndStyleList.size();
	return num;
}

int Product::GetNumFilamentTypes()
{
	int num = 0;
	num = filamentTypesNeeded.size();
	return num;
}