#ifndef BUGWORLDASCII_ABSTRACTGAME_H
#define BUGWORLDASCII_ABSTRACTGAME_H

#include <iostream>
#include <vector>
#include "Thing.h"
#include "Room.h"

class AbstractGame {
private:
    void oneWordCommand(std::string input);
    void twoWordCommand(std::vector<std::string> input);
    void threeWordCommand(std::vector<std::string> input);
    
    void checkInventory();
    
    //Getters
    std::string locationName();
    std::string locationDescriptionShort();
protected:
    //Player data
    int _location; //Index to _world vector
    std::vector<Thing> _inventory;
    std::vector<int> _powers;
    
    //_word must be set by child constructor
    std::vector<Room> _world;
public:
    AbstractGame(int startLocation = 0, std::vector<Room> world = {  });
    ~AbstractGame();
    AbstractGame(AbstractGame&) = delete; //Copy constructor disabled as it needs special implementation to prevent segfaults
    void lookAround();
    void command(std::vector<std::string> input);
    std::vector<Thing> inventory();
    std::vector<int> powers();
    void location(int newLocation);
    void inventory(Thing item);
    void powers(int power);
    void removeItem(Thing item);
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};

#endif //BUGWORLDASCII_ABSTRACTGAME_H
