#include "player.h"
#include "item.h"
#include <conio.h>
#include <unistd.h>

Player::Player(std::vector<Item *> items, int life) : Creature(life, "Player"), items(items)
{
}

void Player::getItem(Room *room)
{
    if (room == nullptr)
    { // Safety check: ensure valid room pointer
        cprintf("Error: You are not in a valid room.\n");
        return;
    }

    Item *itemToTake = room->getItem();
    if (itemToTake != nullptr)
    {
        items.push_back(itemToTake);
        cprintf("You take the %s.\n", itemToTake->getName().c_str());
        room->removeItem(); // Call removeItem() to remove the item from the room
    }
    else
    {
        cprintf("There's nothing to take in this room.\n");
    }
}

void Player::dropItem(const std::string &itemName, Room &room)
{
    bool dropped = false; // Flag to track if the item was dropped

    for (auto it = items.begin(); it != items.end(); ++it)
    {
        Item *item = *it;
        if (item && item->getName() == itemName)
        {
            if (room.addItem(item))
            {
                items.erase(it);
                cprintf("You dropped the %s.\n", item->getName().c_str());
                dropped = true; // Set the flag to indicate successful drop
                break;
            }
            else
            {
                return; // Exit the function if the room is full
            }
        }
    }

    if (!dropped)
    {
        cprintf("You don't have that item in your inventory.\n");
    }
}

void Player::showInventory()
{ // Removed parameters and changed to class method
    if (items.empty())
    {
        cprintf("Your inventory is empty.\n");
    }
    else
    {
        cprintf("Inventory:\n");
        for (Item *item : items)
        { // Using a range-based for loop
            if (item)
            { // Check for null pointers
                cprintf("- %s\n", item->getName().c_str());
            }
            else
            {
                cprintf("Error: Invalid item in inventory.\n");
            }
        }
    }
}

bool Player::hasTheKey()
{

    for (Item *item : items)
    {
        if (item->getName() == "Rusty key")
        {
            return true;
        }
    }

    return false;
}

void Player::read(const std::string &itemName)
{

    for (auto it = items.begin(); it != items.end(); ++it)
    {
        Item *item = *it;
        if (item && item->getName() == itemName)
        {
            if (item->getName() == "diary")
            {
                cprintf("\n");
                cprintf("\033[1;34mJourney Log\033[0m\n");
                cprintf("------------\n");
                std::string dateText = "Day 237: \n";
                for (char c : dateText)
                {
                    cprintf("%c", c);
                    fflush(stdout);
                    usleep(50000);
                }

                std::string entryText = "The sky is a canvas of bruised purples and deep oranges as the sun dips below the horizon. A chill wind whips through the valley, carrying the scent of pine and damp earth.\n\nFinally, after countless moons of traversing rugged terrains and treacherous paths, I have arrived in the fabled region. The whispers of hidden treasures and the menacing ogre echo in my ears, mingling with the rustling leaves and my own quickened heartbeat.\n\nAre these tales mere folklore, spun by firelight to frighten children? Or do they hold a kernel of truth?\n\nA shiver runs down my spine, not entirely from the cold.  Only time, and perhaps a bit of daring, will reveal the answers...\n";
                for (char c : entryText)
                {
                    cprintf("%c", c);
                    fflush(stdout);
                    usleep(25000);
                }
            }
            else if (item->getName() == "Rock with inscription")
            {
                cprintf("You try to read the rock, it seems a little enigmatic:\n \033[1m \" It fell *t t*e bo**om of the *ak* this is why is so shining take a fis******\"\033[0m \n...it seems that the rest of the message is illegible\n");
            }
            else
            {
                cprintf("This item can not be readed...");
            }
        }
    }
}

void Player::fish(Room *room)
{

    for (auto it = items.begin(); it != items.end(); ++it)
    {
        Item *item = *it;
        if (item && item->getName() == "Fishing rod")
        {
            if (room->getName() == "Shining lake" && !fished)
            {
                Item *key = new Item("Rusty key");
                items.push_back(key);
                cprintf("You take the %s.\n", key->getName().c_str());
                fished = false;
                return;
            }
            else
            {
                cprintf("There's no water to fish in this place!\n");
                return;
            }
        }
    }
    cprintf("You don't have anything to fish\n");
}

void Player::attack(Creature &target, int damage)
{
    target.takeDamage(damage);
}

void Player::takeDamage(int damage)
{
    if (isDefending)
    {
        damage /= 2;
        cprintf("The player's defense halved the damage!\n");
        isDefending = false;
    }
    life -= damage;
    cprintf("%s takes %d damage!\n", name.c_str(), damage);

    if (life <= 0)
    {
        cprintf("%s has been defeated!\n", name.c_str());
    }
}

std::vector<Item *> Player::getItems(const Player &player)
{
    return player.items; // Access items directly as player is a const reference
}

bool Player::isDefeated() const
{
    return life <= 0;
}

void Player::defend()
{
    isDefending = true; // Set defending state to true
    cprintf("Player raises their shield in defense!");
}