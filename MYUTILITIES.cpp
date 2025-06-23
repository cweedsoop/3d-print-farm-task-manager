/*
    Filename: MYUTILITIES.cpp
    Description: cpp file for MYUTILITIES.h
    Author: [Jingfu Peng]
    Class: [CSCI 120-70]
    Date: [7/1/2024]
 */

#include "MYUTILITIES.h"
#include <iostream>
#include <conio.h>

string GetlineEX(int maxlength)
{
  string tempString;

  while (true)
  {
    int input = _getch();

    if (input == 0 || input == 224)
    {
      input = _getch();
      continue;
    }

    if (input == 13)
    {
      break;
    }

    if (input == 8)
    {
      cout << "\b \b";
      if (tempString.size() > 0)
      {
        tempString.pop_back();
      }
    }

    else
    {
      if ((input >= 33 && input <= 126) || (input >= 9 && input <= 13) || input == 32)
      {
        tempString = tempString + (char)input;
        cout << (char)input;
      }
    }

    if (tempString.size() == maxlength)
    {
      break;
    }
  }

  return tempString;
}

void RemoveStartingWhitespace(string& inputString)
{
  size_t i = size_t(inputString.find_first_not_of(" \t\f\v\n\r"));

  if (i != -1)
  {
    inputString = inputString.substr(i);
  }
  else
  {
    inputString.clear();
  }
}

void RemoveEndingWhitespace(string& inputString)
{
  inputString.resize(size_t(inputString.find_last_not_of(" \t\f\v\n\r")) + 1); //Deletes trailing whitespaces
}

void WhitespaceCleanup(string& inputString) //Needs independent testing
{
  for (int i = 0; i < inputString.size(); ++i)
  {
    if (inputString.at(i) == '\t' || inputString.at(i) == '\f' || inputString.at(i) == '\v' || inputString.at(i) == '\n' || inputString.at(i) == '\r')
    {
      inputString[i] = ' ';
    }
  }

  for (int i = inputString.size() - 1; i > 0; --i)
  {
    if (inputString.at(i) == ' ')
    {
      if (inputString.at(i - 1) == ' ')
      {
        inputString.erase(i - 1, 1);
      }
    }
  }
}

bool CheckDigitString(string inputString)
{
  for (int i = 0; i < inputString.size(); ++i)
  {
    if (isdigit(inputString[i]) == 0)
    {
      return false;
    }
  }

  return true;
}