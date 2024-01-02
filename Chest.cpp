#include "Chest.h"
#include <iomanip>
#include "AbstractGame.h"
#include "textFormater.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;
using std::string;
using std::vector;

string Chest::take(AbstractGame &player, std::string noun) {
    if(!_open) {
        return "You haven't looked in " + descriptionShort() + " yet.\n";
    }
    for(size_t i {0}; i < _contents.size(); i++) {
        auto descDic {_contents[i].dictionary()};
        if(find(descDic.begin(), descDic.end(), noun) == descDic.end()) continue;
        string message = "you take the " + _contents[i].name() + " from the " + name() + ".\n";
        player.inventory(_contents[i]);
        _contents.erase(_contents.begin() + i);
        return message;
    }
    return "You can't find " + noun + ".\n";
}

Chest::Chest() {  }

Chest::Chest(string name, string descriptionShort, string descriptionLong, vector<string> dictionary, vector<Thing> contents, bool open) :
        Furniture(name, descriptionShort, descriptionLong, dictionary), _contents(contents), _open(open) {  }
        
//Setters
void Chest::contents(Thing item) { _contents.push_back(item); }

string Chest::printDescription() {
    string message = capitalise(descriptionShort()) + ".\n";
    if(!_open || _contents.empty()) return message;
    message += "The " + name() + " holds:\n";
    for(auto i : _contents)
        message += string(4, ' ') + capitalise(i.descriptionShort()) + ".\n";
    return message;
}

vector<string> Chest::contentsDictionary() {
    if(!_open) return {};
    vector<string> contentsDictionary;
    for(Thing i : _contents)
        contentsDictionary.insert(contentsDictionary.end(), i.dictionary().begin(), i.dictionary().end());
    return contentsDictionary;
}

string Chest::command(AbstractGame &player, string verb, string noun) {
    if(noun.empty()) {
        string message;
        switch(VERB.find(verb)->second) {
            case OPEN:
                if(_open) message += capitalise(descriptionShort()) + " is not closed.\n";
                else message += "You open the " + name() + ".\n";
            case LOOK:
                _open = true;
                message += descriptionLong() + "\n";
                if(_contents.empty()) return message;
                message += "The " + name() + " holds:\n";
                for(auto i : _contents)
                    message += string(4, ' ') + capitalise(i.descriptionShort()) + ".\n";
                return message;
            case UNLOCK:
                return "The " + name() + " is not locked.\n";
        }
    } else {
        switch(VERB.find(verb)->second) {
            case TAKE:
                return take(player, noun);
        }
    }
    return Furniture::command(player,verb,noun);
}

template<class Archive>
void Chest::serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Furniture>(*this);
    ar & _contents;
    ar & _open;
}

BOOST_CLASS_EXPORT(Chest)