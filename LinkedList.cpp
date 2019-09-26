
#include "LinkedList.h"
#include <iostream>

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
        current = current->next;
        delete previous;
    }
}

int LinkedList::getSize(){
   return size;
}

//This method is to look at player's hand
int LinkedList::searchTile(std::string tileName) {
    Node *current = head;
    int index = 0;
    while(current != nullptr){
        if(current->tile->getTileName().compare(tileName)==0){
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}

void LinkedList::addFront(Tile* tile){
   Node* newNode = new Node(tile,head,nullptr);
   head = newNode;
   size++;

   //Updating tail if newNode is first node
   if(newNode->next == nullptr){
      tail = newNode;
   } else {
      newNode->next->prev = newNode;
   }
      
}

void LinkedList::addBack(Tile* tile){
   Node* newNode = new Node(tile,nullptr,tail);

   if(tail != nullptr){
      //Update lastNode
      tail->next = newNode;
   } else {
      // head if newNode is first node
      head = newNode;
   }

   //Updating tail
   tail = newNode;
   size++;

}

Node* LinkedList::getNodeAt(int index){
   Node* returnNode = nullptr;

  
   if(index < size/2){
      returnNode = head;
      
      for(int i = 0; i < index; ++i){
         
         returnNode = returnNode->next;
      }
   }else{
      returnNode = tail;
      for(int i = size - 1; i > index; --i){
         returnNode = returnNode->prev;
      }
   }

   return returnNode;
}

//Gets an element 
Tile* LinkedList::getAt(int index){
   Tile* tile = nullptr;
   if(index >= 0 && index < size){
      tile = getNodeAt(index)->tile;
   }else{
      //throw std::runtime_error("invalid index");
   }

   return tile;
}

void LinkedList::removeFront(){
   if(size == 1){
      delete head;
      head = nullptr;
      tail = nullptr;
   } else if(size > 0){
      head = head->next;
      delete head->prev;
      head->prev = nullptr;
   }

   size--;
}

void LinkedList::removeBack(){
   if(size == 1){
      delete head;
      head = nullptr;
      tail = nullptr;
   } else if(size > 0){
      tail = tail->prev;
      delete tail->next;
      tail->next = nullptr;
   }

   size--;
}

void LinkedList::removeAt(int index){
   if(index >= 0 && index < size){
      if(index == 0){
         removeFront();
      }else if(index == size - 1){
         removeBack();
      }else if(index < size/2){
         Node* current = head;

         for(int i = 0; i < index; ++i){
            current = current->next;
         }

         current->next->prev = current->prev;
         current->prev->next = current->next;
         delete current;
         --size;

      }else{
         Node* current = tail;

         for(int i = size - 1; i > index; --i){
            current = current->prev;
         }

         current->next->prev = current->prev;
         current->prev->next = current->next;
         delete current;
         --size;
      }
      
   }else{
      //throw std::runtime_error("invalid index");
   }
}

//may be used for random bag order
Tile* LinkedList::getAndRemoveAt(int index){
   Node* node = getNodeAt(index);
   Tile* returnTile = node->tile;

   if(node == head){
      removeFront();
   }else if(node == tail){
      removeBack();
   }else{
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
      --size;
   }

   return returnTile;
}

//Used by bag,player
//Returns tiles in linkedlist
std::string LinkedList::toString(){
   std::string build = std::string("");
   
   Node* current = head;
   build.append(current->tile->getTileName());

   for (int i = 1; i < size; i++) {
      current = current->next;
      build.append(",");
      build.append(current->tile->getTileName());      
   }
   return build;
}
