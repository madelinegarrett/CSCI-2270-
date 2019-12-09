#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "Hash.hpp"
using namespace std;

////////////////////////////// CONSTRUCTER //////////////////////////////
HashTable::HashTable(string type)
{
  if (type == "Linear Probing")
  {
    method = "Linear Probing";
    TABLE_SIZE = 10009;
    table1 = new Node[TABLE_SIZE];

    for (int i = 0 ;i < TABLE_SIZE; i++)
    {
      table1[i].occupied = false;
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
      table1[i].occupied = false;
      table2[i].occupied = false;
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
    RBTtable = new RBTNode*[TABLE_SIZE];

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
  return floor(key / TABLE_SIZE);
}


////////////////////////////// INSERT //////////////////////////////
void HashTable::insert(int key, string method)
{
  int index;

  if (method == "Linear Probing")
  {
    if (search(key,method) == true)
    {
      //cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }

    else
    {
      index = hashFunction1(key);

      while (index != TABLE_SIZE)
      {
        if (table1[index].occupied == false)
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
    cout << "attempting to insert " << key << ". searching first" << endl;
    //cout << "searching" << endl;
    if (search(key,method) == true)
    {
      cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }

    else
    {
      //cout << "not found" << endl;
      int index1 = hashFunction1(key);
      int temp;
      bool inserted = false;

      while (inserted == false)
      {
        if (table1[index1].occupied == false)
        {
          //cout << "no prob - inserting" << endl;
          table1[index1].key = key;
          table1[index1].occupied = true;
          inserted = true;
          return;
        }

        else
        {
          cuckooInsert(key, key);
          inserted = true;
          return;
        }
      }
    }
  }

  if (method == "LL Chaining")
  {
    //cout << "searching if key exists in LL" << endl;

    if (search(key,method) == true)
    {
      cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }

    else
    {
      //cout << "doesnt exist... continuing... " << endl;
      index = hashFunction1(key);

      insertAtLL(LLtable[index], key);
      return;
    }
  }

  if (method == "RBT Chaining")
  {
    if (search(key,method) == true)
    {
      cout << "key, " << key << ", already exists... not inserting." << endl;
      return;
    }
    else
    {
      index = hashFunction1(key);
      insertatBST();
      return;
    }
  }

}

void HashTable::insertAtLL(LLNode* head, int key)
{
  //cout << "cheking if head empty" << endl;
  if (head == NULL)
  {
    //cout << "head == NULL" << endl;
    head = new LLNode;
    head -> key = key;
    head -> next = NULL;
    head -> head = true;
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


void insertatBST(int key)
{
  Node * temp = root;
  Node * current = new Node;
  Node * parentNode = new Node;
  Node * temp2= new Node;

  if(root = NULL)
  {
    root = createNode(value, NULL, NULL, NULL);

  }

  while(temp != NULL)
  {
    current = temp;
    if(value > temp -> key)
    {
      temp = temp -> right;
    }
    else
    {
      temp = temp -> left;
    }
  }

  if(parentNode == NULL)
  {
    root = createNode(value, NULL, NULL, NULL);
  }

  else if( value < parentNode -> key)
  {
    temp2 = createNode(value, parentNode, NULL, NULL);
    parentNode -> left = temp2;
  }

  else( value > parentNode -> key)
  {
    temp2 = createNode(value, parentNode, NULL, NULL);
    parentNode -> right = temp2;
  }
}


void HashTable::cuckooInsert(int key, int original)
{
  //cout << "in cuckooInsert" << endl;
  int original1 = original;
  //cout << "original1 = " << original1 << endl;
  int index1 = hashFunction1(key);
  int index2 = hashFunction2(key);
  int temp;

  if (table1[index1].occupied == false)
  {
    table1[index1].key = key;
    table1[index1].occupied = true;
    return;
  }

  else if (table2[index2].occupied == false)
  {
    //cout << "inserting in table2" << endl;
    table2[index2].key = key;
    table1[index2].occupied = true;

    return;
  }

  else if (table1[index1].key == original1)
  {
    //cout << "cycle detected" << endl;
    Node *temp1 = table1; //old table1

    TABLE_SIZE ++;
    Node *temparr = new Node[TABLE_SIZE]; // new table with increased size

    table1 = temparr; //pointing to new table

    for (int i = 0; i < TABLE_SIZE - 1; i++)
    {
      insert(temp1[i].key,"Cuckoo Hashing");
    }

    //Deallocate original memory
    delete [] temp1;

    cuckooInsert(temp,original1);
    return;
  }

  else
  {
    //cout << "replacing" << endl;
    //cout << "table1[index1] = " << table1[index1].key << " = temp"<< endl;
    temp = table1[index1].key;
    table1[index1].key = key;
    //cout << "new table1[index1] = " << table1[index1].key << endl;
    //cout << "calling with " << temp << endl;

    cuckooInsert(temp,original1);
    return;
  }

}
////////////////////////////// PRINT //////////////////////////////
void printLL(LLNode* crawler)
{
  while (crawler != NULL)
  {
    cout << crawler -> key << " | ";
    crawler = crawler -> next;
  }
}

void preOrderPrintBST(BSTNode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->key);
    preOrder(node->left);
    preOrder(node->right);
}

void HashTable::print(string method)
{
  if (method == "Linear Probing")
  {
    cout << "table1: " << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (table1[i].occupied == true)
      {
        cout << table1[i].key << " || ";
      }
    }

    cout << endl;
  }

  if (method == "Cuckoo Hashing")
  {
    cout << "table1: " << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (table1[i].occupied == true)
      {
        cout << table1[i].key << " || ";
      }
    }

    cout << endl;

    cout << "table2: " << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (table2[i].occupied == true)
      {
        cout << table2[i].key << " || ";
      }
    }

    cout << endl;
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

    cout << endl;
  }

  if (method == "RBT Chaining")
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (RBTtable[i] != NULL)
      {
        cout << i << " || ";
        preOrderPrintBST(RBTtable[i]);
        cout << endl;
      }
    }
  }
}


////////////////////////////// SEARCH //////////////////////////////
bool searchLL(LLNode* LLNode, int key)
{
  if (LLNode != NULL)
  {
    cout << "in searchLL" << endl;
    if (LLNode -> key == key) // chech head
    {
      return true;
    }

    else
    {
      if (LLNode -> next == NULL)
      {
        cout << "next is NULL" << endl;
      }

      while (LLNode -> next != NULL)
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

  else
  {
    return false;
  }
}


bool searchBST(BSTNode* node, int key)
{
  if(root)
  {

        if(root->key > value && root->left)
            search(root->left, value);

        else if(root->key < value && root->right)
            search(root->right, value);

        else if(root->key == value)
            return root;
        else
            return NULL;
    }
}


bool HashTable::search(int key, string method)
{
  if (method == "Linear Probing")
  {
    int index = hashFunction1(key);

    if (table1[index].key != key)
    {
      return false;
    }

    return true;
  }

  if (method == "Cuckoo Hashing")
  {
    cout << "searching table1" << endl;
    int index = hashFunction1(key);

    if (table1[index].occupied == true)
    {
      if (table1[index].key == key)
      {
        return true;
      }
    }
    //cout << "test2" << endl;
    cout << "searching table2" << endl;
    index = hashFunction2(key);
    cout << "index: " << index << endl;
    cout << "TABLE_SIZE: " << TABLE_SIZE << endl;
    if (table2[index].occupied == true)
    {
      if (table2[index].key == key)
      {
        return true;
      }
    }

    //cout << "test3" << endl;

    return false;
  }

  if (method == "LL Chaining")
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (searchLL(LLtable[i], key) == true)
      {
        return true;
      }
    }

    return false;
  }

  if (method == "RBT Chaining")
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (searchBST(RBTtable[i], int key) == true)
      {
        return true;
      }
    }

    return false;
  }
  return false;
  //}
}


