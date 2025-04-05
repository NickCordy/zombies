#include <iostream>
#include <windows.h>
#include <chrono>
#include <random>
#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"

City::City() {

    for (int i = 0; i < HUMAN_STARTCOUNT; i++) {
        int x = getRand();
        int y = getRand();

        // Check if the grid position is empty
        if (grid[y][x] == nullptr) {
            // Pointer to a Human (memory handled by unique_ptr)
            std::unique_ptr<Organism> humanPtr = std::make_unique<Human>(this, x, y);
            // Upcast to an Organism and store at random grid coords
            // Passes ownership of unique_ptr
            grid[y][x] = std::move(humanPtr);
        }
        else {
            // Reiterate to find a new position in the grid
            i--;
        }
    }

    for (int i = 0; i < ZOMBIE_STARTCOUNT; i++) {
        int x = getRand();
        int y = getRand();

        // Check if the grid position is empty
        if (grid[y][x] == nullptr) {
            // Pointer to a Zombie (memory handled by unique_ptr)
            std::unique_ptr<Organism> zombiePtr = std::make_unique<Zombie>(this, x, y);
            // Upcast to an Organism and store at random grid coords
            // Passes ownership of unique_ptr
            grid[y][x] = std::move(zombiePtr);
        }
        else {
            // Reiterate to find a new position in the grid
            i--;
        }
    }
}

City::~City() = default;

unique_ptr<Organism>& City::getOrganism(int x, int y) {
    return grid[y][x];
}

void City::setOrganism(unique_ptr<Organism>& orgPtr, int x, int y) {
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        grid[y][x] = std::move(orgPtr);
    }
    else {
        std::cout << "PROBLEM" << std::endl;
    }
}

void City::update() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] != nullptr && !grid[row][col]->hadTurn()) {
                grid[row][col]->turn();
            }
        }
    }
}

void City::reset() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->resetTurnStatus();
                if (grid[row][col]->getRemove()) {
                    grid[row][col] = nullptr;
                    std::unique_ptr<Organism> humanPtr = std::make_unique<Human>(this, row, col);
                    grid[row][col] = std::move(humanPtr);
                }
            }
        }
    }

    generation++;
}

int City::getGeneration() const {
    return generation;
}

int City::getHumanTotal() {
    return Human::getTotal();
}

int City::getZombieTotal() {
    return Zombie::getTotal();
}

bool City::hasDiversity() {
    if (Zombie::getTotal() <= 0 || Human::getTotal() <= 0) {
        return false;
    }
    return true;
}

ostream &operator<<(ostream &output, City &city) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            City::colour(WHITE_PALE);
            if (city.grid[row][col] == nullptr) {
                output << "-  ";
            }
            else {
                output << city.grid[row][col]->getSpecies();
                output << "  ";
            }
        }
        output << "\n";
    }
    City::colour(WHITE);

    return output;
}

void City::colour(int c) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

int City::getRand() {
    std::minstd_rand0 generator(std::random_device{}());
    // Range for random numbers from 0 to GRID_SIZE - 1
    std::uniform_int_distribution<int> distribution(0, GRID_SIZE - 1);

    return distribution(generator);
}