#include "Player.h"
#include "Board.h"

#include "Tile.h"
#include "GameHistory.h"

class Controller {
public:

   Controller(Player* one, Player* two);
   ~Controller();

   bool validPlaceTile(Tile* playedTile, std::string boardLocation);

   bool validReplaceTile(Tile* replacedTile);

   void gameplay();

private:
    GameHistory* gameHistory;

    Player* playerOne;
    Player* playerTwo;
    Board* board;
    Bag* bag;

    void placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation);
    void replaceTile(PlayerNum playerNum, Tile* replacedTile);

};