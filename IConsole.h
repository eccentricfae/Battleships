#pragma once
#include "InterfaceIO.h"
#include <iostream>

class IConsole : public InterfaceIO {
public:
    /**
     * @brief Member function that prints the playing board, using two forward iterators passed as arguments.
     * 
     * @param iteratorBegin Iterator to the first element of the 2D-Array (Board.begin())
     * @param iteratorEnd  Iterator that signals the end of the container (Board.end())
     * @see Board
     * @see Player
     */
    void printBoard(const Board::const_iterator & iteratorBegin, const Board::const_iterator & iteratorEnd) override;
    // ^ check if works

    /**
     * @brief Member function that prints text, passed as an arugment of type std::string (no new line character).
     * 
     * @param text Text to be printed.
     */
    inline void printText(const std::string & text) override;

    /**
     * @brief Member function that reads user input and returns value of type int, if the input is in the given range.
     * 
     * @param firstElementInRange First element of the specified range of integers; default value of INT_MIN;
     * @param lastElementInRange Last element of the specified range of integers, default value of INT_MAX;
     * @return int Integer number read from the user input.
     * @throws std::invalid_argument If the user inputs argument out of range or argument of incorrect type, the functions throws exception.
     * @note This function can be called without providing the range arguments, so it would function as a function that just reads an integer from the user, not checking for range.
    */
    int inputInt(const int & firstElementInRange = INT_MIN, const int & lastElementInRange = INT_MAX) override;

    /**
     * @brief Member function that reads user input and returns coordinates to be used with the player board.
     * 
     * @return Coords Coordinates read from the user input. 
     * @see Coords
     * @throws std::invalid_argument If the user inputs data that isn't in the proper format as to be used as board coordinates, the function will throw an exception.
     */
    Coords inputCoordinates() override;

    /**
     * @brief Member function that prints instructions of how to play the Battleships game, and use the program.
     */
    void printInstructions() override;
    // ^ define in .cpp

    /**
     * @brief Member function that prints rules of the Battleships game on screen.
     */
    void printRules() override;
    // ^ define in .cpp

    ~IConsole() {}
};

void IConsole::printText(const std::string & text) {
    std::cout << text;
}