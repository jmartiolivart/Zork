#include "exit.h"
#include "room.h"
#include <iostream>

Exit::Exit(const Room& origin, const Room& destination) : source(origin), destination(destination) {
  
}

const Room& Exit::getDestination() const{
    return destination;
}