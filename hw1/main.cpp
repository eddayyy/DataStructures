#include <iomanip>    // this gives us access to set precision
#include <iostream>
#include <memory>
#include <vector>

#include "GroceryItem.hpp"


int main()
{
  std::cout << std::showpoint << std::fixed << std::setprecision( 2 )
            << "Welcome to Costco Wholesale. Place grocery items into your shopping cart by entering each item's information.\n"
            << "   Enclose string entries in quotes, separate fields with comas\n"
            << "   for example: \"00016000306707\", \"B~etty Crocker\", \"Betty Crocker Double Chocolate Chunk Cookie Mix\", 17.19\n"
            << "   Enter CTRL-z (Windows) or CTRL-D (Linux) to quit\n\n";

  // Making a vector of unique pointers
  std::vector<std::unique_ptr<GroceryItem>> shoppingCart;

  // We're asking the user for the input and taking it in the form of UPC Codes
  // this will go on until the end of file
  GroceryItem item;

  while( std::cout << "Enter the UPC, Product Brand, Product Name, and Price\n", std::cin >> item )
  {
    shoppingCart.emplace_back( std::make_unique<GroceryItem>( std::move( item ) ) );    // making a shallow copy of item by moving it into GroceryItem
    std::cout << "This item was added to your shopping cart: " << *shoppingCart.back() << "\n\n";
  }


  // Now I have to display them in reverse order !!
  std::cout << "\n\nHere is an itemized list of the items in your shopping cart:\n";


  for( auto i = shoppingCart.crbegin(); i < shoppingCart.crend(); i++ ) std::cout
                                                                            << **i << "\n";


  return 0;
}
