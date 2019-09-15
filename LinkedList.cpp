
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   size = 0;

   // TODO
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

Tile* LinkedList::getAt(int index){
   Node* returnNode = head;

   if(index >= 0){
      for(int i = 0; i < index && returnNode != nullptr; i++){
         returnNode = returnNode->next;
      }
   }

   /*TODO bad index handling,
   Current implementation returns a nullptr if index has no node
   Should an exception be thrown?
   */ 
   return returnNode->tile;
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


LinkedList::~LinkedList() {
   Node* current = head;
   Node* previous;


   while(current != nullptr){
      previous = current;
      delete previous;
      current = current->next;
   }
}
