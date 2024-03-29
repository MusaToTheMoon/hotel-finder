#include "hashtable.hpp"

//==========================================
HashTable::HashTable(int capacity)
{
	buckets = new list<Entry>[capacity];	  // Array of Lists of type Entries

	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
}
//==========================================
unsigned int HashTable::getSize() { return size; }
//==========================================
unsigned int HashTable::getCollisions() {	return collisions; }
//==========================================
HashTable::~HashTable() 
{
	delete[] buckets; // deallocate the array
}
//==========================================
unsigned int HashTable::hashCode(string key) // using polynomial hash function
{
	unsigned long h = 0; // to store the hash
	for (int i = 0; i < key.length(); i++) { // uses cyclic hash
		h += (unsigned int)key[i];
		h = (h << 1) | (h >> 31);
		
	}
	return ((h*37) + 41) % capacity;
}
//==========================================
void HashTable::insert(string key, Hotel* value) 
{
	string hotel_name = key.substr(0, key.find(',')); // get just the hotel name
	string city = key.substr(key.find(',')+1); // get just the city name
	unsigned int index = hashCode(key); // get the index to store the key at
	if (buckets[index].size() != 0) { 
		
		this->collisions++; // if the bucket is not empty, consider it a collision
	
		for (Entry e : buckets[index]) {
			if (e.key == hotel_name) { 
				if (e.value == value) return; // if trying to insert the exact same obj for the hotel as the one that already exists, do nothing
				else { // if a record for this hotel exists but not the exact same obj in memory, then update the record
					*e.value = *value; // derefence the pointer and update the record
					delete value;	// delete the obj that was passed in
					
					cout << "Existing record has been successfully updated." << endl;
					return;
				}
			}
		}
	}
	
	// OTHERWISE, if new entry
	buckets[index].push_back(Entry(hotel_name, value)); // add this new entry to the bucket
	cityRecords.insert(cityRecords.getRoot(), city, value); // insert in BST
	this->size++;

	cout << "New record has been successfully added to the database." << endl;
}
//==========================================
Hotel* HashTable::find(string key) 
{
	string hotel_name = key.substr(0, key.find(','));
	unsigned int index = hashCode(key); // to get the hash code
	unsigned long comparisons = 1; // count comparisons
	
	for (Entry e : buckets[index]) { // iterate over the bucket and compare the keys, return the value for the key that matches 
		if (e.key == hotel_name) {
			cout << "Record found after " << to_string(comparisons) << " comparison(s)." << endl;
			return e.value;
		}
		comparisons++;
	}
	cout << "Record not found!" << endl; // otherwise record not found
	return nullptr;
}
//==========================================
void HashTable::erase(string key) 
{
	string hotel_name = key.substr(0, key.find(','));
	string city = key.substr(key.find(',')+1);
	unsigned int index = hashCode(key); // get the index of the key's position

	if (!buckets[index].empty()) {
		for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) { // iterate over the array and erase key when its found
			if (it->key == hotel_name) {
				cityRecords.remove(cityRecords.getRoot(), city, it->value); // remove from BST - memory freed in BST::remove
				it = buckets[index].erase(it); // erase from bucket
				break;
			}
		}
		this->size--;
		cout << hotel_name << " has been successfully deleted." << endl; 
	} else cout << "Record Not Found...!" << endl;
}
//==========================================
void HashTable::dump(string path) 
{
	ofstream dumpFile(path); // open the file
	if (dumpFile) {
		dumpFile << "hotelName,cityName,stars,price,countryName,address" << endl;
		for (unsigned int i = 0; i < capacity; i++) { // iterate over hashtable
			if (buckets[i].size() != 0) { 
				for (auto it = buckets[i].begin(); it != buckets[i].end(); it++) { // if bucket is not empty, iterate over the bucket and write to file
					dumpFile << it->value->toString() << endl;
				}
			}
		}
		
		cout << this->size << " records have been successfully exported to " << path << endl;
	} else cout << "File could not be opened correctly." << endl;
	dumpFile.close();
}
//==========================================
void HashTable::findAll(string city, string stars) 
{
	auto result = cityRecords.findNode(cityRecords.getRoot(), city); // find the node for the city
	if (cityRecords.checkFindNodeReturn(result, city)) get<0>(result)->print(stars); // check if the node returned is valid: see BST::checkFindNodeReturn() for more info. If valid, print the hotels in the city with that many stars
	else cout << "0 records found." << endl;
}
//==========================================