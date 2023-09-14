#ifndef BUGWORLDASCII_GAMEDICTIONARY_H
#define BUGWORLDASCII_GAMEDICTIONARY_H

#include <iostream>
#include <vector>
#include <map>

//Basic commands used outside game
enum{QUIT, SAVE, LOAD, NEW_GAME};
const std::map<std::string, int> META_COMMANDS {
    {"quit", QUIT}, {"save", SAVE}, {"load", LOAD},
    {"new", NEW_GAME}, {"new game", NEW_GAME}
};

//Pairs of words to convert to a single string
const std::multimap<std::string, std::string> DOUBLE_WORDS {
    {"pick", "up"}, {"lock", "pick"}, {"pick", "lock"}, {"new", "game"}, {"look", "around"}, {"look", "about"},
    {"brass", "key"}, {"little", "key"}, {"blue", "door"}, {"red", "door"}, {"wooden", "chest"}, {"wood", "chest"}
};

//Words to be removed before running commands
const std::vector<std::string> DUD_WORDS {"a", "at", "on", "an", "for", "from", "in", "of", "the", "through", "to", "with", "my", "i"};

//ID for types of verb
enum VERB_ID {WALK, JUMP, TAKE, USE, OPEN, UNLOCK, LOOK, ATTACK};

//Input string, verb ID
const std::map<std::string, int> VERB {
    {"walk", WALK}, {"go", WALK}, {"move", WALK},
    {"jump", JUMP}, {"leap", JUMP}, {"hop", JUMP},
    {"take", TAKE}, {"grab", TAKE}, {"pick up", TAKE}, {"pocket", TAKE},
    {"open", OPEN},
    {"unlock", UNLOCK}, {"lock pick", UNLOCK}, {"pick lock", UNLOCK},
    {"use", USE}, {"put", USE},
    {"look", LOOK}, {"inspect", LOOK}, {"check", LOOK}, {"look around", LOOK}, {"look about", LOOK},
    {"attach", ATTACK}, {"hit", ATTACK}, {"break", ATTACK}, {"smash", ATTACK}
};

//Id for general purpose nouns
enum NOUN_ID {PLAYER, ROOM, INVENTORY, POWERS};

const std::map<std::string, int> NOUN {
    {"player", PLAYER}, {"self", PLAYER}, {"myself", PLAYER}, {"me", PLAYER},
    {"room", ROOM}, {"around", ROOM}, {"here", ROOM},
    {"inventory", INVENTORY}, {"items", INVENTORY},
    {"powers", POWERS}, {"mutations", POWERS}
};

//ID for directions
enum DIRECTION_ID {NORTH, EAST, SOUTH, WEST};

//Input string, direction ID
const std::map<std::string, int> NOUN_DIRECTION {
    {"north", NORTH}, {"forward", NORTH}, {"up", NORTH},
    {"east", EAST}, {"right", EAST},
    {"south", SOUTH}, {"back", SOUTH}, {"down", SOUTH},
    {"west", WEST}, {"left", WEST}
};

//Direction ID, output string
const std::map<int, std::string> DIRECTION_NAME {
    {NORTH, "north"},
    {EAST, "east"},
    {SOUTH, "south"},
    {WEST, "west"}
};

enum POWERS {MANTIS_ARMS, CRICKET_LEGS, SPIDER_EYES};

#endif //BUGWORLDASCII_GAMEDICTIONARY_H
