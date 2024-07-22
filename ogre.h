#ifndef OGRE_H
#define OGRE_H
#include "creature.h"
#include <string>

class Ogre: public Creature
{
public:
    Ogre(const std::string& name = "Mapinguari", int life = 50);
    virtual void attack(Creature& target, int damage) override;
    virtual void takeDamage(int damage) override;
    
private:
    std::string name;
};

#endif
