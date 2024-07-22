#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include "room.h"
#include "player.h"

class World
{public:

    void create();
    void look();
    void move();
    void help();
    void drop(Player& player);
    void unlock(Player& player);
    void read(Player& player);

private:
    Room* currentRoom; // Store the current room pointer as a member variable
    bool doorCastle;   // Track if the castle door is locked or not

};
#endif