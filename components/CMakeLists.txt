cmake_minimum_required(VERSION 3.0)
project(components)

set(CMAKE_CXX_STANDARD 23)

set(ChessAI_Project_Src
    Board.cpp
    Board.h
    presenter.cpp
    presenter.h
    bitBoardLoader.cpp
    bitBoardLoader.h
    pieces/bishop.cpp
    pieces/bishop.h
    pieces/king.cpp
    pieces/king.h
    pieces/knight.cpp
    pieces/knight.h
    pieces/pawn.cpp
    pieces/pawn.h
    pieces/queen.cpp
    pieces/queen.h
    pieces/rook.cpp
    pieces/rook.h)

add_library(components ${ChessAI_Project_Src} )