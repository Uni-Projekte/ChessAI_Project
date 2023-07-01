#ifndef CHESSAI_PROJECT_ROOK_H
#define CHESSAI_PROJECT_ROOK_H

#include "../Board.h"
#include <vector>

class rook {
public:
    static void possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y, uint8_t direction);

    static void markFields(BOARD &attackedFieldsOwn , BOARD &pinnedEnemy, BOARD enemyKing , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_ROOK_H