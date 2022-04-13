#ifndef GENERALSTRATEGY_H
#define GENERALSTRATEGY_H

#include "Strategy.h"

/*
 * General strategy inherit strategy class. 
 * ai would use this strategy, if it can not tell
 * what specific strategy that human player are using.
 * It plays card in general way.
*/

class GeneralStrategy: public Strategy {
    private:
        int rate = 8;
    public:
        GeneralStrategy(Suit* suit, Record* record): Strategy(suit, record) {}

        void displayStrategy() {
            cout << "General strategy." << endl;
        }

        int playCard(Card price) {
            
            int round = this->getRecord()->getRound();
            int* prices = this->getRecord()->getPrice();
            int* aiHand = this->getRecord()->getAiHand();
            int* playerHand = this->getRecord()->getPlayerHand();
            Suit* playerSuit = this->getRecord()->getPlayerSuit();
            Suit* aiSuit = this->getRecord()->getAISuit();

            // If it is the first round, take special care
            if (round == 0) {
                srand((unsigned)time(0));
                int i = (rand() % 10);
                if (price.getValue() <= 6 && i >= 3) {
                    // play the smallest card
                    // cout << "first round bailan" << endl;
                    return this->getSuit()->findAndDeleteSmallest();
                } else {
                    // play card normally
                    return playMatchCard(price);
                }
            }

            // for later rounds, if the card value is less than 6
            if (price.getValue() <= 6) {
                // randomly decides whether play the smallest card
                srand((unsigned)time(0));
                int i = (rand() % 10);
                if (i <= rate) {
                    // cout << "later bailan" << endl;
                    return this->getSuit()->findAndDeleteSmallest();
                }
            }
            return playMatchCard(price);
        }

        // according to the price card, play price + 1 or price + 2
        int playMatchCard(Card price) {
            // randomly generate a bonus
            srand((unsigned)time(NULL));
            int bonus = rand() % 2 + 1;
            
            // if the card with value = (price + bonus) exits
            // play that card
            if (this->getSuit()->findAndDelete(price.getValue()+bonus)) { // find and delete
                return price.getValue() + bonus;
            }

            // if not exists, try to use alternative card
            if (bonus == 2 && this->getSuit()->findAndDelete(price.getValue() + 1)) {
                return price.getValue() + 1;
            }
            if (bonus == 1 && this->getSuit()->findAndDelete(price.getValue() + 2)) {
                return price.getValue() + 2;
            }

            // if either card with extra bonus=1, bonus=2 does not exists
            return this->getSuit()->findJustBigger(price.getValue());
        }
};


#endif