#include "GameHistory.h"

#define PLAYER_ONE  1
#define PLAYER_TWO  2
#define UNDO_TURNS  1

GameHistory::GameHistory(Bag* bag, Player* p1, Player* p2){
    head = nullptr;
    tail = nullptr;
    size = 0;

    iBag = new Bag(*bag);
    iPlayerOne = new Player(*p1);
    iPlayerTwo = new Player(*p2);

    playerOneUndos = UNDO_TURNS;
    playerTwoUndos = UNDO_TURNS;
}

GameHistory::GameHistory(Bag* bag, Player* p1, Player* p2, int player1Undos, int player2Undos){
    head = nullptr;
    tail = nullptr;
    size = 0;

    iBag = new Bag(*bag);
    iPlayerOne = new Player(*p1);
    iPlayerTwo = new Player(*p2);

    playerOneUndos = player1Undos;
    playerTwoUndos = player2Undos;
}

GameHistory::~GameHistory(){
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
        if(currAction->playerNum == PLAYER_ONE)
            currAction->action->doAction(bag,board,playerOne);
        else{
            currAction->action->doAction(bag,board,playerTwo);
        }
        currAction = currAction->next;
        std::cout << board->toString() << std::endl;
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

int GameHistory::getPlayerOneUndos(){
    return playerOneUndos;
}

int GameHistory::getPlayerTwoUndos(){
    return playerTwoUndos;
}
    
void GameHistory::setPlayerOneUndos(int undos){
    playerOneUndos = undos;
}

void GameHistory::setPlayerTwoUndos(int undos){
    playerTwoUndos = undos;
}

std::string GameHistory::toString(){
    std::string build;
    build.append(iPlayerOne->toString() + "\n");
    build.append(playerOneUndos + "\n");
    build.append(iPlayerTwo->toString() + "\n");
    build.append(playerTwoUndos + "\n");
    build.append(iBag->toString() + "\n");

    ActionNode* currAction = head;
    while(currAction != nullptr){
        build.append(std::to_string(currAction->playerNum) + "\n");
        build.append(currAction->action->toString() + "\n");
        currAction = currAction->next;
    }

    return build;
}