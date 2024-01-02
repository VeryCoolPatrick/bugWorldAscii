#ifndef BUGWORLDASCII_FURNITURE_H
#define BUGWORLDASCII_FURNITURE_H

#include <iostream>
#include <vector>
#include "Thing.h"
#include "gameDictionary.h"
#include "textFormater.h"

class AbstractGame;

class Furniture: public Thing {
public:
    Furniture();
    Furniture(std::string name, std::string descriptionShort, std::string descriptionLong, std::vector<std::string> dictionary = {});
    virtual std::string printDescription();
    virtual std::vector<std::string> contentsDictionary();
    virtual std::string command(AbstractGame &player, std::string verb, std::string noun = "");
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};

#endif //BUGWORLDASCII_FURNITURE_H
