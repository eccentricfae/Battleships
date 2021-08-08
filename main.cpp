/**
 * @file main.cpp
 * @author Adrian Zaba (adrizab055@student.polsl.pl)
 * @brief brief desc
 * @details description
 * @version 1.0
 * @date 2021-07-08
 */

#include <iostream>
#include <exception>
#include "Player.h"
#include "AIPlayer.h"
#include "Ships.h"
#include "Interface.h"

using namespace std;


int main() {
    InterfaceIO * interface = new IConsole;
    Player * player;
    AIPlayer * ai;

    int choice;
do {
    interface->printMsg("\n\n");
    interface->printMsg("\tWitamy w grze w statki!\n");
    interface->printMsg("\tWybierz co bys chcial zrobic:");
    interface->printMsg("\t1. Nowa gra");
    interface->printMsg("\t2. Wczytaj gre z pliku");
    interface->printMsg("\t3. Zobacz zasady gry");
    interface->printMsg("\t4. Zobacz instrukcje do gry");
    
    try {
        choice = interface->inInt(1,4);
    }
    catch (std::invalid_argument & e) {
        interface->printMsg(e.what());
        interface->printMsg("UPS! Nie ma takiej opcji, konczymy program!");

        std::this_thread::sleep_for(std::chrono::seconds(5));
        delete interface;
        return 0;
    }

    switch(choice) {
        case 1:
            player = new Player(interface);
            ai = new AIPlayer(interface);
            break;
        
        case 2:
            //z pliku:
            try {
                std::string filePath;
                // take path to the save file
                cin >> filePath;

                // validate data in said file

                // create Player and AIPLayer from file
                // can throw
                player = new Player(filePath);
                // can throw
                ai = new AIPlayer(filePath, player->getPosInFile());
            }
            catch (std::runtime_error & e) {
                interface->printMsg(e.what());
                interface->printMsg("Nie powiodlo sie wczytywanie gry z pliku. Wylaczamy program");
                return 0;
            }

            //std::cout << "not yet implemented!";
            break;

        case 3:
            interface->clearScreen();
            interface->printRules();
            break;

        case 4:
            interface->clearScreen();
            interface->printInstructions();
    }
} while (choice == 3 || choice == 4);
    
    // if we get here: the players are created and its time to play
    interface->clearScreen();
    interface->printMsg("Zaczynamy gre!\n");
    
    int round = 0;
    bool savedAndWantToExit = false;
    int hit = 0;
    while (!player->lost() && !ai->lost() && !savedAndWantToExit) {
        if (round % 2 == 0) {
            //kolej gracza
            hit = 0;

            interface->clearScreen();
            player->printBoard(1);
            interface->printMsg("\nCo chcesz zrobic:");
            interface->printMsg("1. Oddaj strzal");
            interface->printMsg("2. Zapisz gre i zakoncz");
            try {
                choice = interface->inInt(1,2);
            }
            catch (std::invalid_argument& e) {
                interface->printMsg("Ups! Wybrales cos niedozwolonego, twoja runda mija.");
                continue;
            }

            switch(choice) {
                case 1:
                    //strzelaj dopoki nie chybisz
                    do {
                        player->printBoard(2);
                        hit = player->shootAt(ai);
                        switch(hit) {
                            case 0:
                                interface->printMsg("Pudlo!");
                                break;

                            case 1:
                                interface->printMsg("Trafiles!");
                                break;

                            case 2:
                                interface->printMsg("Trafiony zatopiony!");
                                break;
                        }
                    } while (hit == 1 || hit == 2 );
                    break;
                
                case 2:
                    //zapisz aktualny stan do pliku
                    try {
                        player->saveGameToFile();
                        ai->saveGameToFile();
                    }
                    catch(std::runtime_error & e) {
                        interface->printMsg("BLAD ZAPISU DO PLIKU: ");
                        interface->printMsg(e.what());
                    }

                    // poinformuj ze zapisano i chcesz wyjsc
                    savedAndWantToExit = true;
                    break;
            }
        }
        else {
            hit = 0;
            interface->printMsg("\n\nTeraz kolej przeciwnika");
            interface->printMsg("Przeciwnik mysli!");
            // iluzja ze AI mysli
            std::this_thread::sleep_for(std::chrono::seconds(3));

            // shoots at the player
            do {
                hit = ai->shootAt(player);
            } while(hit == 1 || hit == 2);
        }
        round++;
    }

    //if we get here someone lost
    interface->clearScreen();
    if (player->lost()) {
        interface->printMsg("Przegrales! Komputer z toba wygral! :)");
    }
    else if (ai->lost()) {
        interface->printMsg("Gratulacje! Wygrales z komputerem gre w statki!");
    }
    interface->printMsg("Gra sie skonczyla, program sie zaraz skonczy");
    std::this_thread::sleep_for(std::chrono::seconds(5));

    delete player;
    delete ai;
    delete interface;


    return 0;
}