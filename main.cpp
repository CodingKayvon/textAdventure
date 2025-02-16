#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include "activities.h"
#include "inventory.h"

using namespace std;

#define MAX_LINE 80 // The maximum length command
Inventory inventory;        // Global inventory object
Activities activities;      // Global activities object


int parse_command(char command[], char *args[]) {
    int i = 0;
    char *pch = strtok(command, " \n");
    while (pch != NULL) {
        args[i] = pch;
        i++;
        pch = strtok(NULL, " \n");
    }
    args[i] = NULL; // Null-terminate the args array
    return i;
}

// enum data for possible locations
enum Location {
  BEGINNING,
  DUNGEON, 
  DUNGEONR2
};

/**
 * Handles possible actions depending on user's current Location
 */
void displayCommands(Location currentLocation) {
  if (currentLocation == BEGINNING) {
    cout << "You are in the beginning\n";
    cout << "You see someone\n";
    if (!inventory.hasItem("Ancient Map")) {
      cout << "You see an old map\n";
    }

    cout << "+--------------------+\n";
    cout << "| Available actions: |\n";
    cout << "| View Inventory     |\n";
    cout << "| Speak with person  |\n";
    if (!inventory.hasItem("Ancient Map")) {
      cout << "| Pick up old map    |\n";
    }
    if (inventory.hasItem("Ancient Map")) {
      cout << "| View Ancient Map   |\n";
    }
    cout << "| go dungeon         |\n";
    cout << "+====================+\n";
  }
  else if (currentLocation == DUNGEON) {
    cout << "+-----------------+\n";
    cout << "| go to next room |\n";
    cout << "+-----------------+\n";
  }
}

int main(int argc, char *argv[]) {
  char command[MAX_LINE];       // the command that was entered
  char last_command[MAX_LINE];  // the last command that was entered
  char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
  char *args_pipe[MAX_LINE / 2 + 1]; // hold arguments for the command after pipe
  int should_run = 1;           /* flag to determine when to exit program */
  bool hasItem;
  int loopCounter = 0;
  Location currentLocation = BEGINNING;   // default location is BEGINNING


  /**
   * main game loop
   */
  while (should_run) {
      displayCommands(currentLocation);

      printf("What will you do? >");
      
      fgets(command, MAX_LINE, stdin);
      

      cout << "==================================\n";

      command[strcspn(command, "\n")] = 0; // Remove the trailing newline character

       // Check for exit command
      if (strcmp(command, "quit") == 0) {
          should_run = 0; // Exit the program
          continue;
      }

      if (currentLocation == BEGINNING && !inventory.hasItem("Ancient Map") && strcmp(command, "pick up map" ) == 0) {
          inventory.addItem("Artifacts", "Ancient Map", 1);
          cout << "\033[3myou picked up an old map!\033[0m\n";
          cout << "==================================\n";
      }

      /**
       * NPC Interaction
       */
      if (currentLocation == BEGINNING && strcmp(command, "speak with person") == 0) {
          cout << "some diologue can go here, take this for your travels\n";
          inventory.addItem("Potions", "Health Potion", 3);
          cout << "\033[3mYou have recieved some health potions.\033[0m\n";
          cout << "==================================\n";
      }

  
      if (inventory.hasItem("Ancient Map") && strcmp(command, "view ancient map") == 0) {
        cout << "+---+---+---+---+---+\n";
        cout << "|   |   |   |   |   |\n";
        cout << "+---+---+---+---+---+\n";
        cout << "|   |   |   |   |   |\n";
        cout << "+---+---+---+---+---+\n";
        cout << "|   |   |   |   |   |\n";
        cout << "+---+---+---+---+---+\n";
        cout << "|   |   |   |   |   |\n";
        cout << "+---+---+---+---+---+\n";
        cout << "|   |   |   |   |   |\n";
        cout << "+---+---+---+---+---+\n";
      }


      if (strcmp(command, "view inventory") == 0) {
        inventory.displayInventory();
     }


     /**
      * Dungeon Commands
      */

     if (strcmp(command, "go dungeon") == 0) {
      currentLocation = DUNGEON;
      cout << "You have entered the Dungeon\n";
        }


      // Locked door  
      if (currentLocation == DUNGEON && strcmp(command, "go next room") == 0) {
        cout << "this door has a lock...\n";
        bool doorUnlock = activities.keyChallenge("Golden Key");
        cin.ignore();
        if (doorUnlock) {
          currentLocation = DUNGEONR2;
          cout << "You have entered the next room on the dungeon\n";
      } else {
          cout << "The door won't budge\n";
      }
    }


    if (strcmp(command, "riddle") == 0) {
           Activities riddle;     // create activities object
           string key = "Golden Key";
           riddle.keyChallenge(key);   // run the game
           cin.ignore();
        }


    if (strcmp(command, "pick up key") == 0) {
      inventory.addItem("Artifacts", "Golden Key", 1);
      cout << "\033[3mYou have the Golden Key!\033[0m\n";
    }


    if (strcmp(command, "tablet puzzle") == 0) {
      Activities tabletGame;
      tabletGame.tabletPuzzle();
      cin.ignore();
    }

       loopCounter++;
  }

  return 0;
}
