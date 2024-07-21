#include "player.h"
#include "item.h"
#include <conio.h>

Player::Player(std::vector<Item*> items):items(items){
    cprintf("Player created!");
}

//Consider one item for room max
void Player::getItem(Room room){ 
    Item* itemToTake = room.getItem();
    if (itemToTake != nullptr) {
        items.push_back(itemToTake);
        cprintf("You take the %s.\n", itemToTake->getName().c_str());
        room.removeItem();  // Remove the item from the room 
    } else {
        cprintf("There's nothing to take in this room.\n");
    }
}

void Player::dropItem(const std::string itemDrop, Room& room) { // Take Item by reference, Room by reference

    for (auto it = items.begin(); it != items.end(); ++it) {
        Item* item = *it;
        if (item && item->getName() == itemDrop.c_str()) { // Compare item names
            room.addItem(item);                              // Add to room
            items.erase(it);                                // Remove from inventory
            cprintf("You dropped the %s.\n", item->getName().c_str());
            return; // Item dropped, exit function
        }
    }

    cprintf("You don't have that item in your inventory.\n");
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