cmake_minimum_required(VERSION 3.14)
project(APT_A2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(APT_A2
        LinkedList.cpp
        LinkedList.h
        Makefile
        Node.cpp
        Node.h
        qwirkle.cpp
        Tile.cpp
        Tile.h
        TileCodes.h MainMenu.cpp MainMenu.h)
