#ifndef APT_THE_SCREAM_A2_BOARD_H
#define APT_THE_SCREAM_A2_BOARD_H

#include <string>
#include "Tile.h"
#define EMPTY_TILE '  '

class Board {
public:
    Board();
    void placePiece(Tile piece, std::string pos);
    std::string displayBoard();
    std::string saveBoard();
    bool canPieceBePlaced();
    int rowToInt(char c);

private:
    int gridSize;
    char row;
    int col;
    Tile board[26][26];
};

#endif //APT_THE_SCREAM_A2_BOARD_H
