#ifndef CHESSAI_PROJECT_KING_H
#define CHESSAI_PROJECT_KING_H

#include <vector>
#include "../Board.h"

class king {
public:
    static void possibleMoves(MOVE_ARRAY &moves, uint8_t moveRights, BOARD &attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);

    static void markFields(BOARD &attackedFieldsOwn, uint8_t xTo, uint8_t yTo);
};


#endif //CHESSAI_PROJECT_KING_H