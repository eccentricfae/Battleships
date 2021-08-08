#include "Player.h"

Player::Player() {
    // set the boards to 0
    for(Board::iterator it = ownBoard.begin(); it!= ownBoard.end(); it++) {
        it->fill(0);
    }
    for(Board::iterator it = radar.begin(); it!= radar.end(); it++) {
        it->fill(0);
    }
}

Player::Player(InterfaceIO * i) : interface(i) {
    // set the boards to 0
    for(Board::iterator it = ownBoard.begin(); it!= ownBoard.end(); it++) {
        it->fill(0);
    }
    for(Board::iterator it = radar.begin(); it!= radar.end(); it++) {
        it->fill(0);
    }
    // create and place 8 ships on the board
    int shipsPlaced = 0;
    int choice;
    bool errorOccured = false;
    std::string errorMessage;
    while (shipsPlaced < 7) {
        try {
            interface->clearScreen();
            if (errorOccured) {
                interface->printMsg(errorMessage + "\n");
            }
            errorOccured = false;
            printBoard(1);

            interface->printMsg("Prosze wybrac jaki statek chcesz umiescic na planszy");
            interface->printMsg("1. Lotniskowiec  (zajmuje 5 pol, max 2 sztuki)");
            interface->printMsg("2. Pancernik (zajmuje 4 pola, max 2 sztuki)");
            interface->printMsg("3. Niszczyciel (zajmuje 3 pola, max 4 sztuki)");
            interface->printMsg("4. Patrolowka (zajmuje 2 pola, max 5 sztuk)");
            
            choice = interface->inInt(1,4);

            switch(choice) {
                case 1:
                    // can it be created?
                    if (Carrier::canBeCreated()) {
                        //create in memory and add to vector
                        ships.emplace_back(new Carrier);
                        //place it
                        //pointer to ship that was created two lines higher
                        placeNewShip(ships[shipsPlaced]);
                        //note that ship was placed
                        shipsPlaced++;
                    }
                    else {
                        //already 2 carriers, choose something else
                        errorOccured = true;
                        errorMessage = "Nie mozna umiescic wiecej statkow typu: Lotniskowiec";
                    }
                    break;
                case 2:
                    if (Battleship::canBeCreated()) {
                        ships.emplace_back(new Battleship);
                        placeNewShip(ships[shipsPlaced]);
                        shipsPlaced++;
                    }
                    else {
                        errorOccured = true;
                        errorMessage = "Nie mozna umiescic wiecej statkow typu: Pancernik";
                    }
                    break;
                case 3:
                    if(Destroyer::canBeCreated()) {
                        ships.emplace_back(new Destroyer);
                        placeNewShip(ships[shipsPlaced]);
                        shipsPlaced++;
                    }
                    else {
                        errorOccured = true;
                        errorMessage = "Nie mozna umiescic wiecej statkow typu: Niszczyciel";
                    }
                    break;
                case 4:
                    if(PatrolBoat::canBeCreated()) {
                        ships.emplace_back(new PatrolBoat);
                        placeNewShip(ships[shipsPlaced]);
                        shipsPlaced++;
                    }
                    else {
                        errorOccured = true;
                        errorMessage = "Nie mozna umiescic wiecej statkow typu: Patrolowka";
                    }
                    break;
                default:
                    interface->printMsg("Prosze wybrac wartosc od 1 do 4!");
                    break;
            }
        }
        catch (std::invalid_argument & e) {
            errorOccured = true;
            errorMessage = e.what();
        } 
    }
    shipsLeft = 7;
}

