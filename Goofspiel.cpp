#include <iostream>
#include <string>

#include "Suit.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
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

    // initialize prize suit
    Suit* valueDeck = new Suit(true);

    // initialize record, which would be used to help ai learning
    Record * record = new Record();

    // initialize ai player and human player
    HumanPlayer* player = new HumanPlayer();
    AiPlayer* aiPlayer = new AiPlayer(record);

    // add the pointers of suits to the record, to let the record have comperhensive view
    record->addSuit(player->getSuit(), aiPlayer->getSuit());


    Card price;                         // price card
    int playerHand, aiHand;             // card that ai, human played
    bool isInputValid = false;          // determines user input valid
    int round = 0;                      

    // main loop of the game
    while(valueDeck->getCards().size() >= 1) {

        // randomly pop an value card;
        price = valueDeck->pop();

        // hints for each round of game
        cout << endl << "Round " << ++round << endl;
        cout <<"The current price card is: " << price.getString() << endl;
        cout << "Your remain cards are: ";
        player->getSuit()->display();
        cout << "AI's remain cards are: ";
        aiPlayer->getSuit()->display();
        cout << endl << "AI's strategy is ";
        aiPlayer->displayStrategy();

        // according to the card, ai select the card it want to play first
        aiHand = aiPlayer->playCard(price);

        // read in user's hand
        while(!isInputValid) {
            playerHand = player->input_handler();
            if (playerHand != -1 && player->findAndDelete(playerHand)) {
                isInputValid = true;
                cout << endl;
            } else {
                cout << "Input card is invalid, please input again. " << endl;
            }
        }
        isInputValid = false;

        cout << "The card you played is: " << playerHand;
        cout << ", the card AI played is: "  << aiHand << endl;

        if (playerHand > aiHand) {
            player->earnPoints(price.getValue());
            cout << "You win this turn." << endl;
        } else if (playerHand < aiHand) {
            aiPlayer->earnPoints(price.getValue());
            cout << "AI win this turn." << endl;
        } else {
            cout << "No one earn the point." << endl;
        }

        cout << "Your current points are: " << player->getPoints();
        cout << " AI's current points are: " << aiPlayer->getPoints() << endl;
        cout << endl;

        record->add(aiHand, playerHand, price.getValue());

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
