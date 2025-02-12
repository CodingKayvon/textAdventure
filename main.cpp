#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>

//Inventory 
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_LINE 80 // The maximum length command

//Inventory System - Struct 
class Inventory {
  private: 
      //Map (Category Name) to a Map (item Name, and quantity)
      //Map -> Map
      map<string, map<string, int>> itemsByCategory;

      //Empty list
      list<string> categoryOrder;

  public:
      void addItem(const string& category, const string& item, int quantity = 1){
        //if the category is not found in the list | Prevent Duplicate categories
        if(find(categoryOrder.begin(), categoryOrder.end(), category) == categoryOrder.end()){
          //Add the category to the list
          categoryOrder.push_back(category);
        }
        //Add item to specific category
        itemsByCategory[category][item] += quantity;
      }

      void displayInventory(){
        //No items within Inventory
        if(itemsByCategory.empty()){
          cout << "Your inventory is empty.\n";
          return;
        }

        //Predefined Category order
        const string categoryOrder[] = {"Weapons", "Potions", "Artifacts"};

        cout << "\n===== Inventory =====\n";
        
        //Display by category
        //For each category name within the category order
        for(const auto& categoryName : categoryOrder) {
          auto it = itemsByCategory.find(categoryName);

          //If a Category Name within categoryOrder is found
          if(it != itemsByCategory.end()){
            cout << "\n[ " << categoryName << " ]\n";

            //For each item within the category, print | Pointint to value
            for(const auto& item : it->second){
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

    while (should_run) {
        printf("What will you do? ");
        fgets(command, MAX_LINE, stdin);

        command[strcspn(command, "\n")] = 0; // Remove the trailing newline character

         // Check for exit command
        if (strcmp(command, "quit") == 0) {
            should_run = 0; // Exit the program
            continue;
        }
    }

    return 0;
}
