#include "Battleship.h"

int Battleship::battleshipCounter = 0;

/**
 * @details Nullary constructor for the objects of the Battleship class. The constructor calls constructor of the Ship class with the argument of "integer 4",
 * which tells the Ship construcor that objects (ships) of class Battleship are 4 board fields long.
 */
Battleship::Battleship() : Ship(4) {
    battleshipCounter++;
    typeOfShip = "Pancernik";
}

Battleship::~Battleship() {
    battleshipCounter--;
}