////////////////////////////// DELETE //////////////////////////////
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

void deleteBST(int key)
{
  Node * node = searchBST(root,value);
	if(node != root){
		if(node -> left == NULL && node -> right == NULL){
			node -> parent -> left = NULL;
		}
		else if(node -> left == NULL && node -> right){
			Node * min = treeMinimum(node -> right);
			if(min == node -> right){
				node -> parent -> left = min;
				min -> parent = node -> parent;
				min -> left = node -> left;
				min -> left -> parent = min;
			}
			else{
				min -> parent -> left = min -> right;
				min -> right -> parent = min -> parent;
				min -> parent = node -> parent;
				node -> parent -> left = min;
				min -> left = node -> left;
				min -> right = node -> right;
				node -> right -> parent = min;
				node -> left -> parent = min;
			}
		}
		else
    {
			Node * temp = node -> left;
			node -> parent -> left = temp;
			temp -> parent = node -> parent;
		}
	}
	else{

	}
	delete node;
}


void HashTable::delete1(int key, string method)
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

      //table1[delete_index].key;
      table1[delete_index].occupied = false;
    }
  }

  if (method == "Cuckoo Hashing")
  {
    if (search(key,method) == false)
    {
      cout << "key, " << key << ", doesn't exists... cannot delete." << endl;
      return;
    }

    else
    {
      delete_index = hashFunction1(key);

      if (table1[delete_index].key == key)
      {
        //table1[delete_index].key;
        table1[delete_index].occupied = false;

        return;
      }

      else
      {
        delete_index = hashFunction2(key);

        if (table1[delete_index].key == key)
        {
          //table2[delete_index].key;
          table2[delete_index].occupied = false;
          return;
        }
      }
    }
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
    if (search(key,method) == false)
    {
      cout << "key, " << key << ", doesn't exists... cannot delete." << endl;
      return;
    }

    else
    {
      delete_index = hashFunction1(key);

      deleteBST(key);
    }
  }
}
