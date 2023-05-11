#ifndef CHESSAI_PROJECT_PAWN_H
#define CHESSAI_PROJECT_PAWN_H

#include <vector>
#include "../Board.h"

class pawn
{
public:
    static void possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y, bool color);
};

#endif //CHESSAI_PROJECT_PAWN_H
