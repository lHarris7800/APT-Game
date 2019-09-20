
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

   void removeFront();
   void removeBack();

   Tile* getAt(int i);
   void removeAt(int i);

   Tile* getAndRemoveAt(int i);

   std::string toString();

private:
   Node* head;
   Node* tail;
   int size;

   Node* getNodeAt(int i);
};

#endif // ASSIGN2_LINKEDLIST_H
