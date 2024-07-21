#ifndef ITEM_H
#define ITEM_H
#include "entity.h"

class Item: public Entity
{public:
    Item(const char *name);
    std::string getName() const;

private:
    std::string name;
};
#endif