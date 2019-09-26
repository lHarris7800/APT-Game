//
// Created by Koder on 20/09/2019.
//
#include <iostream>

#include "MainMenu.h"

MainMenu::MainMenu(){

};
MainMenu::~MainMenu(){

}
int UserInput(){
    int selection;
    std::cin >> selection;
    return selection;
}

void MainMenu::MenuDisplay()
{
    std::cout << "Menu\n----\n1. New Game\n2. Load Game\n3. Show student information(?)\n4. Quit" << std::endl;

}
