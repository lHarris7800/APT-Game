#include "Player.h"
#include "Board.h"

#include "Tile.h"
#include "GameHistory.h"

class Controller {
public:

   Controller(Player* one, Player* two);

   ~Controller();



private:
    GameHistory* gameHistory;

    Player* playerOne;
    Player* playerTwo;
    Board* board;
    Bag* bag;

    void placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation);
    void replaceTile(PlayerNum playerNum, Tile* replacedTile);
};