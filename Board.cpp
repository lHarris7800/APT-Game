#include "Board.h"
#include <iomanip>

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

//void Board::placePiece(Tile* piece, std::string pos){
//  if (canPieceBePlaced(piece, pos)){
//    board[rowToInt(pos[0])][pos[1]] = piece;
//  }
//}

//std::string Board::saveBoard(){
//
//}
