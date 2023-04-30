cmake_minimum_required(VERSION 3.0)
project(components)

set(CMAKE_CXX_STANDARD 23)

set(ChessAI_Project_Src
    Board.cpp
    Board.h
    bitBoardLoader.cpp
    bitBoardLoader.h
)

add_library(components ${ChessAI_Project_Src})