#ifndef MATCHSTRATEGY_H
#define MATCHSTRATEGY_H

#include <time.h>
#include "Strategy.h"
#include "Card.h"
#include "AiPlayer.h"

/*
 * Match strategy inherit class strategy. 
 * It guess the card that user would play, and accordingly decides what card to play.
 * This strategy would be applied when ai detects human player use deterministic strategy.
*/

class MatchStrategy: public Strategy {
    private:
        float suggestValue = 0; // it is the card that ai guess user would play
    public:
        MatchStrategy(Suit* suit, Record* record): Strategy(suit, record) {}
        
        void displayStrategy() {
            cout << "Match strategy." << endl;
        }

        void setSuggestValue(float suggestValue) {
            this->suggestValue = suggestValue;
        }

        float getSuggestValue() {
            return suggestValue;
        }

        int playCard(Card price) {
            return playMatchCard(price);
        }

        int playMatchCard(Card price) {

            int suggestCard = ((int)(price.getValue() + ceil(suggestValue))) % 13 + 1;
            cout << "Match strategy want to play card " << suggestCard << endl;

            // if ai have the card that is just bigger than human would play
            if (this->getSuit()->findAndDelete(suggestCard)) { 
                return suggestCard;
            }

            // //如果当前这张牌是所有卡堆里最高费的卡
            // if (!this->getSuit()->existBigger(price.getValue())) { 
            //     cout << "This is the max card. " << endl;
            //     if (playerSuit->findBiggest() > aiSuit->findBiggest()) { //对方手牌大
            //         cout << "He is bigger than me. " << endl;
            //         return this->getSuit()->findAndDeleteSmallest();
            //     } else if (playerSuit->findBiggest() < aiSuit->findBiggest()) { // ai大
            //         cout << "I'm bigger. " << endl;
            //         srand((unsigned)time(NULL)); 
            //         int random = rand() % 10;
            //         if (random < 5) { //出大牌抢下来
            //             cout << "I'll take it." << endl;
            //             return this->getSuit()->findAndDeleteBiggest();
            //         } else { //出第二大牌防对手摆烂
            //             cout << "I don't want you bailan." << endl;
            //             for (int i=playerSuit->findBiggest() - aiSuit->findBiggest(); i>0; i--) {
            //                 if (this->getSuit()->findAndDelete(aiSuit->findBiggest()-i)) {
            //                     return aiSuit->findBiggest()-i;
            //                 }
            //             }
            //         }
            //     } else { //一样大就兑掉
            //         cout << "手牌一样大，兑掉" << endl;
            //         return this->getSuit()->findAndDeleteBiggest();
            //     }
            // }


            // for cards with higher value
            if (price.getValue() >= 8) { 
                for (int i=0; i<3; i++) {
                    if (this->getRecord()->getPlayerSuit()->existCard(suggestCard-i)) {
                        // if both ai and human player have that card
                        // ai would play that card to prevent human earn score
                        if (this->getSuit()->findAndDelete(suggestCard-i)) {
                            return suggestCard-i;
                        }

                        // if human have that card, but ai don't have
                        // ai would let it go, play the smallest card
                        return this->getSuit()->findAndDeleteSmallest();
                    }
                }
                
            }

            // for cards with low value
            // ai would also let it go, play the current smallest card
            cout << "low value card bailan" << endl;
            return this->getSuit()->findAndDeleteSmallest();
        }

};

#endif