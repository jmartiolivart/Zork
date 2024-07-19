#include "room.h"
#include "entity.h"

class Exit: public Entity
{public:

    enum direction {north, south, west, east};
    Room source;
    Room destination;

};