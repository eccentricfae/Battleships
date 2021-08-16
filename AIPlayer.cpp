/**
 * @file AIPlayer.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Source file for the AIPlayer.h header file.
 * 
 * @version 1.0
 * @date 2021-08-08
 */
#include "AIPlayer.h"

AIPlayer::AIPlayer(InterfaceIO * i) : Player() {
    interface = i;
    lastShotHit = false;

    initializePlacingShips();
}

AIPlayer::AIPlayer(InterfaceIO * i, std::fstream & file) : Player(i, file) {
    std::string currentLine;

    getline(file, currentLine);

    // load lastShotHit from file
    int lastShotHitInt = (int)(currentLine[0] - '0');
    lastShotHit = (lastShotHitInt == 1) ? true : false;

    // load lastShotCoords from file
    lastShotCoords.first = (int)(currentLine[1] - '0');
    lastShotCoords.second = (int)(currentLine[2] - '0');
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

void AIPlayer::saveClassToFile(std::fstream & file) const {
    //save all the basic data
    Player::saveClassToFile(file);

    file << lastShotHit << lastShotCoords.first << lastShotCoords.second;

}