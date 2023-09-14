#include "BoardedDoor.h"
#include "AbstractGame.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;

void BoardedDoor::breakDoor(AbstractGame &player) {
    auto powers {player.powers()};
    if(!std::count(powers.begin(), powers.end(), MANTIS_ARMS)) {
        cout << _lockMessage << "\n";
        return;
    }
    _locked = false;
    cout << _unLockMessage << "\n";
}

BoardedDoor::BoardedDoor() {  }

BoardedDoor::BoardedDoor(std::string name, std::string descriptionShort, std::string descriptionLong, int destination,
                         std::string lockMessage, std::string unlockMessage, std::vector<std::string> dictionary) :
    Door(name, descriptionShort, descriptionLong, destination, dictionary),
    _lockMessage(lockMessage), _unLockMessage(unlockMessage), _locked(true) {  }
    
void BoardedDoor::command(AbstractGame &player, std::string verb, std::string noun) {
    if(!_locked) {
        Door::command(player, verb, noun);
        return;
    }
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case OPEN:
            case UNLOCK:
                cout << _lockMessage << "\n";
                return;
            case ATTACK:
                breakDoor(player);
        }
    }
    Door::command(player, verb, noun);
}

void BoardedDoor::walk(AbstractGame &player) {
    if(!_locked) {
        Door::walk(player);
        return;
    }
    cout << _lockMessage << "\n";
}
