#include <iostream>
#include "room.h"

class World
{public:

    void create();
    void look(const Room* room);
     void move(const Room* currentRoom);
};