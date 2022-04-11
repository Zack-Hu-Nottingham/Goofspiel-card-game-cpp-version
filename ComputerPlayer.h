#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"
#include "Strategy.h"
#include "RandomStrategy.h"
#include "MatchStrategy.h"
#include "GeneralStrategy.h"
#include "Record.h"

using namespace std;

class ComputerPlayer: public Player {
    private:
        Strategy* strategy;
        Record* record;
        int loseCnt = 0;
        int tieCnt = 0;
        int tieValue = 0;


    public:
        ComputerPlayer(Record* record): Player()
        {
            this->record = record;
            strategy = new GeneralStrategy(this->getSuit(), this->record);
        }
        
        ~ComputerPlayer() {
            delete(strategy);
        }

        // according to the current strategy, play the card
        int playCard(Card price) {
            return strategy->playCard(price);
        }

        // change or modify the strategy here
        void learnBehavior() {

            int round = record->getRound();
            int* aiHand = record->getAiHand();
            int* playerHand = record->getPlayerHand();
            int* price = record->getPrice();

            int isWin = 0;
            if (aiHand[round] > playerHand[round]) {
                isWin = 1;
                loseCnt = 0;
            } else if (aiHand[round] < playerHand[round]) {
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
                tieValue += price[round];
            }

            if (this->getPoints() >= (91-tieValue)/2) {
                delete(strategy);
                strategy = new RandomStrategy(this->getSuit(), this->record);
            } else {
                detectMatchPattern();
            }
            // if () // 如果发现多局游戏都在使用match，切换到match
        }

        void displayStrategy() {
            strategy->displayStrategy();
        }

        void detectMatchPattern() {

            bool useMatchPattern = false;

            int round = record->getRound();
            int* aiHand = record->getAiHand();
            int* playerHand = record->getPlayerHand();
            int* price = record->getPrice();

            int cnt[3] = {0};
            for (int i=0; i<round; i++) {
                int difference = ((playerHand[i] - price[i]) + 13) % 13;
                // cout << "Difference: " << difference << endl;
                if (difference <= 3) {
                    cnt[difference - 1] += 1;
                }
            }
            // cout << "rate: " << (cnt[0] + cnt[1] + cnt[2])/(float)round<< endl;
            if ((cnt[0] + cnt[1] + cnt[2])/(float)round >= 3/5.0 && round>=5) {
                useMatchPattern = true;
                // cout << "player is using match pattern." << endl;

                // 对于match>=6，是亏本的
                // 对于match<6, 值加一就可以应对
                int total = 0;
                for (int i=0; i<3; i++) {
                    total += cnt[i] * (i+1);
                }
                float match = ((float)total) / (float)round;
                cout << "match is: " << match << endl;

                delete(strategy);   
                strategy = new MatchStrategy(this->getSuit(), this->record);
                strategy->setSuggestValue(match);

            }


        }
};

#endif
