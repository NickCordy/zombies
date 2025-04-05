#include <iostream>
#include <chrono>
#include <thread>

#include "inc/GameSpecs.h"
#include "inc/Organism.h"
#include "inc/City.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City *city = new City();
    chrono:: milliseconds interval(INTERVAL);

    while (City::hasDiversity() && city->getGeneration() != ITERATIONS) {
        this_thread::sleep_for(interval);
        ClearScreen();
        city->update(); // Includes all actions
        city->reset(); // Resets moved flags
        cout << *city; // Prints city
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << City::getHumanTotal() << endl;
        City::colour(WHITE);
        cout << "ZOMBIES: " << City::getZombieTotal() << endl;
    }
}
