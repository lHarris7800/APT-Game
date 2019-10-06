#include "Board.h"
#include <iomanip>

#define EMPTY_TILE  "  "
#define MAX_SIZE  26


Board::Board(){
    for (int column = 0; column < MAX_SIZE; column++) {
        for (int row = 0; row < MAX_SIZE; row++) {
            board[column][row] = EMPTY_TILE;
        }
    }
}

Board::~Board() {
}

bool Board::canPieceBePlaced(Tile* piece, std::string pos){
    bool result = false;

    int row = (pos[0]-65); //shows 1,2,3,....

    //Converting Strings to Integers
    int column = stoi(pos.substr(1)); // shows A,B,C,...

    if(row >= MAX_SIZE || column >= MAX_SIZE){
      std::cout << "There are no more than 25 rows, therefore you cannot add the tile in this position" << std::endl;
      result = false;
    }
    else if(board[column][row].compare(EMPTY_TILE) == 0){
        if((row % 2 == 0 && column % 2 == 0) || (row % 2 != 0 && column % 2 != 0))
            result= true;
        else
            std::cout << "\n You can't place a tile there" << std::endl;
    }

    else
      std::cout << "\n There is a tile already in that position" << std::endl;

    return result;
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
        }else
        {
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

// TODO: To be implemented
//std::string Board::toString(){
//
//}
