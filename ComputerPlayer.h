#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"
#include "Strategy.h"
#include "RandomStrategy.h"

using namespace std;

class ComputerPlayer: public Player {
    private:
        Strategy* strategy;


    public:
        ComputerPlayer(): Player()
        {
            strategy = new RandomStrategy(this->getSuit());
        }

        // according to the current strategy, play the card
        int playCard(Card price) {
            return strategy->playCard(price);
        }

        // change or modify the strategy here
        void learnBehavior(int round, int playerHand, int aiHand, Card price) {

        }
};

#endif