#ifndef CARD_H
#define CARD_H

/*
 * Class Card, the basic component of this game.
*/

class Card {
    private:
        int value;

    public: 
        Card() {};

        Card(int value) {
            this->value = value;
        }

        int getValue() {
            return value;
        }

        // return the card value in string format
        std::string getString() {
            switch(value){
                case 1  :
                    return "A";

                case 11  :
                    return "J";

                case 12  :
                    return "Q";
                
                case 13  :
                    return "K";

                default :
                    std::string tmp = std::to_string(value);
                    return tmp;
            }
        }

};

#endif