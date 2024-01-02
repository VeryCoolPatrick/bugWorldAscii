#ifndef BUGWORLDASCII_BOARDEDDOOR_H
#define BUGWORLDASCII_BOARDEDDOOR_H

#include <iostream>
#include <vector>
#include "Door.h"

class BoardedDoor: public Door {
private:
    bool _locked;
    std::string _lockMessage;
    std::string _unLockMessage;
    std::string breakDoor(AbstractGame &player);
public:
    BoardedDoor();
    BoardedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
                std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary = {});
    std::string command(AbstractGame &player, std::string verb, std::string noun = "");
    std::string walk(AbstractGame &player);
};


#endif //BUGWORLDASCII_BOARDEDDOOR_H
