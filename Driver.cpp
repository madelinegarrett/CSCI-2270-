#include<iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include "Hash.hpp"
using namespace std;

int getInsertNumber(vector<int> numbers, int current_load)
{
  //cout << "TEST 2" << endl;
  int index = 0;
  index += (rand() % current_load) + current_load;
  return numbers[index-1];
}

void menu()
{
  //cout << "TEST 3" << endl;
  cout << "---------- MAIN MENU ----------" << endl;
  cout << endl;
  cout << "Please enter the number for the following actions:" << endl;
  cout << "1. Start Evaluation" << endl;
  cout << "2. See Performances" << endl;
  cout << "3. Quit" << endl;
  cout << endl;
  cout << "---------- ---------- ----------" << endl;
  cout << endl;
}

int getNumber(vector<int> numbers, int current_load)
{
  //cout << "TEST 4" << endl;
  int index = (rand() % current_load) + current_load;
  return numbers[index];
}

int main(int argc, char* argv[])
{
  //cout << "TEST 5" << endl;
  string filename = argv[1];
  string string_key;
  vector<int> numbers;
  string line;

  ifstream inStream;

  inStream.open(filename);

  if(inStream.is_open())
  {
    while(getline(inStream,line,','))
    {
      stringstream ss(line);
      getline(ss,string_key,',');

      int key = stoi(string_key);

      numbers.push_back(key);
    }
  }

  else
  {
  cout << "Failed to open " << filename << endl;
  exit(0);
  }

  inStream.close();

  string menu_choice;
  string method_choice;
  string method;

  int load = 0;

  float insert_time_linear = 0;
  float delete_time_linear = 0;
  float lookup_time_linear = 0;

  float insert_time_cuckoo = 0;
  float delete_time_cuckoo = 0;
  float lookup_time_cuckoo = 0;

  float insert_time_LL = 0;
  float delete_time_LL = 0;
  float lookup_time_LL = 0;

  float insert_time_RBT = 0;
  float delete_time_RBT = 0;
  float lookup_time_RBT = 0;

  cout << "Welcome to the Hashing Implementation and Analysis Program" << endl;

  while (menu_choice != "3")
  {
    menu();

    getline(cin, menu_choice);

    if ((menu_choice != "1") && (menu_choice != "2") && (menu_choice != "3"))
    {
      cout << "Please choose a valid menu option..." << endl;
    }

    int menuChoice = stoi(menu_choice);

    switch (menuChoice)
    {
      case 1:
        cout << "Creating tables..." << endl;

        HashTable linear1 = HashTable("Linear Probing");
        //HashTable cuckoo1 = HashTable("Cuckoo Hashing");
        HashTable linkedlist1 = HashTable("LL Chaining");
        //HashTable redblack1 = HashTable("RBT Chaining");

        cout << "------ Load factor = 0.1 ------" << endl;

        for (int i = 0; i < 10009*0.1; i++)
        {
          //cout << numbers[i] << endl;
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          //redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";


        for (int i = 0; i < 100; i++)
        {
          auto start1 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop1 = chrono::high_resolution_clock::now();
          auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
          insert_time_linear += duration1.count();
        }
        cout << insert_time_linear/100 << " microseconds" << endl;

        //linear1.print("Linear Probing");
        /*
        cout << "Cuckoo Hashing Insert: ";
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
          linear.insert(getInsertNumber(numbers,10009*0.1),"Cuckoo Hashing");
        }

        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << duration2.count() << " microseconds" << endl;
        */

        linkedlist1.print("LL Chaining");
        cout << "LL Chaining Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start3 = chrono::high_resolution_clock::now();
          linkedlist1.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop3 = chrono::high_resolution_clock::now();
          auto duration3 = chrono::duration_cast<chrono::microseconds>(stop3 - start3);
          insert_time_LL += duration3.count();
        }
        cout << insert_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start4 = chrono::high_resolution_clock::now();
          redblack1.insert(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop4 = chrono::high_resolution_clock::now();
          auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
          insert_time_RBT += duration4.count();
        }

        cout << insert_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start5 = chrono::high_resolution_clock::now();
          linear1.delete1(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop5 = chrono::high_resolution_clock::now();
          auto duration5 = chrono::duration_cast<chrono::microseconds>(stop5 - start5);
          delete_time_linear += duration5.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start6 = chrono::high_resolution_clock::now();
          linkedlist1.delete1(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop6 = chrono::high_resolution_clock::now();
          auto duration6 = chrono::duration_cast<chrono::microseconds>(stop6 - start6);
          delete_time_LL += duration6.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.delete1(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start8 = chrono::high_resolution_clock::now();
          linear1.search(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop8 = chrono::high_resolution_clock::now();
          auto duration8 = chrono::duration_cast<chrono::microseconds>(stop8 - start8);
          delete_time_linear += duration8.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start9 = chrono::high_resolution_clock::now();
          linkedlist1.search(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop9 = chrono::high_resolution_clock::now();
          auto duration9 = chrono::duration_cast<chrono::microseconds>(stop9 - start9);
          delete_time_LL += duration9.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Lookup: ";

        auto start10 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start10 = chrono::high_resolution_clock::now();
          redblack1.search(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop10 = chrono::high_resolution_clock::now();
          auto duration10 = chrono::duration_cast<chrono::microseconds>(stop10 - start10);
          delete_time_RBT += duration10.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        insert_time_linear = 0;
        delete_time_linear = 0;
        lookup_time_linear = 0;
        insert_time_cuckoo = 0;
        delete_time_cuckoo = 0;
        lookup_time_cuckoo = 0;
        insert_time_LL = 0;
        delete_time_LL = 0;
        lookup_time_LL = 0;
        insert_time_RBT = 0;
        delete_time_RBT = 0;
        lookup_time_RBT = 0;

        cout << "------ Load factor = 0.2 ------" << endl;

        for (int i = 10009*0.1; i < 10009*0.2; i++)
        {
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          //redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";

        //linear1.print("Linear Probing");

        for (int i = 0; i < 100; i++)
        {
          auto start11 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop11 = chrono::high_resolution_clock::now();
          auto duration11 = chrono::duration_cast<chrono::microseconds>(stop11 - start11);
          insert_time_linear += duration11.count();
        }
        cout << insert_time_linear/100 << " microseconds" << endl;
        /*
        cout << "Cuckoo Hashing Insert: ";
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
          linear.insert(getInsertNumber(numbers,10009*0.1),"Cuckoo Hashing");
        }

        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << duration2.count() << " microseconds" << endl;
        */
        cout << "LL Chaining Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start12 = chrono::high_resolution_clock::now();
          linkedlist1.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop12 = chrono::high_resolution_clock::now();
          auto duration12 = chrono::duration_cast<chrono::microseconds>(stop12 - start12);
          insert_time_LL += duration12.count();
        }
        cout << insert_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start4 = chrono::high_resolution_clock::now();
          redblack1.insert(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop4 = chrono::high_resolution_clock::now();
          auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
          insert_time_RBT += duration4.count();
        }

        cout << insert_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start13 = chrono::high_resolution_clock::now();
          linear1.delete1(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop13 = chrono::high_resolution_clock::now();
          auto duration13 = chrono::duration_cast<chrono::microseconds>(stop13 - start13);
          delete_time_linear += duration13.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start14 = chrono::high_resolution_clock::now();
          linkedlist1.delete1(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop14 = chrono::high_resolution_clock::now();
          auto duration14 = chrono::duration_cast<chrono::microseconds>(stop14 - start14);
          delete_time_LL += duration14.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.delete1(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start15 = chrono::high_resolution_clock::now();
          linear1.search(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop15 = chrono::high_resolution_clock::now();
          auto duration15 = chrono::duration_cast<chrono::microseconds>(stop15 - start15);
          delete_time_linear += duration15.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start16 = chrono::high_resolution_clock::now();
          linkedlist1.search(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop16 = chrono::high_resolution_clock::now();
          auto duration16 = chrono::duration_cast<chrono::microseconds>(stop16 - start16);
          delete_time_LL += duration16.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Lookup: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.search(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        insert_time_linear = 0;
        delete_time_linear = 0;
        lookup_time_linear = 0;
        insert_time_cuckoo = 0;
        delete_time_cuckoo = 0;
        lookup_time_cuckoo = 0;
        insert_time_LL = 0;
        delete_time_LL = 0;
        lookup_time_LL = 0;
        insert_time_RBT = 0;
        delete_time_RBT = 0;
        lookup_time_RBT = 0;

        cout << "------ Load factor = 0.5 ------" << endl;

        for (int i = 10009*0.2; i < 10009*0.5; i++)
        {
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          //redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";


        for (int i = 0; i < 100; i++)
        {
          auto start11 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop11 = chrono::high_resolution_clock::now();
          auto duration11 = chrono::duration_cast<chrono::microseconds>(stop11 - start11);
          insert_time_linear += duration11.count();
        }
        cout << insert_time_linear/100 << " microseconds" << endl;
        /*
        cout << "Cuckoo Hashing Insert: ";
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
          linear.insert(getInsertNumber(numbers,10009*0.1),"Cuckoo Hashing");
        }

        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << duration2.count() << " microseconds" << endl;
        */
        cout << "LL Chaining Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start17 = chrono::high_resolution_clock::now();
          linkedlist1.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop17 = chrono::high_resolution_clock::now();
          auto duration17 = chrono::duration_cast<chrono::microseconds>(stop17 - start17);
          insert_time_LL += duration17.count();
        }
        cout << insert_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start4 = chrono::high_resolution_clock::now();
          redblack1.insert(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop4 = chrono::high_resolution_clock::now();
          auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
          insert_time_RBT += duration4.count();
        }

        cout << insert_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start19 = chrono::high_resolution_clock::now();
          linear1.delete1(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop19 = chrono::high_resolution_clock::now();
          auto duration19 = chrono::duration_cast<chrono::microseconds>(stop19 - start19);
          delete_time_linear += duration19.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start19 = chrono::high_resolution_clock::now();
          linkedlist1.delete1(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop19 = chrono::high_resolution_clock::now();
          auto duration19 = chrono::duration_cast<chrono::microseconds>(stop19 - start19);
          delete_time_LL += duration19.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.delete1(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start21 = chrono::high_resolution_clock::now();
          linear1.search(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop21 = chrono::high_resolution_clock::now();
          auto duration21 = chrono::duration_cast<chrono::microseconds>(stop21 - start21);
          delete_time_linear += duration21.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start22 = chrono::high_resolution_clock::now();
          linkedlist1.search(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop22 = chrono::high_resolution_clock::now();
          auto duration22 = chrono::duration_cast<chrono::microseconds>(stop22 - start22);
          delete_time_LL += duration22.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Lookup: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.search(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        insert_time_linear = 0;
        delete_time_linear = 0;
        lookup_time_linear = 0;
        insert_time_cuckoo = 0;
        delete_time_cuckoo = 0;
        lookup_time_cuckoo = 0;
        insert_time_LL = 0;
        delete_time_LL = 0;
        lookup_time_LL = 0;
        insert_time_RBT = 0;
        delete_time_RBT = 0;
        lookup_time_RBT = 0;

        cout << "------ Load factor = 0.7 ------" << endl;

        for (int i = 10009*0.5; i < 10009*0.7; i++)
        {
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          //redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";


        for (int i = 0; i < 100; i++)
        {
          auto start23 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop23 = chrono::high_resolution_clock::now();
          auto duration23 = chrono::duration_cast<chrono::microseconds>(stop23 - start23);
          insert_time_linear += duration23.count();
        }
        cout << insert_time_linear/100 << " microseconds" << endl;
        /*
        cout << "Cuckoo Hashing Insert: ";
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
          linear.insert(getInsertNumber(numbers,10009*0.1),"Cuckoo Hashing");
        }

        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << duration2.count() << " microseconds" << endl;
        */
        cout << "LL Chaining Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start24 = chrono::high_resolution_clock::now();
          linkedlist1.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop24 = chrono::high_resolution_clock::now();
          auto duration24 = chrono::duration_cast<chrono::microseconds>(stop24 - start24);
          insert_time_LL += duration24.count();
        }
        cout << insert_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start4 = chrono::high_resolution_clock::now();
          redblack1.insert(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop4 = chrono::high_resolution_clock::now();
          auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
          insert_time_RBT += duration4.count();
        }

        cout << insert_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start26 = chrono::high_resolution_clock::now();
          linear1.delete1(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop26 = chrono::high_resolution_clock::now();
          auto duration26 = chrono::duration_cast<chrono::microseconds>(stop26 - start26);
          delete_time_linear += duration26.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start27 = chrono::high_resolution_clock::now();
          linkedlist1.delete1(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop27 = chrono::high_resolution_clock::now();
          auto duration27 = chrono::duration_cast<chrono::microseconds>(stop27 - start27);
          delete_time_LL += duration27.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.delete1(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start28 = chrono::high_resolution_clock::now();
          linear1.search(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop28 = chrono::high_resolution_clock::now();
          auto duration28 = chrono::duration_cast<chrono::microseconds>(stop28 - start28);
          delete_time_linear += duration28.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start29 = chrono::high_resolution_clock::now();
          linkedlist1.search(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop29 = chrono::high_resolution_clock::now();
          auto duration29 = chrono::duration_cast<chrono::microseconds>(stop29 - start29);
          delete_time_LL += duration29.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Lookup: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.search(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        insert_time_linear = 0;
        delete_time_linear = 0;
        lookup_time_linear = 0;
        insert_time_cuckoo = 0;
        delete_time_cuckoo = 0;
        lookup_time_cuckoo = 0;
        insert_time_LL = 0;
        delete_time_LL = 0;
        lookup_time_LL = 0;
        insert_time_RBT = 0;
        delete_time_RBT = 0;
        lookup_time_RBT = 0;

        cout << "------ Load factor = 0.9 ------" << endl;

        for (int i = 10009*0.7; i < 10009*0.9; i++)
        {
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          //redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";


        for (int i = 0; i < 100; i++)
        {
          auto start30 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop30 = chrono::high_resolution_clock::now();
          auto duration30 = chrono::duration_cast<chrono::microseconds>(stop30 - start30);
          insert_time_linear += duration30.count();
        }
        cout << insert_time_linear/100 << " microseconds" << endl;
        /*
        cout << "Cuckoo Hashing Insert: ";
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
          linear.insert(getInsertNumber(numbers,10009*0.1),"Cuckoo Hashing");
        }

        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << duration2.count() << " microseconds" << endl;
        */
        cout << "LL Chaining Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start31 = chrono::high_resolution_clock::now();
          linkedlist1.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop31 = chrono::high_resolution_clock::now();
          auto duration31 = chrono::duration_cast<chrono::microseconds>(stop31 - start31);
          insert_time_LL += duration31.count();
        }
        cout << insert_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start4 = chrono::high_resolution_clock::now();
          redblack1.insert(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop4 = chrono::high_resolution_clock::now();
          auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
          insert_time_RBT += duration4.count();
        }

        cout << insert_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start33 = chrono::high_resolution_clock::now();
          linear1.delete1(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop33 = chrono::high_resolution_clock::now();
          auto duration33 = chrono::duration_cast<chrono::microseconds>(stop33 - start33);
          delete_time_linear += duration33.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start34 = chrono::high_resolution_clock::now();
          linkedlist1.delete1(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop34 = chrono::high_resolution_clock::now();
          auto duration34 = chrono::duration_cast<chrono::microseconds>(stop34 - start34);
          delete_time_LL += duration34.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.delete1(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start35 = chrono::high_resolution_clock::now();
          linear1.search(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop35 = chrono::high_resolution_clock::now();
          auto duration35 = chrono::duration_cast<chrono::microseconds>(stop35 - start35);
          delete_time_linear += duration35.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start36 = chrono::high_resolution_clock::now();
          linkedlist1.search(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop36 = chrono::high_resolution_clock::now();
          auto duration36 = chrono::duration_cast<chrono::microseconds>(stop36 - start36);
          delete_time_LL += duration36.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Lookup: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.search(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        insert_time_linear = 0;
        delete_time_linear = 0;
        lookup_time_linear = 0;
        insert_time_cuckoo = 0;
        delete_time_cuckoo = 0;
        lookup_time_cuckoo = 0;
        insert_time_LL = 0;
        delete_time_LL = 0;
        lookup_time_LL = 0;
        insert_time_RBT = 0;
        delete_time_RBT = 0;
        lookup_time_RBT = 0;

        cout << "------ Load factor = 1.0 ------" << endl;

        for (int i = 10009*0.9; i < 10009; i++)
        {
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          //redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";


        for (int i = 0; i < 100; i++)
        {
          auto start37 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop37 = chrono::high_resolution_clock::now();
          auto duration37 = chrono::duration_cast<chrono::microseconds>(stop37 - start37);
          insert_time_linear += duration37.count();
        }
        cout << insert_time_linear/100 << " microseconds" << endl;
        /*
        cout << "Cuckoo Hashing Insert: ";
        auto start2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; i++)
        {
          linear.insert(getInsertNumber(numbers,10009*0.1),"Cuckoo Hashing");
        }

        auto stop2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
        cout << duration2.count() << " microseconds" << endl;
        */
        cout << "LL Chaining Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start37 = chrono::high_resolution_clock::now();
          linkedlist1.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop37 = chrono::high_resolution_clock::now();
          auto duration37 = chrono::duration_cast<chrono::microseconds>(stop37 - start37);
          insert_time_LL += duration37.count();
        }
        cout << insert_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start4 = chrono::high_resolution_clock::now();
          redblack1.insert(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop4 = chrono::high_resolution_clock::now();
          auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
          insert_time_RBT += duration4.count();
        }

        cout << insert_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start38 = chrono::high_resolution_clock::now();
          linear1.delete1(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop38 = chrono::high_resolution_clock::now();
          auto duration38 = chrono::duration_cast<chrono::microseconds>(stop38 - start38);
          delete_time_linear += duration38.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Delete: ";

        for (int i = 0; i < 100; i++)
        {
          auto start39 = chrono::high_resolution_clock::now();
          linkedlist1.delete1(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop39 = chrono::high_resolution_clock::now();
          auto duration39 = chrono::duration_cast<chrono::microseconds>(stop39 - start39);
          delete_time_LL += duration39.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Insert: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.delete1(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;

        cout << "Linear Probing Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start40 = chrono::high_resolution_clock::now();
          linear1.search(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop40 = chrono::high_resolution_clock::now();
          auto duration40 = chrono::duration_cast<chrono::microseconds>(stop40 - start40);
          delete_time_linear += duration40.count();
        }
        cout << delete_time_linear/100 << " microseconds" << endl;

        cout << "LL Chaining Lookup: ";

        for (int i = 0; i < 100; i++)
        {
          auto start41 = chrono::high_resolution_clock::now();
          linkedlist1.search(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop41 = chrono::high_resolution_clock::now();
          auto duration41 = chrono::duration_cast<chrono::microseconds>(stop41 - start41);
          delete_time_LL += duration41.count();
        }
        cout << delete_time_LL/100 << " microseconds" << endl;
        /*
        cout << "RBT Chaining Lookup: ";

        auto start7 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          auto start7 = chrono::high_resolution_clock::now();
          redblack1.search(getNumber(numbers,10009*0.1),"BST Chaining");
          auto stop7 = chrono::high_resolution_clock::now();
          auto duration7 = chrono::duration_cast<chrono::microseconds>(stop7 - start7);
          delete_time_RBT += duration7.count();
        }

        cout << delete_time_RBT/100 << "microseconds" << endl;
        */
        cout << "---------------------" << endl;
        break;



                break;


      //case 2:
        //cout << "Enter a movie title:" << endl;
        //getline(cin, deletechoice);

        //mt.deleteMovie(deletechoice);

        //break;
    }
  }

  cout << "Goodbye!" << endl;
  return 0;
}
