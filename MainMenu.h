//
// Created by Koder on 20/09/2019.
//

#ifndef APT_A2_MAINMENU_H
#define APT_A2_MAINMENU_H

#include "Bag.h"

enum MenuOption {
    NEW_GAME,
    LOAD_GAME,
    STUDENT_INFO,
    QUIT_GAME,
    INVALID_OPTION
};

class MainMenu {

public:
    MainMenu();

    ~MainMenu();

    MenuOption MenuDisplay();

    void MenuAction();


private:
    int menuChoice = 0;

    Bag *bag;

    void NewGame();

    void LoadGame();

    void saveGame(std::string filename);

    void StudentInfo();

    std::string PlayerNameInput();

    void GamePlay();
};

#endif //APT_A2_MAINMENU_H
