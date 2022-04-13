#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"
#include "Strategy.h"
#include "RandomStrategy.h"
#include "MatchStrategy.h"
#include "GeneralStrategy.h"
#include "Record.h"

using namespace std;

/*
 * AiPlayer is derived from Player.
 * It contain private field strategy and record.
*/

class AiPlayer: public Player {

    private:
        Strategy* strategy;     // strategy that ai is going to apply
        MatchStrategy* matchStrategy;
        RandomStrategy* randomStrategy;
        GeneralStrategy* generalStrategy;
        Record* record;         // record of the game, help ai learn human player's behavior

    public:
        AiPlayer(Record* record): Player()
        {
            this->record = record;

            // initialize all the possible strategy
            generalStrategy = new GeneralStrategy(this->getSuit(), this->record);
            matchStrategy = new MatchStrategy(this->getSuit(), this->record);
            randomStrategy = new RandomStrategy(this->getSuit(), this->record);
            strategy = generalStrategy;
        }
        
        ~AiPlayer() {
            delete(generalStrategy);
            delete(matchStrategy);
            delete(randomStrategy);
        }

        // according to the current strategy, play the card
        int playCard(Card price) {
            return strategy->playCard(price);
        }

        // change or modify the strategy here
        void learnBehavior() {

            int tieCnt = 0;     // number of games that tie
            int tieValue = 0;   // total value of card that tie

            int round = record->getRound();
            int* aiHand = record->getAiHand();
            int* playerHand = record->getPlayerHand();
            int* price = record->getPrice();

            // this part of code is to count the number of win, lose, and tie
            int isWin = 0;
            if (aiHand[round] > playerHand[round]) {
                isWin = 1;
            } else if (aiHand[round] < playerHand[round]) {
                isWin = -1;
            }
            
            if (isWin == 0) {
                // it is tie, record it
                tieCnt += 1;
                tieValue += price[round];
            }

            // if score earned is already enough to win the game
            if (this->getPoints() >= (91-tieValue)/2) {
                // delete(strategy);
                strategy = randomStrategy;
            } else {
                detectMatchPattern();
            }
        }

        // display the current strategy that are using, for test purpose
        void displayStrategy() {
            strategy->displayStrategy();
        }


        // detect whether human player using deterministic strategy
        void detectMatchPattern() {

            bool useMatchPattern = false;

            // take out the information stored in records
            int round = record->getRound();
            int* aiHand = record->getAiHand();
            int* playerHand = record->getPlayerHand();
            int* price = record->getPrice();

            // 
            int cnt[3] = {0};
            for (int i=0; i<round; i++) {
                // record differences between human played card and the price card
                int difference = ((playerHand[i] - price[i]) + 13) % 13;
                if (difference <= 3) {
                    cnt[difference - 1] += 1;
                }
            }

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

                strategy = matchStrategy;
                strategy->setSuggestValue(match);
            }
        }
        
};

#endif
