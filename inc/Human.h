#ifndef ZOMBIES_HUMAN_H
#define ZOMBIES_HUMAN_H

#include "Organism.h"

class Human : public Organism
{
public:
    Human();
    Human( City *city, int x, int y );
    ~Human() override;

    void turn() override;
    void move();
    void recruit();

    char getSpecies() override;
    static int getTotal();

protected:
    static void addValidDirections(vector<int>& directions, int x, int y);
    static int humanTotal;
};

#endif //ZOMBIES_HUMAN_H
