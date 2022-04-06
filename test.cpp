#include <iostream>
#include <string>

#include "Suit.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

#define ROUND_OF_GAME 1 
#define LEVEL_OF_INTELLIGENCE 1

using namespace std;

int input_handler();

int main() {
    // cout << "Welcome to Goofspiel!" << endl;
    // cout << "Shall we start now?" << endl;

    // initialize prize suit
    Suit* valueDeck = new Suit(true);

    // initialize computer player and human player
    HumanPlayer* player = new HumanPlayer();
    ComputerPlayer* computerPlayer = new ComputerPlayer();

    vector<Card> foo = player->getSuit()->getCards();                               
    cout << "Your cards are: ";
    for (int i=0; i<13; i++) {
        cout << foo[i].getString() << " ";
    }
    cout << endl << endl;
    
    Card price;
    int playerHand, aiHand;
    int round = 0;
    bool isInputValid = false;
    while(valueDeck->getCards().size() >= 1) {


        // randomly pop an value card;
        price = valueDeck->pop();
        cout << "The current price card is: " << price.getString() << endl;
        cout << "Your remain cards are: ";
        player->getSuit()->display();


        // according to the card, computer select its hand first
        aiHand = computerPlayer->playCard(price);

        // read in user's hand
        while(!isInputValid) {
            playerHand = player->input_handler();
            if (playerHand != -1 && player->haveCard(playerHand)) {
                isInputValid = true;
                cout << endl;
            } else {
                cout << "Input card is invalid, please input again: " << endl;
            }
        }
        isInputValid = false;

        cout << "The card you played is: " << playerHand << endl;
        cout << "The card AI played is: "  << aiHand << endl << endl;




        // 
        if (playerHand > aiHand) {
            player->earnPoints(price.getValue());
            cout << "You win this turn." << endl;
        } else if (playerHand < aiHand) {
            computerPlayer->earnPoints(price.getValue());
            cout << "AI win this turn." << endl;
        } 

        cout << "Your current points are: " << player->getPoints() << endl;
        cout << "AI's current points are: " << computerPlayer->getPoints() << endl << endl;

        ++ round;
        computerPlayer->learnBehavior(round, playerHand, aiHand, price);

        cout << endl << endl;
    }
    cout << endl;
    

}
