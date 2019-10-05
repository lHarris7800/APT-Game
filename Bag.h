
#ifndef STARTER_CODE_BAG_H
#define STARTER_CODE_BAG_H

#include "Tile.h"
#include "LinkedList.h"

class Bag {
public:

   Bag();
   Bag(Bag& original);
   Bag(LinkedList* bag);

   ~Bag();

   Tile* getFront();
   Tile* getBack();

   void replaceFront(Tile* tile);
   void replaceBack(Tile* tile);

   LinkedList* getBag();

   void printContents();

   std::string toString();
   

private:
   LinkedList* bag;

};


#endif //STARTER_CODE_BAG_H