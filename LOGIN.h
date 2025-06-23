#pragma once


#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>


#include "MYUTILITIES.h"
#include "HASHTABLE.h"

using namespace std;


int loginMenu();
int login();
int makeAccount();
int GetNewUserName(string& newUserName);
int GetNewPasscode(string& passcode);

unsigned long hashEncryption(string& input);

int loginMenu()
{
  int menuInput = 0;
  bool LoggedIn = false;

  while (LoggedIn == false)
  {
    cout << "Task Manager Login:" << endl << endl;
    cout << "  1. Login" << endl;
    cout << "  2. Create Account" << endl;
    cout << "  3. Exit" << endl;

    while (true)
    {
      menuInput = _getch();

      if (menuInput == 0 || menuInput == 224)
      {
        menuInput = _getch();
        continue;
      }

      if (menuInput == 49)
      {
        int returnVal = 0;
        system("CLS");
        returnVal = login();
        system("CLS");

        if (returnVal == 1) //logged in
        {
          return 1; //Enter Main Menu
        }
        break;
      }

      if (menuInput == 50)
      {
        system("CLS");
        makeAccount();
        system("CLS");
        break;
      }

      else if (menuInput == 51)
      {
        return 0;
      }
    }
  }
  return 0;
}


int login()
{
  HashTable userData(20);
  ifstream dataRead;
  string line;
  int count = 0;
  string key;
  string userName;

  dataRead.open("userAuthentification.txt");

  if (!dataRead.is_open())
  {
    cout << "Could not open datafile" << endl;
    return -1;
  }

  getline(dataRead, line);
  count = stoi(line);

  for (int i = 0; i < count; ++i)
  {
    getline(dataRead, key);
    getline(dataRead, userName);
    userData.insert(key, userName);
  }

  string currName;
  string passcode;
  unsigned long convert = 0;
  string currKey;
  int found = 0;
  int menuInput = 0;

  while (true)
  {
    cout << "Username: ";
    currName = GetlineEX();

    cout << endl << endl;
    cout << "Passcode: ";
    passcode = GetlineEX();

    convert = hashEncryption(passcode);
    currKey = to_string(convert);

    found = userData.findPair(currKey, currName);

    if (found != 1) //not found
    {
      system("CLS");
      cout << "Incorrect Username and Password combination" << endl;
      cout << "Press 1 to reenter, or press 2 to cancel login: " << endl;

      while (true)
      {
        menuInput = _getch();

        if (menuInput == 0 || menuInput == 224)
        {
          menuInput = _getch();
          continue;
        }

        if (menuInput == 49) //reenter
        {
          system("CLS");
          break;
        }

        else if (menuInput == 50)
        {
          dataRead.close();
          return 0; //did not login
        }
      }
    }

    else if (found == 1)
    {
      dataRead.close();
      return 1; //logged in
    }
  }
  dataRead.close();
  return 0;
}



int makeAccount()
{
  string userName;
  string passcode;
  int returnVal = 0;
  unsigned long key = 0;

  returnVal = GetNewUserName(userName);
  if (returnVal == -1)
  {
    return 0; //no account created
  }

  returnVal = GetNewPasscode(passcode);
  if (returnVal == -1)
  {
    return 0; //no account created
  }

  key = hashEncryption(passcode);
  string keyString;
  keyString = to_string(key);

  ifstream dataRead;
  string line;
  int count = 0;
  vector<string> dataVec;
  ofstream dataWrite;

  dataRead.open("userAuthentification.txt");

  if (!dataRead.is_open())
  {
    cout << "Could not open datafile" << endl;
    return -1;
  }

  getline(dataRead, line);
  count = stoi(line);

  for (int i = 0; i < count; ++i)
  {
    getline(dataRead, line); //key
    dataVec.push_back(line);
    getline(dataRead, line); //Username
    dataVec.push_back(line);
  }

  dataVec.push_back(keyString);
  dataVec.push_back(userName);
  ++count;

  dataRead.close();

  dataWrite.open("userAuthentification.txt");

  if (!dataWrite.is_open())
  {
    cout << "Could not open datafile" << endl;
    return -1;
  }

  dataWrite << count << endl;
  int max = 2 * count; //2 lines per data entry

  for (int i = 0; i < max; ++i)
  {
    dataWrite << dataVec.at(i) << endl;
  }

  dataWrite.close();

  cout << "New account succesfully created" << endl << endl;
  cout << "Press any key to return to the login menu:" << endl;
  int exit = 0;
  exit = _getch();
  system("CLS");

  return 0;
}

