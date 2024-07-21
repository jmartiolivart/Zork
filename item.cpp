#include "item.h"
#include <iostream>


Item::Item(const char* name): name(name){

    std::cout << "Item created: " << name << std::endl;
}

std::string Item::getName() const{
    return name;
}