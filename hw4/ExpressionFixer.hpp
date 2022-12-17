#pragma once
// CPP program to convert infix to prefix
#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <stack>
#include <string>

struct ExpressionFixer
{
private:
  bool _isOperator( char c )
  {
    return ( !isalpha( c ) && !isdigit( c ) );
  }
  int _getPriority( char C )
  {
    if( C == '-' || C == '+' )
      return 1;
    else if( C == '*' || C == '/' )
      return 2;
    else if( C == '^' )
      return 3;
    return 0;
  }

public:
  ExpressionFixer() = default;
  std::string infixToPostfix( std::string infix )
  {
    infix = '(' + infix + ')';

    // Special fix for multiplication pedantry 
    // Adds a * operator when an operand is right next to a parentheses
    // Because technically that implies multiplication
    std::regex  pbeg( "\\)([0-9])" );
    std::regex  pend( "([0-9])\\(([0-9])" );

    std::string result;
    std::regex_replace( std::back_inserter( result ), infix.begin(), infix.end(), pbeg, ")*$1" );

    std::string result2;

    std::regex_replace( std::back_inserter( result2 ), result.begin(), result.end(), pend, "$1*($2" );

    infix = result2;
    //////////////////////////////////////////

    int              l = static_cast<int>( infix.size() );
    std::stack<char> char_stack;
    std::string      output;

    for( int i = 0; i < l; i++ )
    {
      char target = infix[i];

      // If the scanned character is an
      // operand, add it to output.
      if( isalpha( target ) || isdigit( target ) )
      {
        // Add a space for multi-digit operands !2022!
        output += target;


        if( !isdigit( infix[i + 1] ) )
        {
          output += ' ';
        }
      }


      // If the scanned character is an
      // ‘(‘, push it to the stack.
      else if( target == '(' )
        char_stack.push( '(' );

      // If the scanned character is an
      // ‘)’, pop and output from the stack
      // until an ‘(‘ is encountered.
      else if( target == ')' )
      {
        while( char_stack.top() != '(' )
        {
          output += char_stack.top();
          char_stack.pop();
        }

        // Remove '(' from the stack
        char_stack.pop();
      }

      // Operator found
      else
      {
        if( _isOperator( char_stack.top() ) )
        {
          if( target == '^' )
          {
            while( _getPriority( target ) <= _getPriority( char_stack.top() ) )
            {
              output += char_stack.top();
              char_stack.pop();
            }
          }
          else
          {
            while( _getPriority( target ) < _getPriority( char_stack.top() ) )
            {
              output += char_stack.top();
              char_stack.pop();
            }
          }

          // Push current Operator on stack
          char_stack.push( target );
        }
      }
    }
    while( !char_stack.empty() )
    {
      output += char_stack.top();
      char_stack.pop();
    }
    return output;
  }

  std::string infixToPrefix( std::string infix )
  {
    /* Reverse std::string
     * Replace ( with ) and vice versa
     * Get Postfix
     * Reverse Postfix  *  */
    int l = static_cast<int>( infix.size() );

    // Reverse infix
    std::reverse( infix.begin(), infix.end() );

    // Replace ( with ) and vice versa
    for( int i = 0; i < l; i++ )
    {
      if( infix[i] == '(' )
      {
        infix[i] = ')';
      }
      else if( infix[i] == ')' )
      {
        infix[i] = '(';
      }
    }

    std::string prefix = infixToPostfix( infix );

    // Reverse postfix
    std::reverse( prefix.begin(), prefix.end() );

    return prefix;
  }
};
