#include "AIPlayer.h"

/**
 * @details This nullary constructor does not call Player(InterfaceIO*) but Player(), because of that constructor default argument (nullptr), which in turn executes 
 *          fragment of code in Player::Player() constructor resposible for generating a seed for generating random numbers (not needed in Player class but very much needed in
 *          the AIPlayer class).
 */
AIPlayer::AIPlayer() : Player() {
    lastShotHit = false;
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

// ! details ?
bool AIPlayer::shootAt(Player * opponent) {
    Coords coords;
    //generate coords where to shoot
    do {
        if (lastShotHit) {
            // shoot somewhere around the last shot
            coords = lastShotCoords;
            int direction = generateRandomDirection();

            switch (direction) {
                case 1:
                    // shoot above last shot; if above is out of bounds -> shoot below
                    if (coords.first - 1 < 0) { coords.first += 1; }
                    else { coords.first -= 1; }
                    break;
                
                case 2:
                    // shoot to the right of the last shot; if to the right is out of bounds -> shoot to the left
                    if (coords.second + 1 > 9) { coords.second -= 1; }
                    else { coords.second += 1; }
                    break;

                case 3:
                    // shoot below the last shot; if below is out of bounds -> shoot above
                    if (coords.first + 1 > 9) { coords.first -= 1; }
                    break;
                
                case 4:
                    // shoot to the left of the last shot; if to the left is out of bounds -> shoot to the right
                    if (coords.second - 1 < 0) { coords.second += 1; }
                    else { coords.second -= 1; }
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
        return false;
    }
    else if (result == 1) {
        radar[coords.first][coords.second] = 3;
        lastShotHit = true;
        return true;
    }
    else {
        radar[coords.first][coords.second] = 3;
        // false becuase this shot sunk a ship; the AI is supposed to search for new ships and not shoot around already sunk ship
        lastShotHit = false; 
        return true;
    }
}