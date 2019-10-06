#ifndef APT_THE_SCREAM_A2_BOARD_H
#define APT_THE_SCREAM_A2_BOARD_H
#include<iostream>
#include <string>
#include "Tile.h"

class Board {
public:
    Board();

    ~Board();

    void placeTile(Tile* piece, std::string pos);

    void removeTile(std::string pos);

    std::string displayBoard();

//    std::string toString();

    bool canPieceBePlaced(Tile* piece, std::string pos);

    std::string** board;
};

#endif //APT_THE_SCREAM_A2_BOARD_H
