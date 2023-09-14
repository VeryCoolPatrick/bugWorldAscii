#ifndef BUGWORLDASCII_ROOM_H
#define BUGWORLDASCII_ROOM_H

#include <iostream>
#include <vector>
#include <map>

#include "Thing.h"
#include "Furniture.h"
#include "Door.h"

class Room: public Thing {
private:
    //Furniture and doors must be stored as pointers for polymorphism
    std::map<int, Door*> _exits;
    std::vector<Furniture*> _furnitureList;
    std::string _imageFile;
public:
    Room();
    Room(std::string name, std::string descriptionShort, std::string descriptionLong, std::vector<std::string> dictionary = {}, std::map<int, Door*> exits = {}, std::string imageFile = {});
    void deletePointers();
    void exit(int direction, Door *newDoor);
    void furniture(Furniture *newFurniture);
    std::map<int, Door*> exitMap();
    std::vector<Furniture*> furnitureList();
    std::string imageFile();
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version);
};


#endif //BUGWORLDASCII_ROOM_H
