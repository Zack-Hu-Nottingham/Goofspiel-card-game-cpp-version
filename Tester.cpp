#include <iostream>
#include <string>

#include "Hand.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
#include "Record.h"

#define LEVEL_OF_INTELLIGENCE 1

#define ROUND_OF_GAME 5000
#define N 5

using namespace std;

int input_handler();

int winCnt, loseCnt, tieCnt;
float aiScore, testerScore;


int main() {

    for (int v=0; v<ROUND_OF_GAME; v++) {
        // initialize prize hand
        Hand* valueDeck = new Hand(true);

        // initialize record, which would be used to help ai learning
        Record * record = new Record();

        // initialize ai player and human player
        HumanPlayer* player = new HumanPlayer();
        AiPlayer* aiPlayer = new AiPlayer(record);

        // add the pointers of hands to the record, to let the record have comperhensive view
        record->addHand(player->getHand(), aiPlayer->getHand());


        Card price;                         // price card
        int humanBid, aiBid;                // card that ai, human bid
        bool isInputValid = false;          // determines user input valid
        int round = 0;                      

        int remainCard[13] = {1};
        for (int i=0; i<13; i++) {
            remainCard[i] = 1;
        }
        srand(time(NULL));
        bool isFound = false;

        // main loop of the game
        while(valueDeck->getCards().size() >= 1) {

            // randomly pop an value card;
            price = valueDeck->pop();
            // cout << "price is: " << price.getValue() << endl;

            // according to the card, ai select the card it want to play first
            aiBid = aiPlayer->playCard(price);

            // N is the value higher than price 
            isFound = false;
            while(!isFound) {
                humanBid = rand() % 13 + 1;
                // cout << "human bid: " << humanBid << endl;
                if (remainCard[humanBid-1] == 1) {
                    remainCard[humanBid-1] = 0;
                    isFound = true;
                }
            } 
            

            // cout << "The card you played is: " << humanBid;
            // cout << ", the card AI played is: "  << aiBid << endl;

            if (humanBid > aiBid) {
                player->earnPoints(price.getValue());
                // cout << "You win this turn." << endl;
            } else if (humanBid < aiBid) {
                aiPlayer->earnPoints(price.getValue());
                // cout << "AI win this turn." << endl;
            } else {
                player->earnPoints((float)price.getValue() / (float)2.0);
                aiPlayer->earnPoints((float)price.getValue() / (float)2.0);
                // cout << "You guys both earned " << (float)price.getValue() / (float)2.0 << " points." << endl;
            }

            // cout << "Your current points are: " << player->getPoints();
            // cout << " AI's current points are: " << aiPlayer->getPoints() << endl;
            cout << endl;

            record->add(aiBid, humanBid, price.getValue());

            aiPlayer->learnBehavior();

            cout << endl;
        }
        



        // Check if user win or AI win
        int winOrLose = player->getPoints() - aiPlayer->getPoints();
        if (winOrLose == 0) {
            // cout << "This is a tie." << endl;
            tieCnt += 1;
        } else if (winOrLose > 0) {
            // cout << "Well done, you win the game!" << endl;
            loseCnt += 1;
        } else {
            // cout << "Oops, you lose the game" << endl;
            winCnt += 1;
        }

        // cout << "Your score is: " << player->getPoints();
        // cout << " AI score is: " << aiPlayer->getPoints() << endl;

        aiScore += aiPlayer->getPoints();
        testerScore += player->getPoints();

        // free the memory used
        delete(record);
        delete(aiPlayer);
        delete(player);
        delete(valueDeck);

    }
    cout << "Total " << ROUND_OF_GAME << " rounds of games." << endl;
    cout << "Ai win " << winCnt << " rounds, earn " << aiScore << " scores." << endl;
    cout << "Tester win " << loseCnt << " rounds, earn " << testerScore << " scores." << endl;

}
