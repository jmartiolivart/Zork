#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item
{
public:
    Item(const char *name);
    std::string getName() const;

private:
    std::string name;
};
#endif