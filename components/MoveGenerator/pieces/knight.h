#ifndef CHESSAI_PROJECT_KNIGHT_H
#define CHESSAI_PROJECT_KNIGHT_H

#include "../MoveGeneratorHelper.h"
#include <vector>

class knight {
public:
    static void possibleMoves(MOVE_ARRAY &moves, Board* board, uint8_t x, uint8_t y);

    static void markFields(BOARD &attackedFieldsOwn, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_KNIGHT_H