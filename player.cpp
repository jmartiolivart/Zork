#include "player.h"
#include "item.h"
#include <conio.h>

Player::Player(std::vector<Item *> items, int life) : Creature(life, "Player"), items(items) {
}

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

bool Player::hasTheKey(){

    for (Item* item : items) {
        if (item->getName() == "Rusty key") {
            return true;
        }
    }

    return false;
}


void Player::read(const std::string& itemName) { 
    
    for (auto it = items.begin(); it != items.end(); ++it) {
        Item* item = *it;
        if (item && item->getName() == itemName) {
            if(item->getName() == "diary"){
                cprintf("Journey ----- \nToday --------- \nFinally after months of travelling I have arrived to the region, let's see if the legends of the hidden treasure and the evil ogre are true or if it is all a fantasy of the common villagers.\n");
            }else if(item->getName() == "ancient manuscrit"){

            }else if(item->getName() == "Rock with inscription"){
                cprintf("You try to read the rock, it seems a little enigmatic:\n \033[1m \" It fell *t t*e bo**om of the *ak* this is why is so shining take a fis******\"\033[0m \n...it seems that the rest of the message is illegible\n");
            }else{
                cprintf("This item can not be readed...");
            }
        }
    }
}

void Player::fish(Room *room){

    for (auto it = items.begin(); it != items.end(); ++it) {
         Item* item = *it;
        if (item && item->getName() == "Fishing rod") {
            if(room->getName() == "Shining lake" && !fished){
                Item* key = new Item("Rusty key");
                items.push_back(key);
                cprintf("You take the %s.\n", key->getName().c_str());
                fished = false;
                return;
            }else{
                cprintf("There's no water to fish in this place!");
                return;
            }
        }
    }
    cprintf("You don't have anything to fish\n");
}

void Player::attack(Creature& target, int damage) {
    target.takeDamage(damage);

}

void Player::takeDamage(int damage){
     life -= damage; // Subtract damage from the creature's life
    if (life <= 0) {
       cprintf("Has has been defeated!");
    }
}

std::vector<Item*>Player::getItems(const Player& player) {
    return player.items;  // Access items directly as player is a const reference
}