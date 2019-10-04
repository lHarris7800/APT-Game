#include "Controller.h"
#include "ReplaceTileAction.h"
#include "PlaceTileAction.h"
#define PLAYER_ONE  1
#define PLAYER_TWO  2

Controller::Controller(Player* playerOne, Player* playerTwo){
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
    bag = new Bag();
    board = new Board();
    gameHistory = new GameHistory(bag,playerOne,playerTwo);
}

Controller::~Controller(){

}

bool Controller::validPlaceTile(Tile* playedTile, std::string boardLocation){
    int row, column;
    bool result = false;
    row = boardLocation[0]-65; //shows 1,2,3,....
    column = stoi(boardLocation.substr(1)); // shows A,B,C,...
    if(row >= MAX_SIZE || column >= MAX_SIZE){
        std::cout << "There are no more than 25 rows, Therefore you cannot add the tile in this position";
    }

    else if (board->board[column][row].compare("") == 0){
        result = true;
    }
    else
        std::cout << "There is a tile already in that position";
    return result;
}

bool Controller::validReplaceTile(Tile* replacedTile){
    bool result = false;
    int position = playerOne->getHand()->searchTile(replacedTile->getTileName());

    if(position != -1){
        result = true;
    }
    else{
        std::cout << "The tile you want to replace doesn't exist in your hand.";
    }

    return result;
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method

void Controller::placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation){
    Action* newAction = new PlaceTileAction(playedTile, boardLocation);
    if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    
    gameHistory->addAction(newAction,playerNum);
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method

void Controller::replaceTile(PlayerNum playerNum, Tile* replacedTile){
    Action* newAction = new ReplaceTileAction(replacedTile);
     if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    gameHistory->addAction(newAction, playerNum);
}
