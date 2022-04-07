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
            // randomly generate a bonus
            int bonus = rand() % 1 + 1;
            
            // if the card with value = (price + bonus) exits
            // play that card
            if (this->getSuit()->haveCard(price.getValue()+bonus)) { // find and delete
                return price.getValue() + bonus;
            }

            // if not exists, try to use alternative card
            if (bonus == 2 && this->getSuit()->haveCard(price.getValue() + 1)) {
                return price.getValue() + 1;
            }
            if (bonus == 1 && this->getSuit()->haveCard(price.getValue() + 2)) {
                return price.getValue() + 2;
            }

            // if either card with extra bonus=1, bonus=2 does 
            // not exists
            return this->getSuit()->findBiggest();
        }
};

#endif