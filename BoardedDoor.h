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
    void breakDoor(AbstractGame &player);
public:
    BoardedDoor();
    BoardedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
                std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary = {});
    void command(AbstractGame &player, std::string verb, std::string noun = "");
    void walk(AbstractGame &player);
};


#endif //BUGWORLDASCII_BOARDEDDOOR_H
