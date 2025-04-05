#ifndef ZOMBIES_ORGANISM_H
#define ZOMBIES_ORGANISM_H

#include <iostream>
#include "../inc/GameSpecs.h"

using namespace std;

class City;

class Organism
{
public:
    Organism();
    Organism(City *city, int x, int y);
    virtual ~Organism();

    virtual void turn() = 0; // Pure virtual function
    //virtual void spawn() = 0;
    virtual char getSpecies() = 0; // Pure virtual function
    //virtual void getPosition() = 0;

    void setPosition( int x, int y );
    void resetTurnStatus();
    bool getRemove() const;
    [[nodiscard]] bool hadTurn() const;

    friend ostream& operator<<( ostream &output, Organism *organism );

protected:
    int x{};
    int y{};
    int timeStep{};
    bool remove;
    bool turnCompleted{};
    City *city{};

    enum { LEFT = 0, UP, RIGHT, DOWN, UPPER_LEFT, UPPER_RIGHT, LOWER_LEFT, LOWER_RIGHT, NUM_DIRECTIONS };
};

#endif //ZOMBIES_ORGANISM_H
