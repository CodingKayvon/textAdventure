#include <iostream>
#include "activities.h"
using namespace std;




    /**
 * Riddle me this activity function
 * This mini-game will inlclude remembering a key event in the player's adventures. Examples of this include the origins of rewards
 * and fun enemy facts. This mini-game will reward the player with special items that will aid in the adventure
 */
void Activities::riddleGame(bool requirment) {
    cout << "----------------------------Event is occuring----------------------------" << endl;

    bool inProgress = true;
    string userIn;

    cout << "Event text" << endl;
    /**
     * main event loop, keeps player in event as long as inProgress is true
     */
    while (inProgress) {
        cout << "Do you wish to attempt this challenge? (yes or no)" << endl;
        cin >> userIn;
        cout << "You have selected " << userIn << endl;
        
        if (userIn == "yes") {  // simple check for user input (TBD)
            cout << "checking if you have required item..." << endl; 
            if (requirment) {   // if requirment is met
                cout << "You had the required item, you did it!!" << endl;
                cout << "---------------------------------------" << endl;
                inProgress = false;
            } else {    // requirment is not met
                cout << "You do not have the required item :(" << endl;
                cout << "---------------------------------------" << endl;
                inProgress = false;
            }
        } else {
            inProgress = false;
        }

        cout << "----------------------------END EVENT----------------------------" << endl; 
    }
}

// string checkItem(bool hasItem) {
//     if (hasItem) {
//         return "you have the item :)";
//     } else {
//         return "you do not have the item :(";
//     }
// }

