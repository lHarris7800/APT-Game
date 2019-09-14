
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

void LinkedList::addFront(Node& newNode){
   newNode.next = head;
   head = &newNode;
   ++size;   

   //Updating tail if newNode is first node
   if(newNode.next == nullptr)
      tail = &newNode;
}

void LinkedList::addBack(Node& newNode){
   if(tail != nullptr){
      tail->next = &newNode;
      tail = &newNode;
   } else {
      //Updating tail and head if newNode is first node
      tail = &newNode;
      head = &newNode;
   }
   ++size;

}

Node* LinkedList::get(int index){
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
   return returnNode;
}

void LinkedList::remove(int index){
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
