/**
 * @file IConsole.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Source file for the IConsole.h header file.
 * 
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#include "IConsole.h"

/**
 * @details This function takes in two const_iterators (const so it doesnt modify anything in the actual board), and uses them to print out the board pointed to by aforementioned iterators.
 *          First the column idientifiers are printed out (numbers 0-9), then variable "rowIdientifierLetter" is declared (used for printing out the row idientifiers), and auxillary iterator "column" that points
 *          to const int, because iteratorBegin points to an array of 10 ints. 
 *          After printing out row idientifier the letter is incremented, and a row of values from the board is printed out.
 */
void IConsole::printBoard(const Board::const_iterator & iteratorBegin, const Board::const_iterator & iteratorEnd) {
    Board::const_iterator row = iteratorBegin;
    
    // print columnumn idientifiers - from o to 9
    std::cout << "\t";
    for (int i = 0; i < 10; i++) {
        std::cout << i;
    }

    
    std::cout << "\n\n";
    char rowIdientifierLetter = 'A';
    std::array<int, 10>::const_iterator column;

    // print row idientifiers (letters from A to J), space for aesthethics / readability, and a row of the board
    for (/*row*/; row != iteratorEnd; row++) {
        std::cout << "     " << rowIdientifierLetter << "  ";
        rowIdientifierLetter++;
        for (column = row->begin(); column != row->end(); column++) {
            switch(*column) {
                case 0: std::cout << "~"; break;
                case 1: std::cout << "S"; break;
                case 2: std::cout << "."; break;
                case 3: std::cout << "X"; break;
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

/**
 * @details Function reads user input, if the input is of wrong type (std::cin.fail() = true) or is out of range the function: clears the error flag (failbit or badbit is set);
 *          ignores what was left in the input stream (so that I/O stream works correctly); and throws an exception.
 *          If a correct number was input by the user, the funciton just returns that number.
 */
int IConsole::inputInt(const int & firstElementInRange /*= INT_MIN*/, const int & lastElementInRange /*= INT_MAX*/) {
    // read user input
    int userInput;
    std::cin >> userInput;

    if (std::cin.fail() || (userInput < firstElementInRange || userInput > lastElementInRange)) {
        std::cin.clear();
        std::cin.ignore(999, '\n');
        throw std::invalid_argument("Podano zly argument");
    }
    else {
        return userInput;
    }
}

/**
 * @details The function reads user input. If the input is of different length than 2 characters, the function throws an exception, because the input is not in the format of board coordinates.
 *          If the format of the input is correct the function checks if the first and second characters in the input are of correct format for their respective rows and columns idientifiers:
 *          Rows are idientified by letters from A to J; columns - by numbers from 0 to 9.
 *          If the input is semantically and syntactically correct, the function converts the input to two integers, and returns them in the form of std::pair container.
 */
Coords IConsole::inputCoordinates() {
    std::string userInput;
    std::cin >> userInput;
    
    if (userInput.length() != 2) {
        throw std::invalid_argument("Podano zly argument!");
    }

    if (std::toupper(userInput[0]) > 'J' || std::toupper(userInput[0]) < 'A') {
        throw std::invalid_argument("Pierwsza skladowa koordynatow jest zla! Powinna to byc litera od 'A' do 'J'.");
    }

    if (userInput[1] > '9' || userInput[1] < '0') {
        throw std::invalid_argument("Druga skladowa koordynatow jest zla! Powinna to byc cyfra od 0 do 9.");
    }

    int firstCoord = (int)(std::toupper(userInput[0]) - 'A'/*(char)65*/);
    int secondCoord = (int)(userInput[1] - '0'/*(char)48*/);

    return std::make_pair(firstCoord, secondCoord);
}

std::string IConsole::inputPathFile() {
    std::string stringInput;
    std::cin >> stringInput;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(999, '\n');
        throw std::invalid_argument("Nie udalo sie wczytac podanego tekstu");
    }

    return stringInput;
}

void IConsole::printInstructions() {
    clearScreen();
    std::cout << "\tInstrukcje i porady od gry w statki:\n";
    std::cout << "\t- Gra korzysta z konsoli do pobierania i drukowania informacji o grze\n";
    std::cout << "\t- Wszystkie operacje wykonywane sa za pomoca klawiatury\n";
    std::cout << "\t- Gdy na ekranie widnieja ponumerowane opcje i gra pyta Cie \"Co bys chcial zrobic\" nalezy wybrac chciana opcje poprzez:\n";
    std::cout << "\t\t- wpisanie odpowiedniego numeru z klawiatury\n";
    std::cout << "\t\t- nacisniecie klawisza Enter. \tPrzyklad: \"1<enter>\"\n";
    std::cout << "\t- Gdy gra prosi Cie o wprowadzenie koordynatow: nalezy wybrac koordynaty (na przedstawionej planszy) odpowiednie do dzialania poprzez:\n";
    std::cout << "\t\t- Wprowadzenie najpierw litery symbolizujacej wiersz\n";
    std::cout << "\t\t- Wprowadzenie cyfry (bez spacji po literze) symbolizujacej kolumne\n";
    std::cout << "\t\t- nacisniecie klawisza Enter. Przyklad: \"A0<enter>\"\n";
    std::cout << "\t- Gdy wybierzesz opcje: \"Wczytaj gre z pliku\" nalezy wprowadzic sciezke do pliku w ktorym znajduje sie zapisany stan gry.\n";
    std::cout << "\t\t- Najlatwiej to zrobic poprzez przeciagniecie pliku battleships_save.txt z folderu bezposrednio do konsoli gdy gra poprosi Cie";
    std::cout << "o wprowadzenie sciezki do pliku z zapisanym stanem gry.\n";
    std::cout << "\t- Plik battleships_save.txt jest automatycznie tworzony w folderze w ktorym znajduje sie plik .exe ktorym uruchomiles gre.\n";
    system("pause");
    clearScreen();
    std::cout << "\t- Statki ustawia sie poprzez wybranie gdzie ma sie znajdowac dziob statku (pierwsze pole zajete przez statek), a nastepnie:\n";
    std::cout << "\t\t- wybranie w jakim kierunku ma sie znajdowac rufa statku (ostatnie pole zajete przez statek). Pomiedzy tymi polami pola automatycznie zostana\n";
    std::cout << "\t\tzarezerowane dla statku ktory wtedy bedziesz umieszczac na planszy.\n";
    std::cout << "\t- Podczas rozgrywki bedziesz mial do wyboru dwie opcje: \"Oddaj strzal\" lub \"Zapisz gre i zakoncz\"\n";
    std::cout << "\t- \"Oddaj strzal\" - gra koontynuje, oddajesz strzal w strone przeciwnika (zobacz zasady gry)\n";
    std::cout << "\t- \"Zapisz gre i zakoncz\" - zapisujesz aktualny stan gry do pliku, ktory zostanie umieszczony w folderze gdzie znajduje sie plik .exe ktorym";
    std::cout << "\turuchomiles gre\n";

    system("pause");
}

void IConsole::printRules() {
    clearScreen();
    std::cout << "\tZasady gry w statki:\n";
    std::cout << "\t- W gre gra dwoje graczy: Ty (uzytkownik) vs Komputer\n.";
    std::cout << "\t- Kazdy z graczy posiada dwie plansze o wymiarach 10x10 pol\n";
    std::cout << "\t- Kazdy z wierszy i kolumn na planszy jest oznaczony odpowiednio: literami od A do J, oraz cyframi od 0 do 9\n";
    std::cout << "\t- Na pierwszej planszy (w grze nazwana \"Twoja plansza\") ustawia sie swoje statki i monitoruje na jakie pola przeciwnik oddaje strzaly\n";
    std::cout << "\t- Druga plansza \"Twoj radar\" (symulujaca poglad na plansze przeciwnika) przeznaczona jest na planowanie i zaznaczanie swoich strzalow\n";
    std::cout << "\t- Do ustawienia na planszy przeznaczone sa 4 rodzaje statkow:\n";
    std::cout << "\t\t- lotniskowiec - 5'cio polowy statek - jedna sztuka\n";
    std::cout << "\t\t- Pancernik - 4'ro polowy statek - dwie sztuki\n";
    std::cout << "\t\t- Niszczyciel - troj polowy statek - trzy sztuki\n";
    std::cout << "\t\t- Patrolowka - dwu polowy statek - dwie sztuki\n";
    std::cout << "\t- Gra polega na oddawaniu strzalow, tj.: zgadywaniu gdzie przeciwnik, na swojej planszy, ustawil swoje statki\n";
    std::cout << "\t- Strzaly oddaje sie naprzemiennie\n";
    std::cout << "\t- Gdy przeciwnik chybi / trafi w okret nalezy go o tym poinformowac, dodatkowo nalezy przeciwnika poinformowac jezeli trafi on w okret i go zatopi\n";
    std::cout << "\t- Gdy trafi sie w okret przeciwnika oddaje sie strzaly poza kolejka do momentu chybienia. Po tym wraca sie do naprzemiennego oddawania strzlow\n";
    std::cout << "\t- Wygrywa ten kto pierwszy zatopi wszystkie statki przeciwnika!\n";
    std::cout << "\n\t- POWODZENIA!!!\n";

    system("pause");
}