/**
 * @file Ships.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Header file for the abstract class Ship.
 * @version 1.0
 * @date 2021-08-08
 */

 #pragma once
 #include <vector>
 #include <utility>
 #include <string>

/**
 * @brief Alias for std::pair<int, int>; used to indicate coordinates for the player's board in "Player" and "AIPlayer" classes.
 * @see Player
 */
 typedef std::pair<int, int> Coords;

/**
 * @class Ship
 * @brief Abstract class used as an auxilliary class for the Player and AIPlayer classes. Base class for derivitive ship classes.
 * @details This abstract class implements majority of the functionality of the derivitive classes. 
 *          The pure virtual function that makes it an abstract class is a pure virtual destructor.
 * @see Carrier
 * @see Destroyer
 * @see Battleship
 * @see PatrolBoat
 */
class Ship {
protected:
    /**
     * @brief Health of a ship. Each type of ship has different amount of starting health. At the start of the game the health of a ship is equal to the length of that ship.
     */
    int health;

    /**
     * @brief Length of a ship, measured by how many fields the ship takes up on the board.
     */
    const int length;

    /**
     * @brief Direction (expressed as an integer) in which the stern of the ship is placed, compared to the bow of the same ship.
     *        1 is North (up on the board), 2 is East (right on the board), 3 is South (down on the board), 4 is West (left on the board).
     */
    int sternDirection;

    /**
     * @brief Type of the ship, like: "Carrier", "Battleship", etc.
     */
    std::string typeOfShip;

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
    inline void addCoords(const Coords & coordinates);

    /**
     * @brief Set the sternDirection field, that represents the direction in which the stern of the ship is placed in regard to the bow of the ship.
     * 
     * @param sternDirection Direction of the stern of the ship in regards to the bow of the ship.
     */
    void setSternDirection(const int & sternDirection);
    
    /**
     * @brief Get the sternDirection field, that represents the direction in which the stern of the ship is placed in regard to the bow of the ship.
     * 
     * @return int Direction of the stern of the ship in regards to the bow of the ship.
     */
    inline int getSternDirection() const;
    
    /**
     * @brief Get the coordinates of where the bow of this ship is placed on the board.
     * 
     * @return Coords Coordinates of the bow of the ship.
     */
    inline Coords getBowCoords() const;

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

    /**
     * @brief  Get the type (name) of *this ship.
     * 
     * @return std::string Type of *this ship.
     */
    inline std::string getTypeOfShip() const;

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
    Ship(int length);

    /**
     * @brief Virtual destructor for the Ship class.
     * @note This is pure virtual destructor implemented so that the class Ship would be an abstract class.
     */
    virtual ~Ship() = 0;

};

void Ship::addCoords(const Coords & ref) {
    if (ownCoords.size() < length) {
        ownCoords.emplace_back(ref);
    }
}

int Ship::getSternDirection() const {
    return sternDirection;
}

int Ship::getLength() const {
    return length;
}

int Ship::getHealth() const {
    return health;
}

std::string Ship::getTypeOfShip() const {
    return typeOfShip;
}

Coords Ship::getBowCoords() const {
    return ownCoords[0];
}