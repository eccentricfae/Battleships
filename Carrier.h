#pragma once
#include "Ship.h"

/**
 * @class Carrier
 * @brief Class that represents a carrier-type ship that is 5 fields long.
 * @see Ship
 */
class Carrier : public Ship {
private:
    /**
     * @brief Variable that stores the information of: how many objects of Carrier class exist.
     */
    //static int carrierCounter;

public:

    /**
     * @brief Construct a new Carrier object, that is a 5 board-fields-long ship.
     */
    Carrier();

    ~Carrier();
};