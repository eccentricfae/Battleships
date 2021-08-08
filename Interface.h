#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <exception>

typedef std::array<std::array<int, 10>, 10> Board;
typedef std::pair<Board::const_iterator, Board::const_iterator> PairBoardRangeIterators;

class InterfaceIO {
public:
    /**
     * @brief Metoda wyswietlajaca plansze do gry na ekranie
     * 
     * @param pairIt Para const iteratorow do poruszania sie po tablicy (see typedef)
     */
    virtual void printBoard(const PairBoardRangeIterators & pairIt) = 0;

    /**
     * @brief Metoda wyswietlajaca wiadomosc na ekranie
     * 
     * @param msg Wiadomosc do wyswietlenia
     */
    virtual void printMsg(const std::string & msg) = 0;

    /**
     * @brief Metoda "tworzaca puste linie w konsoli", zeby dac iluzje prawdziwego silnika graficznego
     * @note Jesli uzywa sie silnika graficznego ktory nie posluguje sie konsola mozna ta
     * metode zignorowac!
     */
    virtual void clearScreen() = 0;

    /**
     * @brief Metoda pokazywujaca instrukcje obslugi programu gry w statki!
     */
    virtual void printInstructions() = 0;

    /**
     * @brief Metoda pokazywujaca zasady gry w statki!
     */
    virtual void printRules() = 0;

    /**
     * @brief Metoda ktora wczytuje dane od uzytkownika, sprawdza czy to jest Int i czy miesci sie
     * w danym przedziale.
     * 
     * @param start_range Poczatek przedzialu z ktorego moga zostaac zwrocone liczby
     * @param end_range Koniec przedzialu z ktorego moga zostaac zwrocone liczby
     * @return int Wczytana od uzytkownika liczba
     * @note Rzuca wyjatkami typu std::invalid_argument
     */
    virtual int inInt(const int & start_range, const int & end_range) = 0;

    /**
     * @brief Metoda wczytujaca koordynaty od uzytkownika. Sprawdza ich poprawnosc, i jesli sa bledne
     * rzuca wyjatkiem.
     * 
     * @return std::pair<int, int> Koordynaty do planszy
     * @note Rzuca wyjatkami std::invalid_argument 
     */
    virtual std::pair<int, int> inCoordinates() = 0;

    /**
     * @brief Wirtualny destruktor dla klasy InterfaceIO
     */
    virtual ~InterfaceIO() {}
};

class IConsole : public InterfaceIO {
public:

    void printBoard(const PairBoardRangeIterators & pairIt) override {
        std::cout << "\t";
        for(int i=0; i<10; i++) {
            std::cout << i;
        }
        std::cout << "\n\n";
        char rLetter = 'A';
        for (auto row = pairIt.first; row != pairIt.second; row++) {
            std::cout << "     " << rLetter << "  ";
            rLetter++;
            for (auto col = row->begin(); col != row->end(); col++) {
                switch(*col) {
                    case 0: std::cout << "~"; break;
                    case 1: std::cout << "S"; break;
                    case 2: std::cout << "."; break;
                    case 3: std::cout << "X"; break;
                    default :
                        // should never happen
                        //throw exception?
                        break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << "\n";
    }

    void printMsg(const std::string & msg) override {
        std::cout << msg << std::endl;
    }

    void clearScreen() override {
        for(int i=0; i<15;i++) std::cout << std::endl;
    }

    // !! implement
    void printInstructions() override {
        std::cout << "not yet implemented\n";
    }

    // !! implement
    void printRules() override {
        std::cout << "not yet implemented\n";
    }

    int inInt(const int & start_range, const int & end_range) override {
        int x;
        std::cin >> x;
        if (std::cin.fail() || (x > end_range || x < start_range) ) {
            // state = goodbit (pozbyc sie badbit'u zeby mozna dalej czytac z cin)
            std::cin.clear();
            // zignoruj co jest teraz w strumieniu wejscia
            std::cin.ignore();
            throw std::invalid_argument("Podano zly argument");
        }
        else {
            return x;
        }
    }

    std::pair<int, int> inCoordinates() override {
        std::string input;
        std::cin >> input;
        if (input.length() != 2) {
            throw std::invalid_argument("Zly argument!");
        }
        // check if input[0] is a letter A-J
        if (std::toupper(input[0]) > 'J' || std::toupper(input[0]) < 'A') {
            throw std::invalid_argument("Pierwsza skladowa koordynatow jest zla!");
        }
        // check if input[1] is a number 0-9
        if (input[1] > '9' || input[1] < '0') {
            throw std::invalid_argument("Druga skladowa koordynatow jest zla!");
        }
        int first = (int)std::toupper(input[0]) - 65;
        int second = (int)input[1] - 48;

        return std::make_pair(first, second);
    }

    ~IConsole() {}
};