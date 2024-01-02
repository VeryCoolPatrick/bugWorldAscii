#include "BoardedDoor.h"
#include "AbstractGame.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;
using std::string;

string BoardedDoor::breakDoor(AbstractGame &player) {
    auto powers {player.powers()};
    if(!std::count(powers.begin(), powers.end(), MANTIS_ARMS)) {
        return _lockMessage + "\n";
    }
    _locked = false;
    return _unLockMessage + "\n";
}

BoardedDoor::BoardedDoor() {  }

BoardedDoor::BoardedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
                         std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary) :
    Door(name, descriptionShort, descriptionLong, destination, dictionary),
    _lockMessage(lockMessage), _unLockMessage(unlockMessage), _locked(true) {  }
    
string BoardedDoor::command(AbstractGame &player, std::string verb, std::string noun) {
    if(!_locked) {
        return Door::command(player, verb, noun);
    }
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case OPEN:
            case UNLOCK:
                return _lockMessage + "\n";
            case ATTACK:
                return breakDoor(player);
        }
    }
    return Door::command(player, verb, noun);
}

string BoardedDoor::walk(AbstractGame &player) {
    if(!_locked) {
        return Door::walk(player);
    }
    return _lockMessage + "\n";
}