Player::Player(const std::string & filePath, std::streampos pos) {
    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.good()) {
        throw std::runtime_error("Nie udalo sie otworzyc pliku!");
    }
    file.seekg(pos);
    // file is good and open

    std::string line;

    for(Board::iterator it = ownBoard.begin(); it!= ownBoard.end(); it++) {
        it->fill(0);
    }
    for(Board::iterator it = radar.begin(); it!= radar.end(); it++) {
        it->fill(0);
    }

    // read the seven ships from the file
    for (int i=0; i<7; i++) {
        std::getline(file, line);
        // depending on what ship it is create new object in memory
        switch(line[0]) {
            case '5':
                ships.emplace_back(new Carrier);
                // place it on the map (dont forget to add coordinates)
                placeNewShip(ships[i], line);
                // set its health
                ships[i]->sethealth(line[1] - '0');
                break;
            case '4':
                ships.emplace_back(new Battleship);
                placeNewShip(ships[i], line);
                ships[i]->sethealth(line[1] - '0');
                break;
            case 3:
                ships.emplace_back(new Destroyer);
                placeNewShip(ships[i], line);
                ships[i]->sethealth(line[1] - '0');
                break;
            case 2:
                ships.emplace_back(new PatrolBoat);
                placeNewShip(ships[i], line);
                ships[i]->sethealth(line[1] - '0');
                break;
        }
    }
    // read shipsLeft
    std::getline(file, line);
    shipsLeft = (int)(line[0] - '0');

    // read ownBoard from file
    for (int i=0; i<10; i++) {
        std::getline(file, line);
        for (int j=0; j<10; j++) {
            ownBoard[i][j] = (int)(line[j] - '0');
        }
    }

    // empty line
    std::getline(file,line);

    //read radar from file
    for (int i=0; i<10; i++) {
        std::getline(file,line);
        for (int j=0; j<10; j++) {
            radar[i][j] = (int)(line[j] - '0');
        }
    }
    posInFile = file.tellg();
    file.close();
}

