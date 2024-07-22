#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <list>

class Entity {
public:
    Entity(); // Corrected declaration
    enum type { creature, exit, room, item};
    std::string name;
    std::string description;
    std::list<Entity*> contains;

    virtual ~Entity() {}

    virtual void update() {};
};

#endif