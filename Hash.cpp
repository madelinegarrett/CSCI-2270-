#include <vector>
#include <iostream>
#include <string>
#include "Hash.hpp"
using namespace std;

HashTable::HashTable(string type)
{
  if (type == "Linear Probing")
  {
    method = "Linear Probing";
    TABLE_SIZE = 10009;
    table1 = new Node[TABLE_SIZE];

    for (int i = 0 ;i < TABLE_SIZE; i++)
    {
      table1[i] = NULL;
    }
  }

  if (type == "Cuckoo Hashing")
  {
    method = "Cuckoo Hashing";
    TABLE_SIZE = 10009;
    table1 = new Node[TABLE_SIZE];
    table2 = new Node[TABLE_SIZE];

    for(int i = 0 ;i < TABLE_SIZE; i++)
    {
      table1[i] = NULL;
      table2[i] = NULL;
    }
  }

  if (type == "LL Chaining")
  {
    method = "LL Chaining";
    TABLE_SIZE = 10009;
    LLtable = new LLNode*[TABLE_SIZE];

    for (int i = 0 ;i < TABLE_SIZE; i++)
    {
      LLtable[i] = NULL;
    }
  }

  if (type == "RBT Chaining")
  {
    method = "RBT Chaining";
    TABLE_SIZE = 10009;
    table1 = new RBTNode*[TABLE_SIZE];

    for (int i = 0 ;i < TABLE_SIZE; i++)
    {
      RBTtable[i] = NULL;
    }
  }

}

unsigned int HashTable::hashFunction1(int key)
{
  return (key % TABLE_SIZE);
}

unsigned int HashTable::hashFunction2(int key)
{
  return Floor(key / TABLE_SIZE);
}

////////////////////////////// INSERT //////////////////////////////
void HashTable::insert(int key, string method)
{
  int index;

  if (method == "Linear Probing")
  {
    if (search(key,method) == true)
    {
      cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }

    else
    {
      index = hashFunction1(key);

      while (index != TABLE_SIZE)
      {
        if (table1[index] == NULL)
        {
          table1[index].key = key;
          return;
        }

        index++;
      }

      cout << "table1 (used for linear probing) is full. did not insert " << key << endl;
      return;
    }
  }

  if (method == "Cuckoo Hashing")
  {
    if (search(key,method) == true)
    {
      cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }

    else
    {
      int index1 = hashFunction1(key);
      int temp;
      bool inserted = false;

      while (inserted == false)
      {
        if (table1[index1] == NULL)
        {
          Node newNode = new Node;
          newNode.key = key;
          table1[index1] = newNode;

          inserted = true;
          return;
        }

        else
        {
          int index2 = hashFunction2(key);

          if (table2[index2] == NULL)
          {
            Node newNode = new Node;
            newNode.key = key;
            table2[index2] = newNode;

            inserted = true;
            return;
          }

          else
          {
            int temp = table1[index1].key;
            table1[index1].key = key;

            index2 = hashFunction2[temp];

            if (table2[index2] == NULL)
            {
              Node newNode = new Node;
              newNode.key = temp;
              table2[index2] = newNode;

              inserted = true;
              return;
            }

            else
            {

            }
          }
        }

      }
    }
  }

  if (method == "LL Chaining")
  {
    if (search(key,method) == true)
    {
      cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }

    else
    {
      index = hashFunction1(key)

      insertAtLL(LLtable[index], key);
      return;
    }
  }

  if (method == "RBT Chaining")
  {

  }

}

void HashTable::insertAtLL(LLNode* head, int key)
{
  if (head == NULL)
  {
    head -> key = key;
    head -> next = NULL;
    head -> head - true;
    return;
  }

  else
  {
    LLNode* crawler = head;

    while (crawler -> next != NULL)
    {
      crawler = crawler -> next;
    }

    LLNode* newLLNode = new LLNode;
    newLLNode -> key = key;
    newLLNode -> next = crawler -> next; // set to NULL
    newLLNode -> head = false;
    crawler -> next = newLLNode;
    return;
  }
}

