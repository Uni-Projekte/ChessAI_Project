#ifndef CHESSAI_PROJECT_ROOK_H
#define CHESSAI_PROJECT_ROOK_H

#include "../Board.h"
#include <vector>

class rook {
public:
    static void possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsWhite , BOARD &attackedFieldsBlack , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_ROOK_H
