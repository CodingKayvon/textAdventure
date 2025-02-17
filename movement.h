#include <iostream>
#include "inventory.h"

// enum data for possible locations
enum Location {
    // Town
    WINDGALE, // start
    SHOP,
    TAVERN,
    FORGE,
    // Dungeon
    DUNGEON,
    ROOM1,
    ROOM2,
    ROOM3, 
    ROOM4,
    BOSS_ROOM,
    TREAS_ROOM,
    END_ROOM

};

void displayCommands(Location currentLocation, Inventory& inventory);

