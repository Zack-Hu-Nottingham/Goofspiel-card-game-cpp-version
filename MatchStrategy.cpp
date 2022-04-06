#ifndef MATCHSTRATEGY_H
#define MATCHSTRATEGY_H

#include "Strategy.h"
#include "Card.h"
#include "ComputerPlayer.h"

class MatchStrategy: public Strategy {
    public:
        MatchStrategy(Suit* suit): Strategy(suit) {

        }

        int playCard(Card price) {

            return price.getValue() + 1;
        }
};

#endif