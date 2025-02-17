#include "entity.h"
#include "inventory.h"
#include <limits>

using namespace std;

// Inventory userInventory;

void Entity::attack(Entity& target)
{
    int damage = generateDamage();
    std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!" << std::endl; // Attack dealt
    target.takeDamage(damage);
}

// Takes damage from the attack
void Entity::takeDamage(int damage)
{
    health -= damage;
    if (health < 0)
    {
        health = 0;
    }
    std::cout << name << " takes " << damage << " damage. Current health: " << health << std::endl; // Damage taken
}

int Entity::getHealth()
{
    return health;
}

int Entity::getMaxHealth() const
{
    return maxHealth;
}

std::string Entity::getName() const
{
    return name;
}

bool Entity::isAlive() const
{
    return health > 0;
}

void Entity::setHealth(int newHealth)
{
    // target.health = newHealth;
    this->health = newHealth;
}

// Display the health bar for the entity (a simple bar with "#" and "-")
void Entity::displayHealthBar() const
{
    int barWidth = 20;
    int filledWidth = (health * barWidth) / maxHealth;
    cout << name << " Health: [";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < filledWidth)
        {
            cout << "#"; // Health portion
        }
        else
        {
            cout << "-"; // Empty portion
        }
    }
    cout << "] " << health << "/" << maxHealth << endl;
}

int Entity::generateDamage() const
{
    return rand() % 11 + 10;
}

void Entity::activeCombat(Enemy& enemy)
{
    /**
     * While the enemy and user/player is alive keep the entities in combat.
     * Flee feature, if user run's away then you are sent back a room (TBD)
     * Ask player if they want to attack, or use an item.
     */
    string userIn;
    bool inCombat = true;
    bool userAttacked;
    Inventory userInventory;
    userInventory.loadInventory();
    // userInventory.displayInventory();
    
    // && userInventory.hasItem("Health Potion")

    while (this->isAlive() && enemy.isAlive())
    {
            userAttacked = false;
            cout << "\n";
            this->displayHealthBar();
            cout << "=================================================\n";
            enemy.displayHealthBar();
            cout << "\nWhat would you like to do?...\n";
            // cout << "Attack\nUse Health Potion\nFlee\nDisplay Inventory\n====================\n";
            cout << "+---------------------+\n";
            cout << "| Available Actions   |\n";
            cout << "| Attack              |\n";
            cout << "| Use health potion   |\n";
            cout << "| Display Inventory   |\n";
            cout << "| Flee                |\n";
            cout << "+---------------------+\n";
            // cin >> userIn;
            getline(cin, userIn);
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "====================\n";

            if (userIn == "attack")
            {
                this->attack(enemy);
                // cout << "Attack hit for " << enemy.getMaxHealth() - enemy.getHealth() << "\n";
                cout << endl;
                userAttacked = true;
                // attackingPlayer.attack(enemy);
            }
            else if (userIn == "use health potion")
            {
                cout << "\033[3mYou have used a Health Potion\033[0m\n";
                cout << "\033[3mHealth Recovered!\033[0m\n";
                this->setHealth(100);
                userInventory.removeItem("Potions", "Health Potion", 1);
                cout << "\n";
            }
            else if (userIn == "flee")
            {
                cout << "\033[3mYou have fled the fight!\033[0m\n";
                break;
            } 
            else if (userIn == "view inventory") {
                userInventory.displayInventory();
            }
            if (enemy.isAlive() && userAttacked) {
                int damage = enemy.generateDamage();
                this->setHealth(this->getHealth() - damage);
                cout << "Enemy's attack hit for " << damage << "\n";
                cout << endl;
            }

        
    }
    if (this->isAlive() && !enemy.isAlive())    // if user is alive and enemy is dead
    {
        cout << "You have defeated " << enemy.getName() << "!!\n";
        cout << "=================================================\n";
    } else {
        cout << "\033[3mYou have escaped safely...\033[0m\n";
        cout << "=================================================\n";
    }
}
