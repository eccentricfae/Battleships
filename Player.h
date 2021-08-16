/**
 * @file Player.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Header file for the implementation of the Player class.
 * 
 * @version 1.0
 * @date 2021-08-08
 */
#pragma once
#include <array>
#include <vector> 
#include <utility> 
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ShipsClasses.h"
#include "IConsole.h"

/**
 * @brief Alias for 2D array of ints (std::array<std::array<int, 10>, 10>) used for more readable code. 
 */
typedef std::array<std::array<int, 10>, 10> Board;

/**
 * @brief Alias for a pair of ints (std::pair<int, int>), used as a coordinates for player board.
 * @see Board
 */
typedef std::pair<int, int> Coords;


/**
 * @class Player
 * @brief Class used to represent the player (user) of the game (program).
 *        Class responsible for majority of the game logic in the "Battleships" game.
 * @see AIPlayer
 * @see Ship
 * @see InterfaceIO 
 */
class Player {
protected:
    /**
     * @brief 2D int array; Player board where the player puts his own ships and tracks where the opponent shoots.
     * @details 2D array of ints, representing one of 10x10 player boards for the game "Battleships". On this board the player places and tracks his own ships,
     *          where the opponent shoots and if they hit/miss. <br>The board is filled with 4 following values: 
     * <br>   0 - the field is empty (no ships are here placed; opponent has not taken a shot at this field yet),
     * <br>   1 - on this field (a part of) a ship is placed, the ship on this field has not been shot,
     * <br>   2 - this field has been shot by the opponent, but the shot has missed (no ships were hit on this field),
     * <br>   3 - on this field a ship was shot and hit.
     */
    Board ownBoard;

    /**
     * @brief 2D int array; Player board where the player keeps track of all their taken shots, and whether they missed or hit enemy's ships.
     * @details 2D array of ints, representing one of 10x10 player boards for the game "Battleships". On this board the player keeps track of all their shots.
     *          The board is filled with the following values:
     * <br>   0 - empty field (no shot aimed at this field has been taken),
     * <br>   2 - missed shot (player shot at this field, but the field was empty),
     * <br>   3 - hit enemy's ship (player shot at this field and hit enemy's ship).
     */
    Board radar;

    /**
     * @brief Vector of pointers to ships placed on player's board (ownBoard).
     */
    std::vector<Ship*> playersShips;

    /**
     * @brief Integer that informs how many ships the player has left (have not been sunk yet).
     */
    int shipsLeft;

    /**
     * @brief Pointer to an interface object responsible for: Input/Output operations; being a graphics engine.
     * @note "interface" will not be an object of InterfaceIO class (abstract class), but an object of derivitave class "hidden" (using runtime polymorphis / pointer conversion)
     *        under the pointer to InterfaceIO class.
     */
    InterfaceIO * interface;

    /**
     * @brief Begins the process of placing 8 ships on the player's board "ownBoard".
     */
    void initializePlacingShips();
    
    /**
     * @brief Loads the ships from the file with saved game.
     * 
     * @param file File from which the ships of the player are to be loaded.
     */
    void initializePlacingShips(std::fstream & file); 

    /**
     * @brief Member function that asks the player where on the board (ownBoard) they would like to place the ship (passed by a pointer).
     *        If appropriate location is input, the function calls the "placeShipOnTheBoard" function.
     * 
     * @param ship Pointer to the ship that is to be placed on the board.
     * @see placeShipOnTheBoard
     */
    virtual void getShipPlacement(Ship * ship);

    /**
     * @brief Member function that places a ship on the "ownBoard" and adds that ship's coordinates to that ship's vector of coordinates.
     * 
     * @param bowCoords Coordinates of where the bow of the ship is supposed to be placed.
     * @param sternDirection Direction of where the stern of the ship is supposed to be placed. 
     * @param ship Pointer to the ship that is being placed.
     * @see Ship
     */
    void placeShipOnTheBoard(const Coords & bowCoords, const int & sternDirection, Ship * ship);

    /**
     * @brief Member function that checks if (according to the game rules) a ship can be placed according to passed arguments.
     * 
     * @param bowCoords Coordinates where the bow of the ship is supposed to be placed.
     * @param sternDirection Direction in which  the stern of the ship is supposed ot be placed.
     * @param lengthOfShip Length of the ship that is to be checked if it can be placed.
     * @return true Ship can be placed according to the passed arguments.
     * @return false Ship cannot be placed according to the passed arguments.
     */
    bool canBePlaced(const Coords & bowCoords, const int & sternDirection, const int & lengthOfShip) const;
    
    /**
     * @brief Member function that checks whether the passed coordinates are NOT on the board (ownBoard / radar) (out of bounds of the 2d array).
     * 
     * @param coords Coordinates to be checked.
     * @return true Passed coordinates are not on either of the player boards.
     * @return false Passed coordinates are on the player boards.
     */
    inline bool isOutOfBounds(const Coords & coords) const;
    /**
     * @brief Member function that checks whether the passed coordinates are NOT on the board (ownBoard / radar) (out of bounds of the 2d array).
     * 
     * @param row Row of a field passed to be checked.
     * @param col Column of a field passed to be checked.
     * @return true Passed coordinates are not on either of the player boards.
     * @return false Passed coordinates are on the player boards.
     */
    inline bool isOutOfBounds(const int & row, const int & col) const;

