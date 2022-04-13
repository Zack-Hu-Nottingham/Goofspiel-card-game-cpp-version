#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "Suit.h"
#include "Record.h"

using namespace std;

/*
 * Strategy class is the base class of a serise of classes. 
*/

class Strategy {
    private:
        vector<Card> cardPlayed;
        Suit* suit;
        Record* record;

    public:
        Strategy(Suit* suit, Record* record) {
            this->suit = suit;
            this->record = record;
        }

        // abstract methods that could be overloaded
        virtual int playCard(Card price) { return 0; }        
        virtual void displayStrategy() {}       
        virtual void setSuggestValue(float match) {} 

        Suit* getSuit() { return suit; }
        Record* getRecord() { return record; }
};

#endif