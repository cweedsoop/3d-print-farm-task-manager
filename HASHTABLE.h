#pragma once

#include <string>
#include <vector>
#include <list>

using namespace std;

class HashTable {
private:
  std::vector<std::list<std::pair<string, string>>> table;
  int size;

public:
  HashTable(int size) {
    this->size = size;
    table.resize(size);
  }

  void insert(string& key, string& value) 
  {
    int index = hash(key);

    /*for (auto it = table[index].begin(); it != table[index].end(); ++it)
    {
      if (it->first == key) 
      {
        it->second = value;
        return;
      }
    }*/
    table[index].push_back(std::make_pair(key, value));
  }

  int findPair(string key, string& inputName) 
  {
    int index = hash(key);

    for (auto it = table[index].begin(); it != table[index].end(); ++it) 
    {
      if (it->first == key) 
      {
        if (inputName == it->second)
        {
          return 1; //found, username matches
        }        
      }
    }
    return -1; // Not found
  }

  void remove(string key) 
  {
    int index = hash(key);

    for (auto it = table[index].begin(); it != table[index].end(); ++it) 
    {
      if (it->first == key) 
      {
        table[index].erase(it);
        return;
      }
    }
  }

  int hash(string key) 
  {
    unsigned long tempVal = 0;
    tempVal = stoul(key);

    return tempVal % size;
  }
};