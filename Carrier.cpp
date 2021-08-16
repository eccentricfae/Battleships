/**
 * @file Carrier.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#include "Carrier.h"

/**
 * @details Nullary constructor for the objects of the Carrier class. The constructor calls constructor of the Ship class with the argument of "integer 5",
 * which tells the Ship construcor that objects (ships) of class Carrier are 5 board fields long.
 */
Carrier::Carrier() : Ship(5) {
    typeOfShip = "Lotniskowiec";
}

Carrier::~Carrier() {}