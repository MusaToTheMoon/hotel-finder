hotelFinder: main.o hashtable.o hotel.o
	g++ main.o hashtable.o hotel.o -o hotelFinder
main.o: hashtable.cpp hashtable.hpp main.cpp
	g++ -c main.cpp
hashtable.o: hashtable.cpp bst.hpp hotel.cpp hashtable.hpp hotel.hpp
	g++ -c hashtable.cpp
hotel.o: hotel.cpp hotel.hpp
	g++ -c hotel.cpp
clean:
	rm -f main.o hashtable.o hotel.o hotelFinder gmon.out	
profile: clean hotelFinder
	g++ -g -Wall -pg main.cpp hashtable.cpp hotel.cpp -o hotelFinder