#include "creature.h"
#include "entity.h" 

Creature::Creature(int life, const std::string& name) : Entity(), life(life), name(name) {
    
}

void Creature::attack(Creature& target) {
}

void Creature::takeDamage(int damage) {
   
}

int Creature::getLife() const{
    return life;
}
