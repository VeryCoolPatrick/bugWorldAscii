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

void LockedDoor::unlock(AbstractGame &player, std::string item) {
    for(Thing i : player.inventory()) {
        auto iDic {i.dictionary()};
        if(std::count(iDic.begin(), iDic.end(), item) == 0) continue;
        if(i == _key) {
            cout << _unLockMessage << "\n";
            _locked = false;
            player.removeItem(_key);
            return;
        }
    }
    cout << capitalise(item) << " does not open the " << name();
}

LockedDoor::LockedDoor() {  }

LockedDoor::LockedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
                       Thing key, std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary) :
    Door(name, descriptionShort, descriptionLong, destination, dictionary),
    _key(key), _lockMessage(lockMessage), _unLockMessage(unlockMessage), _locked(true) {  }

void LockedDoor::command(AbstractGame &player, std::string verb, std::string noun) {
    if(!_locked) {
        Door::command(player, verb, noun);
        return;
    }
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case OPEN:
                cout << _lockMessage << "\n";
                return;
            case UNLOCK:
                cout << "With what?\n>";
                auto input {inputCommandReady()};
                if(input.size() == 1) unlock(player, input[0]);
                else player.command(input);
                return;
        }
    } else {
        switch(VERB.find(verb)->second) {
            case OPEN:
            case UNLOCK:
            case USE:
                unlock(player, noun);
                return;
        }
    }
    Door::command(player, verb, noun);
}

void LockedDoor::walk(AbstractGame &player) {
    if(_locked) {
        cout << "The " << name() << " is locked.\n";
        return;
    }
    Door::walk(player);
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