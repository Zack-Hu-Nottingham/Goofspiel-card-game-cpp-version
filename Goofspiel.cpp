#include <iostream>
#include <string>

#include "Hand.h"
#include "Player/AiPlayer.h"
#include "Player/HumanPlayer.h"
#include "Record.h"

#define ROUND_OF_GAME 1 
#define LEVEL_OF_INTELLIGENCE 1

using namespace std;

int input_handler();

int main() {

    cout << endl << "Welcome to Goofspiel!" << endl;
    cout << "Shall we start now? (Click enter to start, q to quit)" << endl;

    if (cin.get() == 'q') { // quit the game as the user type in q
        return 0;
    }

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

    // main loop of the game
    while(valueDeck->getCards().size() >= 1) {

        // randomly pop an value card;
        price = valueDeck->pop();

        // hints for each round of game
        cout << endl << "Round " << ++round << endl;
        cout <<"The current price card is: " << price.getString() << endl;

        // according to the card, ai select the card it want to play first
        aiBid = aiPlayer->playCard(price);

        // read in user's hand
        while(!isInputValid) {
            humanBid = player->input_handler();
            if (humanBid != -1 && player->findAndDelete(humanBid)) {
                isInputValid = true;
                cout << endl;
            } else {
                cout << "Input card is invalid, please input again. " << endl;
            }
        }
        isInputValid = false;

        if (humanBid > aiBid) {
            player->earnPoints(price.getValue());
            cout << "You win this turn." << endl;
        } else if (humanBid < aiBid) {
            aiPlayer->earnPoints(price.getValue());
            cout << "AI win this turn." << endl;
        } else {
            player->earnPoints((float)price.getValue() / (float)2.0);
            aiPlayer->earnPoints((float)price.getValue() / (float)2.0);
            cout << "You guys both earned " << (float)price.getValue() / (float)2.0 << " points." << endl;
        }

        // hints on current round of game
        cout << "The card you played is: " << humanBid;
        cout << ", the card AI played is: "  << aiBid << endl;

        cout << "Your current points are: " << player->getPoints();
        cout << " AI's current points are: " << aiPlayer->getPoints() << endl;

        // record the round of game, for later ai learning
        record->add(aiBid, humanBid, price.getValue());

        // according to the rounds played previously, decides ai's strategy
        aiPlayer->learnBehavior();

        cout << endl;
    }
    



    // Check if user win or AI win
    int winOrLose = player->getPoints() - aiPlayer->getPoints();
    if (winOrLose == 0) {
        cout << "This is a tie." << endl;
    } else if (winOrLose > 0) {
        cout << "Well done, you win the game!" << endl;
    } else {
        cout << "Oops, you lose the game" << endl;
    }

    cout << "Your score is: " << player->getPoints();
    cout << " AI score is: " << aiPlayer->getPoints() << endl;



    // free the memory used
    delete(record);
    delete(aiPlayer);
    delete(player);
    delete(valueDeck);
}
