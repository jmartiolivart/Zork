#ifndef EXIT_H
#define EXIT_H

#include "room.h"

class Room; // Forward declaration of Room
class Exit
{

public:
    Exit(); // Default constructor declaration
    Exit(const Room& origin, const Room& destination);
    const Room& getDestination() const;
    

private:
    const Room& source;
    const Room& destination; // Store the destination as a reference
};
#endif