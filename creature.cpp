#include "creature.h"
#include "entity.h" 
#include <conio.h>
#include <iostream>

using namespace std;

Creature::Creature(int life, const std::string& name) : Entity(), life(life), name(name) {
    
}

void Creature::attack(Creature& target, int damage) {
        target.takeDamage(damage);
}

void Creature::takeDamage(int damage) {
    life -= damage; // Subtract damage from the creature's life
    if (life <= 0) {
       cout << "Has has been defeated!";
    }
}

int Creature::getLife() const{
    return life;
}
