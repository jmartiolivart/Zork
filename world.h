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
    void battleVsOgre(Player& player);
    void typeWriterEffect(const char *text, unsigned int delay);
    void showStats(int playerLife, int ogreLife);
    int weaponElection(Player& player);

private:
    Room* currentRoom; // Store the current room pointer as a member variable
    bool doorCastle;   // Track if the castle door is locked or not
    std::string weapon;

};
#endif