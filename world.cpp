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

void World::create()
{

    // Creation of Items
    Item *sword = new Item("Sword");
    Item *fishingRod = new Item("Fishing rod");
    Item *rock = new Item("Rock with inscription");
    Item *treasure = new Item("Treasure chest");

    // Creation of rooms
    std::vector<std::unique_ptr<Room>> rooms;
    rooms.push_back(std::make_unique<Room>("Outside old castle", "In the past, this castle was a reference point for travelers and many of the inhabitants of the region came day and night to ask the king for advice. Now it is just a ruin left after the battle between humans and ogres.\n"));
    rooms.push_back(std::make_unique<Room>("Mossy forest", "A great mystical forest with trees of all kinds, where ogres once lived peacefully. There is a fishing rod on the ground in front of you.\n", fishingRod));
    rooms.push_back(std::make_unique<Room>("The wasteland", "In other times the so called wastelands had a very busy well-built road that went throught the forest and lead into the castle, now is an abandoned and vast route only used for outcasts and by bandits who want to avoid the lonely cabin"));
    rooms.push_back(std::make_unique<Room>("Shining lake", "The beautiful lake that was the main source water of the people who lived in the castle and the ogres of the forest before the war ended devastating all the region", rock));
    rooms.push_back(std::make_unique<Room>("Lonely hut", "It's a old and dilapidated hut, it seems peaceful at first but when you approach a sense of danger comes behind the door"));
    rooms.push_back(std::make_unique<Room>("Inside old castle", "This big castle is an ancient ruin of another era.\n *The walls have inscriptions which refer to the ogre in the cabin giving warnings not to approach it.*\n", sword));

    // Creation of paths:
    //  0 -> OUTSIDE OLD CASTLE
    //  1 -> MOSSY FOREST
    //  2 -> THE WASTELANDS
    //  3 -> SHINNING LAKE
    //  4 -> LONELY HUT
    //  5 -> INSIDE OLD CASTLE
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

    vector<Item *> startingItems;
    startingItems.push_back(new Item("diary"));
    Player player(startingItems, 40);
    doorCastle = false;

    // The game starts
    currentRoom = rooms[2].get(); // Starting in the wasteland

    look();

    // User commands
    std::string userInput;
    std::vector<Exit *> currentRoomExits; // Initialize an empty vector

    while (true)
    {
        cprintf("> ");
        std::getline(std::cin, userInput);
        if (userInput == "look")
        {
            look();
        }
        else if (userInput == "move")
        {
            move(); // Call move() on the World object (no argument needed)
        }
        else if (userInput == "exit" || userInput == "quit")
        {
            break; // Exit the game
        }
        else if (userInput == "inventory")
        {
            player.showInventory();
        }
        else if (userInput == "take")
        {
            player.getItem(currentRoom);
        }
        else if (userInput == "help")
        {
            help();
        }
        else if (userInput == "drop")
        {
            cprintf("Which item do you want to drop?\n");
            player.showInventory();
            drop(player);
        }
        else if (userInput == "unlock")
        {
            unlock(player);
        }
        else if (userInput == "read")
        {
            cprintf("Which item do you want to read?\n");
            player.showInventory();
            read(player);
        }
        else if (userInput == "fish")
        {
            player.fish(currentRoom);
        }
        else if (userInput == "fight")
        {
            battleVsOgre(player);
            break;
        }
        else
        {
            cprintf("I can't detect that command. Type help to see all commands availables.\n");
        }

        cprintf("----------------------------------\n");
    }
}

void World::look()
{
    string currentLocation = currentRoom->getName();           // Use -> for pointer access
    string currentDescription = currentRoom->getDescription(); // Use -> for pointer access
    cprintf("\n\033[1mCurrent Location: %s\033[0m \n%s\n", currentLocation.c_str(), currentDescription.c_str());
}

void World::move()
{
    cprintf("Possible routes:\n");
    for (const Exit *exit : currentRoom->getExits())
    {
        cprintf("- %s\n", exit->getDestination().getName().c_str());
    }

    std::string destinationName;
    cprintf("Where do you want to move? ");
    std::getline(std::cin, destinationName);

    bool isCastleDestination = (destinationName == "Inside old castle");
    bool canEnterCastle = isCastleDestination && doorCastle;

    bool foundDestination = false; // Flag to track if the destination is valid

    for (const Exit *exit : currentRoom->getExits())
    {
        const Room &route = exit->getDestination();
        if (destinationName == route.getName() && (!isCastleDestination || canEnterCastle))
        {
            currentRoom = const_cast<Room *>(&route);
            look();
            return;
        }
        else
        {
            if (destinationName == route.getName())
            { // Check if the name matches but door is locked
                foundDestination = true;
            }
        }
    }
    if (foundDestination)
    {
        cprintf("You can't go that way, the door is locked.\n");
    }
    else
    {
        cprintf("There's no path to that destination.\n");
    }
}

