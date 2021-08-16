/**
 * @file PatrolBoat.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#pragma once
#include "Ship.h"

/**
 * @class PatrolBoat
 * @brief Class that represents a patrol-boat-type ship that is 2 fields long.
 * @see Ship
 */
class PatrolBoat : public Ship {
public:
    /**
     * @brief Construct a new PatrolBoat object, that is a 2 board-fields-long ship.
     */
    PatrolBoat();

    ~PatrolBoat();
};