#include "Player.h"
#include "Board.h"
#include "Bag.h"

class Controller {
public:

   Controller();

   ~Controller();



private:
    Player playerOne;
    Player playerTwo;
    Board board;
    Bag bag;

    void placeTile(/*Arguments to be determined*/);
    void replaceTile(/*Arguments to be determined*/);
};