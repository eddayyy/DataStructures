/***************************************************************************************************************************
Program name: "Social Media Simulation".  This program receives the input of 2 text files populated with ids and people    *
  this information is then used to populate lists of all people, connect 2 friends, count how close any 2 given people are.*
                                                                                                                           *
This file is part of the software program "Social Media Simulation".                                                       *
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  *
version 3 as published by the Free Software Foundation.                                                                    *
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY// without even the implied        *
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     *
A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.                           *
****************************************************************************************************************************
========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**

Author information
  Author name: Eduardo M. Nunez Gomez
  Author email: eduardonunez@csu.fullerton.edu

Program information
  Program name: Social Media Simulation
  Programming languages: All modules are written in C++ 
  Date program began: 2022-Dec-09 2200 PDT GMT-07:00
  Date of last update: 2022-Dec-17 0013 PDT GMT-07:00
  Date comments upgraded: 2022-Dec-17
  Files in this program: main.cpp, Person.hpp, SocialNetwork.hpp, connections.txt, people.txt, Build.sh
  Status: Finished.
  References Consulted: Professor Cooper, DFS Algorithm https://www.geeksforgeeks.org/minimum-number-of-edges-between-two-vertices-of-a-graph-using-dfs/, 
    DFS Algorithm Visualized https://algotree.org/algorithms/tree_graph_traversal/depth_first_search/, CPP Reference https://en.cppreference.com/w/ 
 

Purpose
  This program demonstrates how to read from a file, store the contents, and utilize the contents for necessary calculations. 
  The intention is to demonstrate and implement the C++ knowledge I gained through the Data Structures and Algorithms course 
  (CPSC 131) this semester.

This file
  File name: main.cpp
  Language: C++
========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3**
Compiling and Linking this program and file:
File: Build.sh

Instructions:
1) Place the Build.Sh file in the directory above the targeted program.
2) Enter the following in your linux terminal:
chmod +x Build.sh
3) Step into the targeted directory.
4) Enter the following into your linux termnial:
../Build.sh 

More information regarding this file can be found in the header of Build.sh.  

===== Begin code area ========================================================================================================*/

#include <fstream>            // for file input and output
#include <ios>                // for basic input and output stream functions
#include <iostream>           // for standard input and output streams and functions
#include <limits>             // for information about properties of fundamental numeric types
#include <sstream>            // for stringstream class for input and output on strings
#include <stdexcept>          // for standard exception classes
#include <string>             // for string class for manipulating strings
#include <utility>            // for pair class for storing a pair of values
#include <vector>             // for vector class for dynamic sequence container

#include "Person.hpp"         // for Person class
#include "SocialNetwork.hpp"  // for SocialNetwork class

  /*************************************************************************************************************************** 
  Part 1 has 5 tasks: 
  Task 1 - Complete the operator>> overload for std::pair objects so we can properly import connections.txt below
  Task 2 - Create a SocialNetwork Object
  Task 3 - Import the people.txt file contents into your SocialNetwork object as Nodes.
  Task 4 - Import the connections.txt file contents into your SocialNetwork object as Edges.
  Task 5 - Using std::cout, tell us how many Nodes (people) and how many Edges (connections) there are in the graph.
  *****************************************************************************************************************************/

// (1) Override the >> operator for std::pair so we can import Edges from connections.txt
std::istream & operator>>( std::istream & stream, std::pair<int, int> & nums )
{
  char delimiter = '\0';
  std::pair<int, int> ovLoad;
  if (stream >> ovLoad.first && stream >> std::ws >> delimiter && stream >> std::ws >> ovLoad.second){
    nums = std::move(ovLoad);
  }
  else{
    stream.setstate( std::ios::failbit);
  }
  return stream;
}

