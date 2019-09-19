#include "bag.h"
#include "TileCodes.h"
#include <iostream>
#include <stdlib.h>
#include <time.h> 

Bag::Bag(){
    LinkedList* tileSet = new LinkedList();
    bag = new LinkedList();

    //Defining the set of tiles
    for (int i = 0; i < 2; i++)
    {
        //Add all tiles
        tileSet->addFront(new Tile(RED,CIRCLE));
        tileSet->addFront(new Tile(RED,STAR_4));
        tileSet->addFront(new Tile(RED,DIAMOND));
        tileSet->addFront(new Tile(RED,SQUARE));
        tileSet->addFront(new Tile(RED,STAR_6));
        tileSet->addFront(new Tile(RED,CLOVER));
    }
    
    //Seeding random numbers
    srand (time(NULL));
    int tilesLeft;
    //Adding tiles to bag from set of tiles to bag in random order
    while ((tilesLeft = tileSet->getSize()) != 0)
        bag->addFront(tileSet->getAndRemoveAt(rand() % tilesLeft));
    
    
}

Bag::~Bag(){
    delete bag;
}

Tile* Bag::getTile(){
    Tile* returnTile = bag->getAt(0);
    bag->removeAt(0);
    return returnTile;
}

void Bag::replaceTile(Tile* tile){
    //TODO adding back to bag randomly?
    bag->addBack(tile);
}

void Bag::printContents(){
    Tile* currentTile = bag->getAt(0);
    std::cout << 0 << std::endl <<
        currentTile->colour << ", " <<
        currentTile->shape << std::endl;

    for(int i = 1;i<bag->getSize();i++){
        currentTile = bag->getAt(i);

        std::cout << i << std::endl <<
            currentTile->colour << ", " <<
            currentTile->shape << std::endl;
    }
}