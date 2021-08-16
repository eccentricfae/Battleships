/**
 * @file Battleship.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#pragma once
#include "Ship.h"

/**
 * @class Battleship
 * @brief Class that represents a battleship-type ship, that is 4 board-fields long.
 * @see Ship
 */
class Battleship : public Ship {
public:
    /**
     * @brief Construct a new Battleship object, that is a 4 board-fields-long ship.
     */
    Battleship();

    ~Battleship();
};