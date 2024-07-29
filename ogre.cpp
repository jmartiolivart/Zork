#include "ogre.h"
#include "creature.h"
#include <conio.h>
#include <random>
#include <iostream>

using namespace std;

Ogre::Ogre(const std::string& name, int life) : Creature(life, name), isCharging(false) {}


void Ogre::attack(Creature& target, int damage) {
   if (isCharging) {
        target.takeDamage(damage * 3); // Triple damage on charged attack
        cout << "The OGRE unleashes a devastating blow!\n";
        isCharging = false; // Reset charging state after the attack
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 5); // 40% chance of charging up

        if (dis(gen) == 1) { // Charge up
            cout << "The OGRE roars and begins to charge up for a powerful attack!\n";
            isCharging = true;
        } else {
            target.takeDamage(damage); // Normal damage
        }
    }
}

void Ogre::takeDamage(int damage){
    life -= damage; // Subtract damage from the creature's life
    if (life <= 0) {
       cout << "Has has been defeated!";
    }
}

bool Ogre::isDefeated() const {
    return life <= 0;
}