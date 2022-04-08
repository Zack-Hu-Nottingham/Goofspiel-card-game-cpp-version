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

        ~Player() {
            // free malloced memory
            delete(suit);
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

            return suit->haveCard(value);
        }
        
};

#endif