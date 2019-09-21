#include "Tile.h"
#include "LinkedList.h"

class Bag {
public:

   Bag();
   ~Bag();

   Tile* getFront();
   Tile* getBack();

   void replaceFront(Tile* tile);
   void replaceBack(Tile* tile);

   void printContents();

   std::string toString();
   

private:
   LinkedList* bag;

};
