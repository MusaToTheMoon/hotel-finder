# Hotel Finder Application
Hotel Finder is a C++ application utilizing custom, written-from-scratch Hash Table and Binary Search Tree implementations to efficiently store, retrieve, and delete hotel records based on 'hotel name' and 'city name' combinations.

## Important considerations
- To ensure efficiency, the hotel-finder application utilizes a Hash Table as its primary data structure. Hash Tables offer constant-time average-case performance for accessing records (O(1)), making them ideal for quick retrieval based on the unique key generated from the combination of hotelName and cityName. 
- Additionally, an auxiliary Binary Search Tree (BST) is maintained to facilitate efficient findAll searches, leveraging its ability to maintain ordered data and provide logarithmic-time average-case search operations (O(logn)).

## Usage (how-to)
To use the application, run the following command:
```bash
./hotelFinder -f <filename>
#eg: ./hotelFinder -f hotels.csv
```
Two files containing sample hotel data to start you off are provided: 'hotels.csv' and 'hotels100k.csv'.

### List of Commands
<table>
  <tr>
    <td style="padding-right: 20px;">
      insert &lt;Hotel Details&gt;
    </td>
    <td>
      Add a new record to the Database using the formart &lt;HotelName,CityName,Stars,Price,CountryName,Address&gt;
    </td>
  </tr>
  
  <tr>
    <td style="padding-right: 20px;">
      find &lt;HotelName,CityName&gt;
    </td>
    <td>
      Find a specific hotel in the given City.
    </td>
  </tr>
  
  <tr>
    <td style="padding-right: 20px;">
      findAll &lt;CityName&gt;
    </td>
    <td>
      Find all hotels of the given City.
    </td>
  </tr>
  
  <tr>
    <td style="padding-right: 20px;">
      findAll &lt;CityName,Stars&gt;
    </td>
    <td>
      Find all hotels of the given City which are have the stars given as argument.
    </td>
  </tr>
  
  <tr>
    <td style="padding-right: 20px;">
      delete &lt;HotelName,CityName&gt;
    </td>
    <td>
      Delete a specific record.
    </td>
  </tr>
    <tr>
    <td style="padding-right: 20px;">
      dump &lt;file&gt;
    </td>
    <td>
      Dump the content of the entire structure(s) into the given file.
    </td>
  </tr>
  <tr>
    <td style="padding-right: 20px;">
      exit
    </td>
    <td>
      Quit the program.
    </td>
  </tr>
</table>


## Goals
- Efficient implementations of Hash Table and Binary Search Tree data structures.
- Modular, easy-to-understand, and well-commented code.
- Separate compilation using multiple cpp files and header files.
- Use of Makefile for building the project.
- Ability to handle a large number of hotel records and cities efficiently.
- Support for input from terminal or text file.
