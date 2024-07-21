#include "player.h"
#include "item.h"
#include <conio.h>

Player::Player(std::vector<Item*> items):items(items){
    cprintf("Player created!");
}

//Consider one item for room max
void Player::getItem(Room* room) {
    if (room == nullptr) { // Safety check: ensure valid room pointer
        cprintf("Error: You are not in a valid room.\n");
        return;
    }

    Item* itemToTake = room->getItem();
    if (itemToTake != nullptr) {
        items.push_back(itemToTake);
        cprintf("You take the %s.\n", itemToTake->getName().c_str());
        room->removeItem(); // Call removeItem() to remove the item from the room
    } else {
        cprintf("There's nothing to take in this room.\n");
    }
}

void Player::dropItem(const std::string& itemName, Room& room) { 
    bool dropped = false; // Flag to track if the item was dropped

    for (auto it = items.begin(); it != items.end(); ++it) {
        Item* item = *it;
        if (item && item->getName() == itemName) {
            if (room.addItem(item)) {
                items.erase(it);
                cprintf("You dropped the %s.\n", item->getName().c_str());
                dropped = true; // Set the flag to indicate successful drop
                break;
            } else {
                return; // Exit the function if the room is full
            }
        }
    }
    
    if (!dropped) { 
        cprintf("You don't have that item in your inventory.\n");
    }
}

void Player::showInventory() { // Removed parameters and changed to class method
    if (items.empty()) {
        cprintf("Your inventory is empty.\n");
    } else {
        cprintf("Inventory:\n");
        for (Item* item : items) {  // Using a range-based for loop
            if (item) {  // Check for null pointers
                cprintf("- %s\n", item->getName().c_str());
            } else {
                cprintf("Error: Invalid item in inventory.\n");
            }
        }
    }
}