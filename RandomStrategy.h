#ifndef RANDOM_STRATEGY_H
#define RANDOM_STRATEGY_H

#include <stdlib.h>

#include "Strategy.h"
#include "Card.h"
#include "AiPlayer.h"

using namespace std;

/*
 * Random strategy inherit class strategy, it plays card randomly. 
 * This strategy is only applied when ai already earned enough score to win.
*/

class RandomStrategy: public Strategy {
    public:
        RandomStrategy(Suit* suit, Record* record): Strategy(suit, record) {
        }

        void displayStrategy() {
            cout << "random strategy." << endl;
        }

        int playCard(Card price) {
            Card randomChoice = this->getSuit()->pop(true); // randomly pop a card from suit
            return randomChoice.getValue();
        }
};

#endif