#ifndef APT_THE_SCREAM_A2_GAMEHISTORY_H
#define APT_THE_SCREAM_A2_GAMEHISTORY_H

#include "ActionNode.h"

class GameHistory{
public:
    GameHistory(Bag* bag, Player* p1, Player* p2);
    GameHistory(Bag* bag, Player* p1, Player* p2, int player1Undos, int player2Undos);
    ~GameHistory();

    void clear();

    void addAction(Action* action, PlayerNum playerNum);

    void replay();
    void undo(Bag* bag, Board* board, Player* playerOne, Player* playerTwo);

    int getPlayerOneUndos();
    int getPlayerTwoUndos();
    
    void setPlayerOneUndos(int Undos);
    void setPlayerTwoUndos(int Undos);

    std::string toString();

private:
    ActionNode* head;
    ActionNode* tail;
    int size;

    int playerOneUndos;
    int playerTwoUndos;

    Bag* iBag;
    Player* iPlayerOne;
    Player* iPlayerTwo;

    /*
    Player* iPlayerOne;
    Player* iPlayerTwo;
    Bag* iBag;
*/
};
#endif