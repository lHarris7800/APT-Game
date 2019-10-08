#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "GameHistory.h"
#include "ReplaceTileAction.h"
#include "PlaceTileAction.h"
#include <iostream>
#include <fstream>
#define UPRIGHT 1
#define UPLEFT 2
#define DOWNRIGHT 3
#define DOWNLEFT 4
#define LEFT 5
#define RIGHT 6


class Controller {
public:

   Controller(Player* one, Player* two, Bag* bag);
   Controller(Player* one, Player* two, Bag* bag, Board* board, GameHistory* history);
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
    bool tileInHand(PlayerNum playerNum, std::string tileName);
    void displayScoreAndBoard();
};