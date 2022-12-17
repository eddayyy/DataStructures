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
    // A List of Edges has already been created in line 22
    std::list<Edge> result;  // Initialized Result for the return value

    for(Edge edge : EdgeList){
      // Comparing the Values
      if( (edge.first) -> second == person || (edge.second) -> second == person){ 
        result.push_back(edge);
      }
    }

    return result;
  }

  // 1. Use a classic index-based loop on the Graph vector
  // 2. Find the Node where the value = the person provided
  // 3. When found, return the memory address
  // 4. If nothing is found, return nullptr
  Node * _nodeFor( Person person )
  {
    for(int i = 0; i < static_cast<int> (Graph.size()); i++){
      if(Graph[i].second == person){
        return &Graph[i];
      }
    }
    return nullptr;
  }

  // 1. Create a list of Node pointers to return
  // 2. Find the Node pointer for the person provided
  // 3. If the node is found (not nullptr) find the person's Edges
  // 4. Loop through the found edges and find the Node pointer that is NOT the person parameter
  // 5. Add the Node pointer to your return list and return that list at the end
  std::list<Node *> _friendsOf( Person person )
  {
    // Created a list of Node Pointers to return
    std::list<Node *> friends;

    // Finding the node pointer for the person provided
    Node * ogNode = _nodeFor(person);

    // Beginning the loop to search for the right node & find the edges
    if(ogNode != nullptr){
      std::list<Edge> edges = _findEdges(person);
      // Looping through the found edges to find the node pointer that
      // ISN'T the person we received in the parameter.
      for(Edge item : edges){
        // Finding the Node Pointer for the friend of the person.
        Node * friendNode = item.first->second == person ? item.second : item.first;
        friends.push_back(friendNode);
      }
    }
    // Return the list of the person's friends :)
    return friends;
  }

  // This function will calculate the minimum # of edges between 2 Nodes
  // visited, min_edges and edge_count are passed by REFERENCE so they can be modified by this function
  // This function doesn't need to return anything since the important variables are references that are modified
  // Use the Node type's first property as the index for the visited vector.
  // You can use this example as a reference: https://www.geeksforgeeks.org/minimum-number-of-edges-between-two-vertices-of-a-graph-using-dfs/
  // Modifications need to be made for this to work with our structures but it can be done!
  void _minEdges( std::vector<bool> & visited, Person pStart, Person pEnd, int & min_edges, int & edge_count )
{
  // Find the node pointer for the start person
  Node * startNode = _nodeFor(pStart);

  // Set the start node as visited
  visited[startNode -> first] = true;

  // If the start node is the end node, set the minimum number of edges to 0
  if (pStart == pEnd) {
    if(min_edges > edge_count) min_edges = edge_count;
  }
  else{
    auto personEdges = _findEdges(pStart);
    
    for(auto i = personEdges.begin(); i != personEdges.end(); i++ ){
      auto edgeFor = *i;
      Node * edgeOf = edgeFor.first->second == pStart ? edgeFor.second : edgeFor.first;
      if ( !visited[edgeOf->first]){
        edge_count++;
        _minEdges(visited, edgeOf->second, pEnd, min_edges, edge_count);
      }
    }
  }

  visited[startNode->first] = false;
  // Decrement the edge count
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

    // Declaring min_edges as a type other than int because of a warining
    // warning: implicit conversion loses integer precision:
    // std::list<std::pair<std::pair<int, Person> *, std::pair<int, Person>
    // *>>::size_type' (aka 'unsigned long') to 'int'

    int min_edges = static_cast<int>(EdgeList.size());
    int edge_count = 0;
    _minEdges(visited, p1, p2, min_edges, edge_count);
    return min_edges;
  }

  // List of people in the graph
  // 1. Just create a temporary list of people, loop through Graph and add each person to the temporary list.
  // 2. Return the temporary list
  std::list<Person> allPeople()
  {
    // Temporary list of people
    std::list<Person> temp_People;

    // Looping through the graph to add each person to the temp list
    for(const Node& node : Graph){
      temp_People.push_back(node.second);
    }
    // Returning the temp_People list 
    return temp_People;
  }

  // Make use of Lambda functions to find people who meet certain criteria (First/Last Name and/or Age)
  // The first parameter is a lambda function. It returns bool & needs a noexcept flag after the parentheses when you go to use it.
  // Parameter 2 is optional and will help us decide how to sort the list after it is built.
  std::list<Person> findPeople( std::function<bool( Person )> filterFunction, std::function<bool(Person, Person)> sortby = nullptr) noexcept
  {
    // 1. Create a list to return
    // 2. Loop through the Graph
    // 3. For each node in the Graph, run the Node's Person (value) through the filterFunction()
    // 4. IF the filterFunction() returns true, add that person to the output list
    // 5. Use the sortby variable to decide how to sort the list.
    // 6. std::list has a built-in sort function. It requires use of the comparator defined in the Person object.
    std::list<Person> outList;

    for( Node item : Graph )
    {
      if( filterFunction( item.second ) )
      {
        outList.push_back( item.second );
      }
    }

    outList.sort(sortby);
    return outList;
  }

  // Similar to findPeople but we only want to find 1 person
  // Use the findPeople function with a Lambda that checks for the provided first/last Names
  // The age is optional. If age < 0, ignore it. Otherwise use it in the filter & compare it to p.Age()
  // Make sure the resulting list of People is not Empty and, if not, select the first element using .front() and return it.
  // Return a list of people because you might NOT find the person, so the list will be empty!
  std::list<Person> findPerson( std::string firstName, std::string lastName, int age = -1 )
  {
    // Filtering based on first and last names using the findPeople() function
    auto people = findPeople([&](Person p) {return p.FirstName() == firstName && p.LastName() == lastName; });

    // If age is provided remove people based on age
    if (age > 0){
      people.remove_if([&](Person p) {return p.Age() != age; });
    }

    // Checking to see if the list empty, if it is then the first element will be returned
    if (!people.empty()){
      return {people.front()};
    }
    // Return the resulting list of people
    return people;
  }

  // Use the _friendsOf() function to find everyone connected to the person
  // Output their information using std::cout (the Bio() function works well for this)
  void showFriends( Person person )
  {
    // Finding the friends of the person
    auto friendlist = _friendsOf(person);

    // Outputting their information using the Bio() function
    for(auto friends : friendlist){
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
    // Using _nodeFor() function to find the nodes for person 1 & 2 respectively.
    // Note: auto is used frequently as to save time.
    auto np1 = _nodeFor(p1);
    auto np2 = _nodeFor(p2);
    
    // Creating an edge and adding the two nodes
    EdgeList.push_back(std::make_pair(np1, np2));
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
