#include "Furniture.h"
#include "AbstractGame.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

using std::cout;
using std::string;
using std::vector;

Furniture::Furniture() {  }

Furniture::Furniture(string name, string descriptionShort, string descriptionLong, vector<string> dictionary) :
        Thing(name, descriptionShort, descriptionLong, dictionary) {  }

void Furniture::printDescription() { cout << descriptionShort() << ".\n"; }

//Used for chests and other containers
vector<string> Furniture::contentsDictionary() { return {}; }

//Sole interface for child objects
void Furniture::command(AbstractGame &player, string verb, string noun) {
    if(noun.empty()) {
        switch(VERB.find(verb)->second) {
            case LOOK:
                cout << descriptionLong() << '\n';
                return;
        }
    }
    
    cout << "You cant do that to " << name() << ".\n";
}

template<class Archive>
void Furniture::serialize(Archive &ar, const unsigned int version) {
    ar & boost::serialization::base_object<Thing>(*this);
}

BOOST_CLASS_EXPORT(Furniture)