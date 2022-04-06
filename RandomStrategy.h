#ifndef RANDOM_STRATEGY_H
#define RANDOM_STRATEGY_H

#include <stdlib.h>

#include "Strategy.h"
#include "Card.h"
#include "ComputerPlayer.h"

using namespace std;

class RandomStrategy: public Strategy {
    public:
        RandomStrategy(Suit* suit): Strategy(suit) {
        }

        int playCard(Card price) {
            Card randomChoice = this->getSuit()->pop(true); // randomly pop a card from suit
            return randomChoice.getValue();
        }
};

#endif