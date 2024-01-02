#ifndef BUGWORLDASCII_CHEST_H
#define BUGWORLDASCII_CHEST_H

#include <iostream>
#include <vector>
#include "Furniture.h"

class Chest: public Furniture {
protected:
    bool _open;
    std::vector<Thing> _contents;
    std::string take(AbstractGame &player, std::string noun);
public:
    Chest();
    Chest(std::string name, std::string descriptionShort, std::string descriptionLong, std::vector<std::string> dictionary = {  }, std::vector<Thing> contents = {  }, bool open = false);
    void contents(Thing item);
    std::string printDescription();
    std::vector<std::string> contentsDictionary();
    std::string command(AbstractGame &player, std::string verb, std::string noun = "");
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};

#endif //BUGWORLDASCII_CHEST_H
