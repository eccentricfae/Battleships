#pragma once
#include <array>
#include <vector>
#include <utility>
#include <iterator>
#include <iostream>
#include <fstream>
#include "Ships.h"
#include "Interface.h"

/**
 * @typedef std::array<std::array<int, 10>, 10> Board
 * @brief  Alias dla std::array<std::array<int, 10>, 10>
 * @details Alias "std::array<std::array<int, 10>, 10>" na "Board", wprowadzony dla krotszego zapisu typow w calym programie.
 * Board reprezentuje dwuwymiarowa tablice liczb calkowitych (int)
 * 
 */
typedef std::array<std::array<int, 10>, 10> Board;


/**
 * @typedef std::pair<int, int> Coords
 * @brief Alias dla std::pair<int, int>
 * @details Alias wprowadzony dla krotszego zapisu typow w kodzie programu. Coords (ang. Coordinates),
 * po polsku "koordynaty", reprezentuje pare liczb calkowitych (int). Wykorzystywane glownie do dostepu do tablicy 2d "Board"
 * 
 */
typedef std::pair<int, int> Coords;

/**
 * @class Player
 * @brief Glowny element programu "Statki" w ktorym zaimplementowana jest logika gry.
 * @warning Do poprawnego dzialania tej klasy, nalezy zapewnic:<br>- klase Ships,<br>- klase InterfaceIO
 * @warning Wazne zeby obiekt dla gracza klasy Player zostal utworzony przed obiektem AIPlayer
 * @see AIPlayer
 * @see Ship
 * @see InterfaceIO
 */
class Player {
protected:
    /**
     * @brief Tablica std::array dwuwymiarowa, reprezentujca plansze na ktorej gracz ma swoje statki.
     * @details Tablica tablic liczb calkowitych (std::array<std::array<int, 10>, 10>) o wymiarach 10 na 10. Zadeklarowana uzywajac "typedef std::array<std::array<int, 10>, 10> Board;".
     * Kazda komorka w tablicy reprezentuje jedno pole w standardowej wersji gry, i ma jedna z podanych wartosci: <br>
     * 0 - pole jest "puste", nie znajduje sie tutaj zaden statek, ani przeciwnik nie oddal tutaj zadnego strzalu<br>
     * 1 - znajduje sie w tym polu statek gracza, ktory nie zostal jeszcze trafiony przez przeciwnika<br>
     * 2 - na tym polu zostal oddany strzal, ktory nie trafil w nic <br>
     * 3 - na tym polu zostal trafiony statek<br>
     * 
     * @see radar
     */
    Board ownBoard;

    /**
     * @brief Tablica std::array dwuwymiarowa, reprezentujaca plansze na ktorej gracz zaznacza swoje strzaly.
     * @details Tablica tablic liczb calkowitych (std::array<std::array<int, 10>, 10>) o wymiarach 10 na 10. Zadeklarowana uzywajac "typedef std::array<std::array<int, 10>, 10> Board;".
     * Kazda komorka w tablicy reprezentuje jedno pole w standardowej wersji gry, i ma jedna z podanych wartosci: <br>
     * 0 - pole jest "puste", nie oddano jeszcze w tym polu strzalu<br>
     * 1 - wartosc zarezerwowana dla "ownBoard"<br>
     * 2 - w tym polu zrobiono strzal, w nic nie trafiono<br>
     * 3 - w tym polu zostal trafiony statek przeciwnika<br>
     * 
     * @see ownBoard
     */
    Board radar;

    /**
     * @brief Wektor wskaznikow do statkow ustawionych na planszy ownBoard
     * 
     */
    std::vector<Ship*> ships;

    /**
     * @brief Wartosc ktora mowi ile statkow nie zostalo jeszcze zatopionych. Jesli jest rowna 0, to
     * znaczy ze sie przegralo.
     */
    int shipsLeft;

    /**
     * @brief Wskaznik do obiektu dzialajacego jako interfejs wprowadzania danych oraz jako silnik graficzny.
     * @note interface nie jest obiektem InterfaceIO (to jest klasa abstrakcyjna), ale jest obiektem klasy pochodnej "kryjacej sie" pod wskaznikiem
     * do InterfaceIO
     */
    InterfaceIO * interface = nullptr;

    /**
     * @brief Konstruktor bezargumentowy, zarezerwowany specjalnie dla oknstrukcji obiektu typu AIPlayer
     * @details
     * 
     * @see AIPlayer
     */
    Player();

