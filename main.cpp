#include <iostream>
#include <conio.h>
#include "world.h"

using namespace std;

int main(){
     
    cprintf("\nWelcome to Zork, adventurer! \n");
    World world;
    world.create();
    return 0;
}