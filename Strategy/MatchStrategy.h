#ifndef MATCHSTRATEGY_H
#define MATCHSTRATEGY_H

#include <time.h>
#include "Strategy.h"
#include "../Card.h"
#include "../Player/AiPlayer.h"

/*
 * Match strategy inherit class strategy. 
 * It guess the card that user would play, and accordingly decides what card to play.
 * This strategy would be applied when ai detects human player use deterministic strategy.
*/

class MatchStrategy: public Strategy {
    private:
        float suggestValue = 0; // it is the card that ai guess user would play
    public:
        MatchStrategy(Hand* hand, Record* record): Strategy(hand, record) {}
        
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
            if (this->getHand()->findAndDelete(suggestCard)) { 
                return suggestCard;
            }

            // //如果当前这张牌是所有卡堆里最高费的卡
            // if (!this->getHand()->existBigger(price.getValue())) { 
            //     cout << "This is the max card. " << endl;
            //     if (playerHand->findBiggest() > aiHand->findBiggest()) { //对方手牌大
            //         cout << "He is bigger than me. " << endl;
            //         return this->getHand()->findAndDeleteSmallest();
            //     } else if (playerHand->findBiggest() < aiHand->findBiggest()) { // ai大
            //         cout << "I'm bigger. " << endl;
            //         srand((unsigned)time(NULL)); 
            //         int random = rand() % 10;
            //         if (random < 5) { //出大牌抢下来
            //             cout << "I'll take it." << endl;
            //             return this->getHand()->findAndDeleteBiggest();
            //         } else { //出第二大牌防对手摆烂
            //             cout << "I don't want you bailan." << endl;
            //             for (int i=playerHand->findBiggest() - aiHand->findBiggest(); i>0; i--) {
            //                 if (this->getHand()->findAndDelete(aiHand->findBiggest()-i)) {
            //                     return aiHand->findBiggest()-i;
            //                 }
            //             }
            //         }
            //     } else { //一样大就兑掉
            //         cout << "手牌一样大，兑掉" << endl;
            //         return this->getHand()->findAndDeleteBiggest();
            //     }
            // }


            // for cards with higher value
            if (price.getValue() >= 8) { 
                for (int i=0; i<3; i++) {
                    if (this->getRecord()->getPlayerHand()->existCard(suggestCard-i)) {
                        // if both ai and human player have that card
                        // ai would play that card to prevent human earn score
                        if (this->getHand()->findAndDelete(suggestCard-i)) {
                            return suggestCard-i;
                        }

                        // if human have that card, but ai don't have
                        // ai would let it go, play the smallest card
                        return this->getHand()->findAndDeleteSmallest();
                    }
                }
                
            }

            // for cards with low value
            // ai would also let it go, play the current smallest card
            cout << "low value card bailan" << endl;
            return this->getHand()->findAndDeleteSmallest();
        }

};

#endif