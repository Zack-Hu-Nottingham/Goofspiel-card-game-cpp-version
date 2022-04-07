#ifndef SUIT_H
#define SUIT_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "Card.h"

using namespace std;

class Suit {
    private:
        vector<Card> cards;

    public:

        Suit(bool isRandom = false) {
            // Initialize with 13 cards
            for (int i=1; i<14; i++) {
                Card card(i);
                cards.push_back(card);
            }

            // Shuffle the suit
            if (isRandom) {
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::default_random_engine e(seed);
                std::shuffle(std::begin(cards), std::end(cards), e);
            }
        }

        // Pop a card out radomly
        Card pop(bool isRandom = false) {

            int length = cards.size();
            Card answer;
            if (isRandom) {
                vector<Card>::iterator itor;
                srand((unsigned)time(NULL)); 
                int index = rand() % length;
                itor = cards.begin() + index;

                answer = cards[index];
                cards.erase(itor);
            } else {
                answer = cards[length-1];
                cards.pop_back();
            }

            return answer;
        }

        vector<Card> getCards() {
            return cards;
        }

        bool deleteCard(int position) {
            if (position > cards.size()) {
                return false;
            } else {
                cards.erase(cards.begin() + position);
                return true;
            }
        }

        void display() {
            for (int i=0; i<cards.size(); i++) {
                cout << (cards.begin()+i)->getString() << " ";
            }
            cout << endl;
        }

        bool haveCard(int value) {
            bool exist = false;
            vector<Card> cards = this->getCards();
            for (int i=0; i<cards.size(); i++) {
                if (cards[i].getValue() == value) {
                    if (this->deleteCard(i)) { // make sure it is deleted
                        return true;
                    }
                }
            }
            return false;
        }

        int findBiggest() {
            vector<Card> cards = this->getCards();
            
            int max = 0;
            int maxCnt = 0;

            for (int i=0; i<cards.size(); i++) {
                if (cards[i].getValue() >= max) {
                    max = cards[i].getValue();
                    maxCnt = i;
                }
            }

            if (!this->deleteCard(maxCnt)) { // make sure it is deleted
                cout << "The card to be deleted not exist";
            }
            
            return max;            
        }
};


#endif