/**
 * @file Battleship.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#include "Battleship.h"

/**
 * @details Nullary constructor for the objects of the Battleship class. The constructor calls constructor of the Ship class with the argument of "integer 4",
 * which tells the Ship construcor that objects (ships) of class Battleship are 4 board fields long.
 */
Battleship::Battleship() : Ship(4) {
    typeOfShip = "Pancernik";
}

Battleship::~Battleship() {}