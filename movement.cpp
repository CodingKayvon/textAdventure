#include "movement.h"
#include "inventory.h"

using namespace std;

Inventory inventoryCheck;
/**
 * Handles possible actions depending on user's current Location
 * cout << "\033[3m...\033[0m\n";
 */

void displayCommands(Location currentLocation, Inventory& inventory) {
    if (currentLocation == WINDGALE)
  {
    cout << "\033[3mJust before dusk, you arrive at a small town nestled betwixt two mountains. A chilling gust blows from behind you through the town as you approach and you spot a swinging wooden sign with the word Windgale written on it, supposedly the name of this hamlet\033[0m\n";
    cout << "\033[3mAs your eyes sweep the buildings, you spot a general store, a tavern, and a forge as places of interest.\033[0m\n";
    cout << "+---------------------+\n";
    cout << "| Available Actions   |\n";
    cout << "| Go to Shop          |\n";
    cout << "| Go to Tavern        |\n";
    cout << "| Go to Forge         |\n";
    cout << "| Approach Dungeon    |\n";
    cout << "+---------------------+\n";

  } else if (currentLocation == SHOP) {
    cout << "\033[3mThis small general store seems to hold an assortment of goods ranging from adventuring gear to everyday needs. The sign above the door reads, 'Arrielle's Sundries.'\033[0m\n";
    cout << "\033[3mWhen you walk through the entrance you notice someone crouched behind the shop counter vigorously cleaning the shelves which display some of the potions sold here.\033[0m\n";
    cout << "\033[3mThe shopkeep, who you assume to be Arrielle from the sign outside, stands tall as she hears you come in and greets you with a kind smile, her lithe figure and long pointed ears make it obvious to you she is an elf.\033[0m\n";
    cout << "+---------------------+\n";
    cout << "| Available Actions   |\n";
    cout << "| Speak with Arrielle |\n";
    cout << "| Leave Shop          |\n";
    cout << "+---------------------+\n";

    
  } else if (currentLocation == TAVERN) {
    cout << "\033[3mThis tavern is clearly the most popular building in town as it is the largest and loudest area of town. The sign outside reads, 'Gale Valley Brewery and Tavern.'\033[0m\n";
    cout << "\033[3mAs you push open the saloon doors and the full image of this place comes into view, one specific patron catches your eye, a rugged, green-scaled dragonborn who appears to be a retired ranger sipping on hard liquor and plucking at the string of their bow as you would a lyre.\033[0m\n";
    cout << "\033[3mA burly orc stands in front of the wall of available drinks polishing a glass mug. He shoots an inquisitive glare in your direction and beckons you over to him.\033[0m\n";
    cout << "+---------------------+\n";
    cout << "| Available Actions   |\n";
    cout << "| Speak with Moss     |\n";
    cout << "| Speak with Rundigar |\n";
    cout << "| Leave Tavern        |\n";
    cout << "+---------------------+\n";
    
  } else if (currentLocation == FORGE) {
    cout << "\033[3mThe forge is a rather small establishment with various metal weapons and armor kept in barrels scattered about the premises.\033[0m\n";
    cout << "\033[3mThere is no prominent sign outside to indicate the name of the forge, only a small metal plate bolted in the wall next to the doorway with barely legible text scratched into it which reads, 'Lochlin's House.'\033[0m\n";
    cout << "\033[3mStill leaning forward to read the sign, a stout figure races past you out of the house in a blur seemingly unaware of your presence. When you turn around, you see a dwarf clad in tough leather dunking an orange hot blade into a bucket of water and hear the hissing of the metal as it cools.\033[0m\n";
    cout << "+---------------------+\n";
    cout << "| Available Actions   |\n";
    cout << "| Speak with Lochlin  |\n";
    cout << "| Leave Forge         |\n";
    cout << "+---------------------+\n";
  } else if (currentLocation == DUNGEON) {
    cout << "\033[3mEven from the edge of town you can easily make out a large pair of round stone doors inset in the eastern mountain.\033[0m\n";
    cout << "\033[3mYou make the trek over to the entrance of the dungeon and as you get closer a humanoid shape can be seen pacing in front of the doors.\033[0m\n";
    cout << "\033[3mNow, with the doors towering above you, the person's form becomes clear. He is a short tabaxi with amateur adventuring gear strapped to him.\033[0m\n";
    cout << "+---------------------+\n";
    cout << "| Available Actions   |\n";
    cout << "| Speak with Enfys    |\n";
    cout << "| Enter Dungeon       |\n";
    cout << "+---------------------+\n";
  }
  else if (currentLocation == ROOM1)
  {
    cout << "\033[3mThe smell of wet stone and decay rushes over you as you take the first steps into the dungeon. The only light you can see by is the silver glimmer of the moonlight behind you.\033[0m\n";
    cout << "\033[3mYou take stock of this first room, which is seemingly empty save for an unlit lantern hanging on one wall.\033[0m\n";
    cout << "\033[3mYou light the lantern and hook it onto your belt. It appears from here on the warmth of the lantern will be your only comfort and companion.\033[0m\n";
    cout << "+---------------------+\n";
    cout << "| Available Actions   |\n";
    cout << "| Go North            |\n";
    cout << "+---------------------+\n";
  }
  else if(currentLocation == ROOM2)
  {
    // cout << "\033...\033[0m\n";
    // cout << "\033...\033[0m\n";
    // cout << "\033...\033[0m\n";
    cout << "+-----------------------+\n";
    cout << "| Available Actions     |\n";
    cout << "| Go East               |\n";
    cout << "| Search Dead Adventurer|\n";
    cout << "+-----------------------+\n";
  }
  else if(currentLocation == ROOM3)
  {
    cout << "+-----------------------+\n";
    cout << "| Available Actions     |\n";
    cout << "| Go South              |\n";
    cout << "| Approach enemy        |\n";
    cout << "| Pick up item          |\n";
    cout << "+-----------------------+\n";
  }
  else if(currentLocation == ROOM4)
  {
    cout << "\033[3mYou've come to a dead end. The only way out is the way you came but you can hear a loud thudding coming from below the floor.\033[0m\n";
    cout << "\033[3mOn searching the room, you notice three square stone tablets scattered about the floor and three depressions along the walls of the chamber.\033[0m\n";
    cout << "\033[3mEach tablet has the image of an animal engraved in it, one: a humpback whale, another: a goose, and the last: a rattlesnake. There is one depression in the east wall, a second in the west wall, and a third in the south wall.\033[0m\n";
    cout << "+-----------------------+\n";
    cout << "| Available Actions     |\n";
    cout << "| Tablet Challenge      |\n";
    cout << "+-----------------------+\n";
  }
  else if(currentLocation == BOSS_ROOM)
  {
    cout << "\033[3mThe heat emanating from this room is unlike anything you've experienced. It's as if you have stepped foot into the eternal inferno.\033[0m\n";
    cout << "\033[3mThe source of the heat is an object which you can only make out as a large gem-like red mass from behind your squinted eyes.\033[0m\n";
    cout << "\033[3mNow aware of your intrusion, the pile of scaly flesh rises to its feet, its beady eyes pierce through your soul and you finally see it for what it is, a Red Dragon\033[0m\n";
    cout << "+-----------------------+\n";
    cout << "| Available Actions     |\n";
    cout << "| Approach Boss         |\n";
    cout << "| Go North              |\n";
    cout << "+-----------------------+\n";
  }
  else if (currentLocation == TREAS_ROOM)
  {
    cout << "\033[3mThe mounds of gold and jewels in this room are unlike any wealth held by any major city in history.\033[0m\n";
    cout << "\033[3mYour quest accomplished, you may choose to keep this wealth for yourself, never telling a soul of the riches you acquired here, or share it with the people of Windgale and the surrounding towns in hopes of improving the townsfolk's lives.\033[0m\n";
    cout << "\033[3mEither way it'll be quite the task to transport all this coin out of the dungeon.\033[0m\n";
    cout << "\033[3mThanks for playing our game!!!!! :)\033[0m\n";
    cout << "+-----------------------+\n";
    cout << "| Available Actions     |\n";
    cout << "| Quit                  |\n";
    cout << "+-----------------------+\n";
  }

}




    // cout << "You are in the beginning\n";
    // cout << "You see someone\n";
    // if (!inventory.hasItem("Ancient Map"))
    // {
    //   cout << "You see an old map\n";
    // }

    // cout << "+--------------------+\n";
    // cout << "| Available actions: |\n";
    // cout << "| View Inventory     |\n";
    // cout << "| Speak with person  |\n";
    // if (!inventory.hasItem("Ancient Map"))
    // {
    //   cout << "| Pick up old map    |\n";
    // }
    // if (inventory.hasItem("Ancient Map"))
    // {
    //   cout << "| View Ancient Map   |\n";
    // }
    // cout << "| go dungeon         |\n";
    // cout << "+====================+\n";