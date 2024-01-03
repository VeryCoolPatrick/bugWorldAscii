#include "LockedDoor.h"
#include <iostream>
#include "AbstractGame.h"
#include "textFormater.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;

std::string LockedDoor::unlock(AbstractGame &player, std::string item) {
    for(Thing i : player.inventory()) {
        auto iDic {i.dictionary()};
        if(std::count(iDic.begin(), iDic.end(), item) == 0) continue;
        if(i == _key) {
            _locked = false;
            player.removeItem(_key);
            return _unLockMessage + "\n";;
        }
    }
    return capitalise(item) + " does not open the " + name();
}

LockedDoor::LockedDoor() {  }

LockedDoor::LockedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
                       Thing key, std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary) :
    Door(name, descriptionShort, descriptionLong, destination, dictionary),
    _key(key), _lockMessage(lockMessage), _unLockMessage(unlockMessage), _locked(true) {  }

std::string LockedDoor::command(AbstractGame &player, std::string verb, std::string noun) {
    if(!_locked) {
        return Door::command(player, verb, noun);
    }
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case WALK:
                return walk(player);
            case OPEN:
                return _lockMessage + "\n";
            case UNLOCK:
                return"With what?\n";
                // auto input {inputCommandReady()};    //TODO: Fix this, should have back and forth
                // if(input.size() == 1) unlock(player, input[0]);
                // else player.command(input);
                // return;
        }
    } else {
        switch(VERB.find(verb)->second) {
            case OPEN:
            case UNLOCK:
            case USE:
                return unlock(player, noun);
        }
    }
    return Door::command(player, verb, noun);
}

std::string LockedDoor::walk(AbstractGame &player) {
    if(_locked) {
        return "The " + name() + " is locked.\n";
    }
    return Door::walk(player);
}

template<class Archive>
void LockedDoor::serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Door>(*this);
    ar & _locked;
    ar & _lockMessage;
    ar & _unLockMessage;
    ar & _key;
}

BOOST_CLASS_EXPORT(LockedDoor)