    // !
    std::streampos posInFile;

public:
    /**
     * @brief Konstruktor jednoargumentowy dla klasy "Player".
     * @details Konstruktor najpierw inicjalizuje *interface oraz wypelnia tablice ownBoard zerami.
     * Nastepnie wykonuje algorytm wstawiania 7 statkow na plansze: W zaleznosci od rodzaju statku ktory uzytkownik
     * chce ustawic, sprawdzane jest czy taki statek moze byc stworzony (zobacz maksymalna liczba statkow danego typu),
     * i nastepnie tworzony jest w miejscu (na koncu wektora) nowy obiekt odpowniedniej klasy i wstawiany na plansze.
     * 
     * @param i Wskaznik do obiektu pelniacego role interfejsu wejscia i wyjscia.
     * @see placeNewShip
     */
    Player(InterfaceIO * i);

    // ! 2nd constructor for loading from file?
    Player(const std::string & filePath, std::streampos pos = 0);

    /**
     * @brief Destruktor dla klasy Player. Dealokuje obiekty klas pochodnych klasy Ship i czysci wektor
     * @see Ship
     */
    virtual ~Player() {
        for(Ship* pToShip : ships) {
            delete pToShip;
        }
        ships.clear();
    };

    inline std::streampos getPosInFile() const;

    /**
     * @brief Metoda ktora wywoluje rysowanie planszy "ownBoard" oraz "radar" w zaleznosci od argumentu.
     * @param which Podaj 1 dla rysowania "ownBoard"; 2 dla rysowania "radar"
     */
    inline void printBoard(const int & which) const;

    /**
     * @brief Metoda ktora dla podanych koordynatow sprawdza czy te pole na planszy jest puste (wartosc 0)
     * 
     * @param coords Koordynaty dla ktorych metoda ma sprawdzic pole std::pair<int, int>
     * @return true Pole jest puste (wartosc 0)
     * @return false Na tym polu cos jest (wartosc 1, 2 lub 3)
     * @see ownBoard
     */
    inline bool isFieldEmpty(const Coords & coords) const;
    /**
     * @brief Metoda ktora dla podanych koordynatow sprawdza czy te pole na planszy jest puste (wartosc 0)
     * 
     * @param row Indeks w ktorym wierszu ma byc sprawdzone pole
     * @param col Indeks w ktoerj kolumnie ma byc sprawdzone pole
     * @return true Pole jest puste (wartosc 0)
     * @return false Na tym polu cos jest (wartosc 1, 2 lub 3)
     * @see ownBoard
     */
    inline bool isFieldEmpty(const int & row, const int & col) const;

    /**
     * @brief Metoda sprawdzajaca czy pole o podanych koordynatach znajduje sie na planszy
     * 
     * @param coords Koordynaty pola do sprawdzenia
     * @return true Pole o podanych koordynatach jest poza plansza
     * @return false Pole o pdanych koordynatach jest na planszy
     */
    inline bool isOutOfBounds(const Coords & coords) const;
    /**
     * @brief Metoda sprawdzajaca czy pole o podanych koordynatach znajduje sie na planszy
     * 
     * @param row Indeks wiersza pola do sprawdzenia
     * @param col Indeks kolumny pola do sprawdzenia
     * @return true Pole o podanych koordynatach jest poza plansza
     * @return false Pole o pdanych koordynatach jest na planszy
     */
    inline bool isOutOfBounds(const int & row, const int & col) const;

    /**
     * @brief Funkcja sprawdzajaca czy dla podanych argumentow statek moze byc ustawiony na planszy.
     * @details Funkcja, dla podanych: koordynatow dzioba statku, kierunku zwrocenia statku i jego dlugosci, sprawdza
     * czy zgodnie z zasadami statek moze byc tak ustawiony
     * 
     * @param bowCoords Koordynaty gdzie dziob statku ma byc ustawiony
     * @param dir Kierunek w jakim statek ma byc ustawiony: 1 - do gory; 2 - w prawo; 3 - w dol; 4 - w lewo
     * @param length Dlugosc statku dla ktorego sprawdzamy czy moze byc ustawiony
     * @return true Statek moze byc ustawiony zgodnie z podanymi argumentami
     * @return false Statek nie moze byc ustawiony zgodnie z podanymi argumentami
     * @see InterfaceIO::printRules()
     */
    bool canBePlaced(const Coords & bowCoords, const int & dir, const int & length) const;

