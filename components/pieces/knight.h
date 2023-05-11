#ifndef CHESSAI_PROJECT_KNIGHT_H
#define CHESSAI_PROJECT_KNIGHT_H

#include <vector>
#include "../Board.h"

class knight {
    public:
        static void possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_KNIGHT_H
