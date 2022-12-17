#include <iostream>
#include <iomanip>
#include "ExpressionTree.hpp"

// The following code will run with a single expression being fed through your aglorithms
// with an input.txt file. 

// You can test your output with an input.txt file using this syntax: 
// ./Program_Name < input.txt

// You can also feed an expression directly in as a string: 
// ./Program_Name <<< "3+5/6-(2+3)"

/*
The example above should have this EXACT output: 

  Enter Expression 
  Expression Used: 3+5/6-(2+3)
  Postfix: 3 5 6 /2 3 +-+
  Prefix: -+ 3/ 5 6+ 2 3
  Infix: (3+(5/6))-(2+3)
  Solved: -1.167

*/

int main()
{
  std::cout << std::setprecision(4);
  std::string expression;
  std::cout << "Enter Expression \n";
  std::cin >> expression;
  std::cout << "Expression Used: " << expression << std::endl;
  ExpressionTree et( expression );
  std::cout << "Postfix: " << et.postfixExpression() << "\n";
  std::cout << "Prefix: " << et.prefixExpression() << "\n";
  std::cout << "Infix: " << et.getInFix() << std::endl;
  std::cout << "Solved: " << et.solve() << std::endl;
  return 0;
}
