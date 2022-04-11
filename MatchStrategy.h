#ifndef MATCHSTRATEGY_H
#define MATCHSTRATEGY_H

#include <time.h>
#include "Strategy.h"
#include "Card.h"
#include "ComputerPlayer.h"

class MatchStrategy: public Strategy {
    private:
        float suggestValue = 0;
    public:
        MatchStrategy(Suit* suit, Record* record): Strategy(suit, record) {

        }
        
        void setSuggestValue(float suggestValue) {
            this->suggestValue = suggestValue;
        }

        float getSuggestValue() {
            return suggestValue;
        }

        void displayStrategy() {
            cout << "Match strategy." << endl;
        }

        int playCard(Card price) {
            return playMatchCard(price);
        }

        int playMatchCard(Card price) {

            int suggestCard = ((int)(price.getValue() + ceil(suggestValue))) % 13 + 1;
            cout << "Match strategy want to play card " << suggestCard << endl;

            if (this->getSuit()->haveCard(suggestCard)) { // 如果推荐卡不存在
                return suggestCard;
            }

            if (price.getValue() >= 8) { //对于高价值的卡
                for (int i=0; i<3; i++) {
                    // if (this->getSuit()->existCard(suggestCard-i)) {

                    // }
                    if (this->getRecord()->getPlayerSuit()->existCard(suggestCard-i)) {
                        //如果对手有那张牌
                        //如果我有那么兑掉
                        if (this->getSuit()->haveCard(suggestCard-i)) {
                            return suggestCard-i;
                        }
                        //如果我没有，对方大概率会打，所以摆烂
                        return this->getSuit()->findSmallest();
                    }
                }
                
            }
            //对于低价值的卡
            //二话不说直接开摆！
            cout << "low value card bailan" << endl;
            return this->getSuit()->findSmallest();
        }

};

#endif