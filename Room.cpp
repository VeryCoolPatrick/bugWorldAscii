#include "Room.h"
#include "gameDictionary.h"
#include "Furniture.h"
#include "Door.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

using std::cout;
using std::string;
using std::vector;
using std::map;

Room::Room() {  }

Room::Room(string name, string descriptionShort, string descriptionLong, vector<string> dictionary, map<int, Door*> exits, string imageFile) :
        Thing(name, descriptionShort, descriptionLong, dictionary), _exits(exits), _imageFile(imageFile) {  }
Room::~Room() { deletePointers(); }
Room::Room(const Room &other) : Thing(other) {
    _imageFile = other._imageFile;

    // Deep copy of _exits
    for (const auto &pair : other._exits) {
        _exits[pair.first] = new Door(*pair.second);
    }

    // Deep copy of _furnitureList
    for (const auto &furniture : other._furnitureList) {
        _furnitureList.push_back(new Furniture(*furniture));
    }
}


//Used in AbstractGame Destructor
void Room::deletePointers() {
    for(auto door : _exits) delete door.second;
    for(auto furniture : _furnitureList) delete furniture;
}

//Setters
void Room::exit(int direction, Door *newDoor) { _exits[direction] = newDoor; }
void Room::furniture(Furniture *newFurniture) { _furnitureList.push_back(newFurniture); }

//Getters
map<int, Door*> Room::exitMap() { return _exits; }
vector<Furniture *> Room::furnitureList() { return _furnitureList; }
std::string Room::imageFile() { return _imageFile; }

template<class Archive>
void Room::serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Thing>(*this);
    ar & _exits;
    ar & _furnitureList;
    ar & _imageFile;
}

BOOST_CLASS_EXPORT(Room)