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

  double insert_time_linear = 0;
  double delete_time_linear = 0;
  double lookup_time_linear = 0;

  double insert_time_cuckoo = 0;
  double delete_time_cuckoo = 0;
  double lookup_time_cuckoo = 0;

  double insert_time_LL = 0;
  double delete_time_LL = 0;
  double lookup_time_LL = 0;

  double insert_time_RBT = 0;
  double delete_time_RBT = 0;
  double lookup_time_RBT = 0;

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
        HashTable cuckoo1 = HashTable("Cuckoo Hashing");
        HashTable linkedlist1 = HashTable("LL Chaining");
        HashTable redblack1 = HashTable("RBT Chaining");

        cout << "------ Load factor = 0.1 ------" << endl;

        for (int i = 0; i < 10009*0.1; i++)
        {
          linear1.insert(numbers[i],"Linear Probing");
          //cuckoo.insert(numbers[i],"Cuckoo Hashing");
          linkedlist1.insert(numbers[i],"LL Chaining");
          redblack1.insert(numbers[i],"BST Chaining");
        }

        cout << "Linear Probing Insert: ";

        for (int i = 0; i < 100; i++)
        {
          auto start1 = chrono::high_resolution_clock::now();
          linear1.insert(getInsertNumber(numbers,10009*0.1),"Linear Probing");
          auto stop1 = chrono::high_resolution_clock::now();
          auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
          insert_time_linear += duration1;
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
          auto start3 = chrono::high_resolution_clock::now();
          linkedlist.insert(getInsertNumber(numbers,10009*0.1),"LL Chaining");
          auto stop3 = chrono::high_resolution_clock::now();
          auto duration3 = chrono::duration_cast<chrono::microseconds>(stop3 - start3);
          insert_time_LL += duration3;
        }

        cout << insert_time_LL/100 << " microseconds" << endl;

        /*
        cout << "RBT Chaining Insert: " <<;
        auto start4 = chrono::high_resolution_clock::now();

        for (int i = 0; i < 100; i++)
        {
          linear.insert(getNumber(numbers,10009*0.1),"BST Chaining");
        }

        auto stop4 = chrono::high_resolution_clock::now();
        auto duration4 = chrono::duration_cast<chrono::microseconds>(stop4 - start4);
        cout << duration4.count() << "microseconds" << endl;
        */


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
