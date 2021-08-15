#pragma once
#include "Ship.h"

/**
 * @class Battleship
 * @brief Class that represents a battleship-type ship, that is 4 board-fields long.
 * @see Ship
 */
class Battleship : public Ship {
private:
    /**
     * @brief Variable that stores the information of: how many objects of Battleship class exist.
     */
    static int battleshipCounter;

public:

    /**
     * @brief Construct a new Battleship object, that is a 4 board-fields-long ship.
     */
    Battleship();

    ~Battleship();
};