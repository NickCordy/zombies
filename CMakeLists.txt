cmake_minimum_required(VERSION 3.26)
project(zombies)

set(CMAKE_CXX_STANDARD 17)

add_executable(zombies
        main.cpp
        src/City.cpp
        src/Human.cpp
        src/Organism.cpp
        src/Zombie.cpp
)
