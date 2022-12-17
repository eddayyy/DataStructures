#pragma once
#include <iostream>
#include <queue>
#include <stack>

class ToDoList
{
private:
  // Private Containers
  std::queue<std::string> _todo; // STL that stores the queue of things to do
  std::stack<std::string> _undo; // STL that stores things we can undo
  std::stack<std::string> _redo; // STL that stores things we've undone and can redo

  // Private Functions
  void _announce( std::string verb, std::string & msg ); // Output what is being done
  void _warn( std::string verb ); // Warn the user about incorrect input

public:
  // Constructor
  ToDoList();

  // List-Initialized Constructor
  ToDoList( const std::initializer_list<std::string> & tasks );

  // Actional
  void Add( std::string newItem ); //Add an item to the ToDo List
  void DoNext(); // Do the next thing on the ToDo list. How does this effect the "Redo" list? 
  void Undo(); // "Undo" a task from the Undo list and put it in the Redo list
  void Redo(); // "Redo" the last action that was undone, IF it's accessible.
  void Command(std::string command); // Accept text input to perform one of our DoNext/Undo/Redo actions

  // Informational
  bool isEmpty(); // Tell us if the ToDo list is empty
  std::size_t size(); // Give us the size of the ToDo list
};