void HashTable::cuckooInsert(int key)
{
  int index1 = hashFunction1(key);
  int index2 = hashFunction2(key);
  int temp;

  if (table1[index1] == NULL)
  {
    Node newNode = new Node;
    newNode.key = key;
    table1[index1] = newNode;

    return;
  }

  else if (table2[index2] == NULL)
  {
    Node newNode = new Node;
    newNode.key = key;
    table2[index2] = newNode;

    return;
  }

  else if (table1[index1].key == key)
  {
    TABLE_SIZE ++;
    Node *temparr = new Node[TABLE_SIZE];

    //Copy over first n elements
    for (int i = 0; i < TABLE_SIZE - 1; i++)
    {
      temparr[i] = table2[i];
    }

    //Deallocate original memory
    delete [] table2;
    // point p to the new block of memory that's 2n in length
    table2 = temparr;

    temp = table1[index1].key;
    cuckooInsert(temp);
  }

  else
  {
    temp = table1[index1].key;
    table1[index1].key = key;

    cuckooInsert(temp);
  }

}
////////////////////////////// PRINT //////////////////////////////
void HashTable::print(string method)
{
  if (method == "Linear Probing")
  {
    cout << "table1: " << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (table1[i] != NULL)
      {
        cout << table1[i].key << " || ";
      }
    }

    cout << "table2: " << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (table2[i] != NULL)
      {
        cout << table2[i].key << " || ";
      }
    }
  }

  if (method == "Cuckoo Hashing")
  {

  }

  if (method == "LL Chaining")
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (LLtable[i] != NULL)
      {
        cout << i << " || ";
        printLL(LLtable[i]);
        cout << endl;
      }
    }
  }

  if (method == "Linear Probing")
  {

  }

  if (method == "RBT Chaining")
  {

  }
}

void printLL(LLNode* crawler)
{
  while (crawler != NULL)
  {
    cout << crawler -> key << " | ";
    crawler = crawler -> next;
  }
}


////////////////////////////// SEARCH //////////////////////////////
bool HashTable::search(int key, string method)
{
  if (method == "Linear Probing")
  {
    int index = hashFunction1(key);

    if (table1[index] != key)
    {
      return false;
    }

    return true;
  }

  if (method == "Cuckoo Hashing")
  {
    int index = hashFunction1(key);

    if (table1[index] == key)
    {
      return true;
    }

    index = hashFunction2(key);

    if (table2[index] == key)
    {
      return true;
    }

    return false;
  }

  if (method == "LL Chaining")
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (searchLL(LLtable[i], int key) == true)
      {
        return true;
      }
    }

    return false;
  }

  if (method == "RBT Chaining")
  {

  }
}

bool searchLL(LLNode* LLNode, int key)
{
  if (LLNode -> key == key) // chech head
  {
    return true;
  }

  else
  {
    while (LLNode != NULL)
    {
      LLNode = LLNode -> next;

      if (LLNode -> key == key)
      {
        return true;
      }
    }

    return false;
  }
}


bool searchRBT(int key)
{

}

////////////////////////////// DELETE //////////////////////////////
void HashTable::delete(int key, string method)
{
  int delete_index;

  if (method == "Linear Probing")
  {
    if (search(key,method) == false)
    {
      cout << "key, " << key << ", doesn't exists... cannot delete." << endl;
      return;
    }

    else
    {
      delete_index = hashFunction1(key);

      delete table1[delete_index];
      table1[delete_index] = NULL;
    }
  }

  if (method == "Cuckoo Hashing")
  {

  }

  if (method == "LL Chaining")
  {
    if (search(key,method) == false)
    {
      cout << "key, " << key << ", doesn't exists... cannot delete." << endl;
      return;
    }

    else
    {
      delete_index = hashFunction1(key);

      deleteLL(LLtable[delete_index], key);
    }

  }

  if (method == "RBT Chaining")
  {

  }
}

void deleteLL(LLNode *crawler, int key)
{
  if (crawler -> head == true && crawler -> key == key)
  {
    LLNode *temp = crawler;
    crawler = crawler -> next;
    crawler -> head = true;
    delete temp;
  }

  else
  {
    while (crawler -> next -> key != key)
    {
      crawler = crawler -> next;
    }

    LLNode *temp = crawler -> next;
    crawler -> next = crawler -> next -> next;

    delete temp;
  }
}
