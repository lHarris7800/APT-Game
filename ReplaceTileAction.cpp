#include "ReplaceTileAction.h"
#include "Action.h"

ReplaceTileAction::ReplaceTileAction(Tile* replacedTile):Action(){
        this->replacedTile = replacedTile;
        newTile = nullptr;
}

ReplaceTileAction::~ReplaceTileAction(){
    
}

//***No validation*** expects a correct and legal move
void ReplaceTileAction::doAction(Bag* bag, Board* board,Player* player){
    //removing tile from players hand and returning it to bag
    player->removeTile(replacedTile);
    bag->replaceBack(replacedTile);

    //Getting new tile from bag and adding to players hand
    newTile = bag->getFront();
    player->addTile(newTile);
}

//***No validation*** excpects bag,player to be in the state left by doAction 
void ReplaceTileAction::undoAction(Bag* bag, Board* board,Player* player){
    //Remove new tile from players hand and replacing it in bag
    player->removeTile(newTile);
    bag->replaceFront(newTile);

    //Removing tile from back of bag and returning back to players hand
    player->addTile(bag->getBack());
}