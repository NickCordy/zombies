#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "../inc/Zombie.h"
#include "../inc/City.h"

int Zombie::zombieTotal = 0;

Zombie::Zombie() = default;

Zombie::Zombie(City *city, int x, int y) : Organism(city, x, y) {
    zombieTotal++;
}

Zombie::~Zombie() {
    zombieTotal--;
}

void Zombie::turn() {
    moveEat();

    if (timeStep >= ZOMBIE_BREED) {
        convertHuman();
    }

    if (starvationCounter >= ZOMBIE_STARVE) {
        starve();
    }

    turnCompleted = true;
    timeStep++;
}

void Zombie::moveEat() {
    vector<int> validDirections = {}; // Vector to hold valid move moveDirections
    vector<int> humanDirections = {}; // Vector to hold valid eat moveDirections

    addValidDirections(validDirections, x, y); // Adding moveDirections that are within the grid only

    vector<int> moveDirections = validDirections;

    // checkPosition adds to humanDirections and removes from moveDirections based on if
    // the position is occupied by a zombie, human or if empty
    for (int direction : validDirections) {
        if (direction == LEFT) {
            // Storing references to the pointers of the grid organisms for each direction
            unique_ptr<Organism>& left = city->getOrganism(x-1, y);
            checkPosition(moveDirections, humanDirections, left, LEFT);
        }
        else if (direction == RIGHT) {
            unique_ptr<Organism>& right = city->getOrganism(x+1, y);
            checkPosition(moveDirections, humanDirections, right, RIGHT);
        }
        else if (direction == UP) {
            unique_ptr<Organism>& up = city->getOrganism(x, y-1);
            checkPosition(moveDirections, humanDirections, up, UP);
        }
        else if (direction == DOWN) {
            unique_ptr<Organism>& down = city->getOrganism(x, y+1);
            checkPosition(moveDirections, humanDirections, down, DOWN);
        }
        else if (direction == UPPER_LEFT) {
            unique_ptr<Organism>& uLeft = city->getOrganism(x-1, y-1);
            checkPosition(moveDirections, humanDirections, uLeft, UPPER_LEFT);
        }
        else if (direction == LOWER_LEFT) {
            unique_ptr<Organism>& lLeft = city->getOrganism(x-1, y+1);
            checkPosition(moveDirections, humanDirections, lLeft, LOWER_LEFT);
        }
        else if (direction == UPPER_RIGHT) {
            unique_ptr<Organism>& uRight = city->getOrganism(x+1, y-1);
            checkPosition(moveDirections, humanDirections, uRight, UPPER_RIGHT);
        }
        else if (direction == LOWER_RIGHT) {
            unique_ptr<Organism>& lRight = city->getOrganism(x+1, y+1);
            checkPosition(moveDirections, humanDirections, lRight, LOWER_RIGHT);
        }
    }

    // Shuffle direction vectors for randomness
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
    shuffle(moveDirections.begin(), moveDirections.end(), default_random_engine(seed));
    shuffle(humanDirections.begin(), humanDirections.end(), default_random_engine(seed));

    if (!humanDirections.empty()) {
        eat(humanDirections[0]);
    }
    else if (!moveDirections.empty()){
        move(moveDirections[0]);
    }
}

void Zombie::move(int direction) {
    switch (direction) {
        case LEFT:
            std::swap(city->getOrganism(x, y), city->getOrganism(x-1, y));
            this->setPosition(x-1, y);
            break;
        case RIGHT:
            std::swap(city->getOrganism(x, y), city->getOrganism(x+1, y));
            this->setPosition(x+1, y);
            break;
        case UP:
            std::swap(city->getOrganism(x, y), city->getOrganism(x, y-1));
            this->setPosition(x, y-1);
            break;
        case DOWN:
            std::swap(city->getOrganism(x, y), city->getOrganism(x, y+1));
            this->setPosition(x, y+1);
            break;
        case UPPER_LEFT:
            std::swap(city->getOrganism(x, y), city->getOrganism(x-1, y-1));
            this->setPosition(x-1, y-1);
            break;
        case LOWER_LEFT:
            std::swap(city->getOrganism(x, y), city->getOrganism(x-1, y+1));
            this->setPosition(x-1, y+1);
            break;
        case UPPER_RIGHT:
            std::swap(city->getOrganism(x, y), city->getOrganism(x+1, y-1));
            this->setPosition(x+1, y-1);
            break;
        case LOWER_RIGHT:
            std::swap(city->getOrganism(x, y), city->getOrganism(x+1, y+1));
            this->setPosition(x+1, y+1);
            break;
    }

    starvationCounter++;
}

