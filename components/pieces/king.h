#ifndef CHESSAI_PROJECT_KING_H
#define CHESSAI_PROJECT_KING_H

#include <vector>
#include "../Board.h"

class king {
public:
    static void possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn , BOARD &attackedFieldsEnemy , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_KING_H
