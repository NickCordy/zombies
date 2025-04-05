#ifndef ZOMBIES_CITY_H
#define ZOMBIES_CITY_H

#include <iostream>
#include <array>
#include <memory>
#include "GameSpecs.h"
#include "Organism.h"

using namespace std;

class City
{
public:
    City();
    virtual ~City();

    unique_ptr<Organism> & getOrganism(int x, int y );
    void setOrganism(unique_ptr<Organism>& orgPtr, int x, int y );

    void update();
    void reset();
    int getGeneration() const;

    static int getHumanTotal();
    static int getZombieTotal();
    static int getRand();
    static bool hasDiversity();

    friend ostream& operator<<( ostream &output, City &city );
    static void colour(int);

protected:
    array<array<unique_ptr<Organism>, GRID_SIZE>, GRID_SIZE> grid;
    int generation{};
};

#endif //ZOMBIES_CITY_H
