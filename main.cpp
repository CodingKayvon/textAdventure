#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>

#include "activities.h"
#include "inventory.h"


using namespace std;

#define MAX_LINE 80 // The maximum length command

//Inventory System - Class 


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
  DUNGEON
};

void displayCommands(Location currentLocation) {
  if (currentLocation == BEGINNING) {
    cout << "+--------------------+\n";
    cout << "| Available actions: |\n";
    cout << "| View Inventory     |\n";
    cout << "| Pick up sword      |\n";
    cout << "| go dungeon         |\n";
    cout << "+====================+\n";
  }
  else if (currentLocation == DUNGEON) {
    cout << "+-----+\n";
    cout << "| TBD |\n";
    cout << "+-----+\n";
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
  Inventory inventory;        // Inventory object
  Location currentLocation = BEGINNING;   // default location is BEGINNING


  /**
   * main game loop
   */
  while (should_run) {
      // Location check
      if (currentLocation == BEGINNING) {
        cout << "You are in the Beginning\n";
        cout << "You see an old sword on the ground\n";
      }
      else if (currentLocation == DUNGEON) {
        cout << "You are in the Dungeon\n";
      }

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

      if (currentLocation == BEGINNING && strcmp(command, "pick up sword" ) == 0) {
          inventory.addItem("Weapons", "Bronze Sword", 1);
          cout << "you picked up the sword!" << endl;
          cout << "==================================\n";
      }

       if (strcmp(command, "riddle") == 0) {
           Activities riddle;     // create activities object
           bool checkForItem;
           riddle.riddleGame(hasItem);   // run the game
           cin.ignore();
       }

       if (strcmp(command, "view inventory") == 0) {
          inventory.displayInventory();
       }

       if (strcmp(command, "go dungeon") == 0) {
          currentLocation = DUNGEON;
          cout << "You have entered the Dungeon\n";
       }

       loopCounter++;
  }

  return 0;
}
