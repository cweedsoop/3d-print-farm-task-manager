/*
    Author: Jingfu Peng
 */

#include <iostream>
#include <conio.h>
#include <fstream>


#include "HASHTABLE.h"
#include "LOGIN.h"
#include "WORKSPACE.h"
#include "PRODUCT.h"
#include "PRINTER.h"
#include "TASK.h"
#include "USER.h"
#include "MYUTILITIES.h"

using namespace std;

int MainMenu();

int LoadWorkspace(string& workspaceName, Workspace& inputWorkspace);
int WorkspaceMenu(Workspace& currSpace);
int FindWorkspace(string& workSpaceName);
int CreateWorkspace();
int WriteToTaskFile(string& filename, vector<Task> dataVec);

int WorkspaceProductMenu(string& filename, vector<string>& dataVec);
int AddProductToWorkspace(string& filename, vector<string>& dataVec);
int RemoveProductFromWorkspace(string& filename, vector<string>& dataVec);
int WriteToWorkspaceProductFile(string& filename, vector<string>& dataVec);

int WorkspacePrinterMenu(string& filename, vector<string>& dataVec, Workspace& currSpace);
int AddPrinterToWorkspace(string& filename, vector<string>& dataVec, Workspace& currSpace);
int RemovePrinterFromWorkspace(string& filename, vector<string>& dataVec);
int WriteToWorkspacePrinterFile(string& filename, vector<string>& dataVec);

int WorkspaceUserMenu(string& filename, vector<string>& dataVec);
int AddUserToWorkspace(string& filename, vector<string>& dataVec);
int RemoveUserFromWorkspace(string& filename, vector<string>& dataVec);
int WriteToWorkspaceUserFile(string& filename, vector<string>& dataVec);


int LoadProductData(int& count, int& nextID, vector<Product>& dataVec);
int WriteProductData(int count, int nextID, vector<Product>& dataVec);
int EditExistingProduct(Product& inputProduct);
int ViewAndEditProducts();
int AddRemoveProductMasterlist();
int AddProductToMasterlist();
int RemoveProductFromMasterlist();
int SetProductColorStyle(Product& inputProduct);

int LoadPrinterMasterlist(int& count, vector<Printer>& dataVec);
int WritePrinterMasterList(int& count, vector<Printer>& dataVec);
int CreatePrinter(int& count, vector<Printer>& dataVec);
int ManagePrinters();
int PrinterFactoryDisplay(int& count, vector<Printer>& printerMasterlist);

int CreateNewTask(Workspace& currSpace, Task& newTask, vector<Task>& taskList, vector<string>& productList, vector<string>& printerList, vector<string>& userList);
int CheckAvailablePrinters(vector<string>& printerList, int& count, vector<Printer>& dataVec, vector<string>& availableList);
int GetAssignedPrinterIndex(int& numPrintersAvailable, int& numAssignedPrinters);
int ChangeAssignedPrinterData(Workspace& currSpace, string& printerName, Task& assignedTask, int& count, vector<Printer>& dataVec);
int SetTaskUser(string& userName, vector<string>& userList);
int SetTaskProduct(Product& inputProduct, vector<string> productList);
int LoadTaskData(const string& filename, vector<Task>& dataVec);
int ViewTaskDetails(Task& inputTask);
int TaskMenu(Workspace& currSpace, vector<Task>& taskList, vector<string>& productList, vector<string>& printerList, vector<string>& userList);

int LoadUserMasterlist(int& count, vector<User>& dataVec);
int CreateUser(int& count, vector<User>& userMasterlist);
int ManageUsers();


int main()
{
  while (true)
  {
    int loginVal = 0;

    loginVal = loginMenu(); //Uses a hash table for quickly checking login credentials; uses a hash function to encrypt passcode

    if (loginVal == 0)
    {
      system("CLS");
      return 0;
    }


    int mainMenuInput = 0;

    while (true)
    {
      mainMenuInput = MainMenu();

      if (mainMenuInput == 49) //Open workspace
      {
        system("CLS");
        string workspaceName;
        FindWorkspace(workspaceName); //represents workplace place in list.

        if (workspaceName > "0") //Workspace was found/selected
        {
          system("CLS");
          Workspace currWorkspace;
          LoadWorkspace(workspaceName, currWorkspace);
          WorkspaceMenu(currWorkspace);


        }
      }

      else if (mainMenuInput == 50) //Create Workspace
      {
        system("CLS");
        CreateWorkspace();
      }

      else if (mainMenuInput == 51) //View all products/edit existing products
      {
        system("CLS");
        ViewAndEditProducts();
        system("CLS");
      }

      else if (mainMenuInput == 52) //add or remove products from masterlist
      {
        system("CLS");
        AddRemoveProductMasterlist();
        system("CLS");
      }

      else if (mainMenuInput == 53) //Manage Printers
      {
        system("CLS");
        ManagePrinters();
        system("CLS");
      }

      else if (mainMenuInput == 54) //Manage Users
      {
        system("CLS");
        ManageUsers();
        system("CLS");
      }

      else if (mainMenuInput == 55) //Logout
      {
        system("CLS");
        break;
      }
    }
  }

  return 0;
}


int MainMenu() 
{
  int menuInput = 0;

  cout << "Task Manager" << endl << endl;
  cout << "    " << "1. Select Workspace" << endl;
  cout << "    " << "2. Create New Workspace" << endl;
  cout << "    " << "3. View Product Masterlist/Edit Products" << endl;
  cout << "    " << "4. Add or Remove Product from Masterlist" << endl;
  cout << "    " << "5. View and Manage Printers" << endl;
  cout << "    " << "6. View and Manage Users" << endl;
  cout << "    " << "7. Logout" << endl;

  while (menuInput < 49 || menuInput > 55)
  {
    menuInput = _getch();
  }

  return menuInput;
}


int LoadWorkspace(string& workspaceName, Workspace& targetWorkspace)
{
  ifstream productListRead;
  ifstream printerListRead;
  ifstream userListRead;
  string line;

  targetWorkspace.SetName(workspaceName); //Set current workspace name

  string productListName;
  string printerListName;
  string taskListName;
  string userListName;

  productListName = workspaceName + "_product_list.txt";
  printerListName = workspaceName + "_printer_list.txt";
  taskListName = workspaceName + "_task_list.txt";
  userListName = workspaceName + "_user_list.txt";

  vector<string> tempData;

  //Load Product List:
  productListRead.open(productListName);

  if (!productListRead.is_open()) //file not found
  {
    cout << "Could not open product list data file." << endl;
    return -1;
  }

  getline(productListRead, line);
  int count = 0;
  count = stoi(line); // get count

  for (int i = 0; i < count; ++i)
  {
    getline(productListRead, line);
    tempData.push_back(line);
  }

  targetWorkspace.LoadProductList(tempData);
  tempData.resize(0);
  productListRead.close();

  //Load Printer List

  printerListRead.open(printerListName);

  if (!printerListRead.is_open()) //file not found
  {
    cout << "Could not open product list data file." << endl;
    return -1;
  }

  getline(printerListRead, line);
  count = stoi(line); // get count

  for (int i = 0; i < count; ++i)
  {
    getline(printerListRead, line);
    tempData.push_back(line);
  }

  targetWorkspace.LoadPrinterList(tempData);
  tempData.resize(0);
  printerListRead.close();

  //Load Task List

  vector<Task> taskData;
  LoadTaskData(taskListName, taskData);
  targetWorkspace.LoadTaskList(taskData);

  //Load User List

  userListRead.open(userListName);

  if (!userListRead.is_open()) //file not found
  {
    cout << "Could not open product list data file." << endl;
    return -1;
  }

  getline(userListRead, line);
  count = stoi(line); // get count

  for (int i = 0; i < count; ++i)
  {
    getline(userListRead, line);
    tempData.push_back(line);
  }

  targetWorkspace.LoadUserList(tempData);
  tempData.resize(0);
  userListRead.close();

  return 0;
}


int WorkspaceMenu(Workspace& currSpace)
{
  vector<Task> taskList;
  vector<string> productList;
  vector<string> printerList;
  vector<string> userList;

  currSpace.GetTaskList(taskList);
  currSpace.GetProductList(productList);
  currSpace.GetPrinterList(printerList);
  currSpace.GetUserList(userList);

  while (true)
  {
    cout << "Workspace: " << currSpace.GetName() << endl << endl;
    cout << "    1. Tasks" << endl;
    cout << "    2. Products" << endl;
    cout << "    3. Printers" << endl;
    cout << "    4. Users" << endl;
    cout << "    5. Exit this Workspace" << endl;

    int menuInput = 0;

    while (true)
    {
      menuInput = _getch();

      if (menuInput < 49 || menuInput > 53)
      {
        continue;
      }

      break;
    }

    if (menuInput == 49) //Tasks
    {
      system("CLS");
      TaskMenu(currSpace, taskList, productList, printerList, userList);
    }

    else if (menuInput == 50) //Products
    {
      system("CLS");
      string filename;
      filename = currSpace.GetName() + "_product_list.txt";
      WorkspaceProductMenu(filename, productList);
      system("CLS");
    }

    else if (menuInput == 51) //Printers
    {
      system("CLS");
      string filename;
      filename = currSpace.GetName() + "_printer_list.txt";
      WorkspacePrinterMenu(filename, printerList, currSpace);
      system("CLS");
    }

    else if (menuInput == 52) //Users
    {
      system("CLS");
      string filename;
      filename = currSpace.GetName() + "_user_list.txt";
      WorkspaceUserMenu(filename, userList);
      system("CLS");
    }

    else if (menuInput == 53) //Exit
    {
      system("CLS");
      return 0;
    }
  }

  return 0;
}


