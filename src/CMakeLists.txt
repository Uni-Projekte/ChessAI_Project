cmake_minimum_required(VERSION 3.0)
project(src)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-O2 -g")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(CMAKE_CXX_STANDARD 23)

set(ChessAI_Project_Src
    helper.cpp
    helper.h
    Board.cpp
    Board.h
    presenter.cpp
    presenter.h
        MoveGenerator/pieces/bishop.cpp
        MoveGenerator/pieces/bishop.h
        MoveGenerator/pieces/king.cpp
        MoveGenerator/pieces/king.h
        MoveGenerator/pieces/knight.cpp
        MoveGenerator/pieces/knight.h
        MoveGenerator/pieces/pawn.cpp
        MoveGenerator/pieces/pawn.h
        MoveGenerator/pieces/queen.cpp
        MoveGenerator/pieces/queen.h
        MoveGenerator/pieces/rook.cpp
        MoveGenerator/pieces/rook.h ZobristKeyGenerator.cpp ZobristKeyGenerator.h MoveAlgorithms.cpp MoveAlgorithms.h MoveGenerator/MoveGeneratorHelper.cpp MoveGenerator/MoveGeneratorHelper.h Game.cpp Game.h)

add_library(src ${ChessAI_Project_Src} )