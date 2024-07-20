#include "room.h"
#include <iostream>
#include <string>
#include "exit.h"

Room::Room(const char* name, const char* description) : name(name), description(description) 
{
    std::cout << "Room created: " << name << std::endl;
    
}

std::string Room::getName() const {
    return name;
}

std::string Room::getDescription() const {
    return description;
}

//Add exits to rooms
void Room::addExit(Exit* exit){
    exits.insert(exits.begin(), exit);
}

//Get all rooms exits
std::vector<Exit*> Room::getExits() const{
    return exits;
}