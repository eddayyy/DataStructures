#include <iostream>
#include <vector> 
#include <forward_list>
#include <list>

#include "bookStore.hpp"

int main()
{
    std::string bookName;
    std::string genre;
    std::forward_list<std::string> inventory;
    std::cout << "Hello welcome to Barnes & Noble, what book are you looking for today?\n";
    getline(std::cin, bookName);
    std::cout << "Great now we just need the genre of " << bookName << " \n"; 
    getline(std::cin, genre);
    inventoryImport(inventory, bookName, genre);
    for (auto i = inventory.begin(); i != inventory.end(); i++){
        std::cout << "[ " << *i << " ]\n";
    }
    
}