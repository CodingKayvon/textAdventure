#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>

//Inventory 
#include <map>
#include <list>
#include <string>
#include <algorithm>

//Load/Save Inventory
#include <fstream>

using namespace std;

#define MAX_LINE 80 // The maximum length command

//Inventory System - Class 
class Inventory {
  private: 
      //Map (Category Name) to a Map (item Name, and quantity)
      //Map -> Map
      map<string, map<string, int>> itemsByCategory;

      string playerName;

  public:
      //Constructor 
      Inventory() : playerName(" ") {}

      //Set the players name
      void setPlayerName(const string& name) {
        playerName = name;
      }

      //add item to inventory
      void addItem(const string& category, const string& item, int quantity = 1){
        //Add item to specific category
        itemsByCategory[category][item] += quantity;
      }

      //store inventory for next compilation
      void saveInventory(const string& filename = "savedData.txt") {
        ofstream file(filename);
        if(!file) {
          cout << "Error saving Inventory!\n";
          return;
        }

        //Store players name
        file << playerName << "\n";

        //Store each item, and its quantity for specific category
        for(const auto& category : itemsByCategory){
          for(const auto& item : category.second) {
            file << playerName << ", " << category.first << ", " << item.first << ", " << item.second << "\n";
          }
        }
        file.close();
        cout << "Saved Successfully!\n";
      }

      //retrieve inventory from last save
      void loadInventory(const string& filename = "savedData.txt") {
        ifstream file(filename);
        if(!file){
          cout << "No save file available...\n";
          return;
        }

        //Clear inventory before loading 
        itemsByCategory.clear();
        string name, category, item;
        int quantity;

        getline(file, playerName);

        //Reading saved data format and adding previous inventory -> new inventory
        while(getline(file, name, ',')&&
              getline(file >> ws, category, ',')&&
              getline(file >> ws, item, ',')&&
              (file >> quantity)) {
                file.ignore();
                addItem(category, item, quantity);
              }

        file.close();
        cout << "Previous save loaded for " << playerName << "!\n";
      }

      void displayInventory(){
        //No items within Inventory
        if(itemsByCategory.empty()){
          cout << playerName << "'s inventory is empty.\n";
          return;
        }

        //Defined Inventory Order
        const string categoryOrder[] = {"Weapons", "Armor", "Potions", "Misc"};
        
        cout << "\n===== " << playerName << "'s Inventory =====\n";

        //Iterate over each category within categoryOrder
        for(const auto& category : categoryOrder) {
          auto it = itemsByCategory.find(category);

          //Check if the category ("it") exist in the inventory
          if(it != itemsByCategory.end()) {
            cout << "\n[ " << category << " ]\n";

            //iterate over all items in current category | Name and Quantity
            for(const auto& item : it->second) {
              cout << " " << item.first << " x" << item.second << "\n";
            }
          }
        }
        cout << "\n====================\n";
      }
};

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

int main(int argc, char *argv[]) {
    char command[MAX_LINE];       // the command that was entered
    char last_command[MAX_LINE];  // the last command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    char *args_pipe[MAX_LINE / 2 + 1]; // hold arguments for the command after pipe
    int should_run = 1;           /* flag to determine when to exit program */

    Inventory player;
    string name;

    cout << "Start your Journey!\n";
    cout << "The name to be etched into the walls: ";
    getline(cin, name);
    player.setPlayerName(name);
    
    while (should_run) {
        printf("What will you do? (Start - Load - Save - Inventory - Quit)\n");
        fgets(command, MAX_LINE, stdin);

        command[strcspn(command, "\n")] = 0; // Remove the trailing newline character

         // Check for exit command
        if (strcmp(command, "quit") == 0) {
            should_run = 0; // Exit the program
            continue;
        } else if(strcmp(command, "start") == 0) {
             cout << "The Journey begins " << name << "...\n\n";

          

        }else if(strcmp(command, "save") == 0) {
             player.saveInventory();
        } else if(strcmp(command, "load") == 0) {
             player.loadInventory();
        } else if(strcmp(command, "inventory") == 0) {
             player.displayInventory();
     }
    }

    return 0;
}
