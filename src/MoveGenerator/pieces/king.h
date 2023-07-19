#ifndef CHESSAI_PROJECT_KING_H
#define CHESSAI_PROJECT_KING_H

#include "../MoveGeneratorHelper.h"
#include <vector>

class king {
public:
    static void possibleMoves(MOVE_ARRAY &moves, Board *board, uint8_t x, uint8_t y);

    static void markFields(BOARD &attackedFieldsOwn, uint8_t xTo, uint8_t yTo);
};


#endif //CHESSAI_PROJECT_KING_H