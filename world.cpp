#include <iostream>
#include "world.h"
#include "room.h"
#include "item.h"
#include "exit.h"

using namespace std;

void World::create(){

    //Creation of rooms
    Room* castle = new Room("Old castle", 
                          "This big castle is an ancient ruin of another era.\n On the left there is something resemblant ocre ball on the right in a table there\'s a paper");
    // The ocre ball is and old and mosty sword, the paper tells something about how to kill the ogre

    Room* forest = new Room("Mossy forest",
                            "A big mystic forest with different trees it seems that there's a sound comming between the two trees of the left, also there's a rod in the ground in front of you");
    //The rod to fish in the lake and extract the key of the castle

    Room* wasteland = new Room("The wasteland",
                                "In other times it was a well-built road that went inside the forest and lead into the castle, now is an abandoned route only used for outcasts and by bandits who want to avoid the lonely cabin");
    //Starting point of the adventure!                           

    Room* lake = new Room("Shining lake",
                        "The beautiful lake that was the main source water of the castle before the war ended devastating all the region");
    //¿?

    Room* hut = new Room("Lonely hut",
                        "It's a old and dilapidated hut, it seems peaceful at first but when you approach a sense of danger comes behind the door");
    //To kill the ogre take sword of castle / When winning the orgre treasure box appear the end


    //Creation of Items
    Item* sword = new Item("Sword");
    Item* fishingRod = new Item("Fishing Rod");
    Item* key = new Item("Rusty key");
    Item* treasureBox = new Item("Treasure box");

    //Creation of paths
    //Probably change strategy of creating paths
    Exit* ex1 = new Exit(*castle, *forest);
    Exit* ex2 = new Exit(*castle, *hut);
    Exit* ex3 = new Exit(*forest, *castle);
    Exit* ex4 = new Exit(*forest, *wasteland);
    Exit* ex5 = new Exit(*wasteland, *forest);
    Exit* ex6 = new Exit(*wasteland, *lake);
    Exit* ex7 = new Exit(*lake, *wasteland);
    Exit* ex8 = new Exit(*lake, *hut);
    Exit* ex9 = new Exit(*hut, *castle);
    Exit* ex10 = new Exit(*hut, *lake);


}