void World::help()
{
    cprintf("This are the commands availables:\n");
    cprintf("- \033[1mlook\033[0m: it tells in which location you are and a brief description\n");
    cprintf("- \033[1mmove\033[0m: it lets you choose between locations that you can travel\n");
    cprintf("- \033[1mexit\033[0m or \033[1mquit\033[0m: it will end the game\n");
    cprintf("- \033[1minventory\033[0m: you can peek in your bag to see what you are carrying\n");
    cprintf("- \033[1mtake\033[0m: takes the object of the room you are located in\n");
    cprintf("- \033[1munlock\033[0m: tries to use a key to unlock a door in the room you are located in\n");
    cprintf("- \033[1mread\033[0m: it lets you read an item you possess if it has something written\n");
    cprintf("- \033[1mfish\033[0m: with a certain item, lets you try to catch a fish in the water\n");
    cprintf("- \033[1mfight\033[0m: it will teleport you to the lonely hut, where greatness awaits but only when you are fully prepared\n");
}

void World::drop(Player &player)
{

    std::string itemName;
    std::getline(std::cin, itemName);

    player.dropItem(itemName, *currentRoom);
}

void World::unlock(Player &player)
{
    if (player.hasTheKey())
    {
        if (currentRoom->getName() == "Outside old castle")
        {
            doorCastle = true;
            cprintf("The castle door is now unlocked.\n");
        }
        else
        {
            cprintf("There isn't anything to unlock in this location.\n");
        }
    }
    else
    {
        cprintf("A key is required.\n");
    }
}

void World::read(Player &player)
{

    std::string itemName;
    std::getline(std::cin, itemName);
    player.read(itemName);
}

void World::battleVsOgre(Player &player)
{

    // DIALOG PREBATTLE

    cprintf("Knowing you are probably going to die, you enter the lonely hut.\n");
    usleep(2000000);
    typeWriterEffect("Finally, all the legends you heard become true. The room is full of treasures, even more that what the legends said.\n", 50000);
    usleep(2000000);
    typeWriterEffect("You open your inventory and start loading up with all the treasures you can when suddenly...*BRUMMMMMM*\n", 50000);
    usleep(2000000);
    typeWriterEffect("An ogre twice your size enters through the door which you had previously entered.\n", 50000);
    usleep(2000000);
    cprintf("There is no escape, the only thing you can do is fight.\n");
    usleep(2000000);
    typeWriterEffect("The OGRE looks at you and starts running towards you roaring:\033[1mGRAAAAAAAAAAAAAAAAAAAAWWWRR!\033[0m\n", 50000);
    cprintf("-------------------\n");
    
    Ogre ogre;
    std::string userInput;

    cprintf("Which weapon will you use?\n");
    player.showInventory();
    int damage = weaponElection(player);

    cprintf("\033[1;31mThe fight has started!\033[0m\n");
    cprintf("-------------------\n");

    while (true)
    {

        showStats(player.getLife(), ogre.getLife());
        cprintf("\nWhat do you want to do? (attack or defense)\n");

        std::getline(std::cin, userInput);

        if (userInput == "attack")
        {
            cprintf("You attacked with %s\n", weapon.c_str());
            player.attack(ogre, damage);
            ogre.attack(player, 3);
        }
        else if (userInput == "defense")
        {
            player.defend();
            ogre.attack(player, 3);
        }
        else
        {
            cprintf("You can only \033[1mattack\033[0m or \033[1mdefense\033[0m! There's a big OGRE in front of you.\n");
        }

        if (player.isDefeated())
        {
            typeWriterEffect("The ogre with all his strength attacks you with his great hammer and blows your head back to the wasteland where you started.\n", 100000);
            typeWriterEffect("\033[1;31mGAME OVER!\033[0m\n", 500000);
            break;
        }

        if  (ogre.isDefeated()){
            typeWriterEffect("The ogre is about to strike with all the remaning strength his got, but you attack faster knocking him out.\n", 100000);
            typeWriterEffect("Finally your journey is over, you are happy it's finally over you obtain the treasure, and return to your village. Filling a little empty but ambitious for finding new goals.\n", 100000);
            typeWriterEffect("\033[1;32mCONGRATULATIONS FOR KILLING THE OGRE! YOU WIN!!!\033[0m\n", 100000);
            break;
        }
        cprintf("-------------------\n");
    }
}

// Dramatic writting efect
void World::typeWriterEffect(const char *text, unsigned int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay);
    }
}

void World::showStats(int playerLife, int ogreLife)
{

    // Player and ogre stats
    if (playerLife > ogreLife)
    {
        cprintf("You're winning!\n- You: %d HP\n- Ogre: %d HP\n", playerLife, ogreLife);
    }
    else if (playerLife < ogreLife)
    {
        cprintf("Danger!\n- You: %d HP\n- Ogre: %d HP", playerLife, ogreLife);
    }
    else
    {
        cprintf("Neck and neck! You: %d HP\n- Ogre: %d HP", playerLife, ogreLife);
    }
}

int World::weaponElection(Player &player)
{
    while (true)
    {
        std::string itemName;
        cprintf("Enter the name of the weapon you want to use: ");
        std::getline(std::cin, itemName);
        // Search for the item in the player's inventory
        bool foundItem = false;
        for (Item *item : player.getItems(player))
        {
            if (item && item->getName() == itemName)
            {
                foundItem = true;
                break; // Exit the loop once the item is found
            }
        }

        if (foundItem)
        {
            weapon = itemName; // Store the weapon name as a std::string
            if (itemName == "Sword")
            {
                return 5;
            }
            else if (itemName == "Fishing rod" || itemName == "Rock with inscription")
            {
                return 2;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            cprintf("You don't have that item in your inventory. Please choose again.\n");
        }
    }
}