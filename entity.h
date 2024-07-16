using namespace std;

#include <string>
#include<list>
#include<creature.h>
#include<Exit.h>
#include<Room.h>
#include<Item.h>


class Entity
{public:

    enum type { creature, exit, room, item};
    string name;
    string description;
    list<Entity*> contains;

    virtual void update(){};

};