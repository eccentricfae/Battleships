#include "Destroyer.h"

int Destroyer::destroyerCounter = 0;

/**
 * @details Nullary constructor for the objects of the Destroyer class. The constructor calls constructor of the Ship class with the argument of "integer 3",
 * which tells the Ship construcor that objects (ships) of class Destroyer are 3 board fields long. 
 */
Destroyer::Destroyer() : Ship(3) {
    destroyerCounter++;
    typeOfShip = "Niszczyciel";
}

Destroyer::~Destroyer() {
    destroyerCounter--;
}