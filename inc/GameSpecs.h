#ifndef ZOMBIES_GAMESPECS_H
#define ZOMBIES_GAMESPECS_H

const int INTERVAL = 1;
const int GRID_SIZE = 20;
const int HUMAN_STARTCOUNT = 100; // initial Humans
const int ZOMBIE_STARTCOUNT = 5; //initial Zombie count
const int HUMAN_BREED = 3; // steps until a Human breeds
const int ZOMBIE_BREED = 8; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 3; // steps until a Zombie starves and converts back
const char HUMAN_CH = 72;//72 "H"// ascii for Human
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const double PAUSE_SECONDS = .09; // pause between steps
const int ITERATIONS = 1000; // max number of steps

enum {
    BLACK = 0,
    BLUE,
    GREEN,
    TURQUOISE,
    RED,
    PINK,
    YELLOW,
    WHITE,
    WHITE_PALE,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_TURQUOISE,
    BRIGHT_RED,
    BRIGHT_YELLOW,
    BRIGHT_WHITE,
    SOLID_BLOCK
};

const int HUMAN_COLOR = 3; // turquoise
const int ZOMBIE_COLOR = 14; // bright yellow

#endif //ZOMBIES_GAMESPECS_H
