#include "queen.h"
#include "bishop.h"
#include "rook.h"

void queen::possibleMoves(MOVE_ARRAY &moves, Board *board, uint8_t x, uint8_t y, uint8_t direction)
{
    bishop::possibleMoves(moves, board, x, y, direction);
    rook::possibleMoves(moves, board, x, y, direction);
}

void queen::markFields(BOARD &attackedFieldsOwn, BOARD &pinnedEnemy,BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    bishop::markFields(attackedFieldsOwn, pinnedEnemy, enemyKing, allPieces, currentColor, x, y);
    rook::markFields(attackedFieldsOwn, pinnedEnemy, enemyKing, allPieces, currentColor, x, y);
}