#include "queen.h"
#include "bishop.h"
#include "rook.h"

void queen::possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    bishop::possibleMoves(moves, allPieces, currentColor, x, y);
    rook::possibleMoves(moves, allPieces, currentColor, x, y);
}

void queen::markFields(BOARD &attackedFieldsOwn, BOARD &pinnedEnemy,BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    bishop::markFields(attackedFieldsOwn, pinnedEnemy, enemyKing, allPieces, currentColor, x, y);
    rook::markFields(attackedFieldsOwn, pinnedEnemy, enemyKing, allPieces, currentColor, x, y);
}