#include "Board.h"

Board::Board(){
    for (int column = 0; column < MAX_SIZE; column++) {
        for (int row = 0; row < MAX_SIZE; row++) {
            board[column][row] = EMPTY_TILE;
        }
    }
}

Board::~Board() {
}


void Board::placeTile(Tile* piece, std::string pos){
  //Parsing pos to row and column
  int column = pos[0]-65;
  int row = stoi(pos.substr(1));

  board[column][row] = piece->getTileName();
}

void Board::removeTile(std::string pos){
  //Parsing pos to row and column
  int row = pos[0]-65;
  int column = stoi(pos.substr(1));

  board[column][row] = EMPTY_TILE;
}

bool Board::boardEmpty(){
    bool boardEmpty = true;

    for (int column = 0; column < MAX_SIZE && boardEmpty; column++) {
        for (int row = 0; row < MAX_SIZE && boardEmpty; row++) {
            if(board[column][row] != EMPTY_TILE)
                boardEmpty = false;
        }
    }

    return boardEmpty;
}

std::string Board::toString(){
    std::string build = "      ";

    //Displays the top column numbers(0,2,4,...)
    for(int col = 0; col < MAX_SIZE; col++) {
        if(col % 2 == 0) {
            build.append(std::to_string(col));
            if(col < 10)
                build.append("    ");
            else
                build.append("   ");
        }
    }
    //Top boarder
    build.append("\n    ---------------------------------------------------------------------\n");

    for (int row = 0; row < MAX_SIZE; row++) {

        //Displays A, B, C, D, ... in each row
        build.append(std::string(1,65 + row) + "   ");

        if(row % 2 == 0)
            build.append("| ");
        else
            build.append("  ");

        //structures the board according to assignment specs
        for (int column = 0; column < MAX_SIZE; column++) {
            if(row % 2 == column % 2 ){
                build.append(board[row][column]);
            }
            else{
                build.append(" | ");
            }
        }

        //Right boarder
        if(row % 2 != 0)
            build.append(" |");
        else
            build.append("  ");

        build.append("\n");
    }

    //Bottom boarder
    build.append("    ---------------------------------------------------------------------\n");

    //Displays the bottom column numbers(1,3,5,...)
    build.append("          ");
    for(int col = 0; col < MAX_SIZE; col++) {
        if(col % 2 != 0) {
            build.append(std::to_string(col));
            if(col < 10)
                build.append("    ");
            else
                build.append("   ");
        }
    }
    return build;
}

