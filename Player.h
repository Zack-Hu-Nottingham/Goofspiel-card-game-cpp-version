#ifndef PLAYER_H
#define PLAYER_H

/*
 * Player is the base class for HumanPlayer and AiPlayer.
 * It provide the basic operation on player socre and cards.
*/

class Player {
    private:
        int points; // points that player earned
        Suit* suit; // player's cards
        
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
            this->points += points;
        }

        int getPoints() {
            return points;
        }

        Suit* getSuit() {
            return suit;
        }

        bool findAndDelete(int value) {
            return suit->findAndDelete(value);
        }
        
};

#endif