#include "Tile.h"
#include "LinkedList.h"

class Bag {
public:

   Bag();
   ~Bag();

   Tile* getTile();

   void replaceTile(Tile* tile);

   void printContents();
   

private:
   LinkedList* bag;

};
