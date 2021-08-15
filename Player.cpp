#include "Player.h"

Player::Player() : shipsLeft(0) {
    // set the boards to 0
    for (Board::iterator it = ownBoard.begin(); it != ownBoard.end(); it++) {
        it->fill(0);
    }
    for (Board::iterator it = radar.begin(); it != radar.end(); it++) {
        it->fill(0);
    }
}

Player::Player(InterfaceIO * i) : Player() {
    interface = i;

    initializePlacingShips();
}

/**
 * @details Function that initializes the placing of 8 ships on the "ownBoard". The function keeps track of how many ships have been placed, and then using that information
 *          it creates in place (at the end of the "playersShips" vector) new object of appropriate type (class). After creating a new object, the function calls "getShipPlacement"
 *          function, so that the newly created ship is placed on the board.
 */
void Player::initializePlacingShips() {
    int shipsPlaced = 0;
    
    while (shipsPlaced < 8) {
        //printBoard(boardId::playersOwnBoard);

        switch(shipsPlaced) {
            case 0:
                //create new ship of type carrier
                playersShips.emplace_back(new Carrier);
                // place carrier
                getShipPlacement(playersShips[shipsPlaced]);
                break;
            
            case 1:
            case 2:
                // create new ship of type battleship
                playersShips.emplace_back(new Battleship);
                //place battleship
                getShipPlacement(playersShips[shipsPlaced]);
                break;
            
            case 3:
            case 4:
            case 5:
                // create new ship of type destroyer
                playersShips.emplace_back(new Destroyer);
                //place destroyer
                getShipPlacement(playersShips[shipsPlaced]);
                break;
            
            case 6:
            case 7:
                // create new ship of type patrol boat
                playersShips.emplace_back(new PatrolBoat);
                //place patrol boat
                getShipPlacement(playersShips[shipsPlaced]);
                break;
        }
        shipsPlaced++;
    }
    
}

/**
 * @details The function first prints player's "ownBoard" and informs what type of ship will be placed.
 *          Then in a loop (until appropriate location is input by the user) location for the ship is asked.
 *          If appropriate location is input, the function calls "placeShipOnTheBoard()" function to place the ship, on the board, in the location that was given.
 *          Inside the function correct exception handling is implemented because of calling functions that throw (interface->inputCoordinates and interface->inputInt).
 */
void Player::getShipPlacement(Ship * ship) {
    printBoard(boardId::playersOwnBoard);
    
    Coords bowCoords; // coords where to place the bow of the ship
    int sternDirection; // direction in which the tail of the ship is supposed to be placed

    // error handling auxillary variables
    bool firstIteration = true;
    bool errorOccured = false;
    std::string errorMessage;

    interface->printText("Bedziesz ustawial na planszy teraz statek typu: " + ship->getTypeOfShip() + '\n');
    interface->printText("Dlugosc tego statku to: " + std::to_string(ship->getLength()) + " pola\n");

    do {

        try {
            if (errorOccured) {
                interface->printText(errorMessage + '\n');
                errorOccured = false;
            }

            if (!firstIteration) {
                interface->printText("Nie mozna tak ustawic statku! Sproboj ponownie:\n");
            }

            interface->printText("Podaj koordynaty gdzie chcesz zaczepic dziob statku: ");
            bowCoords = interface->inputCoordinates();

            interface->printText("Podaj kierunek w jakim ma sie znajdowac rufa statku:\n");
            interface->printText("1. W gore\n");
            interface->printText("2. W prawo\n");
            interface->printText("3. W dol\n");
            interface->printText("4. W lewo\n");
            sternDirection = interface->inputInt(1, 4);

            firstIteration = false;
        }
        catch (std::invalid_argument & e) {
            errorOccured = true;
            errorMessage = e.what();
        }

    } while (errorOccured || !canBePlaced(bowCoords, sternDirection, ship->getLength()));

    placeShipOnTheBoard(bowCoords, sternDirection, ship);
}

void Player::placeShipOnTheBoard(const Coords & bowCoords, const int & sternDirection, Ship * ship) {
    switch (sternDirection) {
        case directions::north :
            for (int row = bowCoords.first; row != bowCoords.first - ship->getLength(); row--) {
                ownBoard[row][bowCoords.second] = 1;
                ship->addCoords(std::make_pair(row, bowCoords.second));
            }
            break;

        case directions::east :
            for (int col = bowCoords.second; col != bowCoords.second + ship->getLength(); col++) {
                ownBoard[bowCoords.first][col] = 1;
                ship->addCoords(std::make_pair(bowCoords.first, col));
            }
            break;

        case directions::south :
            for (int row = bowCoords.first; row != bowCoords.first + ship->getLength(); row++) {
                ownBoard[row][bowCoords.second] = 1;
                ship->addCoords(std::make_pair(row, bowCoords.second));
            }
            break;

        case directions::west :
            for (int col = bowCoords.second; col != bowCoords.second - ship->getLength(); col--) {
                ownBoard[bowCoords.first][col] = 1;
                ship->addCoords(std::make_pair(bowCoords.first, col));
            }
            break;
    }
    shipsLeft++;
}


