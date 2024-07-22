#include "ogre.h"
#include "creature.h"

Ogre::Ogre(const std::string& name, int life): 
    Creature(life, name){
}

void Ogre::attack(Creature& target) {

}

void Ogre::takeDamage(int damage){
    
}