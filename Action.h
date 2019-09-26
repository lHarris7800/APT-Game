
#ifndef ASSIGN2_ACTION_H
#define ASSIGN2_ACTION_H
#include "Bag.h"
#include "Board.h"
#include "Player.h"

class Action{
public:
    virtual ~Action() = default;
    virtual void doAction(Bag* bag, Board* board,Player* player)=0;
    virtual void undoAction(Bag* bag, Board* board,Player* player)=0;
};

#endif // ASSIGN2_ACTION_H