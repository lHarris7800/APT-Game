
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int getSize();

   void addFront(Node& node);
   void addBack(Node& node);
   
   Node* get(int i);
   void remove(int i);

private:
   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
