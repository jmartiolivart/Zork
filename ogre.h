//This class represents the npc class in the UML (it is renamed because only one npc appears the ogre)
#ifndef OGRE_H
#define OGRE_H
#include "creature.h"
#include <string>

class Creature;

class Ogre: public Creature
{
public:
    Ogre(const std::string& name = "Mapinguari", int life = 50);
    void attack(Creature& target) override;
    void takeDamage(int damage);
    
private:

    std::string name;
    int life = 50;
    
};

#endif