/**
 * @file Interface.h
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Header file for the declaration of the "Input/Output Interface" abstract class.
 * 
 * @version 0.9
 * @date 2021-08-08
 */

#pragma once
#include <array>
#include <utility>
#include <string>
#include <limits>

/**
 * @brief Alias for 2D std::array container, used as a board on which the game is played. 
 * @see Player
 */
typedef std::array<std::array<int, 10>, 10> Board;

/**
 * @brief Alias for std::pair<int, int>; used to indicate coordinates for the player boards in "Player" and "AIPlayer" classes.
 * @see Player
 */
typedef std::pair<int, int> Coords;

/**
 * @class InterfaceIO
 * @brief Abstract class used as a blueprint for derivitive classes used as a Input / Output interface.
 *        InterfaceIO class has declarations (in the form of pure virtual member functions) of all of the functionality that is required for the Battleships game to
 *        properly function.
 * 
 * @warning This class is a blueprint to be implemented as a in-console-style interface.
 *          Depending of the implementation of the interface by a third party, especially if pop-out-window (traditional desktop window applciation) style of interface is implemented,
 *          special care and thought should be paid to this "blueprint" abstract class about how to correctly implement following functionality.  
 */
class InterfaceIO {
public:
    /**
     * @brief Member function that prints / updates the playing board, using two iterators passed as arguments.
     * 
     * @param iteratorBegin Iterator to the first element of the 2D-Array (Board.begin())
     * @param iteratorEnd  Iterator that signals the end of the container (Board.end())
     * @see Board
     * @see Player
     */
    virtual void printBoard(const Board::const_iterator & iteratorBegin, const Board::const_iterator & iteratorEnd) = 0;

    /**
     * @brief Member function that prints text, passed as an arugment of type std::string.
     * 
     * @param text Text to be printed.
     */
    virtual void printText(const std::string & text) = 0;

    // ! virtual void clearScreen() = 0;

    /**
     * @brief Member function that reads user input and returns value of type int, if the input is in the given range.
     * 
     * @param firstElementInRange First element of the specified range of integers.
     * @param lastElementInRange Last element of the specified range of integers.
     * @return int Integer number read from the user input.
     * @throws std::invalid_argument If the user inputs argument out of range or argument of incorrect type, the functions throws exception. 
     * @note This function should have the ability to be called without providing the range arguments (so it uses default argument values), 
     * so it would function as a function that just reads an integer from the user, not "caring" for range. 
     */
    virtual int inputInt(const int & firstElementInRange = INT_MIN, const int & lastElementInRange = INT_MAX) = 0;

    // ! delete this function and just use the one above with INT_MIN INT_MAX as default arguments?
    /**
     * @brief Member function that reads user input and returns value of type int.
     * 
     * @return int Integer number read from the user input.
     * @throws std::invalid_argument If the user inputs argument of incorrect type, the function throws exception.
     */
    //virtual int inputInt() = 0;

    /**
     * @brief Member function that reads user input and returns coordinates to be used with the player board.
     * 
     * @return Coords Coordinates read from the user input. 
     * @see Coords
     * @throws std::invalid_argument If the user inputs data that isn't in the proper format as to be used as board coordinates, the function will throw an exception.
     */
    virtual Coords inputCoordinates() = 0;

    /**
     * @brief Member function that prints instructions of how to play the Battleships game, and use the program.
     */
    virtual void printInstructions() = 0;

    /**
     * @brief Member function that prints rules of the Battleships game on screen.
     */
    virtual void printRules() = 0;

    virtual ~InterfaceIO() {}
};