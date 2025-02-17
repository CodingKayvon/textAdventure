#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

#include "activities.h"
#include "inventory.h"
#include "entity.h"
#include "movement.h"

using namespace std;

#define MAX_LINE 80    // The maximum length command
Inventory inventory;   // Global inventory object
Activities activities; // Global activities object

int parse_command(char command[], char *args[])
{
  int i = 0;
  char *pch = strtok(command, " \n");
  while (pch != NULL)
  {
    args[i] = pch;
    i++;
    pch = strtok(NULL, " \n");
  }
  args[i] = NULL; // Null-terminate the args array
  return i;
}

int main(int argc, char *argv[])
{
  char command[MAX_LINE];            // the command that was entered
  char last_command[MAX_LINE];       // the last command that was entered
  char *args[MAX_LINE / 2 + 1];      // hold parsed out command line arguments
  char *args_pipe[MAX_LINE / 2 + 1]; // hold arguments for the command after pipe
  int should_run = 1;                /* flag to determine when to exit program */
  bool hasItem;
  int loopCounter = 0;
  Location currentLocation = WINDGALE; // default location is BEGINNING
  // Combat Objects
  Player entityPlayer("Player");
  Enemy enemy("Enemy");
  Enemy boss("Boss");
  Inventory inventory;
  // Inventory Objects
  Inventory player; // used for movement as well
  string name;
  string userIn;
  // NPC data members
  bool speakM = false; // moss
  bool speakA = false; // arrielle
  bool speakE = false; // enfys
  bool speakD = false; // dead adventurer
  bool speakR = false; // rundigar
  bool speakL = false; // lochlin

  // Add would you like to load a save...
  cout << "Start your Journey!\n";
  cout << "Would you like to load a save? (yes or no)\n";
  cin >> userIn;
  if (userIn == "yes")
  {
    player.loadInventory();
    cout << "Welcome Back!\n";
    cin.ignore();
  }
  else
  {
    cin.ignore();
    cout << "The name to be etched into the walls: ";
    getline(cin, name);
    player.setPlayerName(name);
  }

  cout << "At anytime, type \"help\" to view important commands.\n";
  bool passed = false;
  bool bossPassed = false;
  /**
   * main game loop
   */
  while (should_run)
  {
    cout << endl;
    displayCommands(currentLocation, player); // displays commands for current lcoation and has access to player inventory

    printf("What will you do? >");

    fgets(command, MAX_LINE, stdin);

    cout << "==================================\n";

    command[strcspn(command, "\n")] = 0; // Remove the trailing newline character
    /**
     * ====================================== Global Commands ======================================
     */

    // Check for exit command
    if (strcmp(command, "quit") == 0)
    {
      should_run = 0; // Exit the program
      continue;
    }

    if (strcmp(command, "help") == 0)
    {
      cout << "+---------------------+\n";
      cout << "| Global Actions:     |\n";
      cout << "| View Inventory      |\n";
      cout << "| Save Progress       |\n";
      cout << "+---------------------+\n";
    }

    /**
     * Save and Loading
     */
    if (strcmp(command, "save") == 0)
    {
      player.saveInventory();
      cout << "Saved Successfully!\n";
    }

    if (strcmp(command, "view inventory") == 0)
    {
      inventory.displayInventory();
    }
    // else if (strcmp(command, "load") == 0)
    // {
    //   player.loadInventory();
    // }

    /**
     * Combat
     */
    if (strcmp(command, "get health") == 0)
    {
      player.addItem("Potions", "Health Potion", 3);
    }
    if (strcmp(command, "fight") == 0)
    {
      player.saveInventory();
      entityPlayer.activeCombat(enemy);
    }

    /**
     * ====================================== Windgale ======================================
     */
    // if (currentLocation == WINDGALE && !inventory.hasItem("Ancient Map") && strcmp(command, "pick up map") == 0)
    // {
    //   inventory.addItem("Artifacts", "Ancient Map", 1);
    //   cout << "\033[3myou picked up an old map!\033[0m\n";
    //   cout << "==================================\n";
    // }
    //--------------------------------------------------------------------------------  SHOP
    if (currentLocation == WINDGALE && strcmp(command, "go to shop") == 0)
    {
      currentLocation = SHOP;
    }

    if (currentLocation == SHOP && strcmp(command, "speak with arrielle") == 0)
    {
      if (!speakA)
      {
        cout << "\"Howdy, sugar! Why, you look like you're 'bout ready to brave the dungeon set in the mountain east here. Here, take some of these to help you on your way and don't worry 'bout the price, it's on the house.\"\n";
        cout << "\033[3mShe gives you a few health potions and sends you off with a wink and a wave.\033[0m\n";
        player.addItem("Potions", "Health Potion", 5);
        cout << "[Health Potion x5 added to Invenory!]\n";
        speakA = true;
      }
      else
      {
        cout << "You have already spoken to Arrielle\n";
        cout << "===================================\n";
      }
    }
    if (currentLocation == SHOP && strcmp(command, "leave shop") == 0)
    {
      currentLocation = WINDGALE;
    }
    //-------------------------------------------------------------------------------- TAVERN

    if (currentLocation == WINDGALE && strcmp(command, "go to tavern") == 0)
    {
      currentLocation = TAVERN;
    }
    if (currentLocation == TAVERN && strcmp(command, "speak with moss") == 0)
    {
      if (!speakM)
      {
        cout << "\"Ahh, come here for riches and glory, have you? I used to be just like you until I took an arrow to the knee. Now I'm stuck here in this tiny village, but it ain't so bad once you get to know the people. Everyone here's pretty welcoming and they all help each other out\"\n";
        cout << "\033[3mThey bring their attention back to their bow and continue plucking at it.\033[0m\n";
        speakM = true;
      }
      else
      {
        cout << "You have already spoken to Moss\n";
        cout << "===================================\n";
      }
    }
    if (currentLocation == TAVERN && strcmp(command, "speak with rundigar") == 0)
    {
      if (!speakR)
      {
        cout << "\'Just by the look on your face I can tell you're dead set on exploring the Skull Dungeon, but let me tell you nearly everyone in this town has lost someone who's ventured down there. That's why we've had to seal it off. Poor Enfys goes there everyday trying to get in cause his own parents died down there. You seem like the type who can handle that kind of danger though so here, this'll get you in there.\'\n";
        cout << "\033[3mHe pulls something out from below the bar counter and slides a large key over to you with a note attached explaining how to reveal the keyhole in the stone door of the dungeon.\033[0m\n";
        inventory.addItem("Artifacts", "Skull Key", 1);
        cout << "[Skull Key x1 added to Inventory!]\n";
        speakR = true;
      }
      else
      {
        cout << "You have already spoken to Rundigar\n";
        cout << "===================================\n";
      }
    }
    if (currentLocation == TAVERN && strcmp(command, "leave tavern") == 0)
    {
      currentLocation = WINDGALE;
    }

    //-------------------------------------------------------------------------------- FORGE

    if (currentLocation == WINDGALE && strcmp(command, "go to forge") == 0)
    {
      currentLocation = FORGE;
    }
    if (currentLocation == FORGE && strcmp(command, "speak with lochlin") == 0)
    {
      if (!speakL)
      {
        cout << "\"Oi! Ya near made me drop ma sword! Oh, ya new here ain'tcha? Gonna challenge the dungeon? 'Ere have this, it's bloody dangerous down there without a weapon. I've got plenty to go 'round so don't bother with yer wallet.\"";
        cout << "\033[3mHe finishes the sword he was working on, slides it into a sheath, and forcefully hands the weapon to you.\033[0m\n";
        inventory.addItem("Weapons", "Trusty Sword", 1);
        cout << "[Trusty Sword x1 added to Inventory!]\n";
        speakL = true;
      }
      else
      {
        cout << "You have already spoken to Lochlin\n";
        cout << "===================================\n";
      }
    }
    if (currentLocation == FORGE && strcmp(command, "leave forge") == 0)
    {
      currentLocation = WINDGALE;
    }
    //-------------------------------------------------------------------------- To go to dungeon :)
    if (currentLocation == WINDGALE && strcmp(command, "approach dungeon") == 0)
    {
      currentLocation = DUNGEON;
    }

    /**
     * ====================================== Dungeon ======================================
     */
    if (currentLocation == DUNGEON && strcmp(command, "speak with enfys") == 0)
    {
      if (!speakE)
      {
        cout << "\"Oh look at you! All geared up to explore the dungeon, huh pipsqueak? Good luck getting in, I've been studying this door's surface for years and haven't been able to get in, which means you have no chance of entering. The thing must be sealed for good.\"\n";
        cout << "\033[3mHe kicks up dirt at you and wanders back into town.\033[0m\n";
        speakE = true;
      }
      else
      {
        cout << "Enfys is no longer here...\n";
        cout << "===================================\n";
      }
    }

    if (currentLocation == DUNGEON && strcmp(command, "enter dungeon") == 0)
    {
      if (activities.keyChallenge("Skull Key"))
      {
        currentLocation = ROOM1;
      }
    }
    /**
     * ====================================== ROOM1 ======================================
     */
    if (currentLocation == ROOM1 && strcmp(command, "go north") == 0)
    {
      currentLocation = ROOM2;
    }
    /**
     * ====================================== ROOM2 ======================================
     */
    if (currentLocation == ROOM2 && strcmp(command, "go east") == 0)
    {
      currentLocation = ROOM3;
    }
    if (currentLocation == ROOM2 && strcmp(command, "search dead adventurer") == 0)
    {
      cout << "\033[3mAs you crouch down toward the humanoid skeleton, you notice a tattered sheet with words scrawled onto it in charcoal. The page reads, 'Where the sun sets the whales breach, and while birds migrate for the winter, the snakes slither toward the moon rise in search of prey.'\033[0m\n";
    }
    /**
     * ====================================== ROOM3 ======================================
     */
    
    if (currentLocation == ROOM3 && strcmp(command, "go south") == 0)
    {
      if (passed)
      {
        currentLocation = ROOM4;
      }
      else
      {
        cout << "You must face the enemy to progress\n";
      }
    }
    if (currentLocation == ROOM3 && strcmp(command, "approach enemy") == 0)
    {
      entityPlayer.activeCombat(enemy);
      if (entityPlayer.isAlive())
      {
        passed = true;
      }
      else
      {
        passed = false;
        currentLocation = WINDGALE;
      }
    }
    if (currentLocation == ROOM3 && strcmp(command, "pick up item") == 0)
    {
      inventory.addItem("Potions", "Health Potion", 3);
    }
    /**
     * ====================================== ROOM4 ======================================
     */
    if (currentLocation == ROOM4 && strcmp(command, "tablet challenge") == 0)
    {
      if (activities.tabletPuzzle())
      {
        cout << "\033[3mThe stone shifts under your feet to reveal a lower floor.\033[0m\n";
        cout << "=============================================================\n";
        cin.ignore();
        currentLocation = BOSS_ROOM;
      }
      else
      {
        cout << "Maybe you should try again...\n";
      }
    }
    /**
     * ====================================== BOSS_ROOM ======================================
     */
    
    if (currentLocation == BOSS_ROOM && strcmp(command, "approach boss") == 0)
    {
      entityPlayer.activeCombat(boss);
      if (entityPlayer.isAlive())
      {
        bossPassed = true;
        cout << "-----------------------------LEGEND FELLED-----------------------------\n";
      }
      else
      {
        bossPassed = false;
      }
    }
    if (currentLocation == BOSS_ROOM && strcmp(command, "go north") == 0)
    {
      if (bossPassed)
      {
        currentLocation = TREAS_ROOM;
      }
      else
      {
        cout << "The dragon stands in your way...\n";
      }

      /**
       * ====================================== TREAS_ROOM ======================================
       */
      if (currentLocation == TREAS_ROOM && strcmp(command, "finish game") == 0) {
        currentLocation = END_ROOM;
      }

      /**
       * ====================================== END_ROOM ======================================
       */

      // ya done did it!

      loopCounter++;
      
    }

  }
  return 0;
}

