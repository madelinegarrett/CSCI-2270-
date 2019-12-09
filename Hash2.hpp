#ifndef HASH_H
#define HASH_H

#include <string>
#include <vector>
using namespace std;

struct Node
{
  int key;
  bool occupied;
};

struct LLNode
{
  int key;
  LLNode* next;
  bool head;
};

struct RBTNode
{
  int key;
  RBTNode* left;
  RBTNode* right;
  RBTNode* parent;
  string color;
};


class HashTable
{
  public:
    HashTable(string type);
    //~HashTable();

    unsigned int hashFunction1(int key); // hash function to map values to key
    unsigned int hashFunction2(int key);

    void insert(int key, string method);
    void insertAtLL(LLNode* head, int key);
    void insertatBST(int key);
    void cuckooInsert(int key, int original);
    void print(string method);
    bool search(int key, string method);
    void delete1(int key, string method);

  private:

    int TABLE_SIZE;
    int TABLE_SIZE2;

    RBTNode root;
    Node *table1;
    Node *table2;
    LLNode* *LLtable;
    RBTNode* *RBTtable;

    string method;

};

/*
Helper functions:

For search:
LLNode* searchLL(int key);
RBTNode* searchRBT(int key);

For Insert:
LLNode* insertToLL(int key);
RBTNode* insertToRBT(int key); // root = insertToBST;

For Delete:
RBTNode* deleteAtRBT(TreeNode* root, int key); //root = deleteInRBT(root, key);
void deleteAtLL(Node* origin, int key); // deleteAtLL(origin, key) call with origin in order to update its head (origin -> head)

For Printing:
void printLL(LLNode* head); //printLL(origin -> head);
void printRBT(RBTNode* root); //printRBT(origin -> root);

For Red Black Tree: // MADELINE
bool isRedBlack(RBTNode* root); // isRedBlack(origin -> root); //check by the criterias in we learned in class
RBTNode* pivot(RBTNode* root, key item);
void reColor() ??

*/

#endif
