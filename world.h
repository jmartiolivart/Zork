#include <iostream>
#include "room.h"

class World
{public:

    void create();
    void look();
    void move();
    void help();

private:

    Room* currentRoom; // Store the current room pointer as a member variable
};