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

class Controller {
public:

   Controller(Player* one, Player* two, Bag* bag);
   Controller(Player* one, Player* two, Bag* bag, Board* board, GameHistory* history);
   ~Controller();

   bool validPlaceTile(Tile* playedTile, std::string boardLocation, bool firstTile);

   int calcScore(Tile* playedTile, std::string boardLocation);

   bool validReplaceTile(Tile* replacedTile, int playerNum);

   void gameplay();

   void save(std::string filename);

private:
    GameHistory* gameHistory;

    Player* playerOne;
    Player* playerTwo;
    Board* board;
    Bag* bag;

    void placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation, int score);
    void replaceTile(PlayerNum playerNum, Tile* replacedTile);
    bool tileInHand(PlayerNum playerNum, std::string tileName);
    void displayScoreAndBoard();
};