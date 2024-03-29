#include "hotel.hpp"

//==========================================
Hotel::Hotel(string name,string city, string stars,string price,string country,string address) : name(name), city(city), stars(stars), price(price), country(country), address(address) {}
//==========================================
string Hotel::getName() { return this->name; }	
//==========================================
string Hotel::getCity()	{ return this->city; }
//==========================================
string Hotel::getStars() { return this->stars; }
//==========================================
string Hotel::getPrice() { return this->price; }
//==========================================
string Hotel::getCountry() { return this->country; }
//==========================================
string Hotel::getAddress() { return this->address; }
//==========================================
string Hotel::toString() // used in dump function
{
  return this->name + "," + this->city + "," + this->stars + "," + this->price + "," + this->country + "," + this->address;
}
//==========================================
void Hotel::print() // used in find function
{
  cout << "Hotel Name: " << this->name << endl;
  cout << "City      : " << this->city << endl;
  cout << "Stars     : " << this->stars << endl;
  cout << "Price     : " << this->price << endl;
  cout << "Country   : " << this->country << endl;
  cout << "Address   : " << this->address << endl;
// << std::left << setw(12) 
}
//==========================================
void Hotel::print2() // used in findAll function
{
  cout << std::left << setw(50) << this->name << " " << setw(10) << this->city << " " << setw(6) << this->stars << " " << setw(10) << this->stars << " " << setw(20) << this->country << " " << this->address << endl;
}
//==========================================
void Hotel::operator=(const Hotel& other) { // used in HashTable::insert() function to modify an existing record by simply overwriting it
  this->name = other.name;
  this->city = other.city;
  this->stars = other.stars;
  this->price = other.price;
  this->country = other.country;
  this->address = other.address;
}
