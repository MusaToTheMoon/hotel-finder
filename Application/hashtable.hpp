//============================================================================
// Name         : hashtable.hpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-04-2023
// Date Modified: 23-08-2023 
// Description  : HashTable class implementation
//============================================================================
#pragma once 
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<list>
#include<tuple>
#include "hotel.hpp"
#include "bst.hpp"

using namespace std;
class Entry
{
	private:
		string key;			//hotel name
		Hotel* value;		//hotel object
	public:
		Entry(string key, Hotel *value)
		{
			this->key = key;
			this->value = value;
		}
		friend class HashTable;
};
//===============================================================
class HashTable
{
	private:
		list<Entry>* buckets;		    			// Array of Lists of type Entries - used for Chaining
		BST<string,Hotel*> cityRecords;
		unsigned int size;					   		//Current Size of HashTable
		unsigned int capacity;				    	// Total Capacity of HashTable
		unsigned int collisions; 					// Total Number of Collisions
	public:
		HashTable(int capacity);		
		unsigned int hashCode(string key);
		void insert(string key, Hotel* value);
		Hotel* find(string key);
		void findAll(string city,string stars);
		void erase(string key); 
		unsigned int getSize();
		unsigned int getCollisions();
		void dump(string path);
		~HashTable();
};
//=================================================================
// implement the methods list above in a file called hashtable.cpp