#include <string>
#include<list>


#ifndef ENTITY_H  // Use a unique identifier based on the filename
#define ENTITY_H

class Entity
{public:

    enum type { creature, exit, room, item};
    std::string name;
    std::string description;
    std::list<Entity*> contains;

    virtual void update(){};

};

#endif  // ENTITY_H
