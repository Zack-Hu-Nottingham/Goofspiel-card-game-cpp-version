#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "../Hand.h"
#include "../Record.h"

using namespace std;

/*
 * Strategy class is the base class of a serise of classes. 
*/

class Strategy {
    private:
        vector<Card> cardPlayed;
        Hand* hand;
        Record* record;

    public:
        Strategy(Hand* hand, Record* record) {
            this->hand = hand;
            this->record = record;
        }

        // abstract methods that could be overloaded
        virtual int playCard(Card price) { return 0; }        
        virtual void displayStrategy() {}       
        virtual void setSuggestValue(float match) {} 

        Hand* getHand() { return hand; }
        Record* getRecord() { return record; }
};

#endif