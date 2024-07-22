#include "item.h"
#include <iostream>


Item::Item(const char* name): name(name){

}

std::string Item::getName() const{
    return name;
}