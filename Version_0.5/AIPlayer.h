#pragma once
#include "Player.h"
#include <cstdlib>
//potrzebne dla chrono::millisecond(10)
#include <chrono>
//potrzebne do this_thread::sleep_for
#include <thread>

/**
 * @class AIPlayer
 * @brief Klasa potomna po Player, w ktorej zaimplementowana jest prosta "sztuczna inteligencja" w roli przeciwnika w grze.
 * @see Player
 */
class AIPlayer : public Player {
private:
    /**
     * @brief Zmienna ktora przechowywuje czy AI podczas ostatniej proby trafilo w
     * jakis statek.
     */
    bool lastShotWasAHit = false;

    Coords lastShotCoords;
public:
    /**
     * @brief Konstruktor jednoargumentowy dla obiektow klasy AIPlayer
     * @details Konstrutkor jednoargumentowy, ktory bierze wskaznik do interfejsu, jak w klasie Player, oraz
     * korzysta ze protected konstruktora bezargumentowego Player(), zeby tylko zainicjalizowac tablice, ale nie
     * wywolywac algorytmu wstawiania manualnie statkow na plansze.
     * 
     * @param i Wskaznik do obiektu pelniacego role interfejsu wejscia i wyjscia.
     * @note Konstruktor inicjuje tez srand() dla funkcji zwracajacych wartosci losowe
     * @see initShips
     */
    AIPlayer(InterfaceIO * i);

    AIPlayer(const std::string & filePath, const std::streampos & pos);

    /**
     * @brief Metoda ustawiajaca 7 statkow na planszy AI.
     * @note AI zawsze bedzie mialo ten sam zestaw statkow: 1 lotniskowiec, 1 pancernik, 2 niszczyciele, 3 patrolowki
     * @see placeNewShip
     */
    void initShips();

    /**
     * @brief Metoda ustawiajaca statek AI na planszy. Przeciazona metoda z klasy Player
     * @note Algorytm szukania miejsca jest "naiwny", poniewaz opiera sie na losowaniu roznich koordynatow
     * i kierunku tak dlugo az wylosuje sie poprawne umieszczenie statku na planszy
     * @param ship 
     * @see Player::placeNewShip
     */
    void placeNewShip(Ship * ship) override;

    /**
     * @brief Metoda zwracajaca losowe koordynaty, ktore mieszcza sie w granicach planszy
     * 
     * @return Coords Losowe koordynaty do planszy
     */
    inline Coords genRandomCoords() const;

    /**
     * @brief Metoda zwracajaca losowa wartosc od 1 do 4
     * 
     * @return int Int z przedzialu <1,4>
     */
    inline int genRandomDirection() const ;

    // !
    int shootAt(Player * rhs) override;

    void saveGameToFile() const override;
};

Coords AIPlayer::genRandomCoords() const {
    return std::make_pair(rand() % 10, rand() % 10);
}

int AIPlayer::genRandomDirection() const {
    return (rand() % 4) + 1;
}