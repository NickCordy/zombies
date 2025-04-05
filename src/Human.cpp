#include <vector>
#include <random>
#include <algorithm>
#include "../inc/Human.h"
#include "../inc/City.h"

int Human::humanTotal = 0;

Human::Human() = default;

Human::Human(City *city, int x, int y) : Organism(city, x, y) {
    humanTotal++;
}

Human::~Human() {
    humanTotal--;
}

void Human::turn() {
    move();

    if (timeStep == HUMAN_BREED) {
        recruit();
    }

    turnCompleted = true;
    timeStep++;
}

void Human::move() {
    vector<int> validDirections = {}; // Vector to hold valid move moveDirections
    addValidDirections(validDirections, x, y); // Adding directions that are within the grid only

    vector<int> moveDirections = validDirections;

    // Loop to check if directions are occupied and remove them from moveDirections if so
    for (int direction : validDirections) {
        switch (direction) {
            case LEFT:
                if (city->getOrganism(x-1, y) != nullptr) {
                    moveDirections.erase(std::remove(moveDirections.begin(), moveDirections.end(), LEFT), moveDirections.end());
                }
                break;
            case RIGHT:
                if (city->getOrganism(x+1, y) != nullptr) {
                    moveDirections.erase(std::remove(moveDirections.begin(), moveDirections.end(), RIGHT), moveDirections.end());
                }
                break;
            case UP:
                if (city->getOrganism(x, y-1) != nullptr) {
                    moveDirections.erase(std::remove(moveDirections.begin(), moveDirections.end(), UP), moveDirections.end());
                }
                break;
            case DOWN:
                if (city->getOrganism(x, y+1) != nullptr) {
                    moveDirections.erase(std::remove(moveDirections.begin(), moveDirections.end(), DOWN), moveDirections.end());
                }
                break;
            default:
                break;
        }
    }

    // Shuffling moveDirections for a random direction
    std::minstd_rand0 generator(std::random_device{}());
    shuffle(moveDirections.begin(), moveDirections.end(), generator);

    // Swap this humans pointer in grid based on direction
    if (!moveDirections.empty()) {
        switch (moveDirections[0]) {
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
        }
    }
}

void Human::recruit() {
    vector<int> validDirections = {}; // Vector to hold valid move moveDirections

    addValidDirections(validDirections, x, y); // Adding moveDirections that are within the grid only

    vector<int> directions = validDirections;

    // Loop to check if directions are occupied and remove them from moveDirections if so
    for (int direction : validDirections) {
        switch (direction) {
            case LEFT:
                if (city->getOrganism(x-1, y) != nullptr) {
                    directions.erase(std::remove(directions.begin(), directions.end(),LEFT), directions.end());
                }
                break;
            case RIGHT:
                if (city->getOrganism(x+1, y) != nullptr) {
                    directions.erase(std::remove(directions.begin(), directions.end(),RIGHT), directions.end());
                }
                break;
            case UP:
                if (city->getOrganism(x, y-1) != nullptr) {
                    directions.erase(std::remove(directions.begin(), directions.end(),UP), directions.end());
                }
                break;
            case DOWN:
                if (city->getOrganism(x, y+1) != nullptr) {
                    directions.erase(std::remove(directions.begin(), directions.end(),DOWN), directions.end());
                }
                break;
            default:
                break;
        }
    }

    // Shuffling moveDirections for a random direction
    std::minstd_rand0 generator(std::random_device{}());
    shuffle(directions.begin(),directions.end(), generator);

    std::unique_ptr<Organism> humanPtr;

    // Make a new human in an adjacent spot if possible
    if (!directions.empty()) {
        switch (directions[0]) {
            case LEFT:
                humanPtr = std::make_unique<Human>(city, x-1, y);
                city->setOrganism(humanPtr, x-1, y);
                break;
            case RIGHT:
                humanPtr = std::make_unique<Human>(city, x+1, y);
                city->setOrganism(humanPtr, x+1, y);
                break;
            case UP:
                humanPtr = std::make_unique<Human>(city, x, y-1);
                city->setOrganism(humanPtr, x, y-1);
                break;
            case DOWN:
                humanPtr = std::make_unique<Human>(city, x, y+1);
                city->setOrganism(humanPtr, x, y+1);
                break;
        }
    }

    timeStep = 0;
}

char Human::getSpecies() {
    City::colour(BLUE);
    return HUMAN_CH;
}

int Human::getTotal() {
    City::colour(BLUE);
    return humanTotal;
}

void Human::addValidDirections(vector<int> &directions, int x, int y) {
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
