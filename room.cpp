#include "room.h"
#include <iostream>
#include <string>

Room::Room(const char* name, const char* description) : name(name), description(description) 
{
    std::cout << "Room created: " << name << std::endl;
    
}

std::string Room::getName() const {
    return name;
}