#include "AbstractGame.h"
#include <algorithm>
#include <fstream>
#include <sstream>

#include "gameDictionary.h"
#include "printImage.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;
using std::string;
using std::vector;

std::string AbstractGame::oneWordCommand(string input) {
    if(NOUN_DIRECTION.count(input)) {
        if(!_world[_location].exitMap().count(NOUN_DIRECTION.find(input)->second)) {
            return "There is nothing in that direction\n";
        }
        return _world[_location].exitMap()[NOUN_DIRECTION.find(input)->second]->walk(*this);
    }
    
    switch(NOUN.find(input)->second) {
        case PLAYER:
        case INVENTORY:
            return checkInventory();
        case ROOM:
            return lookAround();
    }
    
    switch(VERB.find(input)->second) {
        case LOOK:
            return lookAround();
    }
    return "I dont know that one.\n";
}

std::string AbstractGame::twoWordCommand(vector<string> input) {
    if(NOUN_DIRECTION.count(input[1])) { //Find doors by direction
        auto exits {_world[_location].exitMap()};
        if(exits.count(NOUN_DIRECTION.find(input[1])->second) == 0) {
            return "There is nothing in that direction.\n";
        }
        return exits[NOUN_DIRECTION.find(input[1])->second]->command(*this, input[0]);
    }
    
    for(auto i : _world[_location].exitMap()) { //Find doors by name
        auto iDic {i.second->dictionary()};
        if(std::count(iDic.begin(), iDic.end(), input[1])) {
            return i.second->command(*this, input[0]);
        }
    }
    
    for(auto i : _world[_location].furnitureList()) { //Find furniture by name
        auto iDic {i->dictionary()};
        if(std::count(iDic.begin(), iDic.end(), input[1])) {
            return i->command(*this, input[0]);
        }
        iDic = i->contentsDictionary(); //Find furniture by contents
        if(std::count(iDic.begin(), iDic.end(), input[1])) {
            return i->command(*this, input[0], input[1]);
        }
        
    }
    
    return "Whoops, I can't find " + input[1] + ".\n";
}

std::string AbstractGame::threeWordCommand(vector<string> input) {
    if(NOUN_DIRECTION.find(input[1]) != NOUN_DIRECTION.end()) { //Find doors by direction
        auto exits {_world[_location].exitMap()};
        if(exits.find(NOUN_DIRECTION.find(input[1])->second) == exits.end()) {
            return "There is nothing in that direction.\n";
        }
        return exits[NOUN_DIRECTION.find(input[1])->second]->command(*this, input[0], input[2]);
    }
    
    if(NOUN_DIRECTION.find(input[2]) != NOUN_DIRECTION.end()) { //Find doors by direction
        auto exits {_world[_location].exitMap()};
        if(exits.find(NOUN_DIRECTION.find(input[2])->second) == exits.end()) {
            return "There is nothing in that direction.\n";
        }
        return exits[NOUN_DIRECTION.find(input[1])->second]->command(*this, input[0], input[1]);
    }
    
    for(auto i : _world[_location].exitMap()) { //Find doors by name
        auto iDic {i.second->dictionary()};
        if(std::find(iDic.begin(), iDic.end(), input[1]) != iDic.end()) {
            return i.second->command(*this, input[0], input[2]);
        }
        if(std::find(iDic.begin(), iDic.end(), input[2]) != iDic.end()) {
            return i.second->command(*this, input[0], input[1]);
        }
    }
    
    for(auto i : _world[_location].furnitureList()) { //Find furniture by name
        auto iDic {i->dictionary()};
        if(std::find(iDic.begin(), iDic.end(), input[1]) != iDic.end()) {
            return i->command(*this, input[0], input[2]);
        }
        if(std::find(iDic.begin(), iDic.end(), input[2]) != iDic.end()) {
            return i->command(*this, input[0], input[1]);
        }
    }
    return "Whoops, I can't find " + input[1] + " or " + input[2] + ".\n";
}

string AbstractGame::checkInventory() {
    if(_inventory.empty()) {
        return "You don't have any items in your inventory.\n";
    }
    string response = "In your inventory you have:\n";
    for(auto i : _inventory) response += string(4,' ') + i.descriptionShort() + "\n";
    return response;
}

//Getters
string AbstractGame::locationName() { return _world[_location].name(); }
string AbstractGame::locationDescriptionShort() { return _world[_location].descriptionShort(); }

string AbstractGame::command(vector<string> input) {
    if(input.empty()) {
        return "You have to type something!\n";
    }
    if(input.size() == 1) {
        return oneWordCommand(input[0]);
    }
    if(VERB.count(input[0]) == 0) {
        return "I can't find the verb in your sentence.\n";
    }
    switch(input.size()) {
        case 2 :
            return twoWordCommand(input);
        case 3 :
            return threeWordCommand(input);
    }
    return "Command too long. Try something a bit less complicated\n";
}
std::string AbstractGame::command(std::string input) {
    vector<string> formatedInput = formatLine(input);
    return command(formatedInput);
}

AbstractGame::AbstractGame(int startLocation, vector<Room> world) :
        _world(world), _location(startLocation) {  }

AbstractGame::~AbstractGame() { for(auto room : _world) room.deletePointers(); }

//Prints the long description of the room, and short for doors and furniture
string AbstractGame::lookAround() {
    // printImage(_world[_location].imageFile()); //Not used anymore
    string message = "You are in the " + _world[_location].name() + ".\n"
                   + _world[_location].descriptionLong() + "\n";
    for(auto i : _world[_location].exitMap())
        message += "To the " + DIRECTION_NAME.find(i.first)->second + " there is " + i.second->descriptionShort() + ".\n";
    if(_world[_location].furnitureList().empty()) return message;
    message += "In the room you see:\n";
    for(auto i : _world[_location].furnitureList())
        message += i->printDescription();
    return message;
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
std::string AbstractGame::save() {
    std::stringstream ss;
    boost::archive::text_oarchive serialOut(ss);
    serialOut << *this;
    return ss.str();
}

void AbstractGame::load(std::string save) {
    std::stringstream ss(save);
    boost::archive::text_iarchive serialIn(ss);
    serialIn >> *this;
}

template<class Archive>
void AbstractGame::serialize(Archive &ar, const unsigned int version) {
    ar & _location;
    ar & _world;
    ar & _inventory;
    ar & _powers;
}

BOOST_CLASS_EXPORT(AbstractGame)