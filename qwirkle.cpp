#include "LinkedList.h"
#include "MainMenu.h"

#include <cstdio>
#include <iostream>
#include <ctime>

#define EXIT_SUCCESS    0

int main(int argc, char *argv[]) {
    int randSeed = time(NULL);
    if (argc > 1){
        sscanf_s(argv[1], "%d", &randSeed);
    }

    std::cout << "Welcome to Qwirkle!\n-------------------" << std::endl;

    MainMenu* mainMenu = new MainMenu(randSeed);
    mainMenu->MenuAction();

    return EXIT_SUCCESS;
}