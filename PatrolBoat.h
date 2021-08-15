#pragma once
#include "Ship.h"

/**
 * @class PatrolBoat
 * @brief Class that represents a patrol-boat-type ship that is 2 fields long.
 * @see Ship
 */
class PatrolBoat : public Ship {
private:
    /**
     * @brief Variable that stores the information of: how many objects of PatrolBoat class exist.
     */
    //static int patrolBoatCounter;

public:
    /**
     * @brief Construct a new PatrolBoat object, that is a 2 board-fields-long ship.
     */
    PatrolBoat();

    ~PatrolBoat();
};