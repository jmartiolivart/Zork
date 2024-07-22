#include "room.h"
#include <iostream>

Room::Room(const char* name, const char* description, Item* item) : name(name), description(description), item(item) {

}

std::string Room::getName() const {
    return name;
}

std::string Room::getDescription() const {
    return description;
}

void Room::addExit(Exit* exit) {
    exits.insert(exits.begin(), exit);
}

std::vector<Exit*> Room::getExits() const {
    return exits;
}

Item* Room::getItem() const {
    return item;
}

void Room::removeItem() {
    item = nullptr;
}

bool Room::addItem(Item* newItem){
    if (item == nullptr) { // Check if there's already an item in the room
        item = newItem; 
        std::cout << newItem->getName() << " has been added to " << name << std::endl;
        return true;
    } else {
        std::cout << "There's already an item in this room.\n";
        return false;
    }
}
