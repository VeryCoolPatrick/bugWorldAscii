#include "BugDemo.h"
#include "gameDictionary.h"
#include "Chest.h"
#include "LockedDoor.h"
#include "BoardedDoor.h"

BugDemo::BugDemo() : AbstractGame(BASEMENT) {
    _world = std::vector<Room>(NO_OF_ROOMS); //Lets add rooms by enum index
    
    
    _world[BASEMENT] = Room(
        "basement",
        "a dark room",
        "The room is dark and damp.",
        {"room", "dark room", "lab"}
        );
    _world[BASEMENT].exit(
        NORTH,
        new Door(
            "trapdoor",
            "a staircase leading to a trapdoor",
            "There is light pouring through the trapdoor showing how dusty the stairs are.",
            LAB_MID,
            {"trap door", "trap", "door", "stair", "stairs", "staircase", "stair case"}
            )
        );
    Thing keyCard(
        "keycard",
        "a keycard",
        "It looks like it opens a door",
        {"key card", "key", "card", "pass", "pass key", "passkey"}
        );
    _world[BASEMENT].furniture(new Chest(
        "filing cabinet",
        "a filling cabinet",
        "The cabinet is rusty but opens easy enough.",
        {"cabinet", "filingcabinet", "drawer", "drawers"},
        {keyCard}
            )
        );
    
    
    _world[LAB_LEFT] = Room(
        "west lab",
        "the west lab",
        "It looks like office work is done here",
        {"room", "lab"}
        );
    _world[LAB_LEFT].exit(
        EAST,
        new Door(
            "plain door",
            "a plain door",
            "A normal door. It opens and closes",
            LAB_MID,
            {"plain", "door", "normal", "normal door"}
            )
        );
    Thing mantisDNA(
        "mantis dna",
        "a green vial of mantis DNA",
        "The vial has a faint glow to it.",
        {"dna", "mantis", "green", "vial", "green vial"}
        );
    _world[LAB_LEFT].furniture(new Chest(
            "desk",
            "a desk",
            "Just a standard office desk",
            {"desk table", "table", "office table", "office desk"},
            {mantisDNA},
            true
            )
        );
    
    
    _world[LAB_MID] = Room(
        "main lab",
        "",
        "",
        {"room", "lab"}
        );
    _world[LAB_MID].exit(
        WEST,
        new Door(
            "plain door",
            "a plain door",
            "A normal door. It opens and closes",
            LAB_LEFT,
            {"plain", "normal", "normal door"}
        )
    );
    _world[LAB_MID].exit(
        SOUTH,
        new Door(
            "trapdoor",
            "a trapdoor with a staircase leading down",
            "The stairs lead down to a dark room",
            BASEMENT,
            {"trap door", "trap", "stair", "stairs", "staircase", "stair case"}
        )
    );
    _world[LAB_MID].exit(
        EAST,
        new LockedDoor(
            "metal door",
            "a metal door",
            "A heavy door with an electronic lock.",
            LAB_RIGHT,
            keyCard,
            "The door is locked and wont budge.",
            "You swipe the card and the lock clicks open.",
            {"metal", "heavy", "heavy door"}
            )
        );
    _world[LAB_MID].exit(
        NORTH,
        new BoardedDoor(
            "boarded door",
            "a big door covered in boards",
            "The door had been boarded shut",
            OUTSIDE,
            "The door is nailed shut with heavy boards.",
            "You smash the door open!",
            {"big door", "big"}
            )
        );
    
    
    _world[LAB_RIGHT] = Room(
        "east lab",
        "",
        "",
        {"room", "lab"}
        );
    _world[LAB_RIGHT].exit(
        WEST,
        new Door(
            "metal door",
            "a metal door",
            "A heavy door with an electronic lock.",
            LAB_MID,
            {"metal", "heavy", "heavy door"}
            )
        );
    
    _world[OUTSIDE] = Room(
        "open field",
        "open field",
        "You made it out mostly in one piece!"
        );
}
