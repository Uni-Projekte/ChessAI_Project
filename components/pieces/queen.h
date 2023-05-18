#ifndef CHESSAI_PROJECT_QUEEN_H
#define CHESSAI_PROJECT_QUEEN_H

#include "../Board.h"
#include <vector>

class queen {
public:
    static void possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD &attackedFieldsBlack, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_QUEEN_H
