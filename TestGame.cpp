#include "TestGame.h"
#include "gameDictionary.h"
#include "Chest.h"
#include "LockedDoor.h"

TestGame::TestGame() : AbstractGame() {
    
    enum ROOMS {BLUE_ROOM, RED_ROOM,};
    
    _world.push_back(Room(
            "blue room",
            "a room with blue walls",
            "It has a nice navy colour, but it's painted very poorly.",
            {"room"}, {}, "blueRoom.txt"));
    Thing blueDoorKey(
            "brass key",
            "a little brass key",
            "The key looks like it opens a door.",
            {"key", "brass"});
    _world[BLUE_ROOM].exit(NORTH, new LockedDoor(
            "blue door",
            "a blue door with a brass lock",
            "The paint is flaking off the door. It looks sturdy and secure.",
            RED_ROOM, blueDoorKey,
            "The door is locked and wont budge",
            "You have to jiggle it a bit but you unlock the blue door.",
            {"door"}));
    _world[BLUE_ROOM].furniture(new Chest(
            "wooden chest",
            "a wooden chest",
            "The chest is steel bound and sturdy, but is not apparently locked.",
            {"chest"}, {blueDoorKey}));
    
    _world.push_back(Room(
            "red room",
            "a room with red walls",
            "I don't care for this shade of maroon, at least the painters did a better job this time.",
            {"room"},{} , "redRoom.txt"));
    _world[RED_ROOM].exit(SOUTH, new Door(
            "red door",
            "a red door with no lock",
            "Painted with tacky gloss red. Didn't even pay for a lock.",
            BLUE_ROOM, {"door"}));
    _world[RED_ROOM].furniture(new Furniture(
            "gold statue",
            "a shinny gold statue",
            "A beautiful statue made of solid gold. It looks very expensive.",
            {"statue"}
            ));
}