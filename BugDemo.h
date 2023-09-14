#ifndef BUGWORLDASCII_BUGDEMO_H
#define BUGWORLDASCII_BUGDEMO_H

#include "AbstractGame.h"

class BugDemo: public AbstractGame {
private:
    enum ROOMS {BASEMENT, LAB_LEFT, LAB_MID, LAB_RIGHT, OUTSIDE, NO_OF_ROOMS};
public:
    BugDemo();
};

#endif //BUGWORLDASCII_BUGDEMO_H
