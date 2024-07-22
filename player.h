#ifndef CREATURE_H
#define CREATURE_H
#include "creature.h"
#include "item.h"
#include "room.h"
#include<vector>

class Player: public Creature
{
public:

    Player(std::vector<Item *> items);

    void getItem(Room *room);
    void dropItem(const std::string& itemName, Room& room);
    void showInventory();
    bool hasTheKey();
    void read(const std::string& itemName);
    void fish(Room *room);

private:

    std::vector<Item*> items; // Store the items in the inventory of the player
    bool fished = false;
};

#endif