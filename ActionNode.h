
#ifndef ASSIGN2_ACTIONNODE_H
#define ASSIGN2_ACTIONNODE_H
#include "Action.h"
typedef int PlayerNum;

class ActionNode{
public:
    ActionNode(ActionNode* next,ActionNode* prev, Action* action, PlayerNum playerNum);

    ~ActionNode();


    ActionNode* next;
    ActionNode* prev;
    Action* action;
    PlayerNum playerNum;
};

#endif // ASSIGN2_ACTIONNODE_H