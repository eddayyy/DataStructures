// Author: Eduardo Nunez
// Author email: eduardonunez@csu.fullerton.edu
// NOTE: Labels were placed in the order corresponding to the hpp file


#include <iostream>
#include <queue>
#include <stack>
#include "ToDoList.hpp"

  // Private Functions
void ToDoList::_announce( std::string verb, std::string & msg){
    std::cout << verb << " Task: [" << msg << "]\n";
}

void ToDoList::_warn( std::string verb ){
    std::cout << "Nothing to " << verb << "!\n";
}

  // Constructor
ToDoList::ToDoList() = default;

  // List-Initialized Constructor
  ToDoList::ToDoList( const std::initializer_list<std::string> & tasks ){
    for(auto task : tasks) Add(task);
  }

  // Actional
void ToDoList::Add( std::string newItem){
    _todo.push( newItem );
}

void ToDoList::DoNext(){
    if(_todo.empty()){
        _warn( "Do" );
        return; 
    }
    _undo.push( _todo.front());
    _redo = std::stack<std::string>();
    _announce ( "Did", _todo.front() );
    _todo.pop();
}

void ToDoList::Undo(){
    if( _undo.empty() ){
        _warn( "Undo" );
        return;
    }
    _announce( "Undid", _undo.top() ); 
    _redo.push( _undo.top() );
    _undo.pop();
}

void ToDoList::Redo(){
    if( _redo.empty() ){
        _warn( "Redo" );
        return; 
    }
    _announce( "Redid", _redo.top());
    _undo.push( _redo.top()); 
    _redo.pop();
}

void ToDoList::Command( std::string command ){

    if( command == "DoNext" ){
        DoNext();
        return; 
    }

    if( command == "Redo"){
        Redo();
        return;
    }

    if(command == "Undo"){
        Undo();
        return;
    }


    throw std::invalid_argument("Command Not Found");
}

  // Informational
bool ToDoList::isEmpty(){
    return _todo.empty();
}

std::size_t ToDoList::size(){
    return _todo.size();
}
