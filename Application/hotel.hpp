/**
 * Name         : hotel.hpp
 * Author       : Muhammad Musa Khan
 * Description  : Hotel class implementation
*/

#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Hotel
{
	private:
		string name;	//name of the hotel	
		string city;	//city of the hotel
		string stars;	//starts of the hotel
		string price;	//price per night
		string country;	//country
		string address;	//full address of the hotel
	public:
		Hotel(string name,string city, string stars,string price,string country,string address);	//constructor
		string getName();	
		string getCity();	
		string getStars();
		string getPrice();
		string getCountry();
		string getAddress();
		string toString(); // used in dump function
		void print(); // used in find function
		void print2(); // used in findAll function
		void operator=(const Hotel& other); // used in HashTable::insert() function to modify an existing record by simply overwriting it
};
