#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "Suit.h"

using namespace std;

class Strategy {
    private:
        vector<Card> cardPlayed;
        Suit* suit;

    public:
        virtual int playCard(Card price) {
            return 0;
        }
        

        Strategy(Suit* suit) {
            this->suit = suit;
        }

        Suit* getSuit() { return suit; }
};

#endif