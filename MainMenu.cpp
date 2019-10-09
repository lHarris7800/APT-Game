//
// Created by Koder on 20/09/2019.
//
#include "MainMenu.h"
#include "Controller.h"
#define PLAYER_ONE  1
#define PLAYER_TWO  2

MainMenu::MainMenu(int randSeed){
    this->randSeed = randSeed;
}

MainMenu::~MainMenu(){
}

int UserInput(){
    int selection;
    std::cout << ">";
    std::cin >> selection;
    //Input validation checking for integers only
    while(!std::cin) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Invalid input, please try again" << std::endl;
        std::cout << ">";
        std::string badString;
        std::getline(std::cin,badString);
        std::cin >> selection;
    }
    return selection;
};

MenuOption MainMenu::MenuDisplay(){
    std::cout << "Menu\n----\n1. New Game\n2. Load Game\n3. Show student information\n4. Quit\n" << std::endl;
    menuChoice = UserInput();
    MenuOption menuOption = INVALID_OPTION;
    if (menuChoice == 1) {
        menuOption = NEW_GAME;
    } else if (menuChoice == 2) {
        menuOption = LOAD_GAME;
    } else if (menuChoice == 3) {
        menuOption = STUDENT_INFO;
    } else if (menuChoice == 4) {
        menuOption = QUIT_GAME;
    }

    return menuOption;
};

void MainMenu::MenuAction(){

    MenuOption userOption;

    do {
        userOption = MenuDisplay();

        if (userOption == NEW_GAME) {
            std::cout << "\nStarting a New Game" << std::endl;
            NewGame();
        }
        if (userOption == LOAD_GAME) {
            std::cout << "Selected Load Game" << std::endl;
            LoadGame();
        }
        if (userOption == STUDENT_INFO) {
            std::cout << "Selected Student Information" << std::endl;
            StudentInfo();
        }
        if (userOption == QUIT_GAME) {
            std::cout << "Goodbye" << std::endl;
        }
        if (userOption == INVALID_OPTION){
            std::cout << "Please enter a valid option" << std::endl;
        }
    }
    while (userOption != QUIT_GAME);
};

void MainMenu::NewGame(){
    //BEGIN New Game

    std::string playerOneName, playerTwoName;
    std::cout << "Enter a name for Player 1 (uppercase characters only)" << std::endl;
    playerOneName = PlayerNameInput();
    std::cout << "You have entered " + playerOneName << std::endl;
    std::cout << "Enter a name for Player 2 (uppercase characters only)" << std::endl;
    playerTwoName = PlayerNameInput();
    std::cout << "You have entered " + playerTwoName << std::endl;
    std::cout << "Let's Play!\n" << std::endl;

    Bag* bag = new Bag(this->randSeed);

    playerOne = new Player(playerOneName,bag);
    playerTwo = new Player(playerTwoName,bag);

    //Begin playing
    Controller * controller = new Controller(playerOne, playerTwo,bag);
    controller->gameplay(PLAYER_ONE);
    delete controller;
    //END Game
}

std::string MainMenu::PlayerNameInput(){
    bool inputComplete = false;
    std::string playerName;
    std::cout << ">";
    std::cin >> playerName;
    //Input validation
    while(!inputComplete){
        if(!std::all_of(playerName.begin(), playerName.end(), &::isupper)) {
            std::cout << "Please type your name in ALL-CAPS" << std::endl;
            std::cin.clear();
            std::cout << ">";
            std::cin >> playerName;
        }
        else if(!std::cin.fail()) {
            inputComplete = true;
        }
    }
    return playerName;
};

