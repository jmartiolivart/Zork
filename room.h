#include <entity.h>

class Room: public Entity
{public:

    private static int numRooms = 0;

    void numRooms(numRooms){
        if(numRooms >= 3 && numRooms <= 8){
            numRooms++;
        }else{
            //ERROR: Need more or less Rooms
            return null;
        }
    }
};