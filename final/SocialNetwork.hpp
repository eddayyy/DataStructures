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
  File name: SocialNetwork.cpp
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
#include <algorithm>
#include <initializer_list>
#include <list>
#include <map>
#include <utility>
#include <vector>

#include "Person.hpp"

class SocialNetwork
{
  /*
    Private members and type definitions
  */

  // typedef allows us to rename a standard data structure for added clarity
  typedef std::pair<int, Person>    Node;    // A Node has an ID (int) and a value (Person)
  typedef std::pair<Node *, Node *> Edge;    // An Edge is a connection between 2 Nodes

  // Store the list of edges (Connections)
  std::list<Edge> EdgeList;
  // Store the actual Nodes in our graph
  std::vector<Node> Graph;

  /*
    Private Utility Functions
  */

  // 1. Create a list of Edges
  // 2. Search the EdgeList object for edges where either node relates to the person
  // 3. Add them to the new list and return it
  std::list<Edge> _findEdges( Person person )
  {
    std::list<Edge> result;                                                               // Initialize this list to return the values in
    for(Edge edge : EdgeList){                                                            // Iterate through the EdgeList
      if( (edge.first) -> second == person || (edge.second) -> second == person){         // Comparing the Values
        result.push_back(edge);                                                           // Append the initialized list with the edge
      }
    }

    return result;                                                                        // Return the resulting list
  }

  
  // 2. Find the Node where the value = the person provided
  // 3. When found, return the memory address
  // 4. If nothing is found, return nullptr
  Node * _nodeFor( Person person )
  {
    for(int i = 0; i < static_cast<int> (Graph.size()); i++){                             // Use a classic index-based loop on the Graph vector
      if(Graph[i].second == person){                                                      // Find the Node where the value = the person provided
        return &Graph[i];                                                                 // When found, return the memory address
      }
    }
    return nullptr;                                                                       // If nothing is found, return nullptr
  }

  // 1. Create a list of Node pointers to return
  // 2. Find the Node pointer for the person provided
  // 3. If the node is found (not nullptr) find the person's Edges
  // 4. Loop through the found edges and find the Node pointer that is NOT the person parameter
  // 5. Add the Node pointer to your return list and return that list at the end
  std::list<Node *> _friendsOf( Person person )
  {
    std::list<Node *> friends;                                                            // Created a list of Node Pointers to return
    Node * ogNode = _nodeFor(person);                                                     // Finding the node pointer for the person provided
    if(ogNode != nullptr){                                                                // Beginning the loop to search for the right node & find the edges
      std::list<Edge> edges = _findEdges(person);
      for(Edge item : edges){                                                             // Looping through the found edges to find the node pointer
        Node * friendNode = item.first->second == person ? item.second : item.first;      // Finding the Node Pointer for the friend of the person.
        friends.push_back(friendNode);
      }
    }
    return friends;                                                                       // Return the list of the person's friends :)
  }

  // This function will calculate the minimum # of edges between 2 Nodes
  // visited, min_edges and edge_count are passed by REFERENCE so they can be modified by this function
  // This function doesn't need to return anything since the important variables are references that are modified
  // Use the Node type's first property as the index for the visited vector.
  // You can use this example as a reference: https://www.geeksforgeeks.org/minimum-number-of-edges-between-two-vertices-of-a-graph-using-dfs/
  // Modifications need to be made for this to work with our structures but it can be done!
  void _minEdges( std::vector<bool> & visited, Person pStart, Person pEnd, int & min_edges, int & edge_count )
{
  Node * startNode = _nodeFor(pStart);                                                    // Find the node pointer for the start person
  visited[startNode -> first] = true;                                                     // Set the start node as visited
  if (pStart == pEnd) {                                                                   // If the start node is the end node, set the minimum number of edges to 0
    if(min_edges > edge_count) min_edges = edge_count;
  }
  else{
    auto personEdges = _findEdges(pStart);                                                // Iterate through the edges for the start person
    for(auto i = personEdges.begin(); i != personEdges.end(); i++ ){
      auto edgeFor = *i;
      Node * edgeOf = edgeFor.first->second == pStart ? edgeFor.second : edgeFor.first;
      if ( !visited[edgeOf->first]){
        edge_count++;                                                                     // If the end node has not been visited, increment the edge count and recursively call the function
        _minEdges(visited, edgeOf->second, pEnd, min_edges, edge_count);
      }
    }
  }
  visited[startNode->first] = false;                                                      // Set the start node as not visited and decrement the edge count before returning
  edge_count--;  

}



public:
  // Default Constructor
  SocialNetwork() = default;

  // Constructor with a {bracket, separated} list of Person objects
  SocialNetwork( const std::initializer_list<Person> & newUsers )
  {
    for( auto && person : newUsers )
    {
      Add( person );
    }
  }

  // Use the _minEdges() function to calculate the minimum # of edges between 2 people
  // 1. Create the visited vector; initialize it with the same size as the Graph vector so it has enough space!
  // 2. Create the min_edges int and initialize it to the size of the EdgeList (which would be the maximum)
  // 3. Create the edge_count int and set it to 0 to start.
  // 4. Call the _minEdges() function with the appropriate arguments
  // 5. Return the min_edges int. Our _minEdges() function will modify it as needed since it is passed via reference.
  int distanceBetween( Person p1, Person p2 )
  {
    std::vector<bool> visited(Graph.size());
    int min_edges = static_cast<int>(EdgeList.size());                                    // Static cast the size because of type incompatibility
    int edge_count = 0;                                                                   // Initialize the edge count to 0
    _minEdges(visited, p1, p2, min_edges, edge_count);                                    // Let the private function _minEdges() do the work here
    return min_edges;
  }

