#ifndef PLAYER_H
#define PLAYER_H
#include "creature.h"
#include "item.h"
#include "room.h"
#include <vector>

class Player: public Creature
{
public:
    Player(std::vector<Item *> items, int life = 40);

    void getItem(Room *room);
    void dropItem(const std::string& itemName, Room& room);
    void showInventory();
    bool hasTheKey();
    void read(const std::string& itemName);
    void fish(Room *room);
    virtual void attack(Creature& target, int damage) override;
    virtual void takeDamage(int damage) override;
    std::vector<Item*> getItems();
    void defend();
    bool isDefeated() const;

private:
    std::vector<Item*> items; // Store the items in the inventory of the player
    bool fished = false; 
    bool isDefending = false; 

};

#endif