void Player::placeNewShip(Ship * ship, const std::string & line) {
    Coords bowCoords;
    bowCoords.first = (int)(line[3] - '0');
    bowCoords.second = (int)(line[4] - '0');

    int direction;
    if (line[3] == line[5]) {
        // ten sam wiersz
        if (line[4] > line[6]) {
            // kierunek polozenia = w lewo
            direction = 4;
        }
        else {
            // kierunek polozenia = w prawo
            direction = 2;
        }
    }
    else {
        // inny wiersz, ta sama kolumna
        if (line[3] > line[5]) {
            // kierunek polozenia = do gory
            direction = 1;
        }
        else { 
            // kierunek polozenia = w dol
            direction = 3; 
        }
    }
    // we have bowCoords and direction
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

void Player::placeNewShip(Ship * ship) {
    // auxillary variables
    bool goodSpot = false;
    Coords bowCoords;
    int direction;

    //error handling auxillary variables
    bool errorOccured = false;
    std::string errorMessage;
    bool firstIteration = true;
    
    interface->printMsg("Dlugosc tego statku to " + std::to_string(ship->getLength()) + " pola" );
    
    // asks where to put the ship and checks if it can be placed there
    while(!goodSpot) {
        try {
            do {
                // display error
                if (errorOccured) {
                    interface->printMsg(errorMessage + '\n');
                    errorOccured = false;
                }

                if(!firstIteration) {
                    interface->printMsg("Nie mozna tak ustawic statku! Sproboj ponowanie:");
                }

                interface->printMsg("Podaj koordynaty gdzie chcesz zaczepic dziob statku");

                bowCoords = interface->inCoordinates();

                //get in which direction the ship is supposed to be turned
                interface->printMsg("Podaj kierunek w jakim tyl statku ma sie znajdowac:");
                interface->printMsg("1. W gore");
                interface->printMsg("2. W prawo");
                interface->printMsg("3. W dol");
                interface->printMsg("4. W lewo"); 

                direction = interface->inInt(1,4);  
                firstIteration = false;    

            } while(!canBePlaced(bowCoords, direction, ship->getLength()));
            goodSpot = true;
        }
        catch (std::invalid_argument & e) {
            errorOccured = true;
            errorMessage = e.what();
        }
    }

    // if we get here, ship can be placed, now we have to place it on the board
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

//dir: 1 - north, 2 - east, 3 - south, 4 - west
bool Player::canBePlaced(const Coords & bowCoords, const int & dir, const int & length) const {
    switch(dir) {
        case 1:
            for(int row = bowCoords.first + 1; row != bowCoords.first - length - 1; row--) {
                for(int col = bowCoords.second - 1; col != bowCoords.second + 2; col++) {
                    if (bowCoords.first == 9 && row > 9) {
                        // nie ma sensu sprawdzania wiersza ponizej, nic tam nie moze byc
                        row--;
                        continue;
                    }
                    else if (bowCoords.first == (length - 1) && row < 0) {
                        // statek ustawiony tak ze ostatnie pole statku bedzie w wierszu A = 0
                        // jak dojdzie do tego momentu to waruneki sa spelnione
                        return true;
                    } 
                    if (col != bowCoords.second && isOutOfBounds(row, col)) {
                        // Checking column adjecent to where we want to put the ship, 
                        // but it is outside the board so we can assume that field meets the requirements
                        continue;
                    }
                    else if (col != bowCoords.second && !isOutOfBounds(row, col)) {
                        // Checking column adjecent to where we want to put the ship, it is inside the board
                        // so we have ot check if it is empty
                        if (!isFieldEmpty(row, col)) { return false;}
                    }
                    else {
                        // Check if field is inside the board and if it is empty, becuase this is
                        // the column where we want to place the ship
                        if (isOutOfBounds(row, col))  { return false; }
                        if (!isFieldEmpty(row, col))  { return false; }
                    }
                }
            }
            break;

        case 2:
            for(int row = bowCoords.first - 1; row != bowCoords.first + 2; row++) {
                for(int col = bowCoords.second - 1; col != bowCoords.second + length + 1; col++) {
                    if (bowCoords.second == 0 && col < 0) {
                        // if the bow of the shipis in first column there's no need to check the previous column
                        continue;
                    }
                    else if (bowCoords.second == (10 - length) && col > 9) {
                        // stern of a ship will be in the last column, no need to check next column
                        continue;
                    }
                    // Checking the row adjecent to where we want to put the ship, but it is outside
                    // the board, so we can assume it meets the requirements
                    if (row != bowCoords.first && isOutOfBounds(row, col)) {
                        continue;
                    }
                    // Checking the row adjcent to where we want to put the ship, it is inside the board
                    // so we have to check if it is empty
                    else if (row != bowCoords.first && !isOutOfBounds(row, col)) {
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    // Check if the field is inside the board and if it is empty, becuase
                    // this is the row where we want to put the ship
                    else {
                        if (isOutOfBounds(row,col))  { return false; }
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                }
            }
            break;

        case 3:
            for(int row = bowCoords.first - 1; row != bowCoords.first + length + 1; row++) {
                for(int col = bowCoords.second - 1; col != bowCoords.second + 2; col++) {
                    if (bowCoords.first == 0 && row < 0) {
                        // statek w pierszym wierszu, nie trzeba sprawdzac czy isOutOfBounds
                        // ani czy poza plansza sa jakies statki
                        row++;
                        continue;
                    }
                    else if (bowCoords.first == (10 - length) && row > 9) {
                        // koniec statku jest na ostatnim wierszu, nie trzeba sprawdzac isOutOfBounds
                        // ani czy poza plansza sa jakies inne statki
                        return true;
                    }
                    if (col != bowCoords.second && isOutOfBounds(row, col)) {
                        // see case 1 for explanation
                        continue;
                    }
                    else if (col != bowCoords.second && !isOutOfBounds(row, col)) {
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    else {
                        if (isOutOfBounds(row,col)) { return false; }
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                }
            }
            break;

        case 4:
            for(int row = bowCoords.first - 1; row != bowCoords.first + 2; row++) {
                for(int col = bowCoords.second + 1; col != bowCoords.second - length - 1; col--) {
                    if (bowCoords.second == 9 && col > 9) {
                        // poczatek statku jest w col = 9, nie ma sensu sprawdzac czy isOutOfBounds 
                        // ani czy poza plansza sa jakies statki
                        continue;
                    }
                    else if (bowCoords.second == (length - 1) && col < 0) {
                        // koniec statku bedzie w col = 0, nie ma sensu sprawdzac czy statek bedzie isOutOfBounds
                        // ani czy poza plansza sa jakies statki
                        continue;
                    }
                    // see case 2 for explanation
                    if (row != bowCoords.first && isOutOfBounds(row, col)) {
                        continue;
                    }
                    else if (row != bowCoords.first && !isOutOfBounds(row, col)) {
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                    else {
                        if (isOutOfBounds(row,col)) { return false; }
                        if (!isFieldEmpty(row, col)) { return false; }
                    }
                }
            }
            break;
    }
    return true;
}

int Player::shootAt(Player * rhs) {
    // get coordinates gdzie chcesz strzelic
    Coords coords(-1, -1);
    bool firstIteration = true;
    do {
        if (!firstIteration) { interface->printMsg("Juz tam strzelales!"); }

        interface->printMsg("Podaj koordynaty gdzie chcesz strzelic:");
        try {
            coords = interface->inCoordinates();
        }
        catch (std::invalid_argument & e) {
            interface->printMsg(e.what());
        }
    } while ((coords.first == -1 || coords.second == -1) || alreadyShotThere(coords));
    // mamy dobre koordynaty
    int result = rhs->getShotAt(coords);
    if (result == 0) { 
        radar[coords.first][coords.second] = 2;
        return 0; 
    }
    else if(result == 1) { 
        radar[coords.first][coords.second] = 3;
        return 1;
    }
    else {
        radar[coords.first][coords.second] = 3;
        return 2;
    }
}

int Player::getShotAt(const Coords & coords) {
    if (ownBoard[coords.first][coords.second] == 1) {
        // trafil
        // zaznaczamy na swojej planszy ze trafiono w statek
        ownBoard[coords.first][coords.second] = 3;
        // szukamy statku ktory zostal trafiony
        Ship * hitShip;
        for (Ship* p : ships) {
            if (p->isOnThoseCoordinates(coords)) {
                hitShip = p;
                break;
            }
        }
        // damage the ship, and check if it sunk
        bool sunken = hitShip->getDamaged();
        if (sunken) {
            shipsLeft--;
            return 2;
        }
        else {
            return 1;
        }
    }
    else {
        // nie trafil
        ownBoard[coords.first][coords.second] = 2;
        return 0;
    }
}

void Player::saveGameToFile() const {
    std::fstream file;
    file.open("battleships_saved_game.txt", std::ios::out | std::ios::app);
    if (!file.good()) {
        throw std::runtime_error("Nie udalo sie otworzyc pliku!");
    }
    file.seekp(0);
    // file is good and open

    // save ships and their current state
    for (Ship* p : ships) {
        // save length and current health
        file << p->getLength() << p->getHealth() << " ";
        auto it = p->getCoordsVector();
        // save coordinates of this ships
        for(int i=0; i < p->getLength(); i++) {
            file << it[i].first << it[i].second;
        }
        file << '\n';
    }
    // save shipsLeft to file
    file << shipsLeft << '\n';

    //save ownBoard to file
    for (Board::const_iterator itRow = ownBoard.begin(); itRow != ownBoard.end(); itRow++ ) {
        for (std::array<int, 10>::const_iterator itCol = itRow->begin(); itCol != itRow->end(); itCol++) {
            file << *itCol;
        }
        file << '\n';
    }

    file << '\n';
    
    //save radar to file
    for (Board::const_iterator itRow = radar.begin(); itRow != radar.end(); itRow++ ) {
        for (std::array<int, 10>::const_iterator itCol = itRow->begin(); itCol != itRow->end(); itCol++) {
            file << *itCol;
        }
        file << '\n';
    }

    file << '\n';

    file.close();
}