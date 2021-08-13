/**
 * @file Ships.h
 * @brief Header file for the abstract class Ship.
 * 
 * @version 0.9
 * @date 2021-08-08
 */

 #pragma once
 #include <vector>
 #include <utility>

/**
 * @brief Alias for std::pair<int, int>; used to indicate coordinates for the player boards in "Player" and "AIPlayer" classes.
 * @see Player
 */
 typedef std::pair<int, int> Coords;

/**
 * @class Ship
 * @brief Abstract class used as a base class for derivitive ships (classes).
 * @details This abstract class implements majority of the functionality of the derivitive classes. The pure virtual function that makes it an abstract class is pure virtual destructor.
 * @see Carrier
 * @see Destroyer
 * @see Battleship
 * @see PatrolBoat
 */
class Ship {
protected:
    /**
     * @brief Health of a ship. Each type of ship has different amount of starting health. At the start the health is equal the length of a ship.
     */
    int health;

    /**
     * @brief Length of a ship, measured by how many fields the ship takes on the board.
     */
    const int length;

    /**
     * @brief Vector of coordinates that the ship is placed on. Length of the vector is equal the length of the ship.
     */
    std::vector<Coords> ownCoords;

public:
    /**
     * @brief Member function that assigns passed coordinates to the ship.
     * 
     * @param coordinates Coordinates that are to be assigned to the ship. 
     * @see ownCoords
     */
    void addCoords(const Coords & coordinates);

    /**
     * @brief Get the length of the ship.
     * 
     * @return int Length of the ship.
     */
    inline int getLength() const;

    /**
     * @brief Get the health of the ship.
     * 
     * @return int Current health of the ship.
     */
    inline int getHealth() const;

    // ! inline std::vector<Coords>::const_iterator getCoordsVector() const;

    /**
     * @brief Change the health of the ship.
     * 
     * @param health Health value to be set.
     * 
     * @note This member function should be used only for setting the health of the ship while constructing the Ship object from the file (loading the game from file.)
     */
    void setHealth(const int & health);

    /**
     * @brief Damages the ship by one health point. If the ship sinks as a result of the dealt damage, the function returns bool value equal true.
     * 
     * @return true The ship has sunk.
     * @return false The ship didn't sink.
     */
    bool damageShip();

    /**
     * @brief Member function that checks if *this object (ship) is placed on coordinates passed as an argugment.
     * 
     * @param ref Coordinates to be checked if *this ship is placed on them.
     * @return true Ship is placed on coordinates passed as an argument.
     * @return false Ship is not placed on coordinates passed as an argument.
     */
    bool isOnThoseCoordinates(const Coords & coordinates) const;

    /**
     * @brief Construct a new Ship object.
     * 
     * @param length Length of the created ship.
     */
    Ship(int);

    /**
     * @brief Virtual destructor for the Ship class.
     * @note This is pure virtual destructor implemented so that the class Ship would be an abstract class.
     */
    virtual ~Ship() = 0;

};

int Ship::getLength() const {
    return length;
}

int Ship::getHealth() const {
    return health;
}