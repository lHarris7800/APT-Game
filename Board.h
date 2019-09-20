#ifndef APT_THE_SCREAM_A2_BOARD_H
#define APT_THE_SCREAM_A2_BOARD_H
#include<iostream>
#include <string>
#include "Tile.h"
#define  MAX_SIZE 26

class Board {
public:
    Board();

    ~Board();

//    void placePiece(Tile* piece, std::string pos);

    std::string displayBoard();

    std::string saveBoard();

    bool canPieceBePlaced(Tile* piece, std::string pos);

private:
    std::string board[MAX_SIZE][MAX_SIZE];
};

#endif //APT_THE_SCREAM_A2_BOARD_H
