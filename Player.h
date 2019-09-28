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

    Player();

    Player(std::string playerName);

    Player(std::string playerName, int score, LinkedList* hand);

    Player(Player& original);

    ~Player();

    std::string getName();

    int getScore();

    LinkedList* getHand();

    void addScore();

    bool addTile(Tile* tile);

    void removeTile(Tile* tile);

    std::string playerHand();

    std::string toString();

private:
    std::string playerName;
    int score;
    LinkedList* hand;
};


#endif //STARTER_CODE_PLAYER_H
