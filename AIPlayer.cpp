#include "AIPlayer.h"

AIPlayer::AIPlayer(InterfaceIO * i) : Player() {
    interface = i;
    srand(time(0));
    initShips();
    shipsLeft = 7;
}

AIPlayer::AIPlayer(const std::string & filePath, const std::streampos & pos) : Player(filePath, pos) {
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.good()) {
        throw std::runtime_error("Nie udalo sie otworzyc pliku!");
    }
    file.seekg(pos);
    std::string line;
    std::getline(file, line);
    lastShotWasAHit = (bool)((int)(line[0] - '0') );
    lastShotCoords.first = (int)(line[2] - '0');
    lastShotCoords.second = (int)(line[3] - '0');
}

// 1 carrier, 1 battleship, 2 - destroyers, 3 patrol boats
void AIPlayer::initShips() {
    ships.emplace_back(new Carrier);
    placeNewShip(ships[0]);

    ships.emplace_back(new Battleship);
    placeNewShip(ships[1]);

    ships.emplace_back(new Destroyer);
    placeNewShip(ships[2]);

    ships.emplace_back(new Destroyer);
    placeNewShip(ships[3]);

    ships.emplace_back(new PatrolBoat);
    placeNewShip(ships[4]);

    ships.emplace_back(new PatrolBoat);
    placeNewShip(ships[5]);

    ships.emplace_back(new PatrolBoat);
    placeNewShip(ships[6]);
    
}

void AIPlayer::placeNewShip(Ship * ship) {
    bool goodSpot = false;
    Coords bowCoords;
    int direction;

    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        bowCoords = genRandomCoords();
        direction = genRandomDirection();
    } while (!canBePlaced(bowCoords, direction, ship->getLength()));

    // can be placed in current bowCoords and direction
    switch(direction) {
        case 1:
            for(int row = bowCoords.first; row != bowCoords.first - ship->getLength(); row--) {
                ownBoard[row][bowCoords.second] = 1;
                ship->addCoords(row, bowCoords.second);
            }
            break;
        
        case 2:
            for(int col = bowCoords.second; col != bowCoords.second + ship->getLength(); col++) {
                ownBoard[bowCoords.first][col] = 1;
                ship->addCoords(bowCoords.first, col);
            }
            break;
        
        case 3:
            for(int row = bowCoords.first; row != bowCoords.first + ship->getLength(); row++) {
                ownBoard[row][bowCoords.second] = 1;
                ship->addCoords(row, bowCoords.second);
            }
            break;
        
        case 4:
            for(int col = bowCoords.second; col != bowCoords.second - ship->getLength(); col--) {
                ownBoard[bowCoords.first][col] = 1;
                ship->addCoords(bowCoords.first, col);
            } 
            break;
    }
}

int AIPlayer::shootAt(Player * rhs) {
    // generate coords where to shoot
    Coords coords;
    do {
        if (lastShotWasAHit) {
            //shoot around there in random direction
            coords = lastShotCoords;
            int direction = genRandomDirection();
            
            switch(direction) {
                case 1:
                    // shoot above
                    // check if it is out of bounds, and if it is then shoot below
                    if (coords.first - 1 < 0) { coords.first += 1; }
                    else { coords.first -= 1; }
                    break;
                case 2:
                    // shoot to the right
                    if (coords.second + 1 > 9) { coords.second -= 1; }
                    else { coords.second += 1; }
                    break;
                case 3:
                    // shoot below
                    if (coords.first + 1 > 9) { coords.first -= 1; }
                    else { coords.first += 1; }
                    break;
                case 4:
                    // shoot to the left
                    if (coords.second - 1 < 0) { coords.second += 1; }
                    else { coords.second -= 1; }
                    break;
            }
        }
        else {
            coords = genRandomCoords();
        }
    } while(alreadyShotThere(coords));

    int result = rhs->getShotAt(coords);
    lastShotCoords = coords;

    if (result == 0) {
        radar[coords.first][coords.second] = 2;
        lastShotWasAHit = false;
        return 0;
    }
    else if (result == 1) {
        radar[coords.first][coords.second] = 3;
        lastShotWasAHit = true;
        return 1;
    }
    else {
        radar[coords.first][coords.second] = 3;
        // tutaj false bo zatopil wiec chcemu zeby szukal celu gdzies indziej 
        // a nie dalej strzelal w to samo miejsce
        lastShotWasAHit = false;
        return 2;
    }
}

void AIPlayer::saveGameToFile() const {
    Player::saveGameToFile();
    
    std::fstream file;
    file.open("battleships_saved_game.txt", std::ios::out | std::ios::app);
    if (!file.good()) {
        throw std::runtime_error("Nie udalo sie otwrozyc pliku!");
    }

    file << lastShotWasAHit << " " << lastShotCoords.first << lastShotCoords.second;

    file.close();
}
