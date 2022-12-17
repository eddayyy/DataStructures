#include <iostream>
#include <stack>
#include <vector>

#include "ToDoList.hpp"


int main()
{
  // Create a ToDoList
  // For testing you can initialize it with a few things to do.
  // For your final output, the list should start EMPTY.
  ToDoList MyList{ "Feed Dog", "Feed Cat", "Wash Clothes" };

  // Create a simple vector to store some commands
  std::vector<std::string> commands;

  // Create a temporary string to hold commands
  std::string command;

  // Get commands from the input file
  while( std::cin >> command )
  {
    commands.push_back( command );
  }

  // Execute the commands
  for( auto i : commands )
  {
    MyList.Command( i );
  }

  // Your output should make sense. It should throw errors or provide warnings
  // if input is invalid.
  /* EXAMPLE
  The following ToDoList: 

  ToDoList MyList {"Feed Dog", "Feed Cat", "Wash Clothes"};

  With the following command input: 

    DoNext
    Undo
    DoNext
    Redo
    SayHi
  
  Should have the following output: 

    Did Task: [Feed Dog]
    Undid Task: [Feed Dog]
    Did Task: [Feed Cat]
    Nothing to Redo!
    terminate called after throwing an instance of 'std::invalid_argument'
      what():  Command Not Found
    Aborted
  */

  // Notice that last part? It's okay to consider invalid Redo/Undo actions as a warning
  // But bad commands should throw an exception using:
  // throw std::invalid_argument( "Command Not Found" );

  // The input.txt file I use for grading will be unique and should generate both warnings
  // and an invalid argument exception. 

  return 0;
}