/**
 * @details This function takes 3 arguments and checks if a ship of length "lengthOfShip" can be placed there, according to the rules (each ship placed on consecutive empty fields;
 *          no ships can touch each other - each field around the ship has to be empty as well). Depending on the provided direction of the stern of the ship (in respect to the
 *          bow of the ship) a one of four chunks of code is executed.
 *          Each chunk of code is responsible for checking if the ship can be placed.
 *          In each chunk of code there are:<br>
 *          3 main conditional statements:<br>
 *              - currently chekced field is in the row/column where we want to place the ship,<br>
 *              - currently checked field is not in the row/column where we want to place the ship and is out of bounds of the board,<br>
 *              - currently checked field is not in the row/column where we want to place the ship and is not out of bounds of the board.<br>
 *          2 special cases, unique to each chunk of code, that have something to do with trying to check if a field out of bounds of the board is empty (those 2 cases are a 
 *          bug fix from previous version where you couldnt place ships on the first/last rows/columns). 
 */
bool Player::canBePlaced(const Coords & bowCoords, const int & sternDirection, const int & lengthOfShip) const {
    switch (sternDirection) {
        case directions::north:

            for (int row = bowCoords.first + 1; row != bowCoords.first - lengthOfShip - 1; row--) {
                for(int col = bowCoords.second - 1; col != bowCoords.second + 2; col++) {
                    //  bow of the ship  "placed" on the 9'th row
                    if (bowCoords.first == 9 && row > 9) {
                        // dont need to check the row below, it is out of bounds so no ships will be there
                        row--;
                        continue;
                    }
                    //  ship "placed" so the stern of the ship would be on the highest possible row (row = 0)
                    else if (bowCoords.first == (lengthOfShip - 1) && row < 0) {
                        // nothing can be above row 0, so no need to check that row
                        // because of how rows are checked: from lowest (on the map; highest value-wise) to highest, this case means:  conditions have been met
                        return true;
                    }

                    if (col != bowCoords.second && isOutOfBounds(row, col)) {
                        // checking the column adjecent to where we want to put the ship, but it is outside the board so no ship can be there
                        continue;
                    }
                    else if (col != bowCoords.second && !isOutOfBounds(row, col)) {
                        // checking the column adjecent to where we want to put the ship and it is on the board:
                        // if the field is not empty -> we cant place the ship based on the arguments passed to this function
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    else {
                        // this is the column where we want to place the ship
                        // check if the field is inside the board and if it is empty
                        if (isOutOfBounds(row, col) || !isFieldEmpty(row, col)) { return false; }
                    }
                }
            }

            break;

        case directions::east:

            for (int row = bowCoords.first - 1; row != bowCoords.first + 2; row++) {
                for (int col = bowCoords.second - 1; col != bowCoords.second + lengthOfShip + 1; col++) {
                    // if the bow of the ship is "placed" on the first column -> no need to check previous column for ships
                    if (bowCoords.second == 0 && col < 0) {
                        continue;
                    }
                    // stern of the ship will be on the last column -> no need to check next column for ships
                    else if (bowCoords.second == (10 - lengthOfShip) && col > 9) {
                        continue;
                    }

                    if (row != bowCoords.first && isOutOfBounds(row, col)) {
                        // checking row adjecent to where we want to place the ship and it is out of bounds so no need to check that row
                        //row++;
                        continue;
                    }
                    else if (row != bowCoords.first && !isOutOfBounds(row, col)) {
                        // checking row adjecent to where we want to place the ship, it is on the board
                        // check if it is empty
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    else {
                        // checking the row where we want to place the ship -> check if inside the board && if empty
                        if (isOutOfBounds(row, col) || !isFieldEmpty(row, col)) { return false; }
                    }
                }
            }

            break;

        case directions::south:

            for (int row = bowCoords.first - 1; row != bowCoords.first + lengthOfShip + 1; row++) {
                for (int col = bowCoords.second - 1; col != bowCoords.second + 2; col++) {
                    
                    if (bowCoords.first == 0 && row < 0) {
                        // if the bow of the ship is "placed" on the first row -> no need to check the row before, no ships will be there
                        row++;
                    }
                    else if (bowCoords.first == (10 - lengthOfShip) && row > 9) {
                        // stern of the boat is "placed" on the last row
                        // if we got here (because of how the fields are checked here (iterating over rows not columns)) it means that the conditions have been met
                        // we can place the ship according to the passed arguments
                        return true;
                    }

                    if (col != bowCoords.second && isOutOfBounds(row, col)) {
                        // column adjecent to where we want to place the ship and outside the board -> no need to check for ships here
                        continue;
                    }
                    else if (col != bowCoords.second && !isOutOfBounds(row, col)) {
                        // column adjecent to where we want to place the ship and inside the board -> check if empty
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    else {
                        // coulmn where we want to place the ship
                        if (isOutOfBounds(row, col) || !isFieldEmpty(row, col)) { return false; }
                    }
                }
            }

            break;
        
        case directions::west:

            for (int row = bowCoords.first - 1; row != bowCoords.first + 2; row++) {
                for (int col = bowCoords.second + 1; col != bowCoords.second - lengthOfShip - 1; col--) {
                    
                    if (bowCoords.second == 9 && col > 9) {
                        // bow of the ship "placed" on the last column -> no need to check the next column, no ships will be there
                        continue;
                    }
                    else if (bowCoords.second == (lengthOfShip - 1) && col < 0) {
                        // stern of the ship "placed" on the first column -> no need to check the previous column, no ships will be there
                        continue; 
                    }

                    if (row != bowCoords.first && isOutOfBounds(row, col)) {
                        continue;
                    }
                    else if (row != bowCoords.first && !isOutOfBounds(row, col)) {
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    else {
                        if (isOutOfBounds(row, col) || !isFieldEmpty(row, col)) { return false; }
                    }
                }
            }

            break;
    }

    // if we got here, the placement of the ship is possible
    return true;
}

/**
 * @details Destructor for the Player class. Deletes every dynamically created object in the "playersShips" vector, resizes it to 0, and shrinks its capacity.
 */
Player::~Player() {
    for (Ship * ship : playersShips) {
        delete ship;
    }
    playersShips.clear();
    playersShips.shrink_to_fit();
}

void Player::printBoard(const int & whichBoard) const {
    switch (whichBoard) {
        case 1:
            interface->printText("Twoja plansza:\n");
            interface->printBoard(ownBoard.cbegin(), ownBoard.cend());
            break;
        case 2:
            interface->printText("Twoj radar:\n");
            interface->printBoard(radar.cbegin(), radar.cend());
            break;
        default:
            interface->printText("Zle wywolanie Player::printBoard()\n");
            break;
    }
}

/**
 * @details Function first asks the player for coordinates where they want to shoot (asks untill appropriate coordinates are input).
 *          Then the function calls getShotAt function to see if the shot was a miss, hit or hit and sunk.
 *          Lastly the function informs (by returning proper boolean value) whether the shot was a hit or a miss.
 */
int Player::shootAt(Player * opponent) {
    Coords coords(-1, -1);
    bool firstIteration = true;

    // get the coordinates where to shoot
    do {
        if (!firstIteration) {
            interface->printText("Juz tam strzelano!\n");
        }

        interface->printText("Podaj koordynaty gdzie chcesz strzelic: ");
        try {
            coords = interface->inputCoordinates();
        }
        catch (std::invalid_argument & e) {
            interface->printText(e.what());
        }
    } while ((coords.first == -1 || coords.second == -1) || alreadyShotThere(coords));

    // shoot at opponent
    int result = opponent->getShotAt(coords);

    if (result == 0) {
        // missed opponent's ships; mark a missed shot on the radar; inform that the player missed shot
        radar[coords.first][coords.second] = 2;
        return 0;
    }
    else if (result == 1) {
        // hit opponent's ship; mark a hit shot on the radar; inform that the player hit, so they can continue firing
        radar[coords.first][coords.second] = 3;
        return 1;
    }
    else {
        // hit opponent's ship and SUNK IT; mark a hit shot on the radar; inform that the player hit, so they can continue firing
        radar[coords.first][coords.second] = 3;
        return 2;
    }
}

/**
 * @details The function first checks if the opponent has hit a ship or not. Whether they missed or hit, their shot is marked on the player's "ownBoard".
 *          Missed shot is met with return value of 0;
 *          If the opponent hits a ship, the hit ship is searched for, then damaged, and lastly the function checks if the hit ship is sunk or not.
 *          Whether the ship has sunken or not, appropriate values are returned (int = 1 if didnt sink; int = 2 if sunk).
 */
int Player::getShotAt(const Coords & coords) {
    if (ownBoard[coords.first][coords.second] != 1) {
        // opponent missed; mark where they shot at; inform that they missed
        ownBoard[coords.first][coords.second] = 2;
        return 0;
    }
    else {
        // opponent hit a ship; mark a hit ship on the board;
        ownBoard[coords.first][coords.second] = 3;

        // find which ship has been hit
        Ship * hitShip;
        for (Ship* ship : playersShips) {
            if (ship->isOnThoseCoordinates(coords)) {
                hitShip = ship;
                break;
            }
        }

        // damage the ship and check if it sunk
        bool sunk = hitShip->damageShip();
        if (sunk) {
            shipsLeft--;
            return 2;
        }
        else {
            return 1;
        }
    }
}