#include "Ship.h"

void Ship::addCoords(const Coords & ref) {
    if (ownCoords.size() < length) {
        ownCoords.emplace_back(ref);
    }
}

/**
 * @note If incorrect health value is passed the function does nothing.  
 */
void Ship::setHealth(const int & health) {
    if (health > -1 && health <= length) {
        this->health = health;
    }
}

bool Ship::damageShip() {
    health--;
    if (health == 0) { return true; }
    else { return false; }
}

/**
 * @details Function iterates over the ownCoords vector, comparing each set of coordinates in the vector (temp) to the coordinates (coordsToCheck) passed as an argument.
 *          If the coordinates are the same the function return true, which means that the *this ship is placed on those coordinates; 
 *          If no matching coordinates are found in the vector, the function return false, which means that the *this ship is not placed on those coordinates.
 */
bool Ship::isOnThoseCoordinates(const Coords & coordsToCheck) const {
    for (Coords temp: ownCoords) {
        if (temp == coordsToCheck) { return true; }
    }
    return false;
}

Ship::Ship(int length) : length(length), health(length) {
    ownCoords.reserve(length);
}

Ship::~Ship() {};