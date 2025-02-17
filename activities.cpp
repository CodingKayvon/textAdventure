#include <iostream>
#include "activities.h"
#include "inventory.h"
#include <thread>
#include <chrono>
#include <vector>
#include <limits>

using namespace std;

Inventory activity;    // Global inventory object for challenges

/**
 * Template for locked doors
 * @param keyName name of required key
 */
bool Activities::keyChallenge(string keyName) {
    cout << "----------------------------You Approach a Locked Door----------------------------" << endl;
    bool inProgress = true;
    string userIn;
    

    cout << "You must have the appropriate key to pass" << endl;
    /**
     * main event loop, keeps player in event as long as inProgress is true
     */
    while (inProgress) {
        cout << "Do you wish to attempt this challenge? (yes or no)" << endl;
        cin >> userIn;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        
        if (userIn == "yes") {  // simple check for user input (TBD)
            cout << "\033[3mchecking if you have the\033[0m " << keyName << endl; 
            this_thread::sleep_for(chrono::seconds(2));     // pauses for 2 seconds
            if (activity.hasItem(keyName)) {   // if requirment is met
                cout << "You have the "<< keyName << ", you did it!!" << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                inProgress = false;
                return true;
            } else {    // requirment is not met
                cout << "You do not have the " << keyName << " :(" << endl;
                cout << "----------------------------------------------------------------------------------" << endl;
                inProgress = false;
                return false;
            }
        } else {
            inProgress = false;
        } 
    }
}

/**
 * Place tablets in the right order for progressing the duneon
 */
bool Activities::tabletPuzzle() {
    cout << "----------------------------Tablet stuff----------------------------" << endl;
    bool inProgress = true;
    map<int, vector<string>> Walls;   // player's tablet placements
    vector<string> tablets = {"Whale", "Goose", "Snake"};  // tablets to place

    map<int, vector<string>> correctWalls = {
        {1, {"Whale"}}, // west
        {2, {"Goose"}}, // south
        {3, {"Snake"}}  // east
    };
    cout << "1 = West, 2 = South, 3 = East\n";
    while(inProgress) {

    cout << "Place the tablets in the correct Walls to progress.\n";
    for (const auto& tablet : tablets) {    // recieve user input for each tablet placement 
        int choice;
        cout << "Where would you like to place " << tablet << "? (1-3)";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            Walls[choice].push_back(tablet);  // insert tablet into the user choice
            cout << "Placed " << tablet << " on wall " << choice << endl;
        } else {
            cout << "Invalid Wall" << endl;
        }
    }

    cout << "\nFinal Walls:\n";
    for (const auto& wall : Walls) {
        cout << "Wall " << wall.first << ": ";
        for (const auto& tablet : wall.second) {
            cout << tablet << " ";
        }
        cout << endl;
    }

    cout << "========================================\n";
    cout << "Is something happening?\n";
    cout << endl;
    this_thread::sleep_for(chrono::seconds(2));     // pauses for 2 seconds

    // compare user answers to answer key
    if (Walls == correctWalls) {
        cout << "Congratulations, you did it!\n";
        inProgress = false;
        return true;
    } else {
        cout << "Something's not quite right\n";
        inProgress = false;
        return false;
    }
    }
    cout << "==========================================================\n";
    
}
