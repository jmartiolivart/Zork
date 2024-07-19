#include "entity.h"

class Room: public Entity
{public:


    Room(const char* name, const char* description);
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
};
