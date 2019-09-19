
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
        if(current->tile->getTileName().compare(tileName) == 0){
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}

void LinkedList::addFront(Tile& tile){
    Node* newNode = new Node(tile,head);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    //if head wasn't null, then set the new node as the head.
    else{
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

void LinkedList::addBack(Tile& tile){
    Node* newNode = new Node(tile,nullptr);

    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    //if head wasn't null, then set the new node as the tail
    else{
        tail->next = newNode;
        tail = newNode;
    }
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
   }

   else if(index == 0 && current != nullptr){
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
   }

   else if(index == 0 && current != nullptr){
      //Removing first node if it exists
      head = current->next;
      returnTile = current->tile;
      delete current;
      --size;
   }

   return returnTile;
}
