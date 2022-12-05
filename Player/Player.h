#ifndef PLAYER_H
#define PLAYER_H

/*
 * Player is the base class for HumanPlayer and AiPlayer.
 * It provide the basic operation on player socre and cards.
*/

class Player {
    private:
        float points; // points that player earned
        Hand* hand; // player's hand
        
    public:
        Player() {
            points = 0.0;
            hand = new Hand();
        }

        ~Player() {
            // free malloced memory
            delete(hand);
        }

        void earnPoints(float points) {
            this->points += points;
        }

        float getPoints() {
            return points;
        }

        Hand* getHand() {
            return hand;
        }

        bool findAndDelete(int value) {
            return hand->findAndDelete(value);
        }
        
};

#endif