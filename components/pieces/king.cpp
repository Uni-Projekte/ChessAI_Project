#include "king.h"

// currently there is no check if the king run into a position where he can be captured
void king::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn , BOARD attackedFieldsEnemy , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x, y + 1);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x + 1, y + 1);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x + 1, y);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x + 1, y - 1);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x, y - 1);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x - 1, y - 1);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x - 1, y);
    TRY_ADD_MOVE_KING(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, x, y, x - 1, y + 1);
}