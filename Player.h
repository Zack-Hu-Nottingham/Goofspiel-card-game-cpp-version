#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
        int points;
        Suit* suit;
        
    public:
        Player() {
            points = 0;
            suit = new Suit();
        }

        void earnPoints(int points) {
            // cout << "points are: " << points << endl;
            this->points += points;
        }

        int getPoints() {
            return points;
        }

        Suit* getSuit() {
            return suit;
        }

        bool haveCard(int value) {
            bool exist = false;
            vector<Card> cards = this->getSuit()->getCards();
            for (int i=0; i<cards.size(); i++) {
                if (cards[i].getValue() == value) {
                    if (this->getSuit()->deleteCard(i)) { // make sure it is deleted
                        return true;
                    }
                }
            }
            return false;
        }
        
};

#endif