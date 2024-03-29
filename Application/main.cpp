/**
 * Name         : main.cpp
 * Author       : Muhammad Musa Khan
 * Description  : Hotel Finder main program
*/

#include<iostream>
#include<exception>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<list>
#include<cstdio>
#include<cstring>
#include "hashtable.hpp"

using namespace std;
Hotel* stringtoHotel(string details)
{
	try	
	{
		string name,city,country,address,stars,price;
		stringstream sstr(details);
		getline(sstr,name,',');
		getline(sstr,city,',');
		getline(sstr,stars,',');
		getline(sstr,price,',');
		getline(sstr,country,',');
		getline(sstr,address);

		Hotel *hotel = new Hotel(name,city,stars,price,country,address);
		return hotel;
	}
	catch(exception &ex)
	{
		cout<<"Invalid Hotel details. Please use the following format"<<endl;
		cout<<"hotelName,cityName,stars,price,countryName,address"<<endl;
		return nullptr;
	}
}
//=========================================================
void listCommands()
{
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"List of Commands:"<<endl;
	cout<<"insert <Hotel Details>          :Add a new record to the Database using the formart <HotelName,CityName,Stars,Price,CountryName,Address>"<<endl;
	cout<<"find <HotelName,CityName>       :Find a specific hotel in the given City."<<endl;
	cout<<"findAll <CityName>              :Find all hotels of the given City."<<endl;
	cout<<"findAll <CityName,Stars>        :Find all hotels of the given City which are have the stars given as argument."<<endl;
	cout<<"delete <HotelName,CityName>     :Delete a specific record."<<endl;
	cout<<"dump <file>                     :Dump the content of the entire structure(s) into the given file."<<endl;
	cout<<"exit                            :Quit the program."<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
}
//======================================================
int main(int argc, char** args)
{
	HashTable myHashTable(125003);
	
	if(argc==3 and strcmp(args[1],"-f")==0)
	{
		ifstream fin;
		fin.open(args[2]);
		if(!fin){
			cout<<"Can not open the file <zipcodes.txt>...!"<<endl;
			exit(-1);
		}

		// int count=0;
		string line;
		getline(fin,line);  //skip first line
		while(!fin.eof() /* && count < 100 */)
		{
			getline(fin,line);
			Hotel *hotel= stringtoHotel(line);
			myHashTable.insert(hotel->getName()+","+hotel->getCity(),hotel);
			// count++;
		}
		fin.close();
	}
	cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
	cout<<"Total number of collisions = "<<myHashTable.getCollisions()<<endl;
	cout<<"% of collisions = "<<float(myHashTable.getCollisions())/myHashTable.getSize()*100<<endl;	
	
	listCommands();
	while(true)
	{
		string user_input, command, argument1, argument2;
		cout<<">";
		getline(cin,user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,argument1,',');
		getline(sstr,argument2);

		//cout<<argument1<<endl<<argument2<<endl;

		if(command == "find") 
		{
			Hotel *result = myHashTable.find(argument1+","+argument2);
			if(result!=nullptr)	//cout<<result->toString()<<endl;
								result->print();
			fflush(stdin);
			cin.clear();
		}
		else if(command == "findAll")
		{
			myHashTable.findAll(argument1,argument2);
			fflush(stdin);
			cin.clear();
		}
		else if(command == "insert") 
		{
			Hotel *hotel = stringtoHotel(argument1+","+argument2);
			if(hotel!=nullptr)	//if the input is in correct format
				myHashTable.insert(hotel->getName()+","+hotel->getCity(),hotel);
		}
		else if(command == "delete")	myHashTable.erase(argument1+","+argument2);
		else if(command == "help") 		listCommands();
		else if(command == "dump")	    myHashTable.dump(argument1);
		else if(command == "exit")	  	break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}
