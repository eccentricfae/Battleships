#include "IConsole.h"

/**
 * @details This function takes in two const_iterators (const so it doesnt modify anything in the actual board), and uses them to print out the board pointed to by aforementioned iterators.
 *          First the column idientifiers are printed out (numbers 0-9), then variable "rowIdientifierLetter" is declared (used for printing out the row idientifiers), and auxillary iterator "column" that points
 *          to const int, because iteratorBegin points to an array of 10 ints. 
 *          After printing out row idientifier the letter is incremented, and a row of values from the board is printed out.
 */
void IConsole::printBoard(const Board::const_iterator & iteratorBegin, const Board::const_iterator & iteratorEnd) {
    Board::const_iterator row = iteratorBegin;
    
    // print columnumn idientifiers - from o to 9
    std::cout << "\t";
    for (int i = 0; i < 10; i++) {
        std::cout << i;
    }

    
    std::cout << "\n\n";
    char rowIdientifierLetter = 'A';
    std::array<int, 10>::const_iterator column;

    // print row idientifiers (letters from A to J), space for aesthethics / readability, and a row of the board
    for (/*row*/; row != iteratorEnd; row++) {
        std::cout << "     " << rowIdientifierLetter << "  ";
        rowIdientifierLetter++;
        for (column = row->begin(); column != row->end(); column++) {
            switch(*column) {
                case 0: std::cout << "~"; break;
                case 1: std::cout << "S"; break;
                case 2: std::cout << "."; break;
                case 3: std::cout << "X"; break;
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

/**
 * @details Function reads user input, if the input is of wrong type (std::cin.fail() = true) or is out of range the function: clears the error flag (failbit or badbit is set);
 *          ignores what was left in the input stream (so that I/O stream works correctly); and throws an exception.
 *          If a correct number was input by the user, the funciton just returns that number.
 */
int IConsole::inputInt(const int & firstElementInRange /*= INT_MIN*/, const int & lastElementInRange /*= INT_MAX*/) {
    // read user input
    int userInput;
    std::cin >> userInput;

    if (std::cin.fail() || (userInput < firstElementInRange || userInput > lastElementInRange)) {
        std::cin.clear();
        std::cin.ignore(999, '\n');
        throw std::invalid_argument("Podano zly argument");
    }
    else {
        return userInput;
    }
}

/**
 * @details The function reads user input. If the input is of different length than 2 characters, the function throws an exception, because the input is not in the format of board coordinates.
 *          If the format of the input is correct the function checks if the first and second characters in the input are of correct format for their respective rows and columns idientifiers:
 *          Rows are idientified by letters from A to J; columns - by numbers from 0 to 9.
 *          If the input is semantically and syntactically correct, the function converts the input to two integers, and returns them in the form of std::pair container.
 */
Coords IConsole::inputCoordinates() {
    std::string userInput;
    std::cin >> userInput;
    // ! delete or leave the "std::cin.fail()" part?
    if (userInput.length() != 2) {
        throw std::invalid_argument("Podano zly argument!");
    }

    if (std::toupper(userInput[0]) > 'J' || std::toupper(userInput[0]) < 'A') {
        throw std::invalid_argument("Pierwsza skladowa koordynatow jest zla! Powinna to byc litera od 'A' do 'J'.");
    }

    if (userInput[1] > '9' || userInput[1] < '0') {
        throw std::invalid_argument("Druga skladowa koordynatow jest zla! Powinna to byc cyfra od 0 do 9.");
    }

    int firstCoord = (int)(std::toupper(userInput[0]) - 'A'/*(char)65*/);
    int secondCoord = (int)(userInput[1] - '0'/*(char)48*/);

    return std::make_pair(firstCoord, secondCoord);
}

void IConsole::printInstructions() {
    std::cout << "not yet implemented";
}

void IConsole::printRules() {
    std::cout << "not yet implemented";
}