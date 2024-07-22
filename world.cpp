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
#include "ogre.h"
#include <unistd.h>

using namespace std;

void World::create(){

    //Creation of Items
    Item* sword = new Item("Sword");
    Item* fishingRod = new Item("Fishing rod");
    Item* rock = new Item("Rock with inscription");
    Item* treasure = new Item("Treasure chest");


    //Creation of rooms
    std::vector<std::unique_ptr<Room>> rooms;
    rooms.push_back(std::make_unique<Room>("Outside old castle", "This big castle is an ancient ruin of another era.\n On the left there is something resemblant ocre ball on the right in a table there\'s a paper"));
    // The ocre ball is and old and mosty sword, the paper tells something about how to kill the ogre
    rooms.push_back(std::make_unique<Room>("Mossy forest", "A big mystic forest with different trees it seems that there's a sound comming between the two trees of the left, also there's a rod in the ground in front of you", fishingRod));
    //The rod to fish in the lake and extract the key of the castle
    rooms.push_back(std::make_unique<Room>("The wasteland", "In other times the so called wastelands had a very busy well-built road that went throught the forest and lead into the castle, now is an abandoned and vast route only used for outcasts and by bandits who want to avoid the lonely cabin"));
    //Starting point of the adventure!                   
    rooms.push_back(std::make_unique<Room>("Shining lake", "The beautiful lake that was the main source water of the castle before the war ended devastating all the region", rock));
    //¿?
    rooms.push_back(std::make_unique<Room>("Lonely hut", "It's a old and dilapidated hut, it seems peaceful at first but when you approach a sense of danger comes behind the door", treasure));
    //To kill the ogre take sword of castle / When winning the orgre treasure box appear the end
    rooms.push_back(std::make_unique<Room>("Inside old castle", "This big castle is an ancient ruin of another era.\n On the left there is something resemblant ocre ball on the right in a table there\'s a paper", sword));

    //Creation of paths:
    // 0 -> OUTSIDE OLD CASTLE
    // 1 -> MOSSY FOREST
    // 2 -> THE WASTELANDS
    // 3 -> SHINNING LAKE
    // 4 -> LONELY HUT
    // 5 -> INSIDE OLD CASTLE
    rooms[0]->addExit(new Exit(*rooms[0].get(), *rooms[1].get())); // Old castle to Mossy forest
    rooms[0]->addExit(new Exit(*rooms[0].get(), *rooms[4].get())); // Old castle to Lonely hut
    rooms[0]->addExit(new Exit(*rooms[0].get(), *rooms[5].get())); // Old castle to inside old castle
    rooms[1]->addExit(new Exit(*rooms[1].get(), *rooms[0].get())); // Mossy forest to Old castle
    rooms[1]->addExit(new Exit(*rooms[1].get(), *rooms[2].get())); // Mossy forest to The wastelands
    rooms[2]->addExit(new Exit(*rooms[2].get(), *rooms[1].get())); // The wastelands to Mossy Forest
    rooms[2]->addExit(new Exit(*rooms[2].get(), *rooms[3].get())); // The wastelands to Shining lake
    rooms[3]->addExit(new Exit(*rooms[3].get(), *rooms[2].get())); // Shining lake to The wastelands
    rooms[3]->addExit(new Exit(*rooms[3].get(), *rooms[4].get())); // Shinning lake to Lonely hut
    rooms[4]->addExit(new Exit(*rooms[4].get(), *rooms[3].get())); // Lonely hut to Shining lake
    rooms[4]->addExit(new Exit(*rooms[4].get(), *rooms[0].get())); // Lonely hut to Old castle
    rooms[5]->addExit(new Exit(*rooms[5].get(), *rooms[0].get())); // Inside to outside old castle

    vector<Item*> startingItems;
    startingItems.push_back(new Item("diary"));
    Player player(startingItems, 40);
    doorCastle = false;

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
        if (userInput == "look") {
            look();
        } else if(userInput == "move"){
            move(); // Call move() on the World object (no argument needed)
        }else if(userInput == "exit" || userInput == "quit"){
            break; //Exit the game
        }else if(userInput == "inventory"){
            player.showInventory(); 
        }else if(userInput == "take"){
            player.getItem(currentRoom);
        }else if(userInput == "help"){
            help();
        }else if(userInput == "drop") {
            cprintf("Which item do you want to drop?\n");
            player.showInventory(); 
            drop(player);
        }else if(userInput == "unlock"){
            unlock(player);
        }else if(userInput == "read"){
            cprintf("Which item do you want to read?\n");
            player.showInventory(); 
            read(player);
        }else if(userInput == "fish"){
            player.fish(currentRoom);
        }else if(userInput == "fight"){
            battleVsOgre(player);
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
    for (const Exit* exit : currentRoom->getExits()) {
        cprintf("- %s\n", exit->getDestination().getName().c_str());
    }

    std::string destinationName;
    cprintf("Where do you want to move? ");
    std::getline(std::cin, destinationName);

    bool isCastleDestination = (destinationName == "Inside old castle");
    bool canEnterCastle = isCastleDestination && doorCastle;

    bool foundDestination = false; // Flag to track if the destination is valid

    for (const Exit* exit : currentRoom->getExits()) {
        const Room& route = exit->getDestination();
        if (destinationName == route.getName() && (!isCastleDestination || canEnterCastle)) {
            currentRoom = const_cast<Room*>(&route);
            look();
            return;
        } else {
            if (destinationName == route.getName()) { // Check if the name matches but door is locked
                foundDestination = true;
            }
        }
    }
    if (foundDestination) {
        cprintf("You can't go that way, the door is locked.\n");
    } else {
        cprintf("There's no path to that destination.\n");
    }
}


void World::help(){
    cprintf("This are the commands availables:\n");
    cprintf("- look: it tells in which location are and a brief description\n");
    cprintf("- move: it lets you choose between two locations that you can travel\n");
    cprintf("- exit or quit: it will end the game\n");
    cprintf("- inventory: you can poke in your bag to see what you are carrying\n");
    cprintf("- take: take it takes the object of the room you are located\n");
    cprintf("- unlock: tries to use a key to unlock a door in the room you are located\n");
    cprintf("- read: it lets you read an item you posses if it has something written");
}

void World::drop(Player& player){
    
    std::string itemName;
    std::getline(std::cin, itemName);

    player.dropItem(itemName, *currentRoom);
    
}

void World::unlock(Player& player) {
    if (player.hasTheKey()) {
        if (currentRoom->getName() == "Outside old castle") {
            doorCastle = true;
            cprintf("The castle door is now unlocked.\n");
        } else {
            cprintf("There isn't anything to unlock in this location.\n");
        }
    } else {
        cprintf("A key is required.\n");
    }
}

void World::read(Player& player) {

    std::string itemName;
    std::getline(std::cin, itemName);
    player.read(itemName);

}


void World::battleVsOgre(Player& player){

    std::string weapon;
    
    //DIALOG PREBATTLE
    cprintf("Knowing you are probably going to die, you enter the lonely hut.\n");
    usleep(2000000);
    typeWriterEffect("Finally, all the legends you heard become true. The room is full of treasures, even more than what the legends said.\n", 50000); 
    usleep(2000000);
    typeWriterEffect("You open your inventory and start loading up with all the treasures you can when suddenly...*BRUMMMMMM*\n", 50000);
    usleep(2000000);
    typeWriterEffect("An ogre twice your size enters through the door through which you had previously entered.\n", 50000);
    usleep(2000000);
    cprintf("There is no escape, the only thing you can do is fight.\n");
    usleep(2000000);
    typeWriterEffect("The OGRE looks at you and starts running towards you roaring:\033[1mGRAAAAAAAAAAAAAAAAAAAAWWWRR!\033[0m\n", 50000);

    Ogre ogre;
    std::string userInput; 
    
    cprintf("Which weapon will you use?\n");
    player.showInventory();
    weaponElection(player);

    cprintf("The fight has started!\n");

    while (true){

        showStats(player.getLife(), ogre.getLife());
        cprintf("What do you want to do?");

        std::getline(std::cin, userInput);

        if(userInput == "attack"){
            cprintf("You attacked with %s\n", weapon.c_str());
            player.attack(ogre);

        }else if(userInput == "defense"){
            //player.defense();
        }else{
            cprintf("You can only \033[1mattack\033[0m or \033[1mdefense\033[0m! There's a big OGRE in front of you.");
        }

        ogre.attack(player);
    }
    
    


}

//Dramatic writting efect
void World::typeWriterEffect(const char *text, unsigned int delay) {
  for (int i = 0; text[i] != '\0'; i++) {
    putchar(text[i]);
    fflush(stdout);  
    usleep(delay);   
  }
}

void World::showStats(int playerLife, int ogreLife){

    //Player and ogre stats
    cprintf("Player has: %d PV\nOgre has: %d PV\n", playerLife, ogreLife);
}

int World::weaponElection(Player& player) {
    while (true) {
        std::string itemName;
        cprintf("Enter the name of the weapon you want to use: ");
        std::getline(std::cin, itemName);
        // Search for the item in the player's inventory
        bool foundItem = false;
        for (Item* item : player.getItems(player)) {
            if (item && item->getName() == itemName) {
                foundItem = true;
                break; // Exit the loop once the item is found
            }
        }

        if (foundItem) {
            weapon = itemName;
            if (itemName == "sword") {
                return 5;
            } else if (itemName == "fishing rod") {
                return 2;
            } else {
                return 1;
            }
        } else {
            cprintf("You don't have that item in your inventory. Please choose again.\n");
        }
    }
}

