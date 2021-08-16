/**
 * @file Destroyer.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#include "Destroyer.h"

/**
 * @details Nullary constructor for the objects of the Destroyer class. The constructor calls constructor of the Ship class with the argument of "integer 3",
 * which tells the Ship construcor that objects (ships) of class Destroyer are 3 board fields long. 
 */
Destroyer::Destroyer() : Ship(3) {
    typeOfShip = "Niszczyciel";
}

Destroyer::~Destroyer() {}