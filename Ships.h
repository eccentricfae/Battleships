#pragma once
#include <iostream>
#include <vector>
#include <utility>

typedef std::pair<int, int> Coords;

/**
 * @class Ship
 * @brief Klasa abstrakcyjna sluzaca jako fundament dla klas statkow pochodnych 
 */
class Ship {
protected:
    /**
     * @brief Zycie statku (zaczyna z health = length)
     */
    int health;
    /**
     * @brief Dlugosc statku liczona w polach ktore zajmuje
     */
    const int length;

    /**
     * @brief Wektor koordynatow na jakich dany obiekt (statek) sie znajduje
     */
    std::vector<std::pair<int, int>> ownCoords;
public:
    /**
     * @brief Metoda dodajaca podane koordynaty do wektora koordynatow tego statku
     * 
     * @param ref Koordynaty do dodania
     */
    void addCoords(const std::pair<int, int> & ref) {
        if (ownCoords.size() < length) {
            ownCoords.emplace_back(ref);
        }
    }
    
    /**
     * @brief Metoda dodajaca podane koordynaty do wektora koordynatow tego statku
     * 
     * @param row Indeks wiersza koordynatow do dodania
     * @param col Indeks kolumny koordynatow do dodania
     */
    void addCoords(const int & row, const int & col) {
        if (ownCoords.size() < length) {
            ownCoords.emplace_back(std::make_pair(row, col));
        }
    }

    /**
     * @brief Wez dlugosc statku
     * 
     * @return int Dlugosc statku
     */
    int getLength() const {
        return length;
    }

    /**
     * @brief Wez aktualne pozostale punkty zycia statku
     * 
     * @return int Punkty zycia statku
     */
    int getHealth() const {
        return health;
    }

    /**
     * @brief Ustaw ilosc zycia statku
     * 
     * @param x Ilosc zycia do ustawienia
     */
    void sethealth(int x) {
        if (x > -1 && x <= length) {
            health = x;
        }
    }

    //make pure virtual function something different or no pure virtuale at all
    virtual void print() = 0;

    /**
     * @brief "Uszkadza" (dekrementuje health) ten statek.
     * 
     * @return true Statek zatonal
     * @return false Statek nie zatonal
     */
    bool getDamaged() {
        health--;
        if (health == 0) { return true; }
        else { return false; }
    }
    
    /**
     * @brief Metoda ktora sprawdza czy dany statek znajduje sie na koordynatach podanych jako argument
     * 
     * @param ref Koordynaty do sprawdzenia
     * @return true Statek znajduje sie na tych koordynatach
     * @return false Statek nie znajduje sie na tych koordynatach
     */
    bool isOnThoseCoordinates(const Coords & ref) const {
        for (Coords own : ownCoords) {
            if (own == ref) {return true;}
        }
        return false;
    }

    /**
     * @brief Metoda zwracajaca const_iterator do wektora koordynatow statku
     * 
     * @return std::vector<std::pair<int, int>>::const_iterator const_iterator do wektora koordynatow statku
     */
    std::vector<std::pair<int, int>>::const_iterator getCoordsVector() {
        return ownCoords.begin();
    }

    Ship(int length) : length(length), health(length) {
        ownCoords.reserve(length);
    }

    virtual ~Ship() {}
};

/**
 * @class Carrier
 * @brief Klasa reprezentujaca 5'cio polowy statek typu "Lotniskowiec"
 * @see Ship
 */
class Carrier : public Ship {
private:
    /**
     * @brief Ile obiektow tego typu jest utworzonych
     */
    static int carrierCounter;

public: 
    /**
     * @brief Konstruktor dla klasy Carrier (Lotniskowiec). Inkrementuje "carrierCounter"
     * 
     */
    Carrier() : Ship(5) {
        carrierCounter++;
    }

    /**
     * @brief Destruktor dla klasy obiektow Carrier (Lotniskowiec). Dekrementuje "carrierCouter".
     */
    ~Carrier() {
        carrierCounter--;
    }

