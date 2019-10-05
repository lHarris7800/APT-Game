#include "Board.h"
#include <iomanip>

#define EMPTY_TILE  ""

Board::Board(){
    for (int row = 0; row < MAX_SIZE; row++) {
        for (int column = 0; column < MAX_SIZE; column++) {
            board[row][column] = "  ";
        }
    }
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
std::cout << std::setw(4);
	  for(int col = 0; col < MAX_SIZE; col++) {
	    if(col % 2 == 0) {
	      std::cout << col << "    ";
	    }
	  }
	  std::cout << std::endl;

	  for (int row = 0; row < MAX_SIZE; row++) {
	      std::cout << (char) (65 + row) << " ";
	      for (int column = 0; column <= MAX_SIZE; column++) {
	        if(row % 2 == 0 && column % 2 == 0) {
	          std::cout << "|";
	        } else if(row % 2 != 0 && column % 2 != 0){
	          std::cout << "|";
	        }
	          std::cout << board[row][column];
	      }
	      std::cout << std::endl;
	  }
	  std::cout << std::setw(7);
	  for(int col = 0; col < MAX_SIZE; col++) {
	    if(col % 2 != 0) {
	      std::cout << col << "    ";
	    }
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

// TODO: To be implemented
std::string Board::toString(){

}
