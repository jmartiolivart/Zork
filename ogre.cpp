#include "ogre.h"
#include "creature.h"
#include<conio.h>

Ogre::Ogre(const std::string& name, int life): 
    Creature(life, name){
}

void Ogre::attack(Creature& target, int damage) {
    target.takeDamage(damage);
}

void Ogre::takeDamage(int damage){
    life -= damage; // Subtract damage from the creature's life
    if (life <= 0) {
       cprintf("Has has been defeated!");
    }
}