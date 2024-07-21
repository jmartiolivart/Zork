#include <iostream> 
#include <conio.h>   
#include <string>     
#include <cstdio>     
#include <memory>   
#include <vector>    
#include "world.h"   
#include "room.h"    
#include "item.h"    
#include "exit.h"
#include "player.h"    

using namespace std;

void World::create(){

    //Creation of Items
    Item* sword = new Item("Sword");
    Item* fishingRod = new Item("Fishing Rod");
    Item* key = new Item("Rusty key");
    Item* treasure = new Item("Treasure chest");


    //Creation of rooms
    std::vector<std::unique_ptr<Room>> rooms;
    rooms.push_back(std::make_unique<Room>("Old castle", "This big castle is an ancient ruin of another era.\n On the left there is something resemblant ocre ball on the right in a table there\'s a paper", sword));
    // The ocre ball is and old and mosty sword, the paper tells something about how to kill the ogre
    rooms.push_back(std::make_unique<Room>("Mossy forest", "A big mystic forest with different trees it seems that there's a sound comming between the two trees of the left, also there's a rod in the ground in front of you", fishingRod));
    //The rod to fish in the lake and extract the key of the castle
    rooms.push_back(std::make_unique<Room>("The wasteland", "In other times the so called wastelands had a very busy well-built road that went throught the forest and lead into the castle, now is an abandoned and vast route only used for outcasts and by bandits who want to avoid the lonely cabin"));
    //Starting point of the adventure!                   
    rooms.push_back(std::make_unique<Room>("Shining lake", "The beautiful lake that was the main source water of the castle before the war ended devastating all the region", key));
    //¿?
    rooms.push_back(std::make_unique<Room>("Lonely hut", "It's a old and dilapidated hut, it seems peaceful at first but when you approach a sense of danger comes behind the door", treasure));
    //To kill the ogre take sword of castle / When winning the orgre treasure box appear the end

    //Creation of paths:
    // 0 -> OLD CASTLE
    // 1 -> MOSSY FOREST
    // 2 -> THE WASTELANDS
    // 3 -> SHINNING LAKE
    // 4 -> LONELY HUT
    rooms[0]->addExit(new Exit(*rooms[0].get(), *rooms[1].get())); // Old castle to Mossy forest
    rooms[0]->addExit(new Exit(*rooms[0].get(), *rooms[4].get())); // Old castle to Lonely hut
    rooms[1]->addExit(new Exit(*rooms[1].get(), *rooms[0].get())); // Mossy forest to Old castle
    rooms[1]->addExit(new Exit(*rooms[1].get(), *rooms[2].get())); // Mossy forest to The wastelands
    rooms[2]->addExit(new Exit(*rooms[2].get(), *rooms[1].get())); // The wastelands to Mossy Forest
    rooms[2]->addExit(new Exit(*rooms[2].get(), *rooms[3].get())); // The wastelands to Shining lake
    rooms[3]->addExit(new Exit(*rooms[3].get(), *rooms[2].get())); // Shining lake to The wastelands
    rooms[3]->addExit(new Exit(*rooms[3].get(), *rooms[4].get())); // Shinning lake to Lonely hut
    rooms[4]->addExit(new Exit(*rooms[4].get(), *rooms[3].get())); // Lonely hut to Shining lake
    rooms[4]->addExit(new Exit(*rooms[4].get(), *rooms[0].get())); // Lonely hut to Old castle

    vector<Item*> startingItems;
    startingItems.push_back(new Item("Note"));
    Player player(startingItems);

    cprintf("\n \n \n \n");

    // The game starts
    currentRoom = rooms[2].get(); // Starting in the wasteland

    look();

    //User commands
    std::string userInput;
    std::vector<Exit*> currentRoomExits; // Initialize an empty vector

    while (true)
    {
        std::getline(std::cin, userInput);
        for (char &c : userInput) {
            c = std::tolower(c);
        }

        if (userInput == "look") {
            look();
        } else if(userInput == "move"){
            move(); // Call move() on the World object (no argument needed)
        }else if(userInput == "exit" || userInput == "quit"){
            break; //Exit the game
        }else if(userInput == "inventory"){
            player.showInventory(); 
        }else if(userInput == "take"){
            player.getItem(*currentRoom);
        }else if(userInput == "help"){
            help();
        }else if(userInput == "drop") {
            cprintf("Which item do you want to drop?");
            player.showInventory(); 
            drop(player);
        }else{
            cprintf("I can't detect that command. Type help to see all commands availables.\n");
        }
    }
    


}

void World::look() {
    string currentLocation = currentRoom->getName(); // Use -> for pointer access
    string currentDescription = currentRoom->getDescription(); // Use -> for pointer access
    cprintf("\033[1mCurrent Location: %s\033[0m \n%s\n", currentLocation.c_str(), currentDescription.c_str());
}


void World::move() {
    cprintf("Possible routes:\n");
    for (Exit* exit : currentRoom->getExits()) {
        const Room& route = exit->getDestination();
        cprintf("- %s\n", route.getName().c_str());
    }

    std::string destinationName;
    cprintf("Where do you want to move? ");
    std::getline(std::cin, destinationName);

    for (Exit* exit : currentRoom->getExits()) {
        if (destinationName == exit->getDestination().getName()) {
            currentRoom = const_cast<Room*>(&exit->getDestination()); // Remove constness and update the pointer
            look();
            return;
        }
    }
    cprintf("You can't go that way.\n");
}

void World::help(){
    cprintf("This are the commands availables:\n");
    cprintf("- look : it tells in which location are and a brief description\n");
    cprintf("- move : it lets you choose between two locations that you can travel\n");
    cprintf("- exit or quit : it will end the game\n");
    cprintf("- inventory : you can poke in your bag to see what you are carrying\n");
    cprintf("- take: take it takes the object of the room you are located\n");
}

void World::drop(Player& player){
    std::string itemName;
    std::getline(std::cin, itemName);

    player.dropItem(itemName, *currentRoom);
    
}