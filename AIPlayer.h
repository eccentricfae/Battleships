/**
 * @file AIPlayer.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Header file for the implementation of the AIPlayer class used by the logic in the main.cpp file
 * 
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#pragma once
#include "Player.h"

class AIPlayer : public Player {
private:
    /**
     * @brief Boolean that serves as a "memory" whether AI's last shot was a hit or miss.
     */
    bool lastShotHit;

    /**
     * @brief Variable that serves as a "memory" about where the AI's last shot was.
     */
    Coords lastShotCoords;

    /**
     * @brief Member function where the AI places a ship (passed as an argument) on its "ownBoard".
     * 
     * @param ship Pointer to the ship object to be placed on the board "ownBoard".
     */
    void getShipPlacement(Ship * ship) override;

    /**
     * @brief Member function that generates random coordinates.
     * 
     * @return Coords Random coordinates to be used on "ownBoard" or "radar" boards.
     */
    inline Coords generateRandomCoords() const;

    /**
     * @brief Member function that generates a random integer from the range [1, 4].
     * 
     * @return int Random int from range [1, 4].
     * @note The main use of this function is: getting random direction when the AI tries to place its ships on its board.
     */
    inline int generateRandomDirection() const;

public:
    /**
     * @brief Construct a new AIPlayer object.
     * 
     * @param i Pointer to the object serving as an input/output interface.
     */
    AIPlayer(InterfaceIO * i);

    /**
     * @brief Construct a new AIPlayer object from the saved game state file.
     * 
     * @param i Pointer to the object serving as an input/output interface.
     * @param file Object serving as the anchor of the file from which the game/object state is to be loaded.
     */
    AIPlayer(InterfaceIO * i, std::fstream & file);

    ~AIPlayer() {}

    /**
     * @brief Member function that "shoots" at another player's board with ships. 
     * 
     * @param opponent Pointer to the opponent (object of class Player or derivative).
     * @return int: 0 - missed; 1 - hit a ship; 2 - hit and sunk a ship!.
     * @see getShotAt 
     */
    int shootAt(Player * opponent) override;
    
    /**
     * @brief Save current state of *this object to a file.
     * 
     * @param file Object serving as the anchor of the file to which the state of the class is to be saved.
     */
    void saveClassToFile(std::fstream & file) const override;

};

Coords AIPlayer::generateRandomCoords() const {
    return std::make_pair(rand() % 10, rand() % 10);
}

int AIPlayer::generateRandomDirection() const {
    return (rand() % 4) + 1;
}