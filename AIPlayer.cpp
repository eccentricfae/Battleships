#include "AIPlayer.h"

/**
 * @details This nullary constructor does not call Player(InterfaceIO*) but Player(), because of that constructor's default argument (nullptr), which in turn executes 
 *          fragment of code in Player::Player() constructor resposible for generating a seed for generating random numbers (not needed in Player class but very much needed in
 *          the AIPlayer class).
 */
AIPlayer::AIPlayer() : Player() {
    lastShotHit = false;

    initializePlacingShips();
}

/**
 * @details The function works in a "naive way": AI generates random coordinates for the bow of the ship and random direction for the stern of the ship until a ship can be placed
 *          in accordance with aforementioned randomly genereated variables. 
 */
void AIPlayer::getShipPlacement(Ship * ship) {
    bool goodSpot = false;
    Coords bowCoords;
    int sternDirection;

    do {
        // ! sleep here if the computer generates the same random things all the time (program crashes / goes on a endless loop)
        bowCoords = generateRandomCoords();
        sternDirection = generateRandomDirection();
    } while (!canBePlaced(bowCoords, sternDirection, ship->getLength()));

    placeShipOnTheBoard(bowCoords, sternDirection, ship);
}

/**
 * @details This function let's AI generate where to take a shot at the opponent's board. First, if AI's last shot hit a ship, the function tries to take another shot
 *          somewhere around the last shot's coordinates by generating random direction and shooting at a field one step removed from the last shot's coordinates in that direction.
 *          If that generated field is out of bounds of the board, the function takes a shot in the opposite direction.
 *          If the AI's last shot was a miss, the function shoots at a random field on the opponent's board.
 *          Then, according to the result of the shot, function marks that shot on the "radar" board and returns appropriate boolean value (true if hit, false if missed). 
 */
int AIPlayer::shootAt(Player * opponent) {
    Coords coords;
    int antiBugLoopProtection = 0; // ! document?
    int moveByXFields = 1; // ! document?

    do {
        if (lastShotHit) {

            antiBugLoopProtection++;
            if (antiBugLoopProtection > 50) {
                antiBugLoopProtection = 0;
                moveByXFields++;
            }
            // ! do this loop prottection or +/- 2, 3 etc if enough times this looped?
            
            // shoot somewhere around the last shot
            coords = lastShotCoords;
            int direction = generateRandomDirection();

            switch (direction) {
                case 1:
                    // shoot above last shot; if above is out of bounds -> shoot below
                    if (coords.first - moveByXFields < 0) { coords.first += moveByXFields; }
                    else { coords.first -= moveByXFields; }
                    break;
                
                case 2:
                    // shoot to the right of the last shot; if to the right is out of bounds -> shoot to the left
                    if (coords.second + moveByXFields > 9) { coords.second -= moveByXFields; }
                    else { coords.second += moveByXFields; }
                    break;

                case 3:
                    // shoot below the last shot; if below is out of bounds -> shoot above
                    if (coords.first + moveByXFields > 9) { coords.first -= moveByXFields; }
                    break;
                
                case 4:
                    // shoot to the left of the last shot; if to the left is out of bounds -> shoot to the right
                    if (coords.second - moveByXFields < 0) { coords.second += moveByXFields; }
                    else { coords.second -= moveByXFields; }
                    break;
            }
        }
        else {
            coords = generateRandomCoords();
        }
    } while (alreadyShotThere(coords));

    int result = opponent->getShotAt(coords);
    lastShotCoords = coords;

    if (result == 0) {
        radar[coords.first][coords.second] = 2;
        lastShotHit = false;
        return 0;
    }
    else if (result == 1) {
        radar[coords.first][coords.second] = 3;
        lastShotHit = true;
        return 1;
    }
    else {
        radar[coords.first][coords.second] = 3;
        // false becuase this shot sunk a ship; the AI is supposed to search for new ships and not shoot around already sunk ship
        lastShotHit = false; 
        return 2;
    }
}