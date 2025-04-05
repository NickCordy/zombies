#ifndef ZOMBIES_ZOMBIE_H
#define ZOMBIES_ZOMBIE_H

#include <memory>
#include "Organism.h"

class Zombie : public Organism
{
public:
    Zombie();
    Zombie( City *city, int x, int y );
    ~Zombie() override;

    void turn() override;
    void moveEat();
    void move(int direction);
    void eat(int direction);
    void convertHuman();
    void starve();

    char getSpecies() override;
    static int getTotal();

protected:
    static void addValidDirections(vector<int>& directions, int x, int y);
    static void checkPosition(vector<int>& moveDirections, vector<int>& humanDirections, unique_ptr<Organism>& organism, int direction);
    static int zombieTotal;
    int starvationCounter{};
};

#endif //ZOMBIES_ZOMBIE_H
