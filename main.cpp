/**
 * @file main.cpp
 * @author Adrian Zaba (adrianzabax@gmail.com || adrizab055@student.polsl.pl)
 * @brief Main source file for the Battleships game. <br>Also available at: https://github.com/Tinuloth/Battleships
 * 
 * @details detailed here if not then delete
 * 
 * @version 0.9
 * @date 2021-08-08
 * 
 */
// ! Do I need the iostream here?
#include <iostream>

#include "Player.h"
#include "AIPlayer.h"
#include "IConsole.h"
#include <thread>
#include <chrono>
// ! here in aiplayer?

using namespace std;

int main() {
    InterfaceIO * interface = new IConsole;
    Player * player;
    Player * ai; // ! or do i need AIPLayer * ai; here?
    srand(time(NULL));

    interface->printText("\n\n\tWitamy w grze w statki!\n");


    int choice;
    do {
        interface->printText("\tWybierz co bys chcial zrobic:\n");
        interface->printText("\t1. Nowa gra\n");
        interface->printText("\t2. Wczytaj gre z pliku\n");
        interface->printText("\t3. Zobacz zasady gry\n");
        interface->printText("\t4. Zobacz instrukcje do gry\n");
        interface->printText("\t5. Wyjsc z gry\n");

        try {
            choice = interface->inputInt(1,5);
        }
        catch (std::invalid_argument & e) {
            //interface->printText(e.what() + '\n');
            interface->printText("UPS! Nie ma takiej opcji!\n");
            choice = -1;
        }

        switch (choice) {
            case 1:
                player = new Player(interface);
                ai = new AIPlayer; // ! either this breaks the game
                break;
            
            case 2:
                //z pliku
                break;
            
            case 3:
                // ! clearscreen?
                //print rules
                break;

            case 4:
                // ! clearscreen?
                //print instructions
                break;
            
            case 5:
                //exit
                return 0;
            
            default:
                //do nothing
                break;
        }

    } while (choice != 1 && choice != 2);
    
    // if we get here -> the players are created, it's time to play!
    // clear screen?
    interface->printText("\tZaczynamy gre!\n");

    int round = 0;
    int succesfulHit = 0;
    bool savedAndWantToExit = false;
    bool firstChoice = true;

    while (!player->lost() && !ai->lost() && !savedAndWantToExit) {
        succesfulHit = 0;
        
        if (round % 2 == 0) {
            choice = 0;
            //player's turn

            //get what the user wants to do
            do {
                //clearScreen();
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
                catch (std::invalid_argument & e) {
                    firstChoice = false;
                }

            } while (choice != 1 && choice != 2);

            switch (choice) {
                case 1:
                    //shoot until miss
                    do {
                        player->printBoard(Player::radarBoard);

                        succesfulHit = player->shootAt(ai);
                        
                        switch(succesfulHit) {
                            case 0:
                                interface->printText("Pudlo!\n");
                                break;

                            case 1:
                                interface->printText("Trafiony!\n");
                                break;
                            
                            case 2:
                                interface->printText("Trafiony zatopiony!\n");
                                break;
                        }

                    } while (succesfulHit == 1 || succesfulHit == 2);
                    break;

                case 2:
                    //save to current game state to file and exit
                    try {
                        // !
                        //save player to file
                        //save ai to file
                    }
                    catch (std::runtime_error & e) {
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
            } while (succesfulHit != 0);
        }
        round++;
    }

    //if we get here either someone lost or user saved the game and wants to exit
    //clearScreen?
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