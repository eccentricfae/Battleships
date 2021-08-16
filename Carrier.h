/**
 * @file Carrier.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl) 
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#pragma once
#include "Ship.h"

/**
 * @class Carrier
 * @brief Class that represents a carrier-type ship that is 5 fields long.
 * @see Ship
 */
class Carrier : public Ship {
public:
    /**
     * @brief Construct a new Carrier object, that is a 5 board-fields-long ship.
     */
    Carrier();

    ~Carrier();
};