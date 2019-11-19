#ifndef HASH_H
#define HASH_H

#include <string>
using namespace std;

struct Node
{
  int key;
  Node* next;
  LLNode* head = NULL;
  RBTNode* root = NULL;
};

struct LLNode
{
  int key;
  LLNode* next;

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
    HashTable();
    ~HashTable();

    unsigned int hashFunction1(int key); // hash function to map values to key
    unsigned int hashFunction2(int key);

    bool insert(int key);
    void print();
    Node* search(int key);
    Node* delete(int key);

    int linearProbe(int key);

  private:

    const int TABLE_SIZE = 1019;

    Node* *table1;
    Node* *table2;

    Node* createNode(int key, node* next);

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
