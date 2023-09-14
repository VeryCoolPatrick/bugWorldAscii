#ifndef BUGWORLDASCII_DOOR_H
#define BUGWORLDASCII_DOOR_H

#include <iostream>
#include <vector>
#include "Furniture.h"

class Door: public Furniture {
private:
    int _destination;
public:
    Door();
    Door(std::string name, std::string descriptionShort, std::string descriptionLong, int destination, std::vector<std::string> dictionary = {});
    void command(AbstractGame &player, std::string verb, std::string noun = "");
    virtual void walk(AbstractGame &player);
    int destination();
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};

#endif //BUGWORLDASCII_DOOR_H
