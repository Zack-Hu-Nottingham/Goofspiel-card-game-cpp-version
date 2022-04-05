#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"
#include "Strategy.h"

class ComputerPlayer: public Player {
    private:
        Strategy* strategy;


    public:
        ComputerPlayer(): Player()
        {
            strategy = new Random
        }

        // according to the current strategy, play the card
        int playCard(Card price) {


            if (haveCard(price.getValue()+1)) {
                return price.getValue() + 1;
            }
            return -1;
        }


        // change or modify the strategy here
        void learnBehavior(int round, int playerHand, int aiHand, Card price) {

        }
};

#endif