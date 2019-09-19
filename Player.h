//
// Created by Shahrzad Rafezi on 16/9/19.
//

#ifndef STARTER_CODE_PLAYER_H
#define STARTER_CODE_PLAYER_H
#include <string>
#include "LinkedList.h"
#define MAX_TILES 6

class Player {

public:

    Player(std::string playerName);

    Player(std::string playerName, int score, LinkedList hand);

    ~Player();

    std::string getName();

    int getScore();

    void addScore();

    bool addTile(Tile& tile);

    std::string playerScore();

    std::string playerHand();

    std::string toString();

private:
    std::string playerName;
    int score;
    LinkedList* hand;
};


#endif //STARTER_CODE_PLAYER_H