void Zombie::eat(int direction) {
    switch (direction) {
        case LEFT:
            city->getOrganism(x-1, y) = std::move(city->getOrganism(x, y));
            this->setPosition(x-1, y);
            break;
        case RIGHT:
            city->getOrganism(x+1, y) = std::move(city->getOrganism(x, y));
            this->setPosition(x+1, y);
            break;
        case UP:
            city->getOrganism(x, y-1) = std::move(city->getOrganism(x, y));
            this->setPosition(x, y-1);
            break;
        case DOWN:
            city->getOrganism(x, y+1) = std::move(city->getOrganism(x, y));
            this->setPosition(x, y+1);
            break;
        case UPPER_LEFT:
            city->getOrganism(x-1, y-1) = std::move(city->getOrganism(x, y));
            this->setPosition(x-1, y-1);
            break;
        case LOWER_LEFT:
            city->getOrganism(x-1, y+1) = std::move(city->getOrganism(x, y));
            this->setPosition(x-1, y+1);
            break;
        case UPPER_RIGHT:
            city->getOrganism(x+1, y-1) = std::move(city->getOrganism(x, y));
            this->setPosition(x+1, y-1);
            break;
        case LOWER_RIGHT:
            city->getOrganism(x+1, y+1) = std::move(city->getOrganism(x, y));
            this->setPosition(x+1, y+1);
            break;
    }
    starvationCounter = 0;
}

