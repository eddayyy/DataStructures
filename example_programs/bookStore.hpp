#include <math.h>
#include <iostream>
#include <forward_list>
#include <compare>

void inventoryImport (std::forward_list<std::string> inventory, std::string bookName, std::string genre){
    inventory.push_front(genre);
    inventory.push_front(bookName);
}


void print(std::forward_list<std::string> inventory){
    for (auto i = inventory.begin(); i != inventory.end(); i++){
        std::cout << "[ " << *i << " ]\n";
    }
}


class bookStore{
    public:
    void inventoryImport(std::string bookName, std::string genre);

    private:



};