int main( )
{
  // (2) Create SocialNetwork Object
  SocialNetwork networkGraph;
  std::vector<std::pair<int, Person>> Graph;

  // (3) Import people.txt
  std::ifstream peopleFile( "people.txt" );
  if( peopleFile.is_open() )                                          // Check if the file is open
  {
    for( std::string line; std::getline( peopleFile, line ); /**/ )
    {
      Person personObject;                                            // Create a person object
      std::istringstream lineStream(line);                            // Read the person object from the input stream
      lineStream >> personObject;
      if(personObject.isValid()){                                     // Add the person to the network ONLY if it is a valid person
        networkGraph.Add( personObject );
      }
    }
    peopleFile.close();                                               // Close the file
  }

  // (4) Import connection.txt
  std::ifstream connectionFile( "connections.txt" );
  if( connectionFile.is_open() )                                      // Check if the file is open
  {
    for( std::string line; std::getline( connectionFile, line ); /**/ )
    {
      std::pair<int, int> connection;                                 // Create the connection container
      std::istringstream lineStream(line);
      lineStream >> connection;
      if( connection.first != connection.second){                     // Connect the two nodes
        networkGraph.Connect(connection.first, connection.second);
      }
    }
    connectionFile.close();                                           // Close the file
  }

  // (5) Print The Count Of Edges & Connections
  std::cout << "Welcome to Datagram where data structure enthusiasts come to connect.\nLets begin!\n\n\nPart 1 Output:";
  std::cout << "\n\nThere are " << networkGraph.graphSize() << " nodes (people). \n";
  std::cout << "There are " << networkGraph.edgeCount() << " edges (connections).\n";

  /*************************************************************************************************************************** 
  Part 2 has 6 tasks: 
  Task 1 - Output all of the people, sorted ascending by Last Name (A-Z).
  Task 2 - Output all of the people, sorted ascending by age (youngest to oldest).
  Task 3 - Output people whose age is over 33, sorted descending (oldest to youngest).
  Task 4 - Prompt the user to search for a person then find that person and display their bio.
  Task 5 - In addition to the bio in Task 4, output the person's list of friends if they are found.
  Task 6 - Prompt the user to search for 2 people by entering their first and last names then output degrees of separation.
  *****************************************************************************************************************************/

  // (1) Output All People, Sorted in Ascending by Last Name (A-Z)
  std::cout << "________________________________________\n\nPart 2 Output: ";
  std::cout << "\n\n Task 1 - Everyone sorted by last name, ascending: \n";
  auto people = networkGraph.allPeople();                              // Populate a list with a people
  people.sort(Person::lt_lname());                                     // Sort by specifying with the structs defined in the People Class
  for (auto person : people){                                          // Iterate through the created list
    std::cout << person.Bio() << std::endl;                            // Print the people's information
  }

  // (2) Output All People, Sorted in Ascending by Age (youngest to oldests)
  people.sort(Person::lt_age());                                       // Sort by specifying with the structs defined in the People Class
  std::cout << "\n\n Task 2 - Everyone sorted by age, ascending: \n";
  for (auto person : people){                                          // Iterate through the created list
    std::cout << person.Bio() << std::endl;                            // Print the people's information
  }

  // (3) Output people whose age is over 33, sorted descending (oldest to youngest)
  std::cout << "\n Task 3 - People over 33, sorted by age descending: \n";
  auto peopleAge = networkGraph.allPeople();                           // Create a new list so that we won't interfere with the other one
  peopleAge.remove_if([](Person& person){                              // Filter out people less than 33 years old
    return person.Age() <= 33;
  });
  peopleAge.sort(Person::gt_age());                                    // Sort by specifying with the structs defined in the People Class
  for( Person person : peopleAge){                                     // Iterate through the created list
    std::cout << person.Bio() << std::endl;                            // Print out the people's information
  }

  // (4) Prompt the user to search for a person then find that person and display their bio.
  std::string fname, lname;                                           // Declare the variables that we will use to collect the names
  std::cout << "\n Task 4 & 5 - Search for a person and display their bio & friends: "  
            << "Press <Enter> after inputting each name.\n" 
            << "First name & last name: ";
  std::cin >> fname >> lname;                                         // Prompt the user for their person

  auto personTest = networkGraph.findPerson(fname, lname);            // Search for the specified person

  if (!personTest.empty()) {                                          // Making Sure person was found
    Person printedPerson = personTest.front();                        // Insert the found person to a person Object
    std::cout << std::endl                                            // Print Out the found person's information in a neat format
              << printedPerson.FirstName() 
              << " " 
              << printedPerson.LastName() 
              << " has been found, they are " 
              << printedPerson.Age() << " years old.\n" 
              << std::endl
              << fname << "'s friends are: \n";

    // (5) In addition to the bio in Task 4, output the person's list of friends if they are found.
    networkGraph.showFriends(printedPerson);
  }
  else {
    std::cout << "\nWe apologize but we could not find '" << fname << " " << lname << "'." << std::endl;
  }
  
  // (6) Prompt the user to search for 2 people by entering their first and last names
  std::string p1FN, p1LN, p2FN, p2LN;
  std::cout << "\n Task 6 - Find the degrees of separation between 2 people:"
            << "\nEnter data for 2 people to search for...";
  std::cout << "\nPerson 1 First Name: ";
  std::cin >> p1FN;
  std::cout << "Person 1 Last Name: ";
  std::cin >> p1LN;
  std::cout << "\nPerson 2 First Name: ";
  std::cin >> p2FN;
  std::cout << "Person 2 Last Name: ";
  std::cin >> p2LN;

  auto p1Search = networkGraph.findPerson(p1FN, p1LN);                // Populate A list with the inputted persons
  auto p2Search = networkGraph.findPerson(p2FN, p2LN);

  if(!p1Search.empty() && !p2Search.empty()){                         // Check that the lists were populated (implying the person was found)
    Person person1 = p1Search.front();                                // Insert the front of the lists into Person objects
    Person person2 = p2Search.front();                                // Then use distanceBetween() function to find the degrees of separation
    auto distanceBetw = networkGraph.distanceBetween(person1, person2);
    if( distanceBetw > 1 ) {
      std::cout << person1.FirstName() << " and " << person2.FirstName() << " have " << distanceBetw << " degrees of separation!" << std::endl;
    }
    else{
      std::cout << person1.FirstName() << " and " << person2.FirstName() << " are friends!\n";
    }
  } 
  else{                                                               // In case we can't find one or more of the people searched for
    std::cout << "We could not find the people you were searching for! " << std::endl;
  }
return 0;
}
