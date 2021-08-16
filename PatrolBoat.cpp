/**
 * @file PatrolBoat.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#include "PatrolBoat.h"

/**
 * @details Nullary constructor for the objects of the PatrolBoat class. The constructor calls constructor of the Ship class with the argument of "integer 2",
 * which tells the Ship construcor that objects (ships) of class PatrolBoat are 2 board fields long. 
 */
PatrolBoat::PatrolBoat() : Ship(2) {
    typeOfShip = "Patrolowka";
}

PatrolBoat::~PatrolBoat() {}