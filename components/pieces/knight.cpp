#include "knight.h"

// Maximum number of possible moves for a queen is 27.

void knight::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    //up right
    TryAddMove(moves, allPieces, currentColor, x, y, x + 1, y + 2);
    TryAddMove(moves, allPieces, currentColor, x, y, x + 1, y - 2);
    TryAddMove(moves, allPieces, currentColor, x, y, x - 1, y + 2);
    TryAddMove(moves, allPieces, currentColor, x, y, x - 1, y - 2);
    TryAddMove(moves, allPieces, currentColor, x, y, x + 2, y + 1);
    TryAddMove(moves, allPieces, currentColor, x, y, x - 2, y + 1);
    TryAddMove(moves, allPieces, currentColor, x, y, x + 2, y - 1);
    TryAddMove(moves, allPieces, currentColor, x, y, x - 2, y - 1);
}