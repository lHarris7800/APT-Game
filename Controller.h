#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "GameHistory.h"
#include "ReplaceTileAction.h"
#include "PlaceTileAction.h"
#include <iostream>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


class Controller {
public:

   Controller(Player* one, Player* two, Bag* bag);
   Controller(Player* one, Player* two, Bag* bag, GameHistory* history);
   ~Controller();

   bool validPlaceTile(Tile* playedTile, std::string boardLocation);

   bool validReplaceTile(Tile* replacedTile);

   void gameplay();

   void save(std::string filename);

private:
    GameHistory* gameHistory;

    Player* playerOne;
    Player* playerTwo;
    Board* board;
    Bag* bag;

    void placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation);
    void replaceTile(PlayerNum playerNum, Tile* replacedTile);
    void playerChoice();
    bool turn(bool playerOnesTurn);

    void displayScoreAndBoard();
};