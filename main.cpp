/**
 * @file main.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Main source file for the Battleships game. <br>Project available at: https://github.com/Tinuloth/Battleships
 * 
 * @details detailed here / describe here the process that main.cpp goes thru?
 * 
 * @version 1.0
 * @date 2021-08-08
 * 
 */
#include "Player.h"
#include "AIPlayer.h"
#include "IConsole.h"
#include <thread>
#include <chrono>

using namespace std;

/**
 * @brief Save current state of the game to file. This function always saves to file named "battleships_save.txt". If already such file exists in the directory of the executable
 *        file, then that file is lost and overwritten, if no such file exist then new file is created.
 * 
 * @param player Pointer to the object representing the player (user).
 * @param ai Pointer to the object represeting the AI.
 * @throws std::runtime_error If the function fail to open the file, the function throws an exception.
 */
void initializeSavingGame(const Player * player, const Player * ai) {
    std::fstream file;
    file.open("battleships_save.txt", std::ios::out);
    if (!file.good()) {
        throw std::runtime_error("Nie udalo sie zapisac stanu klasy Player do pliku!\n");
    }

    player->saveClassToFile(file);
    ai->saveClassToFile(file);

    file.close();
}

int main() {
    InterfaceIO * interface = new IConsole;
    Player * player = nullptr;
    Player * ai = nullptr;
    srand(time(NULL));

    interface->printText("\n\n\tWitamy w grze w statki!\n");

    int choice;
    bool loadingSucceded = true;

    do {
        interface->clearScreen();
        interface->printText("\tWybierz co bys chcial zrobic:\n");
        interface->printText("\t1. Nowa gra\n");
        interface->printText("\t2. Wczytaj gre z pliku\n");
        interface->printText("\t3. Zobacz zasady gry\n");
        interface->printText("\t4. Zobacz instrukcje do gry\n");
        interface->printText("\t5. Wyjsc z gry\n");

        try {
            choice = interface->inputInt(1,5);
        }
        catch (const std::invalid_argument & e) {
            interface->printText("UPS! Nie ma takiej opcji!\n");
            choice = -1;
        }

        switch (choice) {
            case 1:
                // new game
                player = new Player(interface);
                ai = new AIPlayer(interface);
                break;
            
            case 2:
                // load from file
                try {
                    interface->printText("Prosze wprowadzic sciezke do pliku z zapisanym stanem gry: ");
                    std::string filePath;

                    filePath = interface->inputPathFile();
                    
                    std::fstream file;
                    file.open(filePath, std::ios::in);
                    if (!file.good()) {
                        throw std::runtime_error("Nie udalo otworzyc sie pliku!\n");
                    }

                    // ! data validation? if so remember to tie loadingSucceded to it if it fails

                    player = new Player(interface, file);
                    ai = new AIPlayer(interface, file);

                    // ! check if correctly initialized -> PROLLY DONT MAKE IT CUZ IT SEEMS SUPER HARD TO IMPLEMENT?

                    file.close();
                    loadingSucceded = true;
                }
                catch (const std::invalid_argument & e) {
                    interface->printText(e.what());
                    loadingSucceded = false;
                }
                catch (const std::runtime_error & e) {
                    interface->printText(e.what());
                    loadingSucceded = false;
                }

                if (!loadingSucceded) {
                    interface->printText("Wczytywanie danych z gry nie powiodlo sie!\n");
                    interface->printText("Prosze sprobowac jeszcze raz albo wybrac inna opcje!\n\n");
                }

                break;
            
            case 3:
                interface->clearScreen();
                interface->printRules();
                break;

            case 4:
                interface->clearScreen();
                interface->printInstructions();
                break;
            
            case 5:
                //exit
                return 0;
            
            default:
                //do nothing
                break;
        }

    } while ((choice != 1 && choice != 2) || !loadingSucceded);

    // if we get here -> the players are created, it's time to play!
    interface->clearScreen();
    interface->printText("\n\tZaczynamy gre!\n");
    std::this_thread::sleep_for(std::chrono::seconds(2));

    int round = 0;
    int succesfulHit;
    bool savedAndWantToExit = false;
    bool firstChoice = true;

    while (!player->lost() && !ai->lost() && !savedAndWantToExit) {
        succesfulHit = -1;
        
        if (round % 2 == 0) {
            choice = 0;
            //player's turn

            //get what the user wants to do
            do {
                interface->clearScreen();
                if (!firstChoice) {
                    interface->printText("\nNie ma takiej opcji!\n\n");
                }
                player->printBoard(Player::playersOwnBoard);
                interface->printText("\nCo chcesz zrobic:\n");
                interface->printText("1. Oddaj strzal\n");
                interface->printText("2. Zapisz gre i zakoncz\n");

                try {
                    choice = interface->inputInt(1,2);
                }
                catch (const std::invalid_argument & e) {
                    firstChoice = false;
                }

            } while (choice != 1 && choice != 2);
            firstChoice = true;


            switch (choice) {
                case 1:
                    //shoot until miss
                    do {
                        interface->clearScreen();
                        
                        if (succesfulHit == 1) {interface->printText("Trafiony!\n\n");}
                        else if (succesfulHit == 2) {interface->printText("Trafiony zatopiony!\n\n");}

                        player->printBoard(Player::radarBoard);

                        succesfulHit = player->shootAt(ai);

                        if (succesfulHit == 0) { interface->printText("Pudlo!\n\n"); }

                    } while ((succesfulHit == 1 || succesfulHit == 2) && !ai->lost());
                    break;

                case 2:
                    //save to current game state to file and exit
                    try {
                        initializeSavingGame(player, ai);
                        interface->printText("\nPomyslnie zapisano stan gry do pliku: \"battleships_save.txt\"\n");
                    }
                    catch (const std::runtime_error & e) {
                        interface->printText("BLAD ZAPISU DO PLIKU: ");
                        interface->printText(e.what() + '\n');
                    }

                    savedAndWantToExit = true;
                    break;
            }
        }
        else {
            //AI's turn

            interface->printText("\n\nTeraz kolej przeiwnikia\nPrzeciwnik mysli...\n");
            std::this_thread::sleep_for(std::chrono::seconds(3));

            do {
                succesfulHit = ai->shootAt(player);
            } while (succesfulHit != 0 && !player->lost());
        }
        round++;
    }

    //if we get here either someone lost or user saved the game and wants to exit
    if (player->lost()) {
        interface->printText("Przegrales! Przeciwnik zatopil wszystkie twoje statki!\n");
    }
    else if (ai->lost()) {
        interface->printText("Wygrles! Zatopiles wszystkie statki przeciwnika!\n");
    }

    interface->printText("Gra sie skonczyla, program zaraz sie wylaczy.\n");
    interface->printText("Dziekuje za granie!\n");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    delete ai;
    delete player;
    delete interface;
    return 0;
}