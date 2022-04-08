#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"
#include "Strategy.h"
#include "RandomStrategy.h"
#include "MatchStrategy.h"

using namespace std;

class ComputerPlayer: public Player {
    private:
        Strategy* strategy;
        int loseCnt = 0;
        int tieCnt = 0;
        int tieValue = 0;


    public:
        ComputerPlayer(): Player()
        {
            strategy = new MatchStrategy(this->getSuit());
        }
        
        ~ComputerPlayer() {
            delete(strategy);
        }

        // according to the current strategy, play the card
        int playCard(Card price) {
            return strategy->playCard(price);
        }

        // change or modify the strategy here
        void learnBehavior(int round, int playerHand, int aiHand, Card price) {
            
            int isWin = 0;
            if (aiHand > playerHand) {
                isWin = 1;
                loseCnt = 0;
            } else if (aiHand < playerHand) {
                isWin = -1;
                loseCnt += 1;
            }

            if (isWin == 1) {
                // detect if player lose it intendedly 
                
            } else if (isWin == -1) {
                if (loseCnt >= 2){
                    // switch algorithm
                    delete(strategy);
                    // strategy = new RandomStrategy(this->getSuit());
                }
            
            } else if (isWin == 0) {
                // continue?
                tieCnt += 1;
                tieValue += price.getValue();
            }

            if (this->getPoints() >= (91-tieValue)/2) {
                delete(strategy);
                strategy = new RandomStrategy(this->getSuit());
            }
        }

        void displayStrategy() {
            strategy->displayStrategy();
        }
};

#endif