/**
 * if (strcmp(command, "riddle") == 0)
    {
      Activities riddle; // create activities object
      string key = "Golden Key";
      riddle.keyChallenge(key); // run the game
      cin.ignore();
    }

    if (strcmp(command, "pick up key") == 0)
    {
      inventory.addItem("Artifacts", "Golden Key", 1);
      cout << "\033[3mYou have the Golden Key!\033[0m\n";
    }

    if (strcmp(command, "tablet puzzle") == 0)
    {
      Activities tabletGame;
      tabletGame.tabletPuzzle();
      cin.ignore();
    }

        // Locked door
    if (currentLocation == DUNGEON && strcmp(command, "go next room") == 0)
    {
      cout << "this door has a lock...\n";
      bool doorUnlock = activities.keyChallenge("Golden Key");
      cin.ignore();
      if (doorUnlock)
      {
        currentLocation = DUNGEONR2;
        cout << "You have entered the next room on the dungeon\n";
      }
      else
      {
        cout << "The door won't budge\n";
      }
    }


   /**
     * NPC Interaction
     */
/*
if (currentLocation == BEGINNING && strcmp(command, "speak with person") == 0)
{
  cout << "some diologue can go here, take this for your travels\n";
  inventory.addItem("Potions", "Health Potion", 3);
  cout << "\033[3mYou have recieved some health potions.\033[0m\n";
  cout << "==================================\n";
}


*/