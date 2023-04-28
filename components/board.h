//
// Created by Mateusz Pawelczyk on 28.04.2023.
//

#include <string>
#include <vector>

using namespace std;

#ifndef CHESSAI_PROJECT_BOARD_H
#define CHESSAI_PROJECT_BOARD_H

class Board {
public:
    Board();
    Board(string fen);

public:
    uint64_t GetBlackPawns();
    uint64_t GetBlackQueen();
    uint64_t GetBlackKing();
    uint64_t GetBlackKnights();
    uint64_t GetBlackTowers();
    uint64_t GetBlackBishops();
    uint64_t GetWhitePawns();
    uint64_t GetWhiteQueen();
    uint64_t GetWhiteKing();
    uint64_t GetWhiteKnights();
    uint64_t GetWhiteTowers();
    uint64_t GetWhiteBishops();
    string ToString();

private:
    uint64_t black;
    uint64_t white;
    uint64_t pawns;
    uint64_t kings;
    uint64_t queens;
    uint64_t towers;
    uint64_t bishops;
    uint64_t knights;


    string fromFEN(string fen);
    uint64_t* getPiece(char piece);
    uint64_t* getColor(char piece);

};



#endif //CHESSAI_PROJECT_BOARD_H