void MainMenu::LoadGame(){
    std::string fileName, line;

    std::cout << "Enter the filename from which to load a game" << std::endl;
    std::cout << ">";
    std::cin >> fileName; //input name of previously saved file
    std::ifstream saveFile (fileName + ".save");
    if (saveFile.is_open()){
        //Read data for player one and two
        std::string playerName,playerScore,playerHand;
        
        //Read data for player one
        getline(saveFile,playerName);
        getline(saveFile,playerScore);
        getline(saveFile,playerHand);

        playerOne = new Player(playerName,std::stoi(playerScore),new LinkedList(playerHand));
        
        //Read data for player two
        getline(saveFile,playerName);
        getline(saveFile,playerScore);
        getline(saveFile,playerHand);
        
        playerTwo = new Player(playerName,std::stoi(playerScore),new LinkedList(playerHand));
    
        
        //TODO implement read in for board
        std::string boardLine;
        board = new Board(); 
        

        getline(saveFile,boardLine);
        getline(saveFile,boardLine);
        int offset = 0;
        for(int i = 0; i < MAX_SIZE;i++){
            //read one line of board
            getline(saveFile,boardLine);
            std::istringstream delimitedData (boardLine);
            std::string tileData;
            std::getline(delimitedData,tileData,'|');

            //iterate over places in one line of board
            for(int j = offset; j < MAX_SIZE; j+=2){
                std::getline(delimitedData,tileData,'|');
                if(tileData.compare("    ")){
                    //Added tile to board
                    std::string boardLocation = std::string(1,i+65) + std::to_string(j);
                    board->placeTile(new Tile(tileData.substr(1,2)),boardLocation);
                }
            }

            //toggling board offset (each row starting at column 0 or 1)
            if(offset==0)
                offset = 1;
            else
                offset = 0;
        }
        getline(saveFile,boardLine);
        getline(saveFile,boardLine);

        
        //read data for bag
        std::string bagData;
        getline(saveFile,bagData);
        bag = new Bag(new LinkedList(bagData));

        std::string playersTurn;
        int playersTurnNum;
        getline(saveFile,playersTurn);
        if(playersTurn.compare(playerOne->getName())==0)
            playersTurnNum = PLAYER_ONE;
        else 
            playersTurnNum = PLAYER_TWO;

        //read data for game history
        //read initial player data
        Player* iPlayer1,* iPlayer2;
        std::string iPlayerName,iPlayerScore,iPlayerHand;
        std::string playerOneUndos, playerTwoUndos;
        
        //Reading for initial player1
        getline(saveFile,iPlayerName);
        getline(saveFile,iPlayerScore);
        getline(saveFile,iPlayerHand);

        iPlayer1 = new Player(iPlayerName,std::stoi(iPlayerScore),new LinkedList(iPlayerHand));
        getline(saveFile,playerOneUndos);

        //Reading for initial player2
        getline(saveFile,iPlayerName);
        getline(saveFile,iPlayerScore);
        getline(saveFile,iPlayerHand);

        iPlayer2 = new Player(iPlayerName,std::stoi(iPlayerScore),new LinkedList(iPlayerHand));
        getline(saveFile,playerTwoUndos);

        //read initial bag
        std::string iBagData;
        getline(saveFile,iBagData);
        Bag* iBag = new Bag(new LinkedList(iBagData));
        
        //creating game history with initial state of game
        GameHistory* history = new GameHistory(iBag,iPlayer1,iPlayer2,stoi(playerOneUndos),stoi(playerTwoUndos));

        //read actions
        while(!saveFile.eof()){
            std::string playerNum,actionType, actionData;

            getline(saveFile,playerNum);
            getline(saveFile,actionType);
            getline(saveFile,actionData);

            if(!saveFile.eof()){
                if(!actionType.compare("PlaceTile"))
                    history->addAction(new PlaceTileAction(actionData),std::stoi(playerNum));
                else 
                    history->addAction(new ReplaceTileAction(actionData),std::stoi(playerNum));
            }
        }
        saveFile.close();

        //Creating controller with objects from save file
        Controller* controller = new Controller(playerOne,playerTwo,bag,board,history);
        controller->gameplay(playersTurnNum);
        delete controller;
    }
    else std::cout << "File not found" << std::endl;
}

void MainMenu::StudentInfo(){
    std::cout <<
    "----------------------------------\n"
    "Name: Shahrzad Rafezi\n"
    "Student ID: s3656798\n"
    "Email: s3656798@student.rmit.edu.au\n"
    "\n"
    "Name: Luke Harris\n"
    "Student ID: s3725331\n"
    "Email: s3725331@student.rmit.edu.au\n"
    "\n"
    "Name: Benjamin Koder\n"
    "Student ID: s3774343\n"
    "Email: s3774343@student.rmit.edu.au\n"
    "\n"
    "Name: Adnan Boru\n"
    "Student ID: s3721108\n"
    "Email: s3721108@student.rmit.edu.au\n"
    "----------------------------------" << std::endl;
}