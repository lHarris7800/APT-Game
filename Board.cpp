#include "Board.h"
#include <iomanip>

#define EMPTY_TILE  ""

Board::Board(){

}

Board::~Board() {

}

bool Board::canPieceBePlaced(Tile* piece, std::string pos){
    int row, column;
    bool result = false;

    row = pos[0]-65; //shows 1,2,3,....

    //Converting Strings to Integers
    column = stoi(pos.substr(1)); // shows A,B,C,...

    if(row >= MAX_SIZE || column >= MAX_SIZE ){
      std::cout << "There are no more than 25 rows, therefore you cannot add the tile in this position";
    }

    else if(board[column][row].compare("") == 0){
      board[column][row] = piece->getTileName();
      result = true;
    }

    else{
      std::cout << "There is a tile already in that position";
    }

    return result;
}

void Board::displayBoard(){
    std::cout << "\n   ";
    for (int i = 0; i < MAX_SIZE; i++) {
        std::cout << "| " << (char) (65 + i) << " ";
    }

    std::cout << "|\n";
    for (int i = 0; i < MAX_SIZE; i++) {
        //Sets the field width
        std::cout << std::setw(2) << i << " ";

        for (int j = 0; j < MAX_SIZE; j++) {
            if (board[i][j].compare("") == 0)
                std::cout << "|   ";
            else
                std::cout << "| " << board[i][j];
        }
        std::cout << "|\n";
    }
}

void Board::placeTile(Tile* piece, std::string pos){
  //Parsing pos to row and column
  int row, column;
  row = pos[0]-65;
  column = stoi(pos.substr(1));

  if (canPieceBePlaced(piece, pos)){
    board[column][row] = piece->getTileName();
  }
}

void Board::removeTile(std::string pos){
  //Parsing pos to row and column
  int row, column;
  row = pos[0]-65;
  column = stoi(pos.substr(1));

  board[column][row] = EMPTY_TILE;
}

//std::string Board::saveBoard(){
//
//}
