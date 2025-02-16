#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <sys/wait.h>
#include <cstdlib> 
#include <ctime>   

// Inventory System - Class
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_LINE 80 // The maximum length command

// Inventory System - Class
class Inventory {
private:
    // Map (Category Name) to a Map (Item Name, and Quantity)
    // Map -> Map
    map<string, map<string, int>> itemsByCategory;
    // Empty list to maintain category order
    list<string> categoryOrder;
public:
    // Function to add an item to a specific category in the inventory
    void addItem(const string& category, const string& item, int quantity = 1) {
        // If the category is not found in the list (prevent duplicate categories)
        if (find(categoryOrder.begin(), categoryOrder.end(), category) == categoryOrder.end()) {
            // Add the category to the list
            categoryOrder.push_back(category);
        }
        // Add the item to the specific category
        itemsByCategory[category][item] += quantity;
    }

    // Function to display the items in the inventory, categorized
    void displayInventory() {
        // If there are no items in the inventory
        if (itemsByCategory.empty()) {
            cout << "Your inventory is empty.\n";
            return;
        }

        // Predefined category order (Weapons, Potions, Artifacts)
        const string categoryOrder[] = {"Weapons", "Potions", "Artifacts"};

        cout << "\n===== Inventory =====\n";

        // Display items by category
        // For each category name within the category order
        for (const auto& categoryName : categoryOrder) {
            auto it = itemsByCategory.find(categoryName);
            // If a Category Name within categoryOrder is found
            if (it != itemsByCategory.end()) {
                cout << "\n[ " << categoryName << " ]\n";
                // For each item within the category, print item and its quantity
                for (const auto& item : it->second) {
                    cout << " " << item.first << " x" << item.second << "\n";
                }
            }
        }
        cout << "\n====================\n";
    }
};

// Combat System - Classes
class Entity {
public:
    Entity(const std::string& name, int health) : name(name), health(health), maxHealth(health) {}
    // Attack function: Deals damage to the target and displays the message
    virtual void attack(Entity& target) {
        int damage = generateDamage();
        std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!" << std::endl;  // Attack dealt
        target.takeDamage(damage);  
    }
    // Takes damage from the attack
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
        std::cout << name << " takes " << damage << " damage. Current health: " << health << std::endl; // Damage taken
    }
    int getHealth() const {
        return health;
    }
    int getMaxHealth() const {
        return maxHealth;
    }
    std::string getName() const {
        return name;
    }
    bool isAlive() const {
        return health > 0;
    }
    // Display the health bar for the entity (a simple bar with "#" and "-")
    void displayHealthBar() const {
        int barWidth = 20;
        int filledWidth = (health * barWidth) / maxHealth;
        cout << name << " Health: [";
        for (int i = 0; i < barWidth; ++i) {
            if (i < filledWidth) {
                cout << "#";  // Health portion
            } else {
                cout << "-";  // Empty portion
            }
        }
        cout << "] " << health << "/" << maxHealth << endl;
    }
protected:
    // Function to generate random damage
    int generateDamage() const {
        return rand() % 11 + 10;
    }
private:
    std::string name;
    int health;
    int maxHealth;
};
class Player : public Entity {
public:
    Player(const std::string& name) : Entity(name, 100) {}
};
class Enemy : public Entity {
public:
    Enemy(const std::string& name) : Entity(name, 50) {}
};
// Command Parsing and Main Loop
int parse_command(char command[], char* args[]) {
    int i = 0;
    char* pch = strtok(command, " \n");
    while (pch != NULL) {
        args[i] = pch;
        i++;
        pch = strtok(NULL, " \n");
    }
    args[i] = NULL;  // Null-terminate the args array
    return i;
}

// Function to display available commands under the "What will you do?" prompt
void displayCommands() {
    cout << "\nAvailable actions: \n";
    cout << " - attack enemy\n";
    cout << " - show inventory\n";
    cout << " - quit\n";
}
int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator
    char command[MAX_LINE];
    char* args[MAX_LINE / 2 + 1];
    int should_run = 1;
    Player player("Player");
    Enemy enemy("Enemy");
    Inventory inventory;
    // Initial items in inventory
    inventory.addItem("Weapons", "Sword", 1);
    inventory.addItem("Potions", "Healing Potion", 2);

    // Main loop
    while (should_run) {
        // Display health bars
        player.displayHealthBar();
        enemy.displayHealthBar();
        // Prompt for user input
        printf("\nWhat will you do? ");
        displayCommands();  // Display the commands right after the prompt
        fgets(command, MAX_LINE, stdin);
        command[strcspn(command, "\n")] = 0; // Remove trailing newline

        // Parse command
        parse_command(command, args);

        // Invalid or empty command
        if (args[0] == NULL) {
            cout << "Invalid command. Try again!\n";
            continue;
        }
        // Quit command
        if (strcmp(args[0], "quit") == 0) {
            should_run = 0;
            continue;
        }
        // Show inventory
        if (strcmp(args[0], "show") == 0 && args[1] != NULL && strcmp(args[1], "inventory") == 0) {
            inventory.displayInventory();
        }
        // Attack command
        else if (strcmp(args[0], "attack") == 0) {
            if (args[1] != NULL && strcmp(args[1], "enemy") == 0) {
                // Player attacks enemy
                player.attack(enemy);
                // Only if enemy is still alive, let it attack back
                if (enemy.isAlive()) {
                    enemy.attack(player);
                }
                
                // Check if player or enemy is dead
                if (!player.isAlive()) {
                    cout << "\n" << player.getName() << " has been defeated!\n";
                    should_run = 0;
                } else if (!enemy.isAlive()) {
                    cout << "\n" << enemy.getName() << " has been defeated!\n";
                }
            }
        }
        // Unknown command
        else {
            cout << "Unknown command. Try again!\n";
        }
        // Print a separator line for clarity
        cout << "\n------------------------\n";
    }

    return 0;
}