    /**
     * @brief Metoda statyczna uzywana przy tworzeniu obiektu klasy Player. Zwraca czy aktualnie jest stworzonych mniej niz 2 obiekty typu Carrier
     * 
     * @return true Aktualnie jest stworzonych mniej niz 2 obiekty typu Carrier
     * @return false Aktualnie jest stworzonych 2 lub wiecej obiektow typu Carrier
     * @see Player
     */
    static bool canBeCreated() {
        return (carrierCounter < 2) ? true : false;
    }

    void print() override {std::cout << "maslo";}
};

/**
 * @class Battleship
 * @brief Klasa reprezentujaca 4'ro polowy statek typu Battleship (Pancernik)
 * @see Ship
*/
class Battleship : public Ship {
private:
    /**
     * @brief Ile obiektow tego typu jest utworzonych
     */
    static int battleshipCounter;

public:
    /**
     * @brief Konstruktor dla klasy Battleship (Pancernik). Inkrementuje "battleshipCounter"
     */
    Battleship() : Ship(4) {
        battleshipCounter++;
    }

    /**
     * @brief Destruktor dla klasy Battleship. Dekrementuje "battleshipCounter"
     */
    ~Battleship() {
        battleshipCounter--;
    }

    /**
     * @brief Metoda statyczna uzywana przy tworzeniu obiektu klasy Player. Zwraca czy aktualnie jest stworzonych mniej niz 2 obiekty typu Battleship
     * 
     * @return true Aktualnie jest stworzonych mniej niz 2 obiekty typu Battleship
     * @return false Aktualnie jest stworzonych 2 lub wiecej obiektow typu Battleship
     * @see Player
     */
    static bool canBeCreated() {
        return (battleshipCounter < 2) ? true : false;
    }

    void print() override {std::cout << "maslo";}
};

/**
 * @class Destroyer
 * @brief Klasa reprezentujaca troj polowy statek typu Destroyer (Niszczyciel)
 * @see Ship
 */
class Destroyer : public Ship {
private:
    /**
     * @brief Ile obiektow tego typu jest utworzonych
     */
    static int destroyerCounter;

public:
    /**
     * @brief Konstruktor dla klasy Destroyer. Inkrementuje "destroyerCounter" 
     */
    Destroyer() : Ship(3) {
        destroyerCounter++;
    }

    /**
     * @brief Destruktor dla klasy Destroyer. Dekrementuje destryerCounter
     */
    ~Destroyer() {
        destroyerCounter--;
    }

    /**
     * @brief Metoda statyczna uzywana przy tworzeniu obiektu klasy Player. Zwraca czy aktualnie jest stworzonych mniej niz 2 obiekty typu Destroyer
     * 
     * @return true Aktualnie jest stworzonych mniej niz 2 obiekty typu Destroyer
     * @return false Aktualnie jest stworzonych 2 lub wiecej obiektow typu Destroyer
     * @see Player
     */
    static bool canBeCreated() {
        return (destroyerCounter < 4) ? true : false;
    }

    void print() override {std::cout << "maslo";}
};

/**
 * @class PatrolBoat
 * @brief Klasa reprezentujaca dwu polowy statek typu Patrol Boat (Patrolowka)
 * @see Ship
 */
class PatrolBoat : public Ship {
private:
    /**
     * @brief Ile obiektow tego typu jest utworzonych
     */
    static int patrolBoatCounter;

public:
    /**
     * @brief Konstrutkor dla klasy PatrolBoat. Inkrementuje patrolBoatCounter
     */
    PatrolBoat() : Ship(2) {
        patrolBoatCounter++;
    }

    /**
     * @brief Destruktor dla klasy PatrolBoat. Dekrementuje patrolBoatCounter
     */
    ~PatrolBoat() {
        patrolBoatCounter--;
    }

    /**
     * @brief Metoda statyczna uzywana przy tworzeniu obiektu klasy Player. Zwraca czy aktualnie jest stworzonych mniej niz 2 obiekty typu PatrolBoat
     * 
     * @return true Aktualnie jest stworzonych mniej niz 2 obiekty typu PatrolBoat
     * @return false Aktualnie jest stworzonych 2 lub wiecej obiektow typu PatrolBoat
     * @see Player
     */
    static bool canBeCreated() {
        return (patrolBoatCounter < 5) ? true : false;
    }

    void print() override {std::cout << "maslo";}
};