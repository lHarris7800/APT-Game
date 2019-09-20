#include "Board.h"
#include <iostream>
#include <cstdio>

Board::Board()
{
  gridSize = 26;
  for (int row = 0; row < gridSize; row++)
  {
      for (int column = 0; column < gridSize; column++)
      {
          board[row][column] = EMPTY_TILE;
      }
  }
}
bool Board::canPieceBePlaced(Tile piece, std::string pos)
{
  if(board[rowToInt(pos[0])][pos[1]] != EMPTY_TILE )
  {
    return false;
  } else
  {
    return true;
  }

}

std::string Board::displayBoard()
{
  char cRow = 'A';
  int cCol = 0;
  std::string board;

  board += ((char)32);
  for(int i = 0; i < gridSize; i++)
  {
    // Print x-axis labels
    board += ((char)32);
    board += std::to_string(cCol);
    cCol++;
  }
  board += ('\n');
    for (int row = 0; row < gridSize; row++) {
      // Print y-axis labels
      board += (cRow);
      cRow++;
        for (int column = 0; column <= gridSize; column++) {
            board += ('|');
            board += (array[row][column]);
        }
        board += ('\n');
    }
    std::cout << board << '\n';
    return board;
}

void Board::placePiece(Tile piece, std::string pos)
{
  if (canPieceBePlaced(piece, pos))
  {
    board[rowToInt(pos[0])][pos[1]] = piece;
  }
}

std::string Board::saveBoard()
{

}

int rowToInt(char c)
{
  int row;
  if((int)c > 64 && c < 97)
  {
    row = (int)c - 65;
  } else
  {
    row = (int)c - 97;
  }
  return row;
}
