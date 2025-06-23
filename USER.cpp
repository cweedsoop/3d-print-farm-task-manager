

#include "USER.h"

#include <string>

using namespace std;

void User::SetName(string& inputName)
{
	name = inputName;
}

const string& User::GetName()
{
	return name;
}