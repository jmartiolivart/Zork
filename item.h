#include "entity.h"

class Item: public Entity
{public:
    Item(const char *name);

private:
    std::string name;
};