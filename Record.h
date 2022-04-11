#ifndef RECORD_H
#define RECORD_H

#include "Suit.h"

class Record {
    private:
        int round;
        int aiHand[13];
        int playerHand[13];
        int price[13];
        Suit* playerSuit;
        Suit* aiSuit;

    public:
        Record() {
            round = 0;
            for (int i=0; i<13; i++) {
                aiHand[i] = 0;
                playerHand[i] = 0;
                price[i] = 0;
            }
        }

        void add(int aiHand, int playerHand, int price) {
            this->aiHand[round] = aiHand;
            this->playerHand[round] = playerHand;
            this->price[round] = price;
            round ++;
        }

        void addSuit(Suit* playerSuit, Suit* aiSuit) {
            this->playerSuit = playerSuit;
            this->aiSuit = aiSuit;
        }

        int getRound() {
            return round;
        }

        int* getAiHand() {
            return aiHand;
        }

        int* getPlayerHand() {
            return playerHand;
        }

        int* getPrice() {
            return price;
        }

        Suit* getPlayerSuit() {
            return playerSuit;
        }
        
        Suit* getAISuit() {
            return aiSuit;
        }
};

#endif