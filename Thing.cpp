#include "Thing.h"

using std::string;
using std::vector;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

Thing::Thing() {  }

//Only long description should be capitalised
Thing::Thing(string name, string descriptionShort, string descriptionLong, vector<string> dictionary) :
        _name(name), _descriptionLong(descriptionLong), _descriptionShort(descriptionShort), _dictionary(dictionary) {
    _dictionary.push_back(name);
    _dictionary.push_back(descriptionShort);
}

bool Thing::operator==(Thing rhs) { return _name == rhs._name; }

//Getters
string Thing::name() { return _name; }
string Thing::descriptionShort() { return _descriptionShort; }
string Thing::descriptionLong() { return _descriptionLong; }
vector<string> Thing::dictionary() { return _dictionary; }

template<class Archive>
void Thing::serialize(Archive &ar, const unsigned int version) {
    ar &_name;
    ar &_descriptionShort;
    ar &_descriptionLong;
    ar &_dictionary;
}

BOOST_CLASS_EXPORT(Thing)