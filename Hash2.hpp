
#include <vector>
#include <iostream>
#include <string>
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

  if (type == "BST Chaining")
  {
    method = "BST Chaining";
    TABLE_SIZE = 10009;
    table1 = new BSTNode*[TABLE_SIZE];

    for (int i = 0 ;i < TABLE_SIZE; i++)
    {
      BSTtable[i] = NULL;
    }
  }
}

HashTable::balancingBST()
{
  for (int i = 0 ;i < TABLE_SIZE; i++)
  {
    buildTree(BSTtable[i]);
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


void storeBSTNodes(BSTNode* root, vector<BSTNode*> &nodes)
{

    if (root==NULL)
        return;


    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
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

  if (method == "BST Chaining")
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

Node * HashTable::createNode(int value, Node * P, Node * L, Node * R){
	Node * temp = new Node;
	temp -> key = value;
	temp -> parent = P;
	temp -> right = R;
	temp -> left = L;
	return temp;
}

void HashTable::insertatBST(int key)
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

  if (method == "BST Chaining")
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

void preOrderPrintBST(BSTNode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->key);
    preOrder(node->left);
    preOrder(node->right);
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

  if (method == "BST Chaining")
  {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
      if (searchBST(LLtable[i], int key) == true)
      {
        return true;
      }
    }

    return false;
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

Node* treeMinimum(Node * node){
	while( node -> left){
		node = node -> left;
	}
	return node;
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
