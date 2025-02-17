#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <iostream> // If you plan to use cout in the implementation
#include <fstream>

using namespace std;


class Inventory
{
private:
    // Map (Category Name) to a Map (Item Name, and Quantity)
    // std::map<std::string, std::map<std::string, int>> itemsByCategory;
    // std::list<std::string> categoryOrder;
    string playerName;

public:
    void addItem(const std::string &category, const std::string &item, int quantity = 1);

    void removeItem(const string &category, const string &item, int quantity);

    void displayInventory();

    bool hasItem(const std::string &item) const; // Added 'const'

    Inventory() : playerName(" ") {} // constructor

    void setPlayerName(const string &name);

    void saveInventory(const string &filename = "savedData.txt");

    void loadInventory(const string &filename = "savedData.txt");
};

#endif // INVENTORY_H