  // List of people in the graph
  // 1. Just create a temporary list of people, loop through Graph and add each person to the temporary list.
  // 2. Return the temporary list
  std::list<Person> allPeople()
  {
    std::list<Person> temp_People;                                                        // Temporary list of people
    for(const Node& node : Graph){                                                        // Looping through the graph to add each person to the temp list
      temp_People.push_back(node.second);
    }
    return temp_People;                                                                   // Returning the temp_People list 
  }

  // Make use of Lambda functions to find people who meet certain criteria (First/Last Name and/or Age)
  // The first parameter is a lambda function. It returns bool & needs a noexcept flag after the parentheses when you go to use it.
  // Parameter 2 is optional and will help us decide how to sort the list after it is built.
  std::list<Person> findPeople( std::function<bool( Person )> filterFunction, std::function<bool(Person, Person)> sortby = nullptr) noexcept
  {
    std::list<Person> outList;                                                            // Create a list to return

    for( Node item : Graph )                                                              // Loop through the Graph

    {
      if( filterFunction( item.second ) )                                                 // For each node in the Graph, run the Node's Person (value) through the filterFunction()
      {
        outList.push_back( item.second );                                                 // IF the filterFunction() returns true, add that person to the output list

      }
    }

    outList.sort(sortby);                                                                  // Use the sortby variable to decide how to sort the list.
    return outList;
  }

  // Similar to findPeople but we only want to find 1 person
  // Use the findPeople function with a Lambda that checks for the provided first/last Names
  // The age is optional. If age < 0, ignore it. Otherwise use it in the filter & compare it to p.Age()
  // Make sure the resulting list of People is not Empty and, if not, select the first element using .front() and return it.
  // Return a list of people because you might NOT find the person, so the list will be empty!
  std::list<Person> findPerson( std::string firstName, std::string lastName, int age = -1 )
  {                                                                                       // Filtering based on first and last names using the findPeople() function
    auto people = findPeople([&](Person p) {return p.FirstName() == firstName && p.LastName() == lastName; });
    if (age > 0){                                                                         // If age is provided remove people based on age
      people.remove_if([&](Person p) {return p.Age() != age; });
    }
    if (!people.empty()){                                                                 // Checking to see if the list empty, if it is then the first element will be returned
      return {people.front()};
    }
    return people;                                                                        // Return the resulting list of people
  }

  // Use the _friendsOf() function to find everyone connected to the person
  // Output their information using std::cout (the Bio() function works well for this)
  void showFriends( Person person )
  {
    auto friendlist = _friendsOf(person);                                                 // Finding the friends of the person
    for(auto friends : friendlist){                                                       // Outputting their information using the Bio() function
      std::cout << friends->second.Bio() << std::endl;
    }
  }

  // Just a shortcut to be able to use showFriends() with first/last name and possibly age
  // Just use the findPerson() function and the showFriends() function, this should only be 2 lines of code.
  void showFriends( std::string firstName, std::string lastName, int age = -1 )
  {
    std::list<Person> results = findPerson( firstName, lastName, age );
    if( results.empty() == false )
    {
      Person targetPerson = results.front();
      showFriends( targetPerson );
    }
    std::cout << "Person Not Found" << std::endl;
  }

  // Add a Node to the graph
  // The first property should = Graph size and second = the Person to add
  void Add( Person newPerson )
  {
    Graph.push_back(std::make_pair(Graph.size(), newPerson));
  }

  // Create an Edge between 2 people
  // 1. Find each person's node using _nodeFor
  // 2. Create an edge using std::make_pair() and add it to the EdgeList
  void Connect( Person p1, Person p2 )
  {
    auto np1 = _nodeFor(p1);                                                              // Using _nodeFor() function to find the nodes for person 1 & 2 respectively.
    auto np2 = _nodeFor(p2);                                                              // Note: auto is used frequently as to save time. 
    EdgeList.push_back(std::make_pair(np1, np2));                                         // Creating an edge and adding the two nodes
  }

// Here you don't need _nodeFor you can just access the node on the graph with brackets
// Be sure to subtract 1 from these numbers because the graph vector index is 0-based!
// You'll need to use the address operator here...
  void Connect( int index1, int index2 )
  {
    EdgeList.push_back(std::make_pair(&Graph[index1-1], &Graph[index2-1]));
  }

  // This does the exact same thing as connect but allows us to add many connections at once
  // You need a loop within a loop. The people parameter is itself a list of lists of Person objects.
  // Use a vector in loop 1 to store pairs of people found in loop 2
  // In loop 2, Use bracket[j] notation and the Connect() function to connect the 2 people found
  // Clear the vector before continuing the loop so it only ever has 2 people at once (vector has a .clear() function)
  void Connect( const std::initializer_list<std::initializer_list<Person>> & people )
  {
    for( auto i : people )
    {
      std::vector<Person> targets;
      for( auto j : i )
      {
        targets.push_back( j );
      }
      Connect( targets[0], targets[1] );
      targets.clear();
    }
  }

 // Just return the size of the Graph field. Graph is PRIVATE so your code in main.cpp
 // doesn't have any way of accessing it directly. 
  std::size_t graphSize()
  {
    return Graph.size();
  }
// Return the size of the EdgeList field. EdgeList is PRIVATE so your code in main.cpp
// doesn't have any way of accessing it directly. 
  std::size_t edgeCount()
  {
    return EdgeList.size();
  }
};
