#pragma once

#include <string>

using namespace std;

class User
{
public:
	void SetName(string& inputName);

	const string& GetName();

private:
	string name;
};