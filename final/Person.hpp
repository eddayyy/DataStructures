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
  File name: Person.cpp
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

#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

class Person
{
  // This allows us to override the >> operator to convert text streams to Person objects
  friend std::istream & operator>>( std::istream & stream, Person & person );

  // Private member variables
private:
  std::string _firstName;
  std::string _lastName;
  int         _age;

public:
  // Default Constructor - so we can instantiate a blank Person
  Person() = default;

  // This constructor is the one we'll prefer to use as it creates a VALID Person
  Person( std::string firstName, std::string lastName, int age )
    : _firstName{ std::move( firstName ) },
      _lastName{ std::move( lastName ) },
      _age{ age }
  {}

  Person & operator=( Person const & rhs ) &     = default;    // Copy Assignment
  Person & operator=( Person && rhs ) & noexcept = default;    // Move Assignment
  Person( Person const & other )                 = default;    // Copy Constructor
  Person( Person && other ) noexcept             = default;    // Move Constructor
  ~Person() noexcept                             = default;    // Destructor

  // This determines if the Person object has all the values it needs to be used.
  // We can use this before attempting to do operations which would fail if any of
  // These values were never set, particularly when importing from a stream.
  bool isValid()
  {
    return _firstName != "" && _lastName != "" && _age >= 0;
  }

  // A simple string that combines all the user's data into 1 string.
  // Alternatively we could override the >> operator but this has more uses.
  std::string Bio()
  {
    return _firstName + " " + _lastName + ", age: " + std::to_string( _age );
  }

  // Return the first name string
  std::string FirstName()
  {
    return _firstName;
  }

  // Return the last name string
  std::string LastName()
  {
    return _lastName;
  }

  // Return the age integer
  int Age()
  {
    return _age;
  }

  // This is the == operator, it tells us how to determine if 2 Person objects are the same.
  inline bool operator==( const Person & rhs ) const noexcept
  {
    return rhs._age == _age && rhs._firstName == _firstName && rhs._lastName == _lastName;
  }

  // These struct definitions are special, they act as comparators for sorting functions.
  // Feed one of these into an STL's sort() function with parentheses and it will tell it how to sort.
  // lt (Less-Than) values = sort ascending, with small values on top. Gt (greater-than) is the opposite.
  // The inline keyword is optional, it's used for compiiler efficiency with very small, simple functions like this. 
  struct lt_fname
  {
    inline bool operator()( const Person & pL, const Person & pR )
    {
      return pL._firstName < pR._firstName;
    }
  };

  struct lt_lname
  {
    inline bool operator()( const Person & pL, const Person & pR )
    {
      return pL._lastName < pR._lastName;
    }
  };

  struct lt_age
  {
    inline bool operator()( const Person & pL, const Person & pR )
    {
      return pL._age < pR._age;
    }
  };
  struct gt_fname
  {
    inline bool operator()( const Person & pL, const Person & pR )
    {
      return pL._firstName > pR._firstName;
    }
  };

  struct gt_lname
  {
    inline bool operator()( const Person & pL, const Person & pR )
    {
      return pL._lastName > pR._lastName;
    }
  };

  struct gt_age
  {
    inline bool operator()( const Person & pL, const Person & pR )
    {
      return pL._age > pR._age;
    }
  };
};

// This >> override allows us to convert a string into a Person object
// This is used to read the contents of people.txt and import a bunch of people.
// This should look familiar, we used it in Homework 1 and Homework 2.
// This is defined OUTSIDE of the class because it affects the std::stream object type. 
std::istream & operator>>( std::istream & stream, Person & person )
{
  Person workingPerson;
  char   delimiter = '\0';

  if(
      stream >> std::ws >> std::quoted( workingPerson._firstName )
      && stream >> std::ws >> delimiter
      && delimiter == ','
      && stream >> std::ws >> std::quoted( workingPerson._lastName )
      && stream >> std::ws >> delimiter
      && delimiter == ','
      && stream >> std::ws >> workingPerson._age )

  {
    person = std::move( workingPerson );
  }
  else
    stream.setstate( std::ios::failbit );
  return stream;
}
