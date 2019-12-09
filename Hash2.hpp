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
    bool searchBST(RBTNode* node, int key);
    void deleteBST(int key);
    RBTNode* searchdeleteBST(RBTNode * node, int searchkey);
    void delete1(int key, string method);
    RBTNode *createNode(int value, RBTNode* P, RBTNode* L,RBTNode* R);

  private:

    int TABLE_SIZE;
    int TABLE_SIZE2;

    RBTNode* root = NULL;
    Node *table1;
    Node *table2;
    LLNode* *LLtable;
    RBTNode* *RBTtable;

    string method;

};

#endif