    /**
     * @brief Metoda ustawiajaca statek na planszy dla typu statku podanego przez argument
     * @details Metoda najpierw pyta gdzie uzytkownik chce postawic statek tak dlugo az uzytkownik poda
     * ustawienie ktore jest wykonalne (zgodnie z zasadami). Gdy poprawne ustawienie zostanie podane metoda 
     * nadpisuje odpowiednie pola na tablicy ownBoard wartosciami 1 co oznacza ustawienie statku na planszy
     * @param ship Wskaznik do obiektu reprezentujacego typ statku ktory chcemy ustawic na planszy
     * @note Pod wskaznikiem ship jest obiekt klasy pochodnej od klasy Ship
     * @see Ship
     * @see ownBoard
     * @see canBePlaced
     * @see InterfaceIO::printRules
     */
    virtual void placeNewShip(Ship * ship);

    // !
    void placeNewShip(Ship * ship, const std::string & line);

    /**
     * @brief Metoda do "strzelania" w statki przeciwnika
     * @details Metoda "strzela" do przeciwnika podanego przez wskaznik. Najpierw pobierane sa koordynaty gdzie sie
     * chce strzelic, potem strzelamy do przeciniwka poprzez wywolanie metody getShotAt().
     * W zaleznosci czy trafiono czy nie odpowiednio zaznacza sie to na radarze i zwraca odpowiednia wartosc:
     * 0 - nie trafiono, 1 - trafiono, 2 - trafiono i zatopiono statek. 
     * 
     * @param rhs Wskaznik na jakiego gracza strzelic
     * @return Wynik czy trafilismy czy nie
     * @see getShotAt
     */
    virtual int shootAt(Player * rhs);

    // !
    int getShotAt(const Coords & coords);

    inline bool lost() const;

    /**
     * @brief Metoda ktora zwraca czy gracz strzelal juz w podane pole 
     * 
     * @param coords Koordynaty pola ktore chcemy sprawdzic
     * @return true Uzytkownik juz w te pole strzelal
     * @return false Nie strzelal tam jeszcze
     */
    inline bool alreadyShotThere(const Coords & coords) const;
    /**
     * @brief Metoda ktora zwraca czy gracz strzelal juz w podane pole 
     * 
     * @param row Indeks wiersza do sprawdzenia
     * @param col Indeks kolumny do sprawdzenia
     * @return true Uzytkownik juz w te pole strzelal
     * @return false Nie strzelal tam jeszcze
     */
    inline bool alreadyShotThere(const int & row, const int & col) const;

    virtual void saveGameToFile() const;

};

std::streampos Player::getPosInFile() const {
    return posInFile;
}

void Player::printBoard(const int & which) const {
    switch(which) {
        case 1:
            interface->printMsg("Twoja plansza:");
            interface->printBoard(std::make_pair(ownBoard.begin(), ownBoard.end()));
            break;
        case 2:
            interface->printMsg("Twoj radar:");
            interface->printBoard(std::make_pair(radar.begin(), radar.end()));
            break;
        default:
            interface->printMsg("Zle wywolanie \"printBoard()\"");
    }
}

bool Player::isFieldEmpty(const Coords & coords) const {
    if (ownBoard[coords.first][coords.second] == 0) { return true; }
    else { return false; }
}

bool Player::isFieldEmpty(const int & row, const int & col) const {
    if (ownBoard[row][col] == 0) { return true; }
    else { return false; }
}

bool Player::isOutOfBounds(const Coords & coords) const {
    if (coords.first > 9 || coords.first < 0) { return true;}
    if (coords.second > 9 || coords.second < 0) { return true; }
    return false;
}

bool Player::isOutOfBounds(const int & row, const int & col) const {
    if (row > 9 || row < 0) { return true; }
    if (col > 9 || col < 0) { return true; }
    return false;
}

bool Player::alreadyShotThere(const Coords & coords) const {
    if (radar[coords.first][coords.second] == 0) { return false; }
    else { return true; }
}

bool Player::alreadyShotThere(const int & row, const int & col) const {
    if (radar[row][col] == 0) { return false; }
    else { return true; }
}

bool Player::lost() const {
    return (shipsLeft == 0) ? true : false;
}