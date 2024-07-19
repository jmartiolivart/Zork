#include <iostream>
#include <conio.h>
#include "world.h"

using namespace std;

int main(){
    
    char a;
    cprintf("Welcome to Zork, adventurer! \n");
    World world;

    while (true)
    {          
        a = getch();
        cprintf( "You write %c \n", a);

        if(a == 'S'){
            cprintf( "Welcome to the South \n");
        }else if( a == 'N'){
            cprintf( "Welcome to the North \n");
        }else if ( a == 'E'){
            world.create();
            cprintf( "Welcome to the East \n");
        } else{
            cprintf( "Welcome to the West \n");
            return 0;
        }
    }

    return 0;
}