void Zombie::convertHuman() {
    vector<int> validDirections = {}; // Vector to hold valid moveDirections
    vector<int> humanDirections = {}; // Vector to hold valid eat moveDirections

    addValidDirections(validDirections, x, y); // Adding moveDirections that are within the grid only

    vector<int> moveDirections = validDirections;

    // checkPosition adds to eatDirections and removes from moveDirections based on if
    // the position is occupied by a zombie, human or if empty
    for (int direction : validDirections) {
        if (direction == LEFT) {
            // Storing references to the pointers of the grid organisms for each direction
            unique_ptr<Organism>& left = city->getOrganism(x-1, y);
            checkPosition(moveDirections, humanDirections, left, LEFT);
        }
        else if (direction == RIGHT) {
            unique_ptr<Organism>& right = city->getOrganism(x+1, y);
            checkPosition(moveDirections, humanDirections, right, RIGHT);
        }
        else if (direction == UP) {
            unique_ptr<Organism>& up = city->getOrganism(x, y-1);
            checkPosition(moveDirections, humanDirections, up, UP);
        }
        else if (direction == DOWN) {
            unique_ptr<Organism>& down = city->getOrganism(x, y+1);
            checkPosition(moveDirections, humanDirections, down, DOWN);
        }
        else if (direction == UPPER_LEFT) {
            unique_ptr<Organism>& uLeft = city->getOrganism(x-1, y-1);
            checkPosition(moveDirections, humanDirections, uLeft, UPPER_LEFT);
        }
        else if (direction == LOWER_LEFT) {
            unique_ptr<Organism>& lLeft = city->getOrganism(x-1, y+1);
            checkPosition(moveDirections, humanDirections, lLeft, LOWER_LEFT);
        }
        else if (direction == UPPER_RIGHT) {
            unique_ptr<Organism>& uRight = city->getOrganism(x+1, y-1);
            checkPosition(moveDirections, humanDirections, uRight, UPPER_RIGHT);
        }
        else if (direction == LOWER_RIGHT) {
            unique_ptr<Organism>& lRight = city->getOrganism(x+1, y+1);
            checkPosition(moveDirections, humanDirections, lRight, LOWER_RIGHT);
        }
    }

    // Shuffle moveDirections in both vectors
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // Create random seed using system clock
    shuffle(humanDirections.begin(), humanDirections.end(), default_random_engine(seed));

    if (!humanDirections.empty()) {
        std::unique_ptr<Organism> zombiePtr;
        switch (humanDirections[0]) {
            case LEFT:
                zombiePtr = std::make_unique<Zombie>(city, x-1, y);
                city->getOrganism(x-1, y) = std::move(zombiePtr);
                break;
            case RIGHT:
                zombiePtr = std::make_unique<Zombie>(city, x+1, y);
                city->getOrganism(x+1, y) = std::move(zombiePtr);
                break;
            case UP:
                zombiePtr = std::make_unique<Zombie>(city, x, y-1);
                city->getOrganism(x, y-1) = std::move(zombiePtr);
                break;
            case DOWN:
                zombiePtr = std::make_unique<Zombie>(city, x, y+1);
                city->getOrganism(x, y+1) = std::move(zombiePtr);
                break;
            case UPPER_LEFT:
                zombiePtr = std::make_unique<Zombie>(city, x-1, y-1);
                city->getOrganism(x-1, y-1) = std::move(zombiePtr);
                break;
            case LOWER_LEFT:
                zombiePtr = std::make_unique<Zombie>(city, x-1, y+1);
                city->getOrganism(x-1, y+1) = std::move(zombiePtr);
                break;
            case UPPER_RIGHT:
                zombiePtr = std::make_unique<Zombie>(city, x+1, y-1);
                city->getOrganism(x+1, y-1) = std::move(zombiePtr);
                break;
            case LOWER_RIGHT:
                zombiePtr = std::make_unique<Zombie>(city, x+1, y-1);
                city->getOrganism(x+1, y+1) = std::move(zombiePtr);
                break;
        }
        timeStep = 0;
    }
}

void Zombie::starve() {
    remove = true;
}

char Zombie::getSpecies() {
    City::colour(BRIGHT_RED); // Set console text colour
    return ZOMBIE_CH;
}

int Zombie::getTotal() {
    City::colour(BRIGHT_RED); // Set console text colour
    return zombieTotal;
}

void Zombie::addValidDirections(vector<int> &directions, int x, int y) {
    // Adds all directions that are within the grids bounds

    if (x != 0) directions.push_back(LEFT);

    if (x != GRID_SIZE - 1) directions.push_back(RIGHT);

    if (y != 0) directions.push_back(UP);

    if (y != GRID_SIZE - 1) directions.push_back(DOWN);

    if (x != 0 && y != 0) directions.push_back(UPPER_LEFT);

    if (x != 0 && y != GRID_SIZE - 1) directions.push_back(LOWER_LEFT);

    if (x != GRID_SIZE - 1 && y != 0) directions.push_back(UPPER_RIGHT);

    if (x != GRID_SIZE - 1 && y != GRID_SIZE - 1) directions.push_back(LOWER_RIGHT);
}

void Zombie::checkPosition(vector<int>& moveDirections, vector<int>& humanDirections, unique_ptr<Organism>& organism, int direction) {
    // Remove a direction from moveDirections if occupied, or remove and add to eatDirections if by a human

    if (organism != nullptr && organism->getSpecies() == ZOMBIE_CH) {
        moveDirections.erase(std::remove(moveDirections.begin(), moveDirections.end(),direction), moveDirections.end());
    }
    else if (organism != nullptr) {
        moveDirections.erase(std::remove(moveDirections.begin(), moveDirections.end(),direction), moveDirections.end());
        humanDirections.push_back(direction);
    }
}