int FindWorkspace(string& workSpaceName) //Returns number in list //Done
{
  ifstream nameRead;
  vector<string> workSpaceNames;

  nameRead.open("workspaceList.txt"); //open list of workspace names

  if (!nameRead.is_open()) //file not found
  {
    cout << "Could not open data file." << endl;
    return -1;
  }

  cout << "Workspaces:" << endl << endl;

  string tempName;
  string count;

  getline(nameRead, count);

  if (count == "0") //No workspaces in file
  {
    cout << "No workspaces found.";
    cout << endl << "Press any key to continue:";

    int menuInput = _getch();
    system("CLS");
    nameRead.close();
    return 0;
  }

  else
  {
    int max = 0;

    max = stoi(count);

    for (int i = 0; i < max; ++i)
    {
      getline(nameRead, tempName);
      workSpaceNames.push_back(tempName);
      cout << "    " << i + 1 << ". " << tempName << endl;
    }

    cout << endl << "Select a workspace, or enter 'R' to return to the main menu: ";

    string menuInput;

    while (true)
    {
      menuInput = GetlineEX();
      RemoveStartingWhitespace(menuInput);
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R") //Return to main menu
      {
        system("CLS");
        nameRead.close();
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << endl << endl << "Invalid entry. Please enter a valid number, or 'R' to return to the previous screen: " << endl;
        continue;
      }

      else if (isDigit == true)
      {
        int selection = 0;
        selection = stoi(menuInput);

        if (selection < 1 || selection > max)
        {
          cout << endl << endl << "Invalid entry. Please enter a valid number, or 'R' to return to the previous screen:" << endl;
          continue;
        }

        else
        {
          nameRead.close();
          workSpaceName = workSpaceNames.at(selection - 1);
          return 1;
        }
      }
    }
  }
  return 0;
}


int CreateWorkspace() //Done
{
  string newWorkspaceName;
  bool goodName = false;
  ifstream workspaceListRead;
  ofstream workspaceListWrite;
  ofstream productList;
  ofstream printerList;
  ofstream taskList;
  ofstream userList;

  while (goodName == false) //Prompt user to enter new workspace name
  {
    cout << "New Workspace Name: ";
    newWorkspaceName = GetlineEX();
    RemoveEndingWhitespace(newWorkspaceName);

    if (newWorkspaceName.size() == 0) //if empty, or only whitespaces
    {
      cout << endl << endl << "Workspace Name cannot be empty." << endl << endl;
      cout << "    1. Try a new name" << endl;
      cout << "    2. Return to main menu" << endl;

      int menuInput = 0;

      while (menuInput < 49 || menuInput >> 50)
      {
        menuInput = _getch();

        if (menuInput == 49) // Re-enter workspace name
        {
          system("CLS");
          break;
        }

        else if (menuInput == 50)
        {
          system("CLS");
          return -2; // Did not create a new workspace, return
        }
      }
      continue;
    }

    RemoveStartingWhitespace(newWorkspaceName); //Cleanup name formatting
    WhitespaceCleanup(newWorkspaceName);

    workspaceListRead.open("workspaceList.txt"); //open data file

    if (!workspaceListRead.is_open()) //file not found
    {
      cout << "Could not open data file." << endl;
      return -1;
    }

    else //Load data file
    {
      int count;
      string line;
      vector<string> workspaceNames;

      getline(workspaceListRead, line);
      count = stoi(line);

      workspaceNames.push_back(line);

      for (int i = 0; i < count; ++i)
      {
        getline(workspaceListRead, line);
        workspaceNames.push_back(line);

        if (workspaceListRead.eof()) //Count is incorrect
        {
          return -3;
        }
      }

      workspaceListRead.close();
      string tempName;
      goodName = true;

      for (int i = 1; i < workspaceNames.size(); ++i) //check uniqueness, start at index 1 to skip count
      {
        tempName = workspaceNames.at(i);

        if (tempName == newWorkspaceName)
        {
          goodName = false;
          i = workspaceNames.size(); //to exit for-loop
          cout << endl << endl;
          cout << "A workspace with this name already exists." << endl << endl;
          cout << "    1. Try a new name" << endl;
          cout << "    2. Return to main menu" << endl;

          int menuInput = 0;

          while (menuInput < 49 || menuInput >> 50)
          {
            menuInput = _getch();

            if (menuInput == 49) // Re-enter workspace name
            {
              system("CLS");
              //break;
            }

            else if (menuInput == 50)
            {
              system("CLS");
              return -2; // Did not create a new workspace, return
            }
          }
        }

        else
        {
          goodName = true;
        }
      }

      if (goodName == true)
      {
        workspaceNames.push_back(newWorkspaceName); //append new name
        ++count;
        workspaceNames.at(0) = to_string(count); //update count
        workspaceListWrite.open("workspaceList.txt");

        if (!workspaceListWrite.is_open())
        {
          cout << "Could not open data file." << endl;
          return -1;
        }

        for (int i = 0; i < workspaceNames.size(); ++i) //Overwrite file
        {
          workspaceListWrite << workspaceNames.at(i) << endl;
        }

        workspaceListWrite.close();

        string productListName;
        string printerListName;
        string taskListName;
        string userListName;

        productListName = newWorkspaceName + "_product_list.txt";
        printerListName = newWorkspaceName + "_printer_list.txt";
        taskListName = newWorkspaceName + "_task_list.txt";
        userListName = newWorkspaceName + "_user_list.txt";

        productList.open(productListName, ios_base::app); //create text files for workspace lists
        productList << "0" << endl; //Initialize count to zero
        productList.close();

        printerList.open(printerListName, ios_base::app);
        printerList << "0" << endl;
        printerList.close();

        taskList.open(taskListName);
        taskList << "0" << endl;
        taskList.close();

        userList.open(userListName);
        userList << "0" << endl;
        userList.close();



        system("CLS");
        cout << "New workspace created: " << newWorkspaceName << endl;
        cout << endl << "Press any key to continue: ";
        int menuInput = _getch();
        system("CLS");
        return 1; //Workspace created
      }
    }
  }
  return 0;
}


int WriteToTaskFile(string& filename, vector<Task> dataVec)
{
  ofstream taskDataWrite;
  string line;
  int count;
  vector<string> colorsStyles;
  vector<string> filamentTypes;
  vector<string> printerNames;

  taskDataWrite.open(filename);

  if (!taskDataWrite.is_open())
  {
    cout << "Could not open data file" << endl;
    return -1;
  }

  count = dataVec.size();
  Task* pTempTask = 0;

  taskDataWrite << count << endl;

  for (int i = 0; i < count; ++i)
  {
    pTempTask = &dataVec.at(i);
    taskDataWrite << pTempTask->GetTaskName() << endl;
    taskDataWrite << pTempTask->GetUser() << endl;
    taskDataWrite << pTempTask->GetStatus() << endl;

    Product& tempProduct = pTempTask->GetCurrProduct();
    taskDataWrite << tempProduct.GetName() << endl;
    taskDataWrite << tempProduct.GetProductID() << endl;

    int numStyles = 0;
    numStyles = tempProduct.GetNumColorsStyles();
    taskDataWrite << numStyles << endl;
    tempProduct.GetColorsStylesList(colorsStyles);
    for (int j = 0; j < numStyles; ++j)
    {
      taskDataWrite << colorsStyles.at(j) << endl;
    }
    taskDataWrite << tempProduct.GetCurrColor() << endl;

    int numFilaments = 0;
    numFilaments = tempProduct.GetNumFilamentTypes();
    taskDataWrite << numFilaments << endl;
    filamentTypes = tempProduct.GetFilamentTypes();
    for (int j = 0; j < numFilaments; ++j)
    {
      taskDataWrite << filamentTypes.at(j) << endl;
    }

    int numPrinters = 0;
    pTempTask->GetPrinterList(printerNames);
    numPrinters = printerNames.size();
    taskDataWrite << numPrinters << endl;
    for (int j = 0; j < numPrinters; ++j)
    {
      taskDataWrite << printerNames.at(j) << endl;
    }

    taskDataWrite << endl;
  }

  taskDataWrite.close();
  return 0;
}


int WorkspaceProductMenu(string& filename, vector<string>& dataVec)
{
  int menuInput = 0;
  int count = 0;

  while (true)
  {
    cout << "Product List: " << endl << endl;
    cout << "Press 1 to add a Product to this Workspace" << endl;
    cout << "Press 2 to remove a Product from this Workspace" << endl;
    cout << "Press 3 to return to the previous screen:" << endl << endl;

    count = dataVec.size();

    if (count == 0)
    {
      cout << "No Products to Display" << endl << endl;
    }

    for (int i = 0; i < count; ++i)
    {
      cout << "  " << i + 1 << ". " << dataVec.at(i) << endl;
    }

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
        system("CLS");
        AddProductToWorkspace(filename, dataVec);
        system("CLS");
        break;
      }

      else if (menuInput == 50)
      {
        system("CLS");
        RemoveProductFromWorkspace(filename, dataVec);
        system("CLS");
        break;
      }

      else if (menuInput == 51)
      {
        system("CLS");
        return 0;
      }

      else
      {
        continue;
      }
    }
  }

  return 0;
}


