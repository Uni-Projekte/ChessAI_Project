#ifndef CHESSAI_PROJECT_PAWN_H
#define CHESSAI_PROJECT_PAWN_H

#include "../MoveGeneratorHelper.h"
#include <vector>

class pawn
{
public:

    static void possibleMoves(MOVE_ARRAY &moves, Board* board, uint8_t x, uint8_t y, uint8_t en_passante);

    static void markFields(BOARD &attackedFieldsOwn, uint8_t x, uint8_t y, bool color);
};

#endif //CHESSAI_PROJECT_PAWN_H