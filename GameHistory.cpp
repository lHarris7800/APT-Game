#include "gameHistory.h"
#include "ActionNode.h"

#define PLAYER_ONE  1
#define PLAYER_TWO  2
#define UNDO_TURNS  3

GameHistory::GameHistory(Bag* bag, Board* board, Player* p1, Player* p2){
    head = nullptr;
    tail = nullptr;
    size = 0;

    iBag = *bag;
    iBoard = *board;
    iPlayerOne = *p1;
    iPlayerTwo = *p2;
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
    Player* playerOne = new Player(iPlayerOne);
    Player* playerTwo = new Player(iPlayerTwo);

    Bag* bag = new Bag(iBag);

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