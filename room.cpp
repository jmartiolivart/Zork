#include "room.h"
#include <iostream>

Room::Room(const char* name, const char* description, Item* item) : name(name), description(description), item(item) {
    if (item != nullptr) {  // Check if the item is valid
        std::cout << "Room created: " << name << " with " << item->getName() << std::endl;
    } else {
        std::cout << "Room created: " << name << std::endl; // Don't print the item name if there's no item
    }
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

void Room::addItem(Item* newItem){
    if (item == nullptr) { // Check if there's already an item in the room
        item = newItem; 
        std::cout << newItem->getName() << " has been added to " << name << std::endl;
    } else {
        std::cout << "There's already an item in this room.\n";
    }
}
