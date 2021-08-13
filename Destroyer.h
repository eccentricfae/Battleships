#pragma once
#include "Ship.h"

/**
 * @class Destroyer
 * @brief Class that represents a destroyer-type ship that is 3 fields long.
 * @see Ship
 */
class Destroyer : public Ship {
private:
    /**
     * @brief Variable that stores the information of: how many objects of Destroyer class exist.
     * 
     */
    static int destroyerCounter;

public:
    // ! static bool canBeCreated(); if this is to be implemeted -> define it in .cpp file

    /**
     * @brief Construct a new Destroyer object, that is a 3 board-fields-long ship.
     */
    Destroyer();

    ~Destroyer();
};