//
// Created by Koder on 20/09/2019.
//

#include "MainMenu.h"

MainMenu::MainMenu(){
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
        std::cin >> selection;
    }
    return selection;
};

MenuOption MainMenu::MenuDisplay(){
    std::cout << "Menu\n----\n1. New Game\n2. Load Game\n3. Show student information(?)\n4. Quit\n" << std::endl;
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

    Bag* bag = new Bag();

    playerOne = new Player(playerOneName,bag);
    playerTwo = new Player(playerTwoName,bag);

    //Begin playing
    Controller * controller = new Controller(playerOne, playerTwo,bag);
    controller->gameplay();
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
    std::ifstream saveFile (fileName);
    //Reads file into the console
    //TODO: read file into controller instead
    if (saveFile.is_open()){
        //Read data for player one and two
        for(int i = 0; i < 2; i++){
            std::string playerName,playerScore,playerHand;

            getline(saveFile,playerName);
            getline(saveFile,playerScore);
            getline(saveFile,playerHand);

            if(i == 0)
                playerOne = new Player(playerName,std::stoi(playerScore),new LinkedList(playerHand));
            else
                playerTwo = new Player(playerName,std::stoi(playerScore),new LinkedList(playerHand));
        }

        //TODO implement read in for board
        for(int i = 0; i < 30;i++){
            std::string string;
            getline(saveFile,string);
        }

        //read data for bag
        std::string bagData;
        getline(saveFile,bagData);
        bag = new Bag(new LinkedList(bagData));

        //read data for game history
        //read initial player data
        Player* iPlayer1,* iPlayer2;
        for(int i = 0; i < 2; i++){
            std::string playerName,playerScore,playerHand;

            getline(saveFile,playerName);
            getline(saveFile,playerScore);
            getline(saveFile,playerHand);

            if(i == 0)
                iPlayer1 = new Player(playerName,std::stoi(playerScore),new LinkedList(playerHand));
            else
                iPlayer2 = new Player(playerName,std::stoi(playerScore),new LinkedList(playerHand));
        }

        //read initial bag
        std::string iBagData;
        getline(saveFile,iBagData);
        Bag* iBag = new Bag(new LinkedList(iBagData));
        

        GameHistory* history = new GameHistory(iBag,iPlayer1,iPlayer2);

        //read actions
        while(!saveFile.eof()){
            std::string playerNum,actionType, actionData;

            getline(saveFile,playerNum);
            getline(saveFile,actionType);
            getline(saveFile,actionData);

            if(actionType.compare("PlaceTile"))
                history->addAction(new PlaceTileAction(actionData),std::stoi(playerNum));
            else 
                history->addAction(new ReplaceTileAction(actionData),std::stoi(playerNum));
        }
        saveFile.close();

        Controller* controller = new Controller(playerOne,playerTwo,bag,history);
    }
    else std::cout << "File not found" << std::endl;
}

void MainMenu::saveGame(std::string filename) {

    if (!filename.empty()) {
        // Opens the file
        std::ofstream out(filename);

        if (out.is_open()) {

            //TODO:saves player's toString
            out << playerOne->toString() << std::endl;
            out << playerTwo->toString() << std::endl;

            //TODO:saves board's toString
            out << this->board->toString() << std::endl;

            //TODO:saves bag's toString
            out << this->bag->toString() << std::endl;
            
            //TODO:saves current Player's name


            // Closes the file
            out.flush();
            out.close();
        }
        std::cout << "Game successfully saved" << std::endl
                  << std::endl;
    }
    else {
        std::cout << "Error: Please enter a filename to save" << std::endl;
    }

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