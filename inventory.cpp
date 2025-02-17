#include <iostream>
#include "inventory.h"

// Inventory
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

std::map<std::string, std::map<std::string, int>> itemsByCategory;
std::list<std::string> categoryOrder;

void Inventory::addItem(const string &category, const string &item, int quantity)
{
  // if the category is not found in the list | Prevent Duplicate categories
  if (find(categoryOrder.begin(), categoryOrder.end(), category) == categoryOrder.end())
  {
    // Add the category to the list
    categoryOrder.push_back(category);
  }
  // Add item to specific category
  itemsByCategory[category][item] += quantity;
}

void Inventory::removeItem(const string &category, const string &item, int quantity) {
  auto categoryIt = itemsByCategory.find(category);
  
  // If category doesn't exist, return
  if (categoryIt == itemsByCategory.end()) {
      // cout << "Category '" << category << "' not found in inventory.\n";
      return;
  }

  auto &itemMap = categoryIt->second;
  auto itemIt = itemMap.find(item);

  // If item doesn't exist, return
  if (itemIt == itemMap.end()) {
      // cout << "Item '" << item << "' not found in category '" << category << "'.\n";
      return;
  }

  // Reduce the item's quantity
  if (itemIt->second <= quantity) {
      // Remove the item completely if quantity is 0 or less
      itemMap.erase(itemIt);
      // cout << "Removed all '" << item << "' from category '" << category << "'.\n";
  } else {
      // Decrease the quantity
      itemIt->second -= quantity;
      // cout << "Removed " << quantity << " of '" << item << "' from category '" << category << "'.\n";
  }

  // If category is now empty, remove it from inventory
  if (itemMap.empty()) {
      itemsByCategory.erase(category);
      categoryOrder.remove(category);
      // cout << "Category '" << category << "' is now empty and removed.\n";
  }
}

void Inventory::displayInventory()
{
  // No items within Inventory
  if (itemsByCategory.empty())
  {
    std::cout << "Your inventory is empty.\n";
    return;
  }

  // Predefined Category order
  const string categoryOrder[] = {"Weapons", "Potions", "Artifacts"};

  std::cout << "\n===== Inventory =====\n";

  // Display by category
  // For each category name within the category order
  for (const auto &categoryName : categoryOrder)
  {
    auto it = itemsByCategory.find(categoryName);

    // If a Category Name within categoryOrder is found
    if (it != itemsByCategory.end())
    {
      std::cout << "\n[ " << categoryName << " ]\n";

      // For each item within the category, print | Pointint to value
      for (const auto &item : it->second)
      {
        std::cout << " " << item.first << " x" << item.second << "\n";
      }
    }
  }
  std::cout << "\n====================\n";
}

bool Inventory::hasItem(const string &item) const
{
  // loop through each category
  for (const auto &category : itemsByCategory) 
  {
    // If the item is found within the category
    if (category.second.find(item) != category.second.end())
    {
      return true; // Item exists in the inventory
    }
  }
  return false; // Item not found in any category
                // return itemsByCategory.find(item) != itemsByCategory.end();
}

void Inventory::setPlayerName(const string& name) 
{
  playerName = name;
}

void Inventory::saveInventory(const string &filename)
{
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
        // cout << "Saved Successfully!\n";
}

//retrieve inventory from last save
void Inventory::loadInventory(const string& filename) {
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
  // cout << "Previous save loaded for " << playerName << "!\n";
}