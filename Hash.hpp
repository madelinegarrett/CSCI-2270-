#ifndef HASH_H
#define HASH_H

#include <string>
using namespace std;

struct Node
{
  int key;
};

struct LLNode
{
  int key;
  LLNode* next;
  bool head;
};

struct BSTNode
{
  int key;
  BSTNode* left;
  BSTNode* right;
  BSTNode* parent;
  string color;
};


class HashTable
{
  public:
    HashTable(string type);
    ~HashTable();

    balancingBST(); 

    unsigned int hashFunction1(int key); // hash function to map values to key
    unsigned int hashFunction2(int key);

    void insert(int key, string method);
    void insertAtLL(LLNode* head, int key);
    void cuckooInsert(int key);
    void print(string method);
    bool search(int key, string method);
    void delete(int key, string method);

  private:

    int TABLE_SIZE;

    Node *table1;
    Node *table2;
    LLNode* *LLtable;
    BSTNode* *BSTtable;

    string method;

};
