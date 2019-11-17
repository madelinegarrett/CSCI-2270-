#ifndef HASH_H 
#define HASH_H 

#include <string>


struct LLNode 
{
  int key; 
  LLNode* next; 
  
}; 

struct BSTNode
{
  int key; 
  BSTNode* left; 
  BSTNode* right; 
  BSTNode* parent; 
  
}; 


class HashTable 
{
  public:
    HashTable(int hashTableSize);
    ~HashTable();
  

  private:
  const int TABLE_SIZE = 1019; 

  Node* 
  
};


