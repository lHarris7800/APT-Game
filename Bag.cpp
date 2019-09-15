#include "bag.h"
#include "TileCodes.h"

Bag::Bag(){
    bag = new LinkedList();

    //TODO adding all tiles to bag,
    //to be added in a random order?
    for (int i = 0; i < 2; i++)
    {
        //Add all tiles
        bag->addFront(*(new Tile(RED,CIRCLE)));
        bag->addFront(*(new Tile(RED,STAR_4)));
        bag->addFront(*(new Tile(RED,DIAMOND)));
        bag->addFront(*(new Tile(RED,SQUARE)));
        bag->addFront(*(new Tile(RED,STAR_6)));
        bag->addFront(*(new Tile(RED,CLOVER)));
    }
    
}

Bag::~Bag(){
    delete bag;
}

Tile* Bag::getTile(){
    Tile* returnTile = bag->getAt(0);
    bag->removeAt(0);
    return returnTile;
}

void Bag::replaceTile(Tile& tile){
    //TODO adding back to bag randomly?
    bag->addBack(tile);
}