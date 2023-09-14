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

void Chest::take(AbstractGame &player, std::string noun) {
    if(!_open) {
        cout << "You haven't looked in " << descriptionShort() << " yet.\n";
        return;
    }
    for(size_t i {0}; i < _contents.size(); i++) {
        auto descDic {_contents[i].dictionary()};
        if(find(descDic.begin(), descDic.end(), noun) == descDic.end()) continue;
        cout << "you take the " << _contents[i].name() << " from the " << name() << ".\n";
        player.inventory(_contents[i]);
        _contents.erase(_contents.begin() + i);
        return;
    }
    cout << "You can't find " << noun << ".\n";
}

Chest::Chest() {  }

Chest::Chest(string name, string descriptionShort, string descriptionLong, vector<string> dictionary, vector<Thing> contents, bool open) :
        Furniture(name, descriptionShort, descriptionLong, dictionary), _contents(contents), _open(open) {  }
        
//Setters
void Chest::contents(Thing item) { _contents.push_back(item); }

void Chest::printDescription() {
    cout << capitalise(descriptionShort()) <<".\n";
    if(!_open || _contents.empty()) return;
    cout << "The " << name() << " holds:\n";
    for(auto i : _contents)
        cout << string(4, ' ') << capitalise(i.descriptionShort()) << ".\n";
}

vector<string> Chest::contentsDictionary() {
    if(!_open) return {};
    vector<string> contentsDictionary;
    for(Thing i : _contents)
        contentsDictionary.insert(contentsDictionary.end(), i.dictionary().begin(), i.dictionary().end());
    return contentsDictionary;
}

void Chest::command(AbstractGame &player, string verb, string noun) {
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case OPEN:
                if(_open) cout << capitalise(descriptionShort()) << " is not closed.\n";
                else cout << "You open the " << name() << ".\n";
            case LOOK:
                _open=true;
                cout << descriptionLong() <<"\n";
                if(_contents.empty()) return;
                cout << "The " << name() << " holds:\n";
                for(auto i : _contents)
                    cout << string(4, ' ') << capitalise(i.descriptionShort()) << ".\n";
                return;
            case UNLOCK:
                cout << "The " << name() << " is not locked.\n";
                return;
        }
    } else {
        switch(VERB.find(verb)->second) {
            case TAKE:
                take(player, noun);
                return;
        }
    }
    Furniture::command(player,verb,noun);
}

template<class Archive>
void Chest::serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Furniture>(*this);
    ar & _contents;
    ar & _open;
}

BOOST_CLASS_EXPORT(Chest)