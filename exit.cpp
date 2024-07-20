#include "exit.h"
#include "room.h"
#include <iostream>

Exit::Exit(const Room& origin, const Room& destination) : source(origin), destination(destination) {
    std::cout << "Exit connects: " << std::endl;
    std::cout << "- Origin: " << origin.getName() << std::endl;
    std::cout << "- Destination: " << destination.getName() << std::endl;
}