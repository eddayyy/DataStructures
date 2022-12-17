#pragma once
#include <forward_list>

#include "ExpressionFixer.hpp"


class ExpressionTree
{
public:
  // Tree Node Definition
  class TreeNode
  {
  public:
    // Members
    int         number;
    char        symbol;
    std::string value();
    TreeNode *  left, *right;

    // Constructors
    TreeNode();
    TreeNode( char inSymbol, int inNumber );

    // Accessors/Flags
    bool isLeaf();
    bool isOperator();
    bool isOperand();
  };

private: // Private Members

  // Stack of TreeNodes used for building the tree
  std::forward_list<TreeNode *> _nodeStack;

  // Third-party code that converts an Infix expression to Prefix format
  ExpressionFixer               _fixer;
  // A string to store the original expression the user typed, in case we want to show it to them again. 
  std::string                   _originalExpression;

public:
  // Constructor
  /*
  Construct the tree with an expression string. 
  Use the _buildTree function. It requires a prefix expression so 
  convert your infix expresion to prefix notation first using the ExpressionFixer class. 
  You also might as well store the infix expression in _originalExpression for use later. 
  */
  ExpressionTree( std::string infixExpression );

private: // Utility Functions
  // Build the expression tree with a given expression
  /*
  1.  Loop through the prefix expression's characters (strings are iterable!)
      If you find an operator (math symbol) then _insert() that character
      as a new TreeNode. The number value can be 0. 

  2.  Next check if the character is an operand (number). You could add the
      operand here but that means your code only works with single-digit numbers. 

      To make numbers like 57 or 298 work, you need another loop. 
  
  3.  Create a new loop inside your main loop where the iteration number is the same as your current 
      iteration number (e.g. if you used i for the main loop, use j here and start the loop where i = j). 

  4.  This time we will continue checking if the current character is an operand. 
      If so, we'll add it to an accumulator variable (a new std::string) using the
      string's push_back() function. Be sure to decrement your MAIN iteration variable 
      if you do this because you no longer need to scan that character in the main loop anymore. 

      If the sub-loop detects anything NOT an operand, it should end using a break; statement. 

  5.  After that loop is done, use std::reverse() to reverse the characters in your
      accumulator variable since they will be backwards. Then use std::stoi() to convert it
      into an int. 

  6.  Finally you can use _insert() to insert the new node. Use ' ' (empty space) as your
      symbol and the actual value for your number. 
  */
  void _buildTree( std::string prefixExpression );

  // Insert a TreeNode with either an operator or a number value
  /*
  1.  Create a new tree node using the TreeNode's constructor. 

  2.  Check to see if the new node is going to be an operator or operand. 
      If it's an operator, set the new node's left pointer to the result of the pop() function. 
      Also if it's an operator, set the new node's right pointer to the result of the pop() function.

  3.  use push() to push the new TreeNode to the top of our node stack, which is what holds all of our nodes.
  */
  void _insert( char inSymbol, int inNumber );

  // Is the char A-Z or 0-9? For this homework we don't actually care about A-Z since we can't solve that. 
  bool _isOperand( char ch );

  // Is the char '+','-','*' or '/'? (Plus/Minus/Multiply/Divide)
  bool _isOperator( char ch );

  // Use the tree to get the InFix versino of the expression
  // This is a recursive function that works in tandem with the public function below
  std::string _getInFix( TreeNode * ptr, std::string output );

  // Use the operator and its left/right operands to execute a mathematical function
  float _doMath( char type, float left, float right );

  // Recursive function to solve a simple expression
  // Traverse your Expression Tree and use _doMath to solve each sub-expression and
  // return the value until you're done. 
  float _solve( TreeNode * ptr );

public:
  // Return the expression in "Infix" format
  std::string infixExpression();
  // Return the expression in "Prefix" format
  std::string prefixExpression();
  // Return the expression in "Postfix" format
  std::string postfixExpression();

  // Return the expression in "Infix" format BUT
  // Do this by using your expression tree (use the recursive _getInFix() function for this!)
  std::string getInFix();

  // Push a TreeNode pointer onto the stack using push_front()
  void push( TreeNode * ptr );

  // Pop a TreeNode pointer from the stack and return it
  // Be sure to store the pointer in a variable BEFORE you use pop_front()
  // So you have something to return after you pop the stack. 
  TreeNode * pop();

  // Return a reference to the top TreeNode from the stack
  TreeNode * top();

  // Solve the expression and return the resulting number
  // Use the recursive _solve() function for this!
  // Separating this into a different function allows you to simply
  // Call the _solve() function with top() as the parameter here
  // Instead of making the class consumer feed the argument in. 
  float      solve();
};
