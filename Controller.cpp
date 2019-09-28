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
    gameHistory = new GameHistory(bag,board,playerOne,playerTwo);
}


//Updates bag, board, players with new move and add move to history
//Validation tobe implemented before calling this method
void Controller::placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation){
    Action* newAction = new PlaceTileAction(playedTile,boardLocation);
    if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    
    gameHistory->addAction(newAction,playerNum);
}

//Updates bag, board, players with new move and add move to history
//Validation tobe implemented before calling this method
void Controller::replaceTile(PlayerNum playerNum, Tile* replacedTile){
    Action* newAction = new ReplaceTileAction(replacedTile);
     if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    gameHistory->addAction(newAction, playerNum);
}