    /**
     * @brief Member function that returns a boolean whether the coordinates passed as an argument are empty (on the "ownBoard" board, value of 0 on the board).
     * 
     * @param coords Coordinates on the "ownBoard"  to be checked.
     * @return true Field is empty (int value of 0).
     * @return false Field is not empty (int value != 0).
     */
    inline bool isFieldEmpty(const Coords & coords) const;
    /**
     * @brief Member function that returns a boolean whether the coordinates passed as an argument are empty (on the "ownBoard" board, value of 0 on the board).
     * 
     * @param row Row of the field passed to be checked.
     * @param col Column of the field passed to be checked.
     * @return true Field is empty (int value of 0).
     * @return false Field is not empty (int value != 0).
     */
    inline bool isFieldEmpty(const int & row, const int & col) const;

    /**
     * @brief Member function that tells whether the player has already taken a shot at the field pointed to by the arguments.
     * 
     * @param coords Coordinates of the "radar" board to be checked.
     * @return true Player has already taken a shot at this field.
     * @return false Player has not yet taken a shot at this field.
     */
    inline bool alreadyShotThere(const Coords & coords) const;
    /**
     * @brief Member function that tells whether the player has already taken a shot at the field pointed to by the arguments.
     * 
     * @param row Row of the field on the "radar" board to be checked.
     * @param col Column of the field on the "radar" board to be checked.
     * @return true Player has already taken a shot at this field.
     * @return false Player has not yet taken a shot at this field.
     */
    inline bool alreadyShotThere(const int & row, const int & col) const;

    /**
     * @brief Protected nullary constructor that sets ownBoard and radar to 0, and sets shipsLeft to 0 and interface to nullptr.
     */
    Player();

    /**
     * @enum directions
     * @brief Enumeration of directions for more understandable code in regards to: ship placing functions.
     */
    enum directions {
        north = 1,
        east = 2,
        south = 3,
        west = 4,
    };

public:

    /**
     * @brief Construct a new Player object.
     * 
     * @param i Pointer to the object responsible for being the input/output interface.
     * 
     * @see InterfaceIO
     */
    Player(InterfaceIO * i);

    /**
     * @brief Load and construct the Player object from file with saved game.
     * 
     * @param i Pointer to the object responsible for being the input/output interface.
     * @param file Object serving as the anchor of the file from which the game/object state is to be loaded.
     */
    Player(InterfaceIO * i, std::fstream & file);

    /**
     * @brief Destroy the Player object and all dynamically allocated member variables / objects.
     */
    virtual ~Player();

    /**
     * @brief Print (or update) the "ownBoard" or "radar" player board on the screen. 
     * 
     * @param whichBoard Argument which board to print: 1 for "ownBoard"; 2 for "radar".
     */
    void printBoard(const int & whichBoard) const;

    /**
     * @brief Shoot at the opponent's board with ships. 
     * 
     * @param opponent Pointer to the opponent (object of class Player or derivative).
     * @return int: 0 - missed; 1 - succesfully hit a ship; 2 - hit and sunk a ship!.
     * @see getShotAt 
     */
    virtual int shootAt(Player * opponent);

    /**
     * @brief Member function that informs the player that the opponent has taken a shot at their board.
     * 
     * @param coords Coordinates of the opponent's shot. 
     * @return int Result of the shot: int = 0 - opponent missed; int = 1 - opponent hit; int = 2 - opponent hit and sunk a ship
     * @see shootAt
     */
    int getShotAt(const Coords & coords);

    /**
     * @brief Member function that checks if *this player lost the game (by checking how many ships *this player has left).
     * 
     * @return true Player lost the game (0 ships unsunken remaining).
     * @return false Player didn't yet lose the game (at lesat 1 unsunken ship remaining).
     */
    inline bool lost() const;

    /**
     * @enum boardId
     * @brief Enumeration of idientifiers for player's boards (ownBoard and radar) for "printBoard()" member function. ""
     */
    enum boardId {
        playersOwnBoard = 1,
        radarBoard = 2,
    };

    /**
     * @brief Save current state of *this object to a file.
     * 
     * @param file Object serving as the anchor of the file to which the state of the class is to be saved.
     */
    virtual void saveClassToFile(std::fstream & file) const;

};

bool Player::isFieldEmpty(const Coords & coords) const {
    if (ownBoard[coords.first][coords.second] == 0) { return true; }
    else { return false; }
}

bool Player::isFieldEmpty(const int & row, const int & col) const {
    if (ownBoard[row][col] == 0) { return true; }
    else { return false; }
}

bool Player::isOutOfBounds(const Coords & coords) const {
    if ( (coords.first > 9 || coords.first < 0) || (coords.second > 9 || coords.second < 0) ) { return true; }
    else { return false; }
}

bool Player::isOutOfBounds(const int & row, const int & col) const {
    if ( (row > 9 || row < 0) || (col > 9 || col < 0) ) { return true; }
    else { return false; }
}

bool Player::alreadyShotThere(const Coords & coords) const {
    if (radar[coords.first][coords.second] == 0) { return false; }
    else { return true; }
}

bool Player::alreadyShotThere(const int & row, const int & col) const {
    if (radar[row][col] == 0) { return false; }
    else { return true; }
}

bool Player::lost() const {
    return (shipsLeft == 0) ? true : false;
}