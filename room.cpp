#include "room.h"
#include <iostream>

Room::Room(const char* name, const char* description) : name(name), description(description) 
{
    std::cout << "Room created: " << name << std::endl;
}
