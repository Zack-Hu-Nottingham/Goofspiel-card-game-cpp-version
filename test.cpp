#include <iostream>
#include <string>

#include "Suit.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Record.h"

#define ROUND_OF_GAME 1 
#define LEVEL_OF_INTELLIGENCE 1

using namespace std;

int input_handler();

int main() {
    // cout << "Welcome to Goofspiel!" << endl;
    // cout << "Shall we start now?" << endl;

    // initialize prize suit
    Suit* valueDeck = new Suit(true);

    // initialize record
    Record * record = new Record();

    // initialize computer player and human player
    HumanPlayer* player = new HumanPlayer();
    ComputerPlayer* computerPlayer = new ComputerPlayer(record);

    record->addSuit(player->getSuit(), computerPlayer->getSuit());

    vector<Card> foo = player->getSuit()->getCards();                               
    cout << "Your cards are: ";
    for (int i=0; i<13; i++) {
        cout << foo[i].getString() << " ";
    }
    cout << endl << endl;
    
    Card price;
    int playerHand, aiHand;
    bool isInputValid = false;
    int round = 0;
    while(valueDeck->getCards().size() >= 1) {

        // randomly pop an value card;
        price = valueDeck->pop();
        cout << "Round: " << ++round <<" The current price card is: " << price.getString() << endl;
        cout << "Your remain cards are: ";
        player->getSuit()->display();
        cout << "AI's remain cards are: ";
        computerPlayer->getSuit()->display();
        cout << endl << "AI's strategy is ";
        computerPlayer->displayStrategy();

        // according to the card, computer select its hand first
        aiHand = computerPlayer->playCard(price);

        // read in user's hand
        while(!isInputValid) {
            playerHand = player->input_handler();
            if (playerHand != -1 && player->haveCard(playerHand)) {
                isInputValid = true;
                cout << endl;
            } else {
                cout << "Input card is invalid, please input again. " << endl;
            }
        }
        isInputValid = false;

        cout << "The card you played is: " << playerHand << endl;
        cout << "The card AI played is: "  << aiHand << endl;

        if (playerHand > aiHand) {
            player->earnPoints(price.getValue());
            cout << "You win this turn." << endl;
        } else if (playerHand < aiHand) {
            computerPlayer->earnPoints(price.getValue());
            cout << "AI win this turn." << endl;
        } else {
            cout << "No one earn the point." << endl;
        }

        cout << "Your current points are: " << player->getPoints() << endl;
        cout << "AI's current points are: " << computerPlayer->getPoints() << endl;
        cout << endl;

        record->add(aiHand, playerHand, price.getValue());

        computerPlayer->learnBehavior();

        cout << endl;
    }
    
    // Check if user win or AI win
    int winOrLose = player->getPoints() - computerPlayer->getPoints();
    if (winOrLose == 0) {
        cout << "This is a tie." << endl;
    } else if (winOrLose > 0) {
        cout << "Well done, you win the game!" << endl;
    } else {
        cout << "Oops, you lose the game" << endl;
    }

    cout << "Your score is: " << player->getPoints();
    cout << " AI score is: " << computerPlayer->getPoints() << endl;

    // free the memory used
    delete(record);
    delete(computerPlayer);
    delete(player);
    delete(valueDeck);
}
