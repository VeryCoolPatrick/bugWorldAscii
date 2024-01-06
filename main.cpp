#include <iostream>
#include <vector>
#include <fstream>
#include "TestGame.h"
#include "BugDemo.h"
#include "textFormater.h"
#include "gameDictionary.h"
#include "printImage.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>

using std::cout;
using std::cin;
using std::string;
using std::vector;

const string SAVE_FILE {"testGameSave.txt"};

void saveGame(AbstractGame &game);
void loadGame(AbstractGame &game);
bool getYN();

int main() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    printImage("titleFile.txt");
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    AbstractGame *game {new TestGame};

    cout << game->lookAround();
    bool run = true;
    while(run) {
        cout << "\n>";
        vector<string> input {inputCommandReady()};
        if(input.size() == 1) {
            switch(META_COMMANDS.find(input[0])->second) {
                case QUIT :
                    run = false;
                    continue;
                case SAVE :
                    saveGame(*game);
                    continue;
                case LOAD :
                    loadGame(*game);
                    continue;
                case NEW_GAME:
                    cout << "Save before starting a new game? (Y/N)\n>";
                    if(getYN()) saveGame(*game);
                    delete game;
                    game = new TestGame;
                    cout << game->lookAround();
                    continue;
            }
        }
        cout << game->command(input);
    }
    cout << "Save before quitting? (Y/N)\n>";
    if(getYN()) saveGame(*game);
    return 0;
}

void saveGame(AbstractGame &game) {
    std::ofstream fileOut(SAVE_FILE);
    boost::archive::text_oarchive serialOut(fileOut);
    serialOut << game;
    cout << "Game saved.\n";
}

//Returns false if save file does not exist
void loadGame(AbstractGame &game) {
    std::ifstream fileIn(SAVE_FILE);
    if(!fileIn) {
        cout << "No save file found!\n";
        return;
    }
    boost::archive::text_iarchive serialIn(fileIn);
    serialIn >> game;
    cout << "Game loaded.\n";
    game.lookAround();
}

//Gets a char and returns true if y or Y, false otherwise
bool getYN() {
    switch(cin.get()) {
        case 'y':
        case 'Y':
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        default:
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        case '\n':
            return false;
    }
}