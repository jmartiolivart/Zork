#ifndef EXIT_H
#define EXIT_H

#include "room.h"
#include "entity.h"

class Exit : public Entity {

public:
    Exit(); // Default constructor declaration
    Exit(const Room& origin, const Room& destination);

private:
    enum direction {north, south, west, east};
    Room source;
    Room destination;
};
#endif