int AddProductToWorkspace(string& filename, vector<string>& dataVec)
{
  vector<Product> productListData;
  bool alreadyAdded;
  vector<Product*> nonRedundant;
  Product* pProduct = 0;
  string currName;
  int count = 0;
  int nextID = 0;
  string menuInput;
  int selection = 0;
  string chosenProduct;

  LoadProductData(count, nextID, productListData);

  while (true)
  {
    cout << "Add Product: " << endl << endl;
    cout << "Select a product to add to this workspace" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    if (count == 0)
    {
      cout << "No Products To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < count; ++i) //check to see which products are already added
    {
      pProduct = &productListData.at(i);
      currName = pProduct->GetName();
      alreadyAdded = false;

      for (int j = 0; j < dataVec.size(); ++j)
      {
        if (currName == dataVec.at(j))
        {
          alreadyAdded = true;
          j = dataVec.size();
        }
      }

      if (alreadyAdded == false)
      {
        nonRedundant.push_back(pProduct);
      }
    }

    int displayCount = 0;
    displayCount = nonRedundant.size();

    if (displayCount == 0)
    {
      cout << "No Products To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < displayCount; ++i)
    {
      pProduct = nonRedundant.at(i);
      currName = pProduct->GetName();
      cout << "  " << i + 1 << ". " << currName << endl;
    }

    cout << endl;

    while (true)
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R")
      {
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      selection = stoi(menuInput);

      if (selection < 1 || selection > count)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      break;
    }

    pProduct = nonRedundant.at(selection - 1);
    chosenProduct = pProduct->GetName();
    dataVec.push_back(chosenProduct);
    WriteToWorkspaceProductFile(filename, dataVec);
    nonRedundant.resize(0);

    system("CLS");
    cout << chosenProduct << " was added to this Workspace" << endl;
    cout << "Press any key to continue:" << endl;
    int exit = 0;
    exit = _getch();
    system("CLS");
  }

  return 0;
}


int RemoveProductFromWorkspace(string& filename, vector<string>& dataVec)
{
  int count = 0;
  string menuInput;
  int selection = 0;
  string chosenProduct;

  while (true)
  {
    cout << "Remove Product: " << endl << endl;
    cout << "Select a product to remove from this workspace" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    count = dataVec.size();

    if (count == 0)
    {
      cout << "No Products To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < count; ++i)
    {
      cout << "  " << i + 1 << ". " << dataVec.at(i) << endl;
    }

    while (true)
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R")
      {
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      selection = stoi(menuInput);

      if (selection < 1 || selection > count)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      break;
    }

    chosenProduct = dataVec.at(selection - 1);
    dataVec.at(selection - 1) = dataVec.at(count - 1);
    dataVec.pop_back();
    WriteToWorkspaceProductFile(filename, dataVec);

    system("CLS");
    cout << chosenProduct << " was removed from this Workspace" << endl;
    cout << "Press any key to continue:" << endl;
    int exit = 0;
    exit = _getch();
    system("CLS");
  }

  return 0;
}


int WriteToWorkspaceProductFile(string& filename, vector<string>& dataVec)
{
  ofstream productFileWrite;
  int count = 0;

  productFileWrite.open(filename);

  if (!productFileWrite.is_open())
  {
    cout << "Unable to open data file" << endl;
    return -1;
  }

  count = dataVec.size();
  productFileWrite << count << endl;

  for (int i = 0; i < count; ++i)
  {
    productFileWrite << dataVec.at(i) << endl;
  }

  productFileWrite.close();
  return 0;
}


int WorkspacePrinterMenu(string& filename, vector<string>& dataVec, Workspace& currSpace)
{
  int menuInput = 0;

  while (true)
  {
    cout << "Printer List: " << endl << endl;
    cout << "Press 1 to add a Printer to this Workspace" << endl;
    cout << "Press 2 to remove a Printer from this Workspace" << endl;
    cout << "Press 3 to return to the previous screen:" << endl << endl;

    for (int i = 0; i < dataVec.size(); ++i)
    {
      cout << "  " << i + 1 << ". " << dataVec.at(i) << endl;
    }

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
        system("CLS");
        AddPrinterToWorkspace(filename, dataVec, currSpace);
        system("CLS");
        break;
      }

      else if (menuInput == 50)
      {
        system("CLS");
        RemovePrinterFromWorkspace(filename, dataVec);
        system("CLS");
        break;
      }

      else if (menuInput == 51)
      {
        system("CLS");
        return 0;
      }

      else
      {
        continue;
      }
    }
  }

  return 0;
}


int AddPrinterToWorkspace(string& filename, vector<string>& dataVec, Workspace& currSpace)
{
  vector<Printer> printerListData;
  bool alreadyAdded;
  vector<Printer*> nonRedundant;
  Printer* pPrinter = 0;
  string currName;
  int count = 0;
  string menuInput;
  int selection = 0;
  string chosenPrinter;

  LoadPrinterMasterlist(count, printerListData);

  while (true)
  {
    cout << "Add Printer: " << endl << endl;
    cout << "Select a Printer to add to this Workspace" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    if (count == 0)
    {
      cout << "No Printers To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < count; ++i) //check to see which printers are already added
    {
      pPrinter = &printerListData.at(i);
      currName = pPrinter->GetName();
      alreadyAdded = false;

      for (int j = 0; j < dataVec.size(); ++j)
      {
        if (currName == dataVec.at(j))
        {
          alreadyAdded = true;
          j = dataVec.size();
        }
      }

      if (alreadyAdded == false)
      {
        nonRedundant.push_back(pPrinter);
      }
    }

    int displayCount = 0;
    displayCount = nonRedundant.size();

    if (displayCount == 0)
    {
      cout << "No Printers To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < displayCount; ++i)
    {
      pPrinter = nonRedundant.at(i);
      currName = pPrinter->GetName();
      cout << "  " << i + 1 << ". " << currName << endl;
    }

    cout << endl;

    while (true)
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R")
      {
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      selection = stoi(menuInput);

      if (selection < 1 || selection > count)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      break;
    }

    pPrinter = nonRedundant.at(selection - 1);
    chosenPrinter = pPrinter->GetName();
    dataVec.push_back(chosenPrinter);
    WriteToWorkspacePrinterFile(filename, dataVec);
    nonRedundant.resize(0);

    //NOTE: the below would be applicable if implementation changes such that 
    //printers are no longer manageable across multiple workspaces
    //string workspaceName = currSpace.GetName(); 
    //pPrinter->SetWorkspace(workspaceName); //Update printer's assigned workspace

    //WritePrinterMasterList(count, printerListData); //Update printer masterfile

    system("CLS");
    cout << chosenPrinter << " was added to this Workspace" << endl;
    cout << "Press any key to continue:" << endl;
    int exit = 0;
    exit = _getch();
    system("CLS");
  }


  return 0;
}


int RemovePrinterFromWorkspace(string& filename, vector<string>& dataVec)
{
  int count = 0;
  string menuInput;
  int selection = 0;
  string chosenPrinter;
  vector<Printer> printerListData;

  while (true)
  {
    cout << "Remove Printer: " << endl << endl;
    cout << "Select a Printer to remove from this workspace" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    count = dataVec.size();

    if (count == 0)
    {
      cout << "No Printers To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < count; ++i)
    {
      cout << "  " << i + 1 << ". " << dataVec.at(i) << endl;
    }

    while (true)
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R")
      {
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      selection = stoi(menuInput);

      if (selection < 1 || selection > count)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      break;
    }

    chosenPrinter = dataVec.at(selection - 1);
    dataVec.at(selection - 1) = dataVec.at(count - 1);
    dataVec.pop_back();
    WriteToWorkspacePrinterFile(filename, dataVec);

    //Update printer masterfile
    int dataCount = 0;
    Printer* pPrinter = 0;
    string emptyString;

    emptyString.resize(0);
    LoadPrinterMasterlist(dataCount, printerListData);

    for (int i = 0; i < dataCount; ++i)
    {
      pPrinter = &printerListData.at(i);
      if (chosenPrinter == pPrinter->GetName())
      {
        pPrinter->SetWorkspace(emptyString);
        i = dataCount;
      }
    }

    WritePrinterMasterList(dataCount, printerListData);

    system("CLS");
    cout << chosenPrinter << " was removed from this Workspace" << endl;
    cout << "Press any key to continue:" << endl;
    int exit = 0;
    exit = _getch();
    system("CLS");
  }

  return 0;
}


int WriteToWorkspacePrinterFile(string& filename, vector<string>& dataVec)
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


int WorkspaceUserMenu(string& filename, vector<string>& dataVec)
{
  int menuInput = 0;

  while (true)
  {
    cout << "User List: " << endl << endl;
    cout << "Press 1 to add a User to this Workspace" << endl;
    cout << "Press 2 to remove a User from this Workspace" << endl;
    cout << "Press 3 to return to the previous screen:" << endl << endl;

    for (int i = 0; i < dataVec.size(); ++i)
    {
      cout << "  " << i + 1 << ". " << dataVec.at(i) << endl;
    }

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
        system("CLS");
        AddUserToWorkspace(filename, dataVec);
        system("CLS");
        break;
      }

      else if (menuInput == 50)
      {
        system("CLS");
        RemoveUserFromWorkspace(filename, dataVec);
        system("CLS");
        break;
      }

      else if (menuInput == 51)
      {
        system("CLS");
        return 0;
      }

      else
      {
        continue;
      }
    }
  }

  return 0;
}


int AddUserToWorkspace(string& filename, vector<string>& dataVec)
{
  vector<User> userListData;
  bool alreadyAdded;
  vector<User*> nonRedundant;
  User* pUser = 0;
  string currName;
  int count = 0;
  string menuInput;
  int selection = 0;
  string chosenUser;

  LoadUserMasterlist(count, userListData);

  while (true)
  {
    cout << "Add User: " << endl << endl;
    cout << "Select a User to add to this Workspace" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    if (count == 0)
    {
      cout << "No Users To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < count; ++i) //check to see which Users are already added
    {
      pUser = &userListData.at(i);
      currName = pUser->GetName();
      alreadyAdded = false;

      for (int j = 0; j < dataVec.size(); ++j)
      {
        if (currName == dataVec.at(j))
        {
          alreadyAdded = true;
          j = dataVec.size();
        }
      }

      if (alreadyAdded == false)
      {
        nonRedundant.push_back(pUser);
      }
    }

    int displayCount = 0;
    displayCount = nonRedundant.size();

    if (displayCount == 0)
    {
      cout << "No Printers To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < displayCount; ++i)
    {
      pUser = nonRedundant.at(i);
      currName = pUser->GetName();
      cout << "  " << i + 1 << ". " << currName << endl;
    }

    cout << endl;

    while (true)
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R")
      {
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      selection = stoi(menuInput);

      if (selection < 1 || selection > count)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      break;
    }

    pUser = nonRedundant.at(selection - 1);
    chosenUser = pUser->GetName();
    dataVec.push_back(chosenUser);
    WriteToWorkspacePrinterFile(filename, dataVec);
    nonRedundant.resize(0);

    system("CLS");
    cout << chosenUser << " was added to this Workspace" << endl;
    cout << "Press any key to continue:" << endl;
    int exit = 0;
    exit = _getch();
    system("CLS");
  }

  return 0;
}


int RemoveUserFromWorkspace(string& filename, vector<string>& dataVec)
{
  int count = 0;
  string menuInput;
  int selection = 0;
  string chosenUser;
  //vector<Printer> printerListData;

  while (true)
  {
    cout << "Remove User: " << endl << endl;
    cout << "Select a User to remove from this workspace" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    count = dataVec.size();

    if (count == 0)
    {
      cout << "No Users To Display." << endl;
      cout << "Press any key to continue:" << endl << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      return 0;
    }

    for (int i = 0; i < count; ++i)
    {
      cout << "  " << i + 1 << ". " << dataVec.at(i) << endl;
    }

    while (true)
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R")
      {
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      selection = stoi(menuInput);

      if (selection < 1 || selection > count)
      {
        cout << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      break;
    }

    chosenUser = dataVec.at(selection - 1);
    dataVec.at(selection - 1) = dataVec.at(count - 1);
    dataVec.pop_back();
    WriteToWorkspaceUserFile(filename, dataVec);


    system("CLS");
    cout << chosenUser << " was removed from this Workspace" << endl;
    cout << "Press any key to continue:" << endl;
    int exit = 0;
    exit = _getch();
    system("CLS");
  }

  return 0;
}


int WriteToWorkspaceUserFile(string& filename, vector<string>& dataVec)
{
  ofstream userFileWrite;
  int count = 0;

  userFileWrite.open(filename);

  if (!userFileWrite.is_open())
  {
    cout << "Unable to open data file" << endl;
    return -1;
  }

  count = dataVec.size();
  userFileWrite << count << endl;

  for (int i = 0; i < count; ++i)
  {
    userFileWrite << dataVec.at(i) << endl;
  }

  userFileWrite.close();
  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

int LoadProductData(int& count, int& nextID, vector<Product>& dataVec) //Done
{
  ifstream productListRead;
  string line;
  int numLines = 0;
  Product tempProduct;

  productListRead.open("product_masterlist.txt"); //Load data

  if (!productListRead.is_open())
  {
    return -1; //Could not open file
  }

  getline(productListRead, line); //number of products
  count = stoi(line);

  getline(productListRead, line); //nextID
  nextID = stoi(line);

  for (int i = 0; i < count; ++i) //Load products into data vector
  {
    getline(productListRead, line);
    numLines = stoi(line);

    getline(productListRead, line); //Name
    tempProduct.SetName(line);

    getline(productListRead, line); //ProductID
    int tempID = 0;
    tempID = stoi(line);
    tempProduct.SetProductID(tempID);

    getline(productListRead, line);
    int numColorStyle = 0; //Number of colors and styles
    numColorStyle = stoi(line);
    for (int i = 0; i < numColorStyle; ++i) //load colors and styles
    {
      getline(productListRead, line);
      tempProduct.AddToColorStyleList(line);
    }

    getline(productListRead, line); //current color
    tempProduct.SetCurrColor(line);

    getline(productListRead, line); //Number of filament types needed
    int numFilaments = 0;
    numFilaments = stoi(line);
    for (int i = 0; i < numFilaments; ++i) //load filament types
    {
      getline(productListRead, line);
      tempProduct.AddFilamentType(line);
    }

    getline(productListRead, line); //consume empty space between product entries.

    dataVec.push_back(tempProduct);
    tempProduct.EraseColorStyleList();
    tempProduct.EraseFilamentList();
  }
  productListRead.close();
  return 0;
}


int WriteProductData(int count, int nextID, vector<Product>& dataVec) //Done
{
  ofstream ProductListWrite;
  Product currProduct;
  int numColorsStyles = 0;
  int numFilamentTypes = 0;
  vector<string> colorsStylesList;
  vector<string> filamentsList;

  ProductListWrite.open("product_masterlist.txt");

  if (!ProductListWrite.is_open())
  {
    cout << "Could not open data file";
    return -1;
  }

  ProductListWrite << count << endl;
  ProductListWrite << nextID << endl;

  for (int i = 0; i < dataVec.size(); ++i)
  {
    currProduct = dataVec.at(i);
    ProductListWrite << currProduct.GetNumLines() << endl;
    ProductListWrite << currProduct.GetName() << endl;
    ProductListWrite << currProduct.GetProductID() << endl;

    numColorsStyles = currProduct.GetNumColorsStyles();
    ProductListWrite << numColorsStyles << endl;
    currProduct.GetColorsStylesList(colorsStylesList);
    for (int i = 0; i < numColorsStyles; ++i)
    {
      ProductListWrite << colorsStylesList.at(i) << endl;
    }

    ProductListWrite << "null" << endl;

    numFilamentTypes = currProduct.GetNumFilamentTypes();
    ProductListWrite << numFilamentTypes << endl;
    filamentsList = currProduct.GetFilamentTypes();
    for (int i = 0; i < numFilamentTypes; ++i)
    {
      ProductListWrite << filamentsList.at(i) << endl;
    }

    ProductListWrite << endl; //space between entries
  }

  ProductListWrite.close();
  return 0;
}


int EditExistingProduct(Product& inputProduct) //Done
{
  cout << endl << endl << "This feature is still under construction." << endl;
  cout << "Press any key to continue: " << endl;

  int exit = 0;
  exit = _getch();
  system("CLS");
  //Return 1 if an edit was made, otherwise return 0

  return 0;
}


int ViewAndEditProducts() //Done
{
  vector<Product> productListData;
  Product tempProduct;
  string line;
  //int numLines = 0; //number of lines occupied by a product in the file
  int count = 0;
  int nextID = 0;

  LoadProductData(count, nextID, productListData);

  Product currProduct;
  string currName;
  int currID = 0;
  string menuInput;
  int selection = 0;
  bool madeEdit = false;

  while (true) //List out product names and IDs
  {

    if (madeEdit == true) //reload data if an edit was made in the last loop iteration
    {
      LoadProductData(count, nextID, productListData);
    }

    cout << "Product Masterlist:" << endl << endl;

    if (count == 0)
    {
      cout << "No Products To Display." << endl;
    }

    else
    {
      cout << "Enter an entry number to view detailed information for that product." << endl;
    }

    cout << "Enter 'R' to return to the previous screen." << endl << endl;

    for (int i = 0; i < count; ++i)
    {
      currProduct = productListData.at(i);
      currName = productListData.at(i).GetName();
      currID = productListData.at(i).GetProductID();
      cout << "    " << i + 1 << ". " << currName << endl;
      cout << "    - Product ID: " << currID << endl << endl;
    }

    while (true)
    {
      menuInput = GetlineEX();
      RemoveStartingWhitespace(menuInput);
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      else if (menuInput == "r" || menuInput == "R") //Return to prior menu
      {
        system("CLS");
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << endl << endl << "Invalid entry. Please enter a valid number, or 'R' to return to the previous screen: " << endl;
        continue;
      }

      else if (isDigit == true)
      {
        selection = stoi(menuInput);

        if (selection < 1 || selection > productListData.size())
        {
          cout << endl << endl << "Invalid entry. Please enter a valid number, or 'R' to return to the previous screen:" << endl;
          continue;
        }
      }

      break;
    }

    while (true)
    {
      system("CLS");
      currProduct = productListData.at(selection - 1);
      currProduct.DisplayFullProductInfo();
      cout << endl << endl << "Press 1 to edit " << currProduct.GetName() << endl;
      cout << "Press 2 to return to Product List view" << endl;

      int choice = 0;

      while (choice < 49 || choice > 50)
      {
        choice = _getch();
      }

      if (choice == 49) //edit entry
      {
        int editReturn = 0;
        editReturn = EditExistingProduct(currProduct);

        if (editReturn == 0) // no edit made
        {
          madeEdit = false;
        }

        else if (editReturn == 1) //edit was made
        {
          madeEdit = true;
          WriteProductData(count, nextID, productListData);
        }
      }

      else if (choice == 50) //Return to list view, no edit
      {
        system("CLS");
        madeEdit = false;
        break;
      }
    }
  }
  return 0;
}


int AddRemoveProductMasterlist()
{
  while (true)
  {
    cout << "Product Masterlist Editing Utility:" << endl << endl;
    cout << "    1. Add a product to the masterlist" << endl;
    cout << "    2. Remove a product from the masterlist" << endl;
    cout << "    3. Return to main menu" << endl;

    int menuInput = 0;

    while (menuInput < 49 || menuInput > 51)
    {
      menuInput = _getch();
    }

    if (menuInput == 49)
    {
      system("CLS");
      AddProductToMasterlist();
      continue;
    }

    else if (menuInput == 50)
    {
      system("CLS");
      RemoveProductFromMasterlist();
      continue;
    }

    else if (menuInput == 51)
    {
      return 0;
    }
  }
  return 0;
}


int AddProductToMasterlist()
{
  vector<Product> productListData;
  int count = 0;
  int nextID = 0;

  LoadProductData(count, nextID, productListData); //Load Data

  string newName;
  string dataName;
  bool goodName = false;

  while (true) //Generate new product name
  {
    cout << "Creating New Product:" << endl << endl;
    cout << "Enter the Product Name:" << endl << endl;

    newName = GetlineEX();
    RemoveEndingWhitespace(newName);

    if (newName.size() == 0) //if empty, or only whitespaces
    {
      cout << endl << "Product name cannot be empty." << endl << endl;
      cout << "    1. Try a new name" << endl;
      cout << "    2. Return to previous menu" << endl;

      int menuInput = 0;

      while (menuInput < 49 || menuInput >> 50)
      {
        menuInput = _getch();

        if (menuInput == 49) // Re-enter product name
        {
          system("CLS");
          break;
        }

        else if (menuInput == 50)
        {
          system("CLS");
          return -2; // Did not create a new product, return
        }
      }
      continue;
    }

    RemoveStartingWhitespace(newName); //Clean up the name formatting
    WhitespaceCleanup(newName);

    if (count == 0)
    {
      goodName = true;
    }

    else
    {
      for (int i = 0; i < count; ++i) //Check uniqueness
      {
        goodName = true;
        dataName = productListData.at(i).GetName();

        if (newName == dataName)
        {
          goodName = false;
          break;
        }
      }
    }

    if (goodName == false)
    {
      cout << endl << endl << "A Product with this name already exists. " << endl;
      cout << "    1. Try a new name" << endl;
      cout << "    2. Return to previous menu" << endl;

      int menuInput = 0;

      while (menuInput < 49 || menuInput >> 50)
      {
        menuInput = _getch();

        if (menuInput == 49) // Re-enter product name
        {
          system("CLS");
        }

        else if (menuInput == 50)
        {
          system("CLS");
          return -2; // Did not create a new product, return
        }
      }
    }

    else if (goodName == true)
    {
      system("CLS");
      break;
    }
  }

  //Unique Product name has been confirmed.

  Product newProduct;

  newProduct.SetName(newName);
  newProduct.SetProductID(nextID);

  ++count;
  ++nextID;

  while (true) //Add color and style options
  {
    cout << "Enter a color or style option for " << newProduct.GetName() << "." << endl;
    cout << "To continue without adding, press Enter:" << endl << endl;

    string colorStyleOption;
    colorStyleOption = GetlineEX();
    RemoveEndingWhitespace(colorStyleOption);

    if (colorStyleOption.size() == 0)
    {
      break;
    }

    else
    {
      RemoveStartingWhitespace(colorStyleOption);
      WhitespaceCleanup(colorStyleOption);
      newProduct.AddToColorStyleList(colorStyleOption);
      cout << endl << endl;
    }
  }

  system("CLS");

  while (true) //Add filament type options
  {
    cout << "Enter a Filament Type for " << newProduct.GetName() << "." << endl;
    cout << "To continue without adding, press Enter:" << endl << endl;

    string filamentType;
    filamentType = GetlineEX();
    RemoveEndingWhitespace(filamentType);

    if (filamentType.size() == 0)
    {
      break;
    }

    else
    {
      RemoveStartingWhitespace(filamentType);
      WhitespaceCleanup(filamentType);
      newProduct.AddFilamentType(filamentType);
      cout << endl << endl;
    }
  }

  system("CLS");

  productListData.push_back(newProduct);
  WriteProductData(count, nextID, productListData);

  cout << "New Product " << newProduct.GetName() << " has been created." << endl << endl;
  cout << "Press any key to continue: " << endl;

  int pressKey = 0;
  pressKey = _getch();
  system("CLS");
}


int RemoveProductFromMasterlist()
{
  vector<Product> productListData;
  int count = 0;
  int nextID = 0;
  string menuInput;
  int selectedID = 0;
  Product* tempProduct = 0;

  LoadProductData(count, nextID, productListData);

  cout << "Enter the ID number of the Product you wish to delete. To return to the previous screen, enter 'R': " << endl;

  while (true)
  {
    menuInput = GetlineEX();
    RemoveStartingWhitespace(menuInput);
    RemoveEndingWhitespace(menuInput);

    if (menuInput.size() == 0)
    {
      continue;
    }

    else if (menuInput == "r" || menuInput == "R")
    {
      system("CLS");
      return 0; //return without deletion
    }

    bool isDigit = false;
    isDigit = CheckDigitString(menuInput);

    if (isDigit == false)
    {
      cout << endl << endl << "Invalid entry. Please enter a valid number, or 'R' to return to the previous screen: " << endl;
      continue;
    }

    selectedID = stoi(menuInput);

    if (selectedID <= 1000 || selectedID >= nextID) //check within valid range
    {
      cout << endl << endl << "Invalid entry. Please enter a valid number, or 'R' to return to the previous screen: " << endl;
      continue;
    }

    else
    {
      int tempID = 0;
      bool IDfound = false;
      int deletionIndex = 0;

      for (int i = 0; i < productListData.size(); ++i) //Check if product exists in list
      {
        tempProduct = &productListData.at(i);
        tempID = tempProduct->GetProductID();

        if (selectedID == tempID)
        {
          IDfound = true;
          deletionIndex = i;
          break;
        }
      }

      if (IDfound == false)
      {
        cout << endl << endl << "Entry not found. Please enter a valid number, or 'R' to return to the previous screen: " << endl;
        continue;
      }

      else if (IDfound == true)
      {
        system("CLS");
        cout << "Are you sure you want to delete " << tempProduct->GetName() << "?" << endl << endl;
        cout << "Enter 1 to confirm deletion." << endl;
        cout << "Enter 2 to cancel." << endl << endl;

        int menuInput = 0;

        while (!cin || menuInput < 1 || menuInput > 2)
        {
          cin >> menuInput;
        }

        if (menuInput == 1)
        {
          int lastIndex = 0;
          lastIndex = productListData.size() - 1;
          productListData.at(deletionIndex) = productListData.at(lastIndex);
          productListData.pop_back();

          --count;

          WriteProductData(count, nextID, productListData);

          cout << endl << "Deletion successful" << endl;
          cout << "Press any key to continue: " << endl;

          int keyPress = 0;
          keyPress = _getch();
          system("CLS");
          return 1; //return after deletion
        }

        else if (menuInput == 2)
        {
          system("CLS");
          return 0; //return without deletion
        }
      }
    }
  }
  return 0;
}


int SetProductColorStyle(Product& inputProduct)
{
  int selection = 0;
  int max = 0;
  vector<string> colorStyleList;
  string color;

  cout << "Select from the following colors and styles:" << endl << endl;
  inputProduct.GetColorsStylesList(colorStyleList);
  max = colorStyleList.size();

  for (int i = 0; i < max; ++i)
  {
    cout << "  " << i + 1 << ". " << colorStyleList.at(i) << endl;
  }

  cin >> selection;

  while (!cin || selection < 1 || selection > max)
  {
    cin.clear();
    cin.ignore();
    cout << "Invalid entry, please enter again: " << endl << endl;
    cin >> selection;
  }

  color = colorStyleList.at(selection - 1);
  inputProduct.SetCurrColor(color);

  return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////


int LoadPrinterMasterlist(int& count, vector<Printer>& dataVec)
{
  ifstream printerDataRead;
  string line;
  Printer tempPrinter;

  printerDataRead.open("printer_masterlist.txt");

  if (!printerDataRead.is_open())
  {
    cout << "Could not open data file" << endl;
    return -1;
  }

  getline(printerDataRead, line);
  count = stoi(line);

  for (int i = 0; i < count; ++i)
  {
    getline(printerDataRead, line); //name
    tempPrinter.SetName(line);

    getline(printerDataRead, line); //serial
    tempPrinter.SetSerial(line);

    getline(printerDataRead, line); //workspace
    tempPrinter.SetWorkspace(line);

    getline(printerDataRead, line); //current task
    tempPrinter.SetCurrTask(line);

    getline(printerDataRead, line); //current product name
    tempPrinter.SetCurrProduct(line);

    getline(printerDataRead, line); //current color/style
    tempPrinter.SetCurrColorStyle(line);

    getline(printerDataRead, line); //current user's name
    tempPrinter.SetCurrUser(line);

    getline(printerDataRead, line); //filament status
    tempPrinter.SetFilamentStatus(line);

    getline(printerDataRead, line); //functional 0 false, 1 true
    int functional = 0;
    functional = stoi(line);
    tempPrinter.SetIsFunctional(functional);

    getline(printerDataRead, line); //space between entries

    dataVec.push_back(tempPrinter);
  }
  printerDataRead.close();
  return 0;
}


int WritePrinterMasterList(int& count, vector<Printer>& dataVec)
{
  ofstream printerDataWrite;
  string line;

  printerDataWrite.open("printer_masterlist.txt");

  if (!printerDataWrite.is_open())
  {
    cout << "Could not open data file" << endl;
    return -1;
  }

  printerDataWrite << count << endl;

  for (int i = 0; i < count; ++i)
  {
    printerDataWrite << dataVec.at(i).GetName() << endl;
    printerDataWrite << dataVec.at(i).GetSerial() << endl;
    printerDataWrite << dataVec.at(i).GetWorkspace() << endl;
    printerDataWrite << dataVec.at(i).GetCurrTask() << endl;
    printerDataWrite << dataVec.at(i).GetCurrProduct() << endl;
    printerDataWrite << dataVec.at(i).GetCurrColorStyle() << endl;
    printerDataWrite << dataVec.at(i).GetCurrUser() << endl;
    printerDataWrite << dataVec.at(i).GetFilamentStatus() << endl;
    printerDataWrite << dataVec.at(i).GetIsFunctional() << endl;
    printerDataWrite << endl;
  }

  printerDataWrite.close();

  return 0;
}


int CreatePrinter(int& count, vector<Printer>& dataVec)
{
  string newName;
  string tempName;
  bool goodName = false;
  string serialNum;
  string tempSerial;
  bool goodSerial = false;
  Printer newPrinter;

  cout << "Creating New Printer:" << endl << endl;

  //set name
  while (goodName == false)
  {
    PrinterEditPrompt("Printer Name", newName);
    goodName = true;

    for (int i = 0; i < count; ++i)
    {
      tempName = dataVec.at(i).GetName();

      if (tempName == newName)
      {
        i = count;
        cout << endl << endl << "A Printer with this name already exists." << endl << endl;
        cout << "Press 1 to try a new name" << endl;
        cout << "Press 2 to cancel Printer creation:" << endl << endl;

        int menuInput = 0;

        while (true)
        {
          menuInput = _getch();

          if (menuInput == 0 || menuInput == 224)
          {
            menuInput = _getch();
          }

          if (menuInput == 49)
          {
            i = count;
            goodName = false;
            system("CLS");
            break;
          }

          else if (menuInput == 50)
          {
            system("CLS");
            return 0;
          }

          else
          {
            continue;
          }
        }
      }
    }
  }


  cout << endl << endl;

  //set serial number
  while (goodSerial == false)
  {
    PrinterEditPrompt("Printer's Serial Number", serialNum);
    goodSerial = true;

    for (int i = 0; i < count; ++i)
    {
      tempSerial = dataVec.at(i).GetSerial();

      if (tempSerial == serialNum)
      {
        i = count;
        cout << endl << endl << "A Printer with this Serial Number already exists." << endl << endl;
        cout << "Press 1 to try a new Serial Number" << endl;
        cout << "Press 2 to cancel Printer creation:" << endl << endl;

        int menuInput = 0;

        while (true)
        {
          menuInput = _getch();

          if (menuInput == 0 || menuInput == 224)
          {
            menuInput = _getch();
          }

          if (menuInput == 49)
          {
            i = count;
            goodSerial = false;
            system("CLS");
            break;
          }

          else if (menuInput == 50)
          {
            system("CLS");
            return 0;
          }

          else
          {
            continue;
          }
        }
      }
    }
  }

  cout << endl << endl << "Are you sure you want to create the new Printer " << "'" << newName << "'?" << endl << endl;
  cout << "  1. Confirm" << endl;
  cout << "  2. Cancel" << endl;

  int menuInput = 0;

  while (menuInput != 49 && menuInput != 50)
  {
    menuInput = _getch();
  }

  if (menuInput == 49)
  {
    newPrinter.SetName(newName);
    newPrinter.SetSerial(serialNum);
    dataVec.push_back(newPrinter);
    ++count;

    WritePrinterMasterList(count, dataVec);

    cout << endl << "Printer " << "'" << newName << "' has been added to the masterlist." << endl << endl;
    cout << "Press any key to continue: " << endl;

    int exitKey = 0;
    exitKey = _getch();
    system("CLS");
    return 1;
  }

  else if (menuInput == 50)
  {
    system("CLS");
    return 0;
  }
  return 0;
}


int ManagePrinters()
{
  int count = 0;
  vector<Printer> printerMasterlist;
  int menuInput = 0;

  LoadPrinterMasterlist(count, printerMasterlist);

  while (true)
  {
    cout << "Printers:" << endl << endl;
    cout << "Press 'F' to enter Factory Display Mode" << endl;
    cout << "Press 'C' to create a new Printer" << endl;
    cout << "Press 'R' to return to the main menu: " << endl << endl;

    if (count == 0)
    {
      cout << "No Printers on file." << endl;
    }

    for (int i = 0; i < count; ++i)
    {
      cout << "  " << i + 1 << ". " << printerMasterlist.at(i).GetName() << endl;
    }

    while (true)
    {
      menuInput = _getch();

      if (menuInput == 0 || menuInput == 224) //control keys
      {
        menuInput = _getch();
      }

      if (menuInput == 70 || menuInput == 102) //factory display mode
      {
        break;
      }

      if (menuInput == 67 || menuInput == 99) //create printer
      {
        break;
      }

      else if (menuInput == 82 || menuInput == 114) //return to main menu
      {
        return 0;
      }

      else
      {
        cout << "Invalid input. Reenter: " << endl << endl;
        continue;
      }
    }

    if (menuInput == 70 || menuInput == 102) //factory display mode
    {
      system("CLS");
      PrinterFactoryDisplay(count, printerMasterlist);
      system("CLS");
      break;
    }

    if (menuInput == 67 || menuInput == 99) //create printer
    {
      system("CLS");
      CreatePrinter(count, printerMasterlist);
    }
  }
  return 0;
}


int PrinterFactoryDisplay(int& count, vector<Printer>& printerMasterlist)
{
  cout << "Printer Factory Display:" << endl << endl;
  cout << "Press [ESC] to exit." << endl << endl;

  Printer* pPrinter = 0;

  for (int i = 0; i < count; ++i)
  {
    pPrinter = &printerMasterlist.at(i);
    cout << "  " << i + 1 << ". " << pPrinter->GetName() << endl;
    cout << "     Serial Number: " << pPrinter->GetSerial() << endl;
    cout << "     Current Workspace: " << pPrinter->GetWorkspace() << endl;
    cout << "     Current Task: " << pPrinter->GetCurrTask() << endl;
    cout << "     Current Product: " << pPrinter->GetCurrProduct() << endl;
    cout << "     Current Color/Style: " << pPrinter->GetCurrColorStyle() << endl;
    cout << "     Current User: " << pPrinter->GetCurrUser() << endl;
    cout << "     Filament Status: " << pPrinter->GetFilamentStatus() << endl;

    bool functional = false;
    functional = pPrinter->GetIsFunctional();
    if (functional == true)
    {
      cout << "     Functioning Properly" << endl << endl;
    }

    else if (functional == false)
    {
      cout << "     OUT Of ORDER" << endl << endl;
    }
  }

  int exit = 0;

  while (true)
  {
    exit = _getch();

    if (exit == 0 || exit == 224)
    {
      exit = _getch();
    }

    else if (exit == 27)
    {
      return 0;
    }
  }
  return 0;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////


int CreateNewTask(Workspace& currSpace, Task& newTask, vector<Task>& taskList, vector<string>& productList, vector<string>& printerList, vector<string>& userList)
{
  int numPrintersAvailable = 0;
  string newName;
  string tempTaskname;
  bool goodName = false;
  int count = 0;
  string userName;
  Product currProduct;
  vector<Printer> printerMasterlist;
  vector<string> availablePrinters;
  string addedPrinter;

  cout << "Creating New Task:" << endl << endl;

  if (productList.size() == 0)
  {
    cout << "Product list for this workspace is empty." << endl;
    cout << "Please add a product to the workspace before creating a task" << endl << endl;
    cout << "Press any key to continue: " << endl;

    int exit = 0;
    exit = _getch();
    system("CLS");
    return 0;
  }

  if (printerList.size() == 0)
  {
    cout << "Printer list for this workspace is empty." << endl;
    cout << "Please add a printer to the workspace before creating a task" << endl << endl;
    cout << "Press any key to continue: " << endl;

    int exit = 0;
    exit = _getch();
    system("CLS");
    return 0;
  }

  if (userList.size() == 0)
  {
    cout << "User list for this workspace is empty." << endl;
    cout << "Please add a user to the workspace before creating a task" << endl << endl;
    cout << "Press any key to continue: " << endl;

    int exit = 0;
    exit = _getch();
    system("CLS");
    return 0;
  }

  //Check if any printers are available, and if there are any, add their names to the vector "availablePrinters"
  numPrintersAvailable = CheckAvailablePrinters(printerList, count, printerMasterlist, availablePrinters);

  if (numPrintersAvailable == 0)
  {
    cout << "All printers for this workspace are in use." << endl;
    cout << "A printer must be available for use before creating a task" << endl << endl;
    cout << "Press any key to continue: " << endl;

    int exit = 0;
    exit = _getch();
    system("CLS");
    return 0;
  }


  while (goodName == false)
  {
    cout << "Enter Task Name: " << endl << endl;

    while (true)
    {
      newName = GetlineEX();
      RemoveEndingWhitespace(newName);
      goodName = true;

      if (newName.size() == 0)
      {
        cout << "Task Name cannot be empty. Please reenter: " << endl << endl;
        continue;
      }
      break;
    }

    RemoveStartingWhitespace(newName);
    WhitespaceCleanup(newName);

    int taskListSize = 0;
    taskListSize = taskList.size();

    for (int i = 0; i < taskListSize; ++i) //check uniqueness
    {
      tempTaskname = taskList.at(i).GetTaskName();

      if (tempTaskname == newName)
      {
        i = taskListSize;
        cout << endl << "A task with this name already exists" << endl << endl;
        cout << "Press 1 to try a new name" << endl;
        cout << "Press 2 to cancel Task creation:" << endl << endl;

        int menuInput = 0;

        while (true)
        {
          menuInput = _getch();

          if (menuInput == 0 || menuInput == 224)
          {
            menuInput = _getch();
          }

          if (menuInput == 49)
          {
            goodName = false;
            system("CLS");
            break;
          }

          else if (menuInput == 50)
          {
            system("CLS");
            return 0;
          }

          else
          {
            continue;
          }
        }
      }

      else
      {
        goodName = true;
      }
    }
  }

  newTask.SetTaskName(newName);

  system("CLS");
  SetTaskUser(userName, userList);
  newTask.SetUser(userName);

  system("CLS");
  SetTaskProduct(currProduct, productList);

  system("CLS");
  SetProductColorStyle(currProduct);
  newTask.SetCurrProduct(currProduct);

  int numAssignedPrinters = 0;

  system("CLS");
  while (true)
  {
    cout << "Available Printers: " << endl << endl;
    numPrintersAvailable = availablePrinters.size();


    if (numPrintersAvailable == 0)
    {
      cout << endl << endl << "No more Printers available" << endl;
      cout << "Press any key to continue:" << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      break;
    }

    for (int i = 0; i < numPrintersAvailable; ++i)
    {
      cout << "  " << i + 1 << ". " << availablePrinters.at(i) << endl;
    }

    int index = 0;
    index = GetAssignedPrinterIndex(numPrintersAvailable, numAssignedPrinters);

    if (index >= 0)
    {
      addedPrinter = availablePrinters.at(index);
      newTask.AddPrinter(addedPrinter);
      ++numAssignedPrinters;
      availablePrinters.at(index) = availablePrinters.at(numPrintersAvailable - 1);
      availablePrinters.pop_back();
      ChangeAssignedPrinterData(currSpace, addedPrinter, newTask, count, printerMasterlist);
      system("CLS");
    }

    else if (index == -1)
    {
      break;
    }
  }
  return 1;
}


int CheckAvailablePrinters(vector<string>& printerList, int& count, vector<Printer>& dataVec, vector<string>& availableList)
{
  int listCount = 0;
  string listName;
  Printer* currPrinter = 0;
  string dataName;
  string currTask;
  int numAvailable = 0;

  listCount = printerList.size();
  LoadPrinterMasterlist(count, dataVec);

  for (int i = 0; i < listCount; ++i)
  {
    listName = printerList.at(i);

    for (int j = 0; j < count; ++j)
    {
      currPrinter = &dataVec.at(j);
      dataName = currPrinter->GetName();

      if (listName == dataName)
      {
        currTask = currPrinter->GetCurrTask();

        if (currTask.size() == 0)
        {
          availableList.push_back(dataName);
          ++numAvailable;
        }
      }
    }
  }
  return numAvailable;
}


int GetAssignedPrinterIndex(int& numPrintersAvailable, int& numAssignedPrinters)
{
  string selection;
  bool isDigit = false;
  int index = 0;

  cout << endl << "Select a Printer to assign to this Task." << endl;

  if (numAssignedPrinters != 0)
  {
    cout << "Enter 'C' << to continue without adding another Printer: " << endl;
  }

  while (true)
  {
    selection = GetlineEX();
    RemoveEndingWhitespace(selection);

    if (selection.size() == 0)
    {
      continue;
    }

    if ((numAssignedPrinters != 0 && selection == "C") || (numAssignedPrinters != 0 && selection == "c"))
    {
      system("CLS");
      return -1;
    }


    isDigit = CheckDigitString(selection);

    if (isDigit == false)
    {
      cout << "Invalid entry. Reenter: " << endl << endl;
      continue;
    }

    index = stoi(selection) - 1;

    if (index < 0 || index >= numPrintersAvailable)
    {
      cout << "Invalid entry. Reenter: " << endl << endl;
      continue;
    }

    else
    {
      return index;
    }
  }
  return 0;
}


int ChangeAssignedPrinterData(Workspace& currSpace, string& printerName, Task& assignedTask, int& count, vector<Printer>& dataVec)
{
  string workspaceName;
  string taskName;
  string productName;
  string colorStyle;
  string userName;
  string tempName;
  Printer* pPrinter = 0;

  workspaceName = currSpace.GetName();
  taskName = assignedTask.GetTaskName();
  Product& currProduct = assignedTask.GetCurrProduct();
  productName = currProduct.GetName();
  colorStyle = currProduct.GetCurrColor();
  userName = assignedTask.GetUser();

  for (int i = 0; i < count; ++i)
  {
    tempName = dataVec.at(i).GetName();

    if (tempName == printerName)
    {
      pPrinter = &dataVec.at(i);
      pPrinter->SetWorkspace(workspaceName);
      pPrinter->SetCurrTask(taskName);
      pPrinter->SetCurrProduct(productName);
      pPrinter->SetCurrColorStyle(colorStyle);
      pPrinter->SetCurrUser(userName);
      break;
    }
  }

  WritePrinterMasterList(count, dataVec);

  return 0;
}


int SetTaskUser(string& userName, vector<string>& userList)
{
  int selection = 0;
  int max = 0;

  cout << "User Selection:" << endl << endl;
  cout << "Users currently assigned to this workspace:" << endl << endl;

  max = userList.size();

  for (int i = 0; i < max; ++i)
  {
    cout << "  " << i + 1 << ". " << userList.at(i) << endl;
  }

  cin >> selection;

  while (!cin || selection < 1 || selection > max)
  {
    cin.clear();
    cin.ignore();
    cout << "Invalid entry, please enter again: " << endl << endl;
    cin >> selection;
  }

  userName = userList.at(selection - 1);
  return 0;
}


int SetTaskProduct(Product& inputProduct, vector<string> productList)
{
  int selection = 0;
  int max = 0;
  string productName;

  max = productList.size();

  cout << "Select a Product from the current Workspace:" << endl << endl;
  for (int i = 0; i < max; ++i)
  {
    cout << "  " << i + 1 << ". " << productList.at(i) << endl;
  }

  cin >> selection;

  while (!cin || selection < 1 || selection > max)
  {
    cin.clear();
    cin.ignore();
    cout << "Invalid entry, please enter again: " << endl << endl;
    cin >> selection;
  }

  productName = productList.at(selection - 1);

  int count = 0;
  int nextID = 0;
  vector<Product> productMasterlist;
  Product* pCurrProduct = 0;
  bool productFound = false;

  LoadProductData(count, nextID, productMasterlist);

  for (int i = 0; i < productMasterlist.size(); ++i)
  {
    pCurrProduct = &productMasterlist.at(i);

    if (productName == pCurrProduct->GetName())
    {
      productFound = true;
      break;
    }
  }

  if (productFound == false)
  {
    cout << "Error: workspace and product masterlist data mismatch.";
    return -1;
  }

  else
  {
    inputProduct = *pCurrProduct;
  }

  return 0;
}


int LoadTaskData(const string& filename, vector<Task>& dataVec)
{
  ifstream taskDataRead;
  string line;
  int count;

  taskDataRead.open(filename);

  if (!taskDataRead.is_open())
  {
    cout << "Could not open data file" << endl;
    return -1;
  }

  getline(taskDataRead, line);
  count = stoi(line);
  Task tempTask;
  Product tempProduct;

  for (int i = 0; i < count; ++i)
  {
    getline(taskDataRead, line);
    tempTask.SetTaskName(line);

    getline(taskDataRead, line);
    tempTask.SetUser(line);

    getline(taskDataRead, line);
    tempTask.SetStatus(line);

    getline(taskDataRead, line);
    tempProduct.SetName(line);

    getline(taskDataRead, line);
    int tempID = 0;
    tempID = stoi(line);
    tempProduct.SetProductID(tempID);

    getline(taskDataRead, line);
    int numColorStyle = 0; //Number of colors and styles
    numColorStyle = stoi(line);
    for (int i = 0; i < numColorStyle; ++i) //load colors and styles
    {
      getline(taskDataRead, line);
      tempProduct.AddToColorStyleList(line);
    }

    getline(taskDataRead, line); //current color
    tempProduct.SetCurrColor(line);

    getline(taskDataRead, line); //Number of filament types needed
    int numFilaments = 0;
    numFilaments = stoi(line);
    for (int i = 0; i < numFilaments; ++i) //load filament types
    {
      getline(taskDataRead, line);
      tempProduct.AddFilamentType(line);
    }

    getline(taskDataRead, line); //number of associated printers
    int numPrinters = 0;
    numPrinters = stoi(line);
    for (int i = 0; i < numPrinters; ++i) //load printer names
    {
      getline(taskDataRead, line);
      tempTask.AddPrinter(line);
    }

    getline(taskDataRead, line); //consume empty line

    tempTask.SetCurrProduct(tempProduct);
    dataVec.push_back(tempTask);

    tempTask.ErasePrinterList();
    tempProduct.EraseColorStyleList();
    tempProduct.EraseFilamentList();
  }

  taskDataRead.close();
  return 0;
}


int ViewTaskDetails(Task& inputTask)
{
  Product* pCurrProduct = 0;
  vector<string> printerList;

  pCurrProduct = &inputTask.GetCurrProduct();
  inputTask.GetPrinterList(printerList);

  cout << inputTask.GetTaskName() << ": " << endl << endl;
  cout << "Task User: " << inputTask.GetUser() << endl;
  cout << "Status: " << inputTask.GetStatus() << endl;
  pCurrProduct->DisplayFullProductInfo();
  cout << endl << "Currently Assigned Printers: " << endl;

  for (int i = 0; i < printerList.size(); ++i)
  {
    cout << "  " << i + 1 << ". " << printerList.at(i) << endl;
  }
  //Can add Edit functionality in the future
  return 0;
}


int TaskMenu(Workspace& currSpace, vector<Task>& taskList, vector<string>& productList, vector<string>& printerList, vector<string>& userList)
{
  Task* pCurrTask = 0;
  string menuInput;
  int selection = 0;

  while (true)
  {
    //currSpace.GetTaskList(taskList); //load task data
    cout << "Task View: " << currSpace.GetName() << endl << endl;
    cout << "Enter a task number to view task details" << endl;
    cout << "Enter 'C' to create a new Task" << endl;
    cout << "Enter 'R' to return to the previous screen:" << endl << endl;

    Task* currTask;

    for (int i = 0; i < taskList.size(); ++i)
    {
      currTask = &taskList.at(i);
      cout << i + 1 << ". " << currTask->GetTaskName() << endl;
    }

    while (true) //get user input
    {
      menuInput = GetlineEX();
      RemoveEndingWhitespace(menuInput);

      if (menuInput.size() == 0)
      {
        continue;
      }

      if (menuInput == "c" || menuInput == "C")
      {
        break;
      }

      if (menuInput == "r" || menuInput == "R")
      {
        system("CLS");
        return 0;
      }

      bool isDigit = false;
      isDigit = CheckDigitString(menuInput);

      if (isDigit == false)
      {
        cout << endl << "Invalid input, please reenter:" << endl << endl;
        continue;
      }

      if (isDigit == true)
      {
        selection = stoi(menuInput);
        if (selection < 1 || selection > taskList.size())
        {
          cout << endl << "Invalid input, please reenter:" << endl << endl;
          continue;
        }

        else
        {
          break;
        }
      }
    }

    if (menuInput == "c" || menuInput == "C") //Create new Task
    {
      int returnVal = 0;
      system("CLS");
      Task newTask;
      returnVal = CreateNewTask(currSpace, newTask, taskList, productList, printerList, userList);

      if (returnVal == 1) //task was created succesfully
      {
        //////////////////////
        //write to workspace's task list file using function AddTaskToWorkspace
        taskList.push_back(newTask);

        string spaceName;
        string fileName;

        spaceName = currSpace.GetName();
        fileName = spaceName + "_task_list.txt";
        WriteToTaskFile(fileName, taskList);

        LoadWorkspace(spaceName, currSpace);
        currSpace.GetTaskList(taskList); //reload task data


        cout << "New Task " << newTask.GetTaskName() << " has been created." << endl;
        cout << "Press any key to continue:" << endl;

        int exit = 0;
        exit = _getch();
        system("CLS");
      }

      continue;
    }

    else
    {
      system("CLS");
      pCurrTask = &taskList.at(selection - 1);
      ViewTaskDetails(*pCurrTask);

      cout << endl << endl << "Press any key to continue:" << endl;

      int exit = 0;
      exit = _getch();
      system("CLS");
      continue;
      // if edit task need to rewrite and reload
    }

    return 0;
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////

int LoadUserMasterlist(int& count, vector<User>& dataVec)
{
  ifstream userDataRead;
  string line;
  User tempUser;

  userDataRead.open("user_masterlist.txt");

  if (!userDataRead.is_open())
  {
    cout << "Could not open data file" << endl;
    return -1;
  }

  getline(userDataRead, line);
  count = stoi(line);

  for (int i = 0; i < count; ++i)
  {
    getline(userDataRead, line);
    tempUser.SetName(line);
    dataVec.push_back(tempUser);
  }

  userDataRead.close();
  return 0;
}


int CreateUser(int& count, vector<User>& userMasterlist)
{
  ofstream userDataWrite;
  string newName;
  string currName;
  User* pCurrUser = 0;

  cout << "Enter name of new User: " << endl << endl;

  bool goodName = false;

  while (goodName == false)
  {
    newName = GetlineEX();
    RemoveEndingWhitespace(newName);

    if (newName.size() == 0)
    {
      cout << "Name cannot be empty. Please reenter: " << endl << endl;
      continue;
    }

    goodName = true;
    RemoveStartingWhitespace(newName);
    WhitespaceCleanup(newName);

    for (int i = 0; i < userMasterlist.size(); ++i)
    {
      pCurrUser = &userMasterlist.at(i);
      currName = pCurrUser->GetName();

      if (newName == currName)
      {
        cout << "A user with this name already exists. Please reenter:" << endl << endl;
        goodName = false;
        break;
      }
    }
  }

  cout << endl << endl << "Are you sure you want to create the new User " << "'" << newName << "'?" << endl << endl;
  cout << "  1. Confirm" << endl;
  cout << "  2. Cancel" << endl;

  int menuInput = 0;

  while (menuInput != 49 && menuInput != 50)
  {
    menuInput = _getch();
  }

  if (menuInput == 49)
  {
    User newUser;

    newUser.SetName(newName);
    userMasterlist.push_back(newUser);
    ++count;

    userDataWrite.open("user_masterlist.txt");

    if (!userDataWrite.is_open())
    {
      cout << "Could not open data file" << endl;
      return -1;
    }

    userDataWrite << count << endl;
    for (int i = 0; i < count; ++i)
    {
      userDataWrite << userMasterlist.at(i).GetName() << endl;
    }

    userDataWrite.close();

    cout << endl << "User " << "'" << newName << "' has been added to the masterlist." << endl << endl;
    cout << "Press any key to continue: " << endl;

    int exitKey = 0;
    exitKey = _getch();
    system("CLS");
    return 1; //created a new user
  }

  else if (menuInput == 50)
  {
    system("CLS");
    return -2; //did not create new user
  }
  return 0;
}


int ManageUsers()
{
  int count = 0;
  vector<User> userMasterlist;
  int menuInput = 0;

  LoadUserMasterlist(count, userMasterlist);

  while (true)
  {
    cout << "User Masterlist:" << endl << endl;
    cout << "Press 'C' to create a new User" << endl;
    cout << "Press 'R' to return to the main menu: " << endl << endl;

    for (int i = 0; i < count; ++i)
    {
      cout << "  " << i + 1 << ". " << userMasterlist.at(i).GetName() << endl;
    }

    while (true)
    {
      menuInput = _getch();

      if (menuInput == 0 || menuInput == 224)
      {
        menuInput = _getch();
      }

      if (menuInput == 67 || menuInput == 99)
      {
        break;
      }

      else if (menuInput == 82 || menuInput == 114)
      {
        return 0;
      }

      else
      {
        cout << "Invalid input. Reenter: " << endl << endl;
        continue;
      }
    }

    if (menuInput == 67 || menuInput == 99)
    {
      system("CLS");
      CreateUser(count, userMasterlist);
    }
  }
  return 0;
}
