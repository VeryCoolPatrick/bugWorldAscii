#ifndef BUGWORLDASCII_THING_H
#define BUGWORLDASCII_THING_H

#include <iostream>
#include <vector>

class Thing {
private:
    std::string _name, _descriptionShort, _descriptionLong;
    std::vector<std::string> _dictionary;
public:
    Thing();
    Thing(std::string name, std::string descriptionShort, std::string descriptionLong, std::vector<std::string> dictionary = {});
    bool operator==(Thing rhs);
    std::string name();
    std::string descriptionShort();
    std::string descriptionLong();
    std::vector<std::string> dictionary();
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};

#endif //BUGWORLDASCII_THING_H
