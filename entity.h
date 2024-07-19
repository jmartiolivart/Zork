using namespace std;

#include <string>
#include<list>


class Entity
{public:

    enum type { creature, exit, room, item};
    string name;
    string description;
    list<Entity*> contains;

    virtual void update(){};

};