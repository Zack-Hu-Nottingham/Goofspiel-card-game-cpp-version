#ifndef GENERALSTRATEGY_H
#define GENERALSTRATEGY_H

#include "Strategy.h"

class GeneralStrategy: public Strategy {
    private:
        int rate = 8;
    public:
        GeneralStrategy(Suit* suit, Record* record): Strategy(suit, record) {

        }

        void displayStrategy() {
            cout << "General strategy." << endl;
        }

        int playCard(Card price) {
            
            int round = this->getRecord()->getRound();
            int* aiHand = this->getRecord()->getAiHand();
            int* playerHand = this->getRecord()->getPlayerHand();
            int* prices = this->getRecord()->getPrice();

            // 针对高费卡，进行特判
            // if (price.getValue() == 13) {
            //     bool playerHave = true;
            //     bool aiHave = true;
            //     for (int i=0; i<13; i++) {
            //         if (aiHand[i] == 13) {
            //             aiHave = false;
            //         }
            //         if (playerHand[i] == 13) {

            //         }
            //     }
            // }

            // 如果是第一局，特判
            if (round == 0) {
                srand((unsigned)time(0));
                int i = (rand() % 10);
                if (price.getValue() <= 6 && i >= 3) {
                    // 开摆！
                    cout << "first round bailan" << endl;
                    return this->getSuit()->findSmallest();
                } else {
                    // 正常出牌
                    return playMatchCard(price);
                    // this->getSuit()->findJustBigger(price.getValue());
                }
            }

            // 不是第一局的话
            if (price.getValue() <= 6) {
                //适度摆烂
                srand((unsigned)time(0));
                int i = (rand() % 10);
                if (i <= rate) {
                    // 开摆！
                    cout << "later bailan" << endl;
                    return this->getSuit()->findSmallest();
                }
            }
            return playMatchCard(price);
        }

        int playMatchCard(Card price) {

            cout << "play match card." << endl;

            // randomly generate a bonus
            srand((unsigned)time(NULL));
            int bonus = rand() % 2 + 1;
            // cout << "bonus:" << bonus << endl;
            
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
            return this->getSuit()->findJustBigger(price.getValue());
        }
};


#endif