#include "Door.h"
#include "AbstractGame.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using std::string;
using std::vector;

Door::Door() {  }

Door::Door(string name, string descriptionShort, string descriptionLong, int destination, vector<string> dictionary) :
        Furniture(name, descriptionShort, descriptionLong, dictionary), _destination(destination) {  }
//Getters
int Door::destination() { return _destination; }

string Door::command(AbstractGame &player, std::string verb, std::string noun) {
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case WALK:
            case OPEN:
            case USE:
                return walk(player);
            case UNLOCK:
                return capitalise(descriptionShort()) + " is not locked!\n";
        }
    }
    return Furniture::command(player, verb, noun);
}

string Door::walk(AbstractGame &player) {
    player.location(_destination);
    return + "You walk through the " + name() + ".\n" + player.lookAround();
}

template<class Archive>
void Door::serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Furniture>(*this);
    ar & _destination;
}

BOOST_CLASS_EXPORT(Door)