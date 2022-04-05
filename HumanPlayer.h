#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer: public Player {
    private:

    public:
        HumanPlayer(): Player()
        {

        }
        
        
        int input_handler() {
            cout << "Which cards you want to play: ";
            string input;
            cin >> input;
            
            if (input == "A" || input == "a" || input == "1") {
                return 1;
            } else if (input == "2") {
                return 2;
            } else if (input == "3") {
                return 3;
            } else if (input == "4") {
                return 4;
            } else if (input == "5") {
                return 5;
            } else if (input == "6") {
                return 6;
            } else if (input == "7") {
                return 7;
            } else if (input == "8") {
                return 8;
            } else if (input == "9") {
                return 9;
            } else if (input == "10") {
                return 10;
            } else if (input == "J" || input == "j" || input == "11") {
                return 11;
            } else if (input == "Q" || input == "q" || input == "12") {
                return 12;
            } else if (input == "K" || input == "k" || input == "13") {
                return 13;
            } else {
                return -1; // illegal input
            }
        }
};

#endif