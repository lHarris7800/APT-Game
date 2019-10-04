//
// Created by Koder on 20/09/2019.
//
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <algorithm>

#include "MainMenu.h"
#include "Controller.h"
#include "Player.h"

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
    std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
    playerOneName = PlayerNameInput();
    std::cout << "You have entered " + playerOneName << std::endl;
    std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
    playerTwoName = PlayerNameInput();
    std::cout << "You have entered " + playerTwoName << std::endl;
    std::cout << "Let's Play!" << std::endl;

    Player* playerOne = new Player(playerOneName);
    Player* playerTwo = new Player(playerTwoName);

    //Begin playing
    //TODO: Fix Player and Controller initialization
    Controller * controller = new Controller(playerOne, playerTwo);
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
        while (getline (saveFile,line)){
            std::cout << line << "\n";
        }
        saveFile.close();
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