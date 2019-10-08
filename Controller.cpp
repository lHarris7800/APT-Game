#include "Controller.h"
#include <regex>
#define PLAYER_ONE  1
#define PLAYER_TWO  2

Controller::Controller(Player* playerOne, Player* playerTwo,Bag* bag){
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
    this->bag = bag;
    board = new Board();
    gameHistory = new GameHistory(bag,playerOne,playerTwo);
}


Controller::Controller(Player* one, Player* two, Bag* bag,Board* board, GameHistory* history){
    playerOne = one;
    playerTwo = two;
    this->bag = bag;
    this->board = board;
    gameHistory = history;
}

Controller::~Controller(){
}

void Controller::gameplay() {
    int playersTurn = PLAYER_ONE;
    bool quitGame = false;
    bool firstMove = true;
    do { //while 'quit' is not selected
        bool endTurn = false;
        do { //while still player's turn
            if (playersTurn == PLAYER_ONE) {
                std::cout << playerOne->getName() << ", it's your turn" << std::endl;
                displayScoreAndBoard();
                std::cout << "Your hand is\n" << playerOne->playerHand() << std::endl;
            }
            else {
                std::cout << playerTwo->getName() << ", it's your turn" << std::endl;
                displayScoreAndBoard();
                std::cout << "Your hand is\n" << playerTwo->playerHand() << std::endl;
            }

            std::cout << "What would you like to do?" << std::endl;
            std::string input; //For user input
            bool validInput = false; //Ensures user won't exit the loop until a valid input is registered
            std::smatch match;
            std::regex placeInputValid(R"(place [ROYGBP][1-6] at [A-Z](\d\d|\d))");
            std::regex replaceInputValid("replace [ROYGBP][1-6]");
            std::regex saveFileNameValid("\\w{1,}");
            do { //while input is valid
                std::cout << ">";
                std::cin >> std::ws;
                getline(std::cin, input);
                //Place Tile
                if (std::regex_match(input, match, placeInputValid)) {
                    std::string tileName = input.substr(6, 2);
                    std::string boardLocation = input.substr(12, 3);
                    Tile *requestedTile = new Tile(tileName);
                    if (tileInHand(playersTurn, tileName)) {
                        if (validPlaceTile(requestedTile, boardLocation, firstMove)) {
                            validInput = true;
                            placeTile(playersTurn, requestedTile, boardLocation, calcScore(requestedTile, boardLocation));
                            firstMove = false;
                            endTurn = true;
                        }
                    }
                    //Replace Tile
                } else if (std::regex_match(input, match, replaceInputValid)) {
                    std::string tileName = input.substr(8,2);
                    std::cout << "User wants to replace " << tileName << std::endl;
                    Tile *requestedTile = new Tile(tileName);
                    if (tileInHand(playersTurn, tileName)) {
                        if (validReplaceTile(requestedTile,playersTurn)) {
                            validInput = true;
                            replaceTile(playersTurn, requestedTile);
                            endTurn = true;
                        }
                    }
                    //Save Game
                } else if (input.find("save") == 0) {
                    std::string saveFileName;
                    std::cout << "Input a name for your save file" << std::endl;
                    std::cout << ">";
                    std::cin >> saveFileName;
                    save(saveFileName);
                    validInput = true;
                    //Quit Game
                } else if (input.find("quit") == 0) {
                    std::cout << "exiting game..." << std::endl;
                    validInput = true;
                    endTurn = true;
                    quitGame = true;
                }
                if (!validInput) {
                    std::cout << "Improper input, please use 'place', 'replace', 'save', or 'quit'. " << std::endl;
                    input.clear();
                }
            } while (!validInput);
        }
        while (!endTurn);
        if (playersTurn == PLAYER_ONE){ playersTurn = PLAYER_TWO; }
        else { playersTurn = PLAYER_ONE; }
    } while (!quitGame);
};

void Controller::displayScoreAndBoard(){
    std::cout << "Score for " << playerOne->getName() << ": " << playerOne->getScore() << std::endl
    << "Score for " << playerTwo->getName() << ": " << playerTwo->getScore() << std::endl
    << board->toString() << std::endl;
};

void Controller::save(std::string filename){
    std::ofstream saveFile;

    saveFile.open(filename);

    saveFile << playerOne->toString() << std::endl;
    saveFile << playerTwo->toString() << std::endl;
    saveFile << board->toString() << std::endl;
    saveFile << bag->toString() << std::endl;
    saveFile << gameHistory->toString() << std::endl;

    saveFile.close();
}

bool Controller::tileInHand(PlayerNum playerNum, std::string tileName){
    bool foundTile = false;
    if (playerNum == PLAYER_ONE) { //Checks against Player One's hand
        if (playerOne->getHand()->searchTile(tileName) != -1) {
            foundTile = true;
        }
        else{
            std::cout << "That tile is not in your hand!" << std::endl;
        }
    } else { //Checks against Player Two's hand
        if (playerTwo->getHand()->searchTile(tileName) != -1) {
            foundTile = true;
        }
        else {
            std::cout << "That tile is not in your hand!" << std::endl;
        }
    }
    return foundTile;
}

bool Controller::validPlaceTile(Tile* playedTile, std::string boardLocation, bool firstTile){
    int row, column;
    bool result = false;

    column = boardLocation[0]-65; // gets from A,B,C,...

    //Converting Strings to Integers
    row = stoi(boardLocation.substr(1));  //shows 1,2,3,...

    //checks if the tile that we are placing is inside of bounds, otherwise return false
    if(row >= MAX_SIZE || column >= MAX_SIZE )
        std::cout << "There are no more than 25 rows and columns, therefore you cannot add the tile in this position";
    else if(row % 2 != column % 2)
        std::cout << "\n You can't place a tile there" << std::endl;
    else if(board->board[column][row].compare(EMPTY_TILE) != 0)
        std::cout << "\n There is a tile already in that position" << std::endl;
    else if(!firstTile){
        int newRow, newCol;

        bool badNeighbour = false;
        bool goodNeighbour = false;

        //checks the surroundings of the tile
        for(int dir = 1; dir <= 4 && !badNeighbour; dir++){
            newRow = row;
            newCol = column;

            //name variable is confusing, this should go down
            if(dir == DOWNRIGHT){
                newCol++;
                newRow++;
            }
            else if(dir == UPRIGHT){
                newCol++;
                newRow--;
            }
            //name variable is confusing, this should go up
            else if(dir == DOWNLEFT){
                newCol--;
                newRow++;
            }
            else if(dir == UPLEFT){
                newCol--;
                newRow--;
            }

            //only checks adjacent tiles in bounds of board
            if(newRow >= 0 && newRow < MAX_SIZE && newCol >= 0 && newCol < MAX_SIZE){
                //looks at all 4 sides to see if the position is empty. 
                if(board->board[newCol][newRow].compare(EMPTY_TILE) != 0){
                    //This is to check if the tile has the same colour as the tile that's already in the board
                    if(playedTile->getTileName()[0] == board->board[newCol][newRow][0]){
                        int offsetRow = newRow - row;
                        int offsetCol = newCol - column;

                        newRow+=offsetRow;
                        newCol+=offsetCol;
                        //Goes through line of tiles insuring they all share the same colour
                        while(newRow >= 0 && newRow < MAX_SIZE && 
                                    newCol >= 0 && newCol < MAX_SIZE &&
                                    board->board[newCol][newRow].compare(EMPTY_TILE) != 0){

                            if(playedTile->getTileName()[0] != board->board[newCol][newRow][0]){
                                badNeighbour = true;
                                std::cout << "\n Each diagonal must share a common shape or colour." << std::endl;
                            }

                            newRow+=offsetRow;
                            newCol+=offsetCol;

                        } 
                            
                        goodNeighbour = true;
                    }

                    //This is to check if the tile has the same shape as the tile that's already in the board
                    else if(playedTile->getTileName()[1] == board->board[newCol][newRow][1]){
                        int offsetRow = newRow - row;
                        int offsetCol = newCol - column;

                        newRow+=offsetRow;
                        newCol+=offsetCol;
                        
                        //Goes through line of tiles insuring they all share the same shape
                        while(newRow >= 0 && newRow < MAX_SIZE && 
                                    newCol >= 0 && newCol < MAX_SIZE &&
                                    board->board[newCol][newRow].compare(EMPTY_TILE) != 0){
                           
                            if(playedTile->getTileName()[1] != board->board[newCol][newRow][1]){
                                badNeighbour = true;
                                std::cout << "\n Each diagonal must share a common shape or colour." << std::endl;
                            }

                            newRow+=offsetRow;
                            newCol+=offsetCol;

                        } 

                        goodNeighbour = true;
                    }
                    else{
                        std::cout << "\n You can only place a tile if it has the same colour or shape as adjacent tiles." << std::endl;
                        badNeighbour = true;
                    }
                }
            }
        }   
    

        //if all four tile's neighbour is empty, then place the tile.
        if(!badNeighbour){
            if(goodNeighbour)
                result = true;
            else
                std::cout << "\n You can only place a tile if it is adjacent to at least one other tile." << std::endl;
        }
    }
    return result;
}

int Controller::calcScore(Tile* playedTile, std::string boardLocation){
    int returnScore = 0;

    int row, col;
    col = boardLocation[0]-65; // gets from A,B,C,...
    //Converting Strings to Integers
    row = stoi(boardLocation.substr(1));


    //number of tiles in \ diagonal
    int numTilesBackDiagonal = 0;
    //number of tiles in / diagonal
    int numTilesForwardDiagonal = 0;

    int offsetRow, offsetCol;
    for(int dir = 1; dir <= 4; dir++){

        if(dir == DOWNRIGHT){
            offsetCol=1;
            offsetRow=1;
        }
        else if(dir == UPRIGHT){
            offsetCol=1;
            offsetRow=-1;
        }
        else if(dir == DOWNLEFT){
            offsetCol=-1;
            offsetRow=1;
        }
        else{
            offsetCol=-1;
            offsetRow=-1;
        }

        int newRow = row+offsetRow;
        int newCol = col+offsetCol;

        while(newRow >= 0 && newRow < MAX_SIZE && 
                    newCol >= 0 && newCol < MAX_SIZE &&
                    board->board[newCol][newRow].compare(EMPTY_TILE) != 0){
            returnScore++;
            if(dir == UPLEFT || dir == DOWNRIGHT)
                numTilesBackDiagonal++;
            else 
                numTilesForwardDiagonal++;
            
            newRow+=offsetRow;
            newCol+=offsetCol;
        } 
    }

    //Adding extra point for the tile currently being placed
    if(numTilesForwardDiagonal>0)
        returnScore++;
    if(numTilesBackDiagonal>0)
        returnScore++;
    
    //Adding bonus 6 points if a qwirkle is score in either direction
    if(numTilesForwardDiagonal==5)
        returnScore+=6;
    if(numTilesBackDiagonal==5)
        returnScore+=6;
    std::cout << "Score: " << returnScore <<std::endl;
    return returnScore;
}

bool Controller::validReplaceTile(Tile* replacedTile, int playerNum){
    bool result = false;
    int position;

    //searches the position of the tile in player's hand
    if(playerNum == PLAYER_ONE)
        position = playerOne->getHand()->searchTile(replacedTile->getTileName());
    else 
        position = playerTwo->getHand()->searchTile(replacedTile->getTileName());
    

    //checks to see if that tile exist in player's hand
    if(position != -1)
        result = true;
    else
        std::cout << "The tile you want to replace doesn't exist in your hand." << std::endl;

    return result;
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method

void Controller::placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation,int score){
    Action* newAction = new PlaceTileAction(playedTile, boardLocation,score);
    if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    
    gameHistory->addAction(newAction,playerNum);
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method

void Controller::replaceTile(PlayerNum playerNum, Tile* replacedTile){
    Action* newAction = new ReplaceTileAction(replacedTile);
     if(playerNum == PLAYER_ONE)
        newAction->doAction(bag,board,playerOne);
    else
        newAction->doAction(bag,board,playerTwo);
    gameHistory->addAction(newAction, playerNum);
}
