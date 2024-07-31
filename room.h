#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "item.h" // Add this line to include the Item class definition

class Exit; // Forward declaration of Exit

class Room
{
public:
    Room(const char* name, const char* description, Item* item = nullptr);

    std::string getName() const; 
    std::string getDescription() const;
    void addExit(Exit* exit);   // Add an exit to the room
    std::vector<Exit*> getExits() const; // Get all exits from the room
    Item* getItem() const;
    void removeItem();
    bool addItem(Item* newItem);

private:
    std::string name;
    std::string description;
    std::vector<Exit*> exits; // Store exits within the room
    Item* item;
};

#endif