int GetNewUserName(string& newUserName)
{
  ifstream userInfo;
  int menuInput = 0;
  bool hasSpaces = true;
  string line;
  int count = 0;
  string tempPasscode;
  string tempUserName;
  bool unique = false;

  while (true)
  {
    system("CLS");
    cout << "Enter a username." << endl << endl << "Your username must be unique, and cannot contain spaces." << endl;
    cout << "Minimum username length is 4 characters, maximum length is 30." << endl << endl << "Your username: ";

    newUserName = GetlineEX();
    hasSpaces = false;
    unique = true;

    if ((newUserName.size() < 4) || (newUserName.size() > 30))
    {
      cout << endl << endl << newUserName << " is not a valid username. Username must be at least 4 characters long, and no more than 31 characters long." << endl << endl;
      cout << "Press 1 to enter a valid username" << endl << "Press 2 to exit account creation" << endl;

      while (true)
      {
        menuInput = _getch();

        if (menuInput == 0 || menuInput == 224)
        {
          menuInput = _getch();
          continue;
        }

        if (menuInput == 49)
        {
          break;
        }

        else if (menuInput == 50)
        {
          return -1; //did not create new username
        }
      }
      continue;
    }

    for (int i = 0; i < newUserName.size(); ++i) //check if has spaces
    {
      if ((newUserName.at(i) == ' ') || (newUserName.at(i) == '\t'))
      {
        hasSpaces = true;
        i = newUserName.size();
      }
    }

    if (hasSpaces == true)
    {
      cout << endl << endl << newUserName << " is not a valid username. Usernames cannot contain spaces." << endl << endl;
      cout << "Enter 1 to enter a valid username" << endl << "Enter 2 to exit account creation" << endl;

      while (true)
      {
        menuInput = _getch();

        if (menuInput == 0 || menuInput == 224)
        {
          menuInput = _getch();
          continue;
        }

        if (menuInput == 49)
        {
          break;
        }

        else if (menuInput == 50)
        {
          return -1;
        }
      }
      continue;
    }

    userInfo.open("userAuthentification.txt");
    if (!userInfo.is_open()) //check if data file exists
    {
      cout << "Could not open data file." << endl;
      return -1; // error code is returned
    }

    getline(userInfo, line);
    count = stoi(line);

    for (int i = 0; i < count; ++i)
    {
      userInfo >> tempPasscode;
      userInfo >> tempUserName;

      if (tempUserName == newUserName)
      {
        unique = false;
        i = count;
      }
    }

    if (unique == false)
    {
      userInfo.close();
      cout << endl << endl << newUserName << " is not a valid username. Username already exists." << endl << endl;
      cout << "Press 1 to try a different username" << endl;
      cout << "Press 2 to exit account creation" << endl;

      while (true)
      {
        menuInput = _getch();

        if (menuInput == 0 || menuInput == 224)
        {
          menuInput = _getch();
          continue;
        }

        if (menuInput == 49)
        {
          break;
        }

        else if (menuInput == 50)
        {
          userInfo.close();
          return -1;
        }
      }
      continue;
    }
    break;
  }

  userInfo.close();
  system("CLS");
  cout << "New Username created: " << newUserName << endl << endl;
  cout << "Press any key to continue:" << endl;
  int exit = 0;
  exit = _getch();
  system("CLS");

  return 1;
}

int GetNewPasscode(string& passcode)
{
  int menuInput = 0;
  bool confirm = false;

  while (confirm == false)
  {
    cout << "Enter a 4 character passcode: " << endl << endl;
    passcode = GetlineEX(4);


    cout << endl << endl << "New passcode: " << passcode << endl << endl;
    cout << "Press 1 to confirm" << endl;
    cout << "Press 2 to re-enter" << endl;
    cout << "Press 3 to cancel account creation" << endl;

    while (true)
    {
      menuInput = _getch();

      if (menuInput == 0 || menuInput == 224)
      {
        menuInput = _getch();
        continue;
      }

      if (menuInput == 49)
      {
        confirm = true;
        system("CLS");
        break;
      }

      if (menuInput == 50)
      {
        system("CLS");
        break;
      }

      else if (menuInput == 51)
      {
        return -1; //cancel account creation
      }
    }
  }

  return 0;
}

unsigned long hashEncryption(string& input)
{
  unsigned long tempVal = 0;
  unsigned long key = 0;
  unsigned int length = 0;

  length = input.size();

  for (int i = 0; i < length; ++i)
  {
    tempVal = tempVal + input.at(i);
  }

  key = tempVal * length * 739 * 1609 + (1);

  return key;
}

