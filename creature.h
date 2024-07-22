#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include "entity.h"

class Creature : public Entity
{
public:
    
    Creature(int life, const std::string& name = "");
    virtual ~Creature() {} //Class that will be inherited by ogre and player

    int getLife() const;
    const std::string& getName() const;

    virtual void attack(Creature &target, int damage);
    virtual void takeDamage(int damage);
    

protected:
    int life;
    std::string name;
};

#endif
