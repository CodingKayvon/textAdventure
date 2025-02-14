#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <iostream> // If you plan to use cout in the implementation

class Inventory {
private:
    // Map (Category Name) to a Map (Item Name, and Quantity)
    // std::map<std::string, std::map<std::string, int>> itemsByCategory;
    // std::list<std::string> categoryOrder;

public:
    void addItem(const std::string& category, const std::string& item, int quantity = 1);

    void displayInventory();

    bool hasItem(const std::string& item) const; // Added 'const'
};

#endif // INVENTORY_H