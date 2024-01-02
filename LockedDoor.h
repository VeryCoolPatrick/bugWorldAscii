#ifndef BUGWORLDASCII_LOCKEDDOOR_H
#define BUGWORLDASCII_LOCKEDDOOR_H

#include "Door.h"
#include <iostream>
#include <vector>

class LockedDoor: public Door {
private:
    bool _locked;
    std::string _lockMessage;
    std::string _unLockMessage;
    Thing _key;
    std::string unlock(AbstractGame &player, std::string item);
public:
    LockedDoor();
    LockedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
               Thing key, std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary = {});
    std::string command(AbstractGame &player, std::string verb, std::string noun = "");
    std::string walk(AbstractGame &player);
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};

#endif //BUGWORLDASCII_LOCKEDDOOR_H
