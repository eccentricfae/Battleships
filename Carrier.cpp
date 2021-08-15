#include "Carrier.h"

//int Carrier::carrierCounter = 0;

/**
 * @details Nullary constructor for the objects of the Carrier class. The constructor calls constructor of the Ship class with the argument of "integer 5",
 * which tells the Ship construcor that objects (ships) of class Carrier are 5 board fields long. 
 */
Carrier::Carrier() : Ship(5) {
    //carrierCounter++;
    typeOfShip = "Lotniskowiec";
}

Carrier::~Carrier() {
    //carrierCounter--;
}