#include "Controller.h"
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
/*PSEUDOCODE
BEGIN
WHILE GAME HAS NOT ENDED DO{
    <<PlayerOneName //Player one's turn
    <<Score for Player One
    <<Score for Player Two
    <<
    <<PRINT GAME BOARD
    <<
    <<Player One's hand
    <<
        Do {
        >>player input //Use Regex101.com
        **Choices: place x at y, replace z with tile from bag, save, forfeit, help
        VALIDATE INPUT (must share attribute and be connected with another tile)
            IF (input is invalid) << Please input from following options: ... lists options
        } while (input is invalid)

    <<PlayerTwoName //Player Two's turn
    <<...
    }
END*/
    bool playerOnesTurn = true;
    bool endgame = false;
    do {
        turn(playerOnesTurn);
    } while (!endgame);
};


bool Controller::turn(bool playerOnesTurn){
    bool endTurn = false;
    if (playerOnesTurn) {
        std::cout << playerOne->getName() << ", it's your turn" << std::endl;
        displayScoreAndBoard();
        std::cout << "Your hand is\n" << playerOne->playerHand() << std::endl; //TODO fix player hand
        playerOnesTurn = false; //ends Player One's turn
    }
    if (!playerOnesTurn) {
        std::cout << playerTwo->getName() << ", it's your turn" << std::endl;
        displayScoreAndBoard();
        std::cout << "Your hand is\n" << playerTwo->playerHand() << std::endl; //TODO fix player hand
        playerOnesTurn = true; //ends Player Two's turn
    }
    else {
        std::cout << "Something has gone terribly wrong..." << std::endl;
        endTurn = true;
    }
    return endTurn;
};

void Controller::displayScoreAndBoard(){
    std::cout << "Score for " << playerOne->getName() << ": " << playerOne->getScore() << std::endl
    << "Score for " << playerTwo->getName() << ": " << playerTwo->getScore() << std::endl
    << board->toString() << std::endl;
}

void Controller::playerChoice(){
    //todo "place" "replace" input and validation, save & quit.
    //todo figure out how to do this. enumerator?
}

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


bool Controller::validPlaceTile(Tile* playedTile, std::string boardLocation){
    int row, column;
    bool result = false;

    column = boardLocation[0]-65; // shows A,B,C,...

    //Converting Strings to Integers
    row = stoi(boardLocation.substr(1));  //shows 1,2,3,...

    //checks if the tile that we are placing is inside of bounds, otherwise return false
    if(row >= MAX_SIZE || column >= MAX_SIZE ){
        std::cout << "There are no more than 25 rows and columns, therefore you cannot add the tile in this position";
        result = false;
    }

    int blankNeighbour = 0;
    int newRow, newCol;

    //checks the surroundings of the tile
    for(int dir = 1; dir <= 4; dir++){
        newRow = row;
        newCol = column;
        if(dir == UP)
            newCol++;
        else if(dir == DOWN)
            newCol--;
        else if(dir == LEFT)
            newRow--;
        else
            newRow++;

        //Looks at the size of the board
        if(newRow >= 0 && newRow < MAX_SIZE && newCol >= 0 && newCol < MAX_SIZE){
            //looks at all 4 sides to see if the position is empty. if true, then add 1 to blank neighbour
            if(board->board[newCol][newRow].compare(EMPTY_TILE)==0)
                blankNeighbour++;

            //This is to check if the tile has the same shape or colour as the tile that's already in the board
            else if(playedTile->getTileName()[0] == board->board[newCol][newRow][0] || playedTile->getTileName()[1] == board->board[newCol][newRow][1])
                result = true;
        }
        else
            blankNeighbour++;
    }

    //if all four tile's neighbour is empty, then place the tile.
    if(blankNeighbour == 4){
        if((row % 2 == 0 && column % 2 == 0) || (row % 2 != 0 && column % 2 != 0))
            result= true;
        else
            std::cout << "\n You can't place a tile there" << std::endl;
    }

    else
        std::cout << "There is a tile already in that position";

    return result;
}

bool Controller::validReplaceTile(Tile* replacedTile){
    bool result = false;

    //searches the position of the tile in player's hand
    int position = playerOne->getHand()->searchTile(replacedTile->getTileName());

    //checks to see if that tile exist in player's hand
    if(position != -1)
        result = true;
    else
        std::cout << "The tile you want to replace doesn't exist in your hand.";

    return result;
}

//Updates bag, board, players with new move and add move to history
//Validation to be implemented before calling this method

void Controller::placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation){
    Action* newAction = new PlaceTileAction(playedTile, boardLocation);
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
