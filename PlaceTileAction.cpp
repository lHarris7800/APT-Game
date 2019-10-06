#include "PlaceTileAction.h"

PlaceTileAction::PlaceTileAction(Tile* playedTile, std::string boardLocation):Action(){
    this->playedTile = playedTile;
    this->boardLocation = boardLocation;
    newTile = nullptr;
}

PlaceTileAction::~PlaceTileAction(){
    if(newTile != nullptr)
        delete newTile;
}

//***No validation*** expects a correct and legal move
void PlaceTileAction::doAction(Bag* bag, Board* board,Player* player){
    //removing tile from players hand and moving it to the board
    player->removeTile(playedTile);
    board->placeTile(playedTile,boardLocation);

    //Getting new tile from bag and adding to players hand
    newTile = bag->getFront();
    player->addTile(new Tile(*newTile));
}

//***No validation*** excpects bag,player,board to be in the state left by doAction 
void PlaceTileAction::undoAction(Bag* bag, Board* board,Player* player){
    //Remove new tile from players hand and replacing it in bag
    player->removeTile(newTile);
    bag->replaceFront(new Tile(*newTile));

    //Removing tile from board and replacing into players hand
    board->removeTile(boardLocation);
    player->addTile(playedTile);
}

std::string PlaceTileAction::toString(){
    std::string build = "PlaceTile,";
    build.append(playedTile->getTileName() + ",");
    build.append(boardLocation + ",");
    build.append(newTile->getTileName());

    return build;
}