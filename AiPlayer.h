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
            generalStrategy = new GeneralStrategy(this->getHand(), this->record);
            matchStrategy = new MatchStrategy(this->getHand(), this->record);
            randomStrategy = new RandomStrategy(this->getHand(), this->record);
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

            // int tieCnt = 0;     // number of games that tie
            // int tieValue = 0;   // total value of card that tie

            int round = record->getRound();
            int* aiPlayedCards = record->getAiPlayedCards();
            int* humanPlayedCards = record->getHumanPlayedCards();
            int* price = record->getPrice();

            // this part of code is to count the number of win, lose, and tie
            int isWin = 0;
            if (aiPlayedCards[round] > humanPlayedCards[round]) {
                isWin = 1;
            } else if (aiPlayedCards[round] < humanPlayedCards[round]) {
                isWin = -1;
            }
            
            // if (isWin == 0) {
            //     // it is tie, record it
            //     tieCnt += 1;
            //     tieValue += price[round];
            // }

            // if score earned is already enough to win the game
            if (this->getPoints() >= ((float)91)/2) {
            // if (this->getPoints() >= (91-tieValue)/2) {
                strategy = randomStrategy; // switch strategy
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
            int* aiPlayedCards = record->getAiPlayedCards();
            int* humanPlayedCards = record->getHumanPlayedCards();
            int* price = record->getPrice();

            // 
            int cnt[3] = {0};
            for (int i=0; i<round; i++) {
                // record differences between human played card and the price card
                int difference = ((humanPlayedCards[i] - price[i]) + 13) % 13;
                if (difference <= 3) {
                    cnt[difference - 1] += 1;
                }
            }

            // if for more than five rounds and human have 60% rates that played match cards
            // ai would switch to the match pattern
            if ((cnt[0] + cnt[1] + cnt[2])/(float)round >= 3/5.0 && round>=5) {
                useMatchPattern = true;

                int total = 0;
                for (int i=0; i<3; i++) {
                    total += cnt[i] * (i+1);
                }
                float match = ((float)total) / (float)round;
                cout << "match is: " << match << endl;

                strategy = matchStrategy;
                strategy->setSuggestValue(match);
            }

            // test code
            if (!useMatchPattern) {
                strategy = generalStrategy;
            }
        }
        
};

#endif
