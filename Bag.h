#include "Tile.h"
#include "LinkedList.h"

class Bag {
public:

   Bag();
   Bag(Bag& original);
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
