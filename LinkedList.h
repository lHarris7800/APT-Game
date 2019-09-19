
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();

   ~LinkedList();

   int getSize();

   void clear();

   int searchTile(std::string tileName);

   void addFront(Tile* tile);

   void addBack(Tile* tile);

   Tile* getAt(int i);

   void removeAt(int i);

   Tile* getAndRemoveAt(int i);

private:
   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
