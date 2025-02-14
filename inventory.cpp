#include <iostream>
#include "inventory.h"

//Inventory 
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

    std::map<std::string, std::map<std::string, int>> itemsByCategory;
    std::list<std::string> categoryOrder;


        void Inventory::addItem(const string& category, const string& item, int quantity){
          //if the category is not found in the list | Prevent Duplicate categories
          if(find(categoryOrder.begin(), categoryOrder.end(), category) == categoryOrder.end()){
            //Add the category to the list
            categoryOrder.push_back(category);
          }
          //Add item to specific category
          itemsByCategory[category][item] += quantity;
        }
  
        void Inventory::displayInventory(){
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
        
        bool Inventory::hasItem(const string& item) const{
          return itemsByCategory.find(item) != itemsByCategory.end();
        }