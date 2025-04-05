#include "../inc/Organism.h"

Organism::Organism() = default;

Organism::Organism(City *city, int x, int y) : city(city), x(x), y(y) {
    remove = false;
}

Organism::~Organism() = default;

void Organism::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Organism::resetTurnStatus() {
    turnCompleted = false;
}

bool Organism::hadTurn() const {
    return turnCompleted;
}

bool Organism::getRemove() const {
    return remove;
}

ostream &operator<<(ostream &output, Organism *organism) {
    output << organism->getSpecies();

    return output;
}
