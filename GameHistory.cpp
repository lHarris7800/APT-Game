#include "GameHistory.h"

#define PLAYER_ONE  1
#define PLAYER_TWO  2
#define UNDO_TURNS  3

GameHistory::GameHistory(Bag* bag, Player* p1, Player* p2){
    std::cout << "Post" << std::endl;
    head = nullptr;
    tail = nullptr;
    size = 0;

    iBag = new Bag(*bag);
    iPlayerOne = new Player(*p1);
    iPlayerTwo = new Player(*p2);
}

GameHistory::~GameHistory(){
    std::cout << "GameHistory delete" << std::endl;
    delete iPlayerOne;
    delete iPlayerTwo;
    delete iBag;

    clear();
}

void GameHistory::clear() {
    
    if(head != nullptr){
        ActionNode* current = head->next;
    
        while(current != nullptr){
            delete current->prev;
            current = current->next;
        }
    }

    delete tail;
}

void GameHistory::addAction(Action* action,PlayerNum playerNum){
    ActionNode* newNode = new ActionNode(nullptr,tail,action,playerNum);
    
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

void GameHistory::replay(){
    Player* playerOne = new Player(*iPlayerOne);
    Player* playerTwo = new Player(*iPlayerTwo);

    Bag* bag = new Bag(*iBag);

    Board* board = new Board();

    ActionNode* currAction = head;
    while(currAction != nullptr){
        std::cout << "up here" << std::endl;
        if(currAction->playerNum == PLAYER_ONE)
            currAction->action->doAction(bag,board,playerOne);
        else{
            currAction->action->doAction(bag,board,playerTwo);
            std::cout << "out" << std::endl;
        }
        std::cout << "here" << std::endl;
        currAction = currAction->next;
        board->displayBoard();
    }

    delete playerOne;
    delete playerTwo;
    delete bag;
    delete board;
}

void GameHistory::undo(Bag* bag, Board* board, Player* playerOne, Player* playerTwo){
    for(int i = 0; i < UNDO_TURNS*2 && tail != nullptr;i++){
        if(tail->playerNum == PLAYER_ONE)
            tail->action->undoAction(bag,board,playerOne);
        else
            tail->action->undoAction(bag,board,playerTwo);
        
        tail = tail->prev;
        if(tail != nullptr)
            delete tail->next;
        else{
            delete head;
            head = nullptr;
        }
    }
}