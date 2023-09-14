#include "AbstractGame.h"
#include <algorithm>
#include <fstream>
#include "gameDictionary.h"
#include "printImage.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;
using std::string;
using std::vector;

void AbstractGame::oneWordCommand(string input) {
    if(NOUN_DIRECTION.count(input)) {
        if(!_world[_location].exitMap().count(NOUN_DIRECTION.find(input)->second)) {
            cout << "There is nothing in that direction\n";
            return;
        }
        _world[_location].exitMap()[NOUN_DIRECTION.find(input)->second]->walk(*this);
        return;
    }
    
    switch(NOUN.find(input)->second) {
        case PLAYER:
        case INVENTORY:
            checkInventory();
            return;
        case ROOM:
            lookAround();
            return;
    }
    
    switch(VERB.find(input)->second) {
        case LOOK:
            lookAround();
            return;
    }
    cout << "I dont know that one.\n";
}

void AbstractGame::twoWordCommand(vector<string> input) {
    if(NOUN_DIRECTION.count(input[1])) { //Find doors by direction
        auto exits {_world[_location].exitMap()};
        if(exits.count(NOUN_DIRECTION.find(input[1])->second) == 0) {
            cout << "There is nothing in that direction.\n";
            return;
        }
        exits[NOUN_DIRECTION.find(input[1])->second]->command(*this, input[0]);
        return;
    }
    
    for(auto i : _world[_location].exitMap()) { //Find doors by name
        auto iDic {i.second->dictionary()};
        if(std::count(iDic.begin(), iDic.end(), input[1])) {
            i.second->command(*this, input[0]);
            return;
        }
    }
    
    for(auto i : _world[_location].furnitureList()) { //Find furniture by name
        auto iDic {i->dictionary()};
        if(std::count(iDic.begin(), iDic.end(), input[1])) {
            i->command(*this, input[0]);
            return;
        }
        iDic = i->contentsDictionary(); //Find furniture by contents
        if(std::count(iDic.begin(), iDic.end(), input[1])) {
            i->command(*this, input[0], input[1]);
            return;
        }
        
    }
    
    cout << "Whoops, I can't find " << input[1] << ".\n";
}

void AbstractGame::threeWordCommand(vector<string> input) {
    if(NOUN_DIRECTION.find(input[1]) != NOUN_DIRECTION.end()) { //Find doors by direction
        auto exits {_world[_location].exitMap()};
        if(exits.find(NOUN_DIRECTION.find(input[1])->second) == exits.end()) {
            cout << "There is nothing in that direction.\n";
            return;
        }
        exits[NOUN_DIRECTION.find(input[1])->second]->command(*this, input[0], input[2]);
        return;
    }
    
    if(NOUN_DIRECTION.find(input[2]) != NOUN_DIRECTION.end()) { //Find doors by direction
        auto exits {_world[_location].exitMap()};
        if(exits.find(NOUN_DIRECTION.find(input[2])->second) == exits.end()) {
            cout << "There is nothing in that direction.\n";
            return;
        }
        exits[NOUN_DIRECTION.find(input[1])->second]->command(*this, input[0], input[1]);
        return;
    }
    
    for(auto i : _world[_location].exitMap()) { //Find doors by name
        auto iDic {i.second->dictionary()};
        if(std::find(iDic.begin(), iDic.end(), input[1]) != iDic.end()) {
            i.second->command(*this, input[0], input[2]);
            return;
        }
        if(std::find(iDic.begin(), iDic.end(), input[2]) != iDic.end()) {
            i.second->command(*this, input[0], input[1]);
            return;
        }
    }
    
    for(auto i : _world[_location].furnitureList()) { //Find furniture by name
        auto iDic {i->dictionary()};
        if(std::find(iDic.begin(), iDic.end(), input[1]) != iDic.end()) {
            i->command(*this, input[0], input[2]);
            return;
        }
        if(std::find(iDic.begin(), iDic.end(), input[2]) != iDic.end()) {
            i->command(*this, input[0], input[1]);
            return;
        }
    }
    cout << "Whoops, I can't find " << input[1] << " or " << input[2] << ".\n";
}

void AbstractGame::checkInventory() {
    if(_inventory.empty()) {
        cout << "You don't have any items in your inventory.\n";
        return;
    }
    cout << "In your inventory you have:\n";
    for(auto i : _inventory) cout << string(4,' ') << i.descriptionShort() << "\n";
}

//Getters
string AbstractGame::locationName() { return _world[_location].name(); }
string AbstractGame::locationDescriptionShort() { return _world[_location].descriptionShort(); }

void AbstractGame::command(vector<string> input) {
    if(input.empty()) {
        cout << "You have to type something!\n";
        return;
    }
    if(input.size() == 1) {
        oneWordCommand(input[0]);
        return;
    }
    if(VERB.count(input[0]) == 0) {
        cout << "I can't find the verb in your sentence.\n";
        return;
    }
    switch(input.size()) {
        case 2 :
            twoWordCommand(input);
            return;
        case 3 :
            threeWordCommand(input);
            return;
    }
    cout << "Command too long. Try something a bit less complicated\n";
}

AbstractGame::AbstractGame(int startLocation, vector<Room> world) :
        _world(world), _location(startLocation) {  }

AbstractGame::~AbstractGame() { for(auto room : _world) room.deletePointers(); }

//Prints the long description of the room, and short for doors and furniture
void AbstractGame::lookAround() {
    printImage(_world[_location].imageFile());
    cout << "You are in the " << _world[_location].name() << ".\n"
         << _world[_location].descriptionLong() << "\n";
    for(auto i : _world[_location].exitMap())
        cout << "To the " << DIRECTION_NAME.find(i.first)->second << " there is " << i.second->descriptionShort() << ".\n";
    if(_world[_location].furnitureList().empty()) return;
    cout << "In the room you see:\n";
    for(auto i : _world[_location].furnitureList())
        i->printDescription();
}

//Getters
std::vector<Thing> AbstractGame::inventory() { return _inventory; }
std::vector<int> AbstractGame::powers() { return _powers; }

//Setters
void AbstractGame::location(int newLocation) { _location = newLocation; }
void AbstractGame::inventory(Thing item) { _inventory.push_back(item); }
void AbstractGame::powers(int power) { _powers.push_back(power); }

void AbstractGame::removeItem(Thing item) {
    auto itemIt {std::find(_inventory.begin(), _inventory.end(), item)};
    if(itemIt != _inventory.end())
        _inventory.erase(itemIt);
}

template<class Archive>
void AbstractGame::serialize(Archive &ar, const unsigned int version) {
    ar & _location;
    ar & _world;
    ar & _inventory;
    ar & _powers;
}

BOOST_CLASS_EXPORT(AbstractGame)