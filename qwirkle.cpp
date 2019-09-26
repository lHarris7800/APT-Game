#include "LinkedList.h"
#include "MainMenu.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
    LinkedList* list = new LinkedList();
    delete list;

    std::cout << "Welcome to Qwirkle!\n-------------------" << std::endl;

    MainMenu mainMenu;
    mainMenu.MenuDisplay();

    return EXIT_SUCCESS;
}