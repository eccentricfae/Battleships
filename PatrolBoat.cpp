#include "PatrolBoat.h"

int PatrolBoat::patrolBoatCounter = 0;

/**
 * @details Nullary constructor for the objects of the PatrolBoat class. The constructor calls constructor of the Ship class with the argument of "integer 2",
 * which tells the Ship construcor that objects (ships) of class PatrolBoat are 2 board fields long. 
 */
PatrolBoat::PatrolBoat() : Ship(2) {
    patrolBoatCounter++;
    typeOfShip = "Patrol Boat";
}

PatrolBoat::~PatrolBoat() {
    patrolBoatCounter--;
}