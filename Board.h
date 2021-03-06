#ifndef APT_THE_SCREAM_A2_BOARD_H
#define APT_THE_SCREAM_A2_BOARD_H
#include<iostream>
#include <string>
#include "Tile.h"
#include <iomanip>
#define EMPTY_TILE  "  "
#define MAX_SIZE  26

class Board {
public:
    Board();

    ~Board();

    void placeTile(Tile* piece, std::string pos);

    void removeTile(std::string pos);

    bool boardEmpty();

    std::string toString();

    std::string board[MAX_SIZE][MAX_SIZE];
};

#endif //APT_THE_SCREAM_A2_BOARD_H
