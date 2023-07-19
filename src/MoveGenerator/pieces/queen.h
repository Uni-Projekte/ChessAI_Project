#ifndef CHESSAI_PROJECT_QUEEN_H
#define CHESSAI_PROJECT_QUEEN_H

#include "../MoveGeneratorHelper.h"
#include <vector>

class queen {
public:
    static void possibleMoves(MOVE_ARRAY &moves, Board* board, uint8_t x, uint8_t y, uint8_t direction);

    static void markFields(BOARD &attackedFieldsOwn, BOARD &pinnedEnemy,BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_QUEEN_H