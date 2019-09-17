
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::clear() {
    Node* current = head;
    Node* previous;

    while(current != nullptr){
        previous = current;
        delete previous;
        current = current->next;
    }
}

int LinkedList::getSize(){
   return size;
}

void LinkedList::addFront(Tile& tile){
   Node* newNode = new Node(tile,head);
   head = newNode;
   ++size;   

   //Updating tail if newNode is first node
   if(newNode->next == nullptr)
      tail = newNode;
}

void LinkedList::addBack(Tile& tile){
   Node* newNode = new Node(tile,nullptr);

   if(tail != nullptr){
      //Update lastNode
      tail->next = newNode;
   } else {
      // head if newNode is first node
      head = newNode;
   }
   //Updating tai
   tail = newNode;
   ++size;

}

//Gets an element 
Tile* LinkedList::getAt(int index){
    Tile *tile = nullptr;

    if (head != nullptr) {
        Node *currNode = head;
        for (int j = 0; j < index; ++j) {
            currNode = currNode->next;
        }
        tile = currNode->tile;
    }

    return tile;
}

void LinkedList::removeAt(int index){
   Node* current = head;
   Node* previous;

   //Finding node to remove
   if(index > 0){
      for(int i = 0; i < index && current != nullptr; i++){
         previous = current;
         current = current->next;
      }

      //Removing i'th node if it exists
      if(current != nullptr){
         previous->next = current->next;
         delete current;
         --size;
      }
   } else if(index == 0 && current != nullptr){
      //Removing first node if it exists
      head = current->next;
      delete current;
      --size;
   }
}

//may be used for random bag order
Tile* LinkedList::getAndRemoveAt(int index){
   Tile* returnTile = nullptr;
   Node* current = head;
   Node* previous;

   //Finding node to remove
   if(index > 0){
      for(int i = 0; i < index && current != nullptr; i++){
         previous = current;
         current = current->next;
      }

      //Removing i'th node if it exists
      if(current != nullptr){
         previous->next = current->next;
         returnTile = current->tile;
         delete current;
         --size;
      }
   } else if(index == 0 && current != nullptr){
      //Removing first node if it exists
      head = current->next;
      returnTile = current->tile;
      delete current;
      --size;
   }

   return returnTile;
}
