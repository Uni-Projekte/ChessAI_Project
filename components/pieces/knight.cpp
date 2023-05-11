#include "knight.h"

// Maximum number of possible moves for a queen is 27.
#define MAX_MOVES 8

void knight::possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    //up right
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x + 1, y + 2);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x + 1, y - 2);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x - 1, y + 2);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x - 1, y - 2);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x + 2, y + 1);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x - 2, y + 1);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x + 2, y - 1);
    TRY_ADD_MOVE(moves, allPieces, currentColor, x, y, x - 2, y - 1);
}