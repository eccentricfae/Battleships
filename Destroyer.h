/**
 * @file Destroyer.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#pragma once
#include "Ship.h"

/**
 * @class Destroyer
 * @brief Class that represents a destroyer-type ship that is 3 fields long.
 * @see Ship
 */
class Destroyer : public Ship {
public:
    /**
     * @brief Construct a new Destroyer object, that is a 3 board-fields-long ship.
     */
    Destroyer();

    ~Destroyer();
};