
#ifndef ROOM_H
#define ROOM_H

#include<vector>
#include "entity.h"

class Exit; // Forward declaration of Exit
class Room: public Entity
{public:


    Room(const char* name, const char* description);

    std::string getName() const; 
    std::string getDescription() const;
    void addExit(Exit* exit);   // Add an exit to the room
    std::vector<Exit*> getExits() const; // Get all exits from the room

    //private static int numRooms = 0;

    /*void numRooms(numRooms){
        if(numRooms >= 3 && numRooms <= 8){
            numRooms++;
        }else{
            //ERROR: Need more or less Rooms
            return null;
        }
    }*/
   

private:
    std::string name;
    std::string description;
    std::vector<Exit*> exits; // Store exits within the room
};

#endif
