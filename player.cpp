#include "player.h"
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

void Player::dropItem(Item item, Room room){

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