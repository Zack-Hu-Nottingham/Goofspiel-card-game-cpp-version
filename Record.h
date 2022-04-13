#ifndef RECORD_H
#define RECORD_H

#include "Hand.h"

/*
 * Record class is used to save the record of the game
 * And this records can be used by ai to leanrn human behavior
*/

class Record {
    private:
        int round;
        int aiPlayedCards[13];         // record ai played card at each round
        int humanPlayedCards[13];     // record human played card at each round
        int price[13];
        Hand* playerHand;
        Hand* aiHand;

    public:
        Record() {
            round = 0;
            for (int i=0; i<13; i++) {
                aiPlayedCards[i] = 0;
                humanPlayedCards[i] = 0;
                price[i] = 0;
            }
        }

        // add a piece of record
        void add(int aiPlayedCards, int humanPlayedCards, int price) {
            this->aiPlayedCards[round] = aiPlayedCards;
            this->humanPlayedCards[round] = humanPlayedCards;
            this->price[round] = price;
            round ++;
        }

        // add human and ai's cards
        void addHand(Hand* playerHand, Hand* aiHand) {
            this->playerHand = playerHand;
            this->aiHand = aiHand;
        }

        int getRound() {
            return round;
        }

        int* getAiPlayedCards() {
            return aiPlayedCards;
        }

        int* getHumanPlayedCards() {
            return humanPlayedCards;
        }

        int* getPrice() {
            return price;
        }

        Hand* getPlayerHand() {
            return playerHand;
        }
        
        Hand* getAIHand() {
            return aiHand;
        }
};

#endif