#include "pawn.h"

void pawn::possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y, bool color)
{
    if (color == WHITE)
    {
        if ((y == 1) && (SINGLE_BIT_BOARD(x, 0) & ~currentColor & ~allPieces))
        {
            ADD_MOVE(moves, x, y, x, 0, UPGRADE_ROOK);
            ADD_MOVE(moves, x, y, x, 0, UPGRADE_KNIGHT);
            ADD_MOVE(moves, x, y, x, 0, UPGRADE_BISHOP);
            ADD_MOVE(moves, x, y, x, 0, UPGRADE_QUEEN);
        }
        TRY_ADD_MOVE_NO_CAPTURE(moves, allPieces, currentColor, x, y, x, y + 1)
        TRY_ADD_MOVE_ONLY_CAPTURE(moves, allPieces, currentColor, x, y, x - 1, y + 1);
        TRY_ADD_MOVE_ONLY_CAPTURE(moves, allPieces, currentColor, x, y, x + 1, y + 1);
    }
    else
    {
        if ((y == 6) && (SINGLE_BIT_BOARD(x, 7) & ~currentColor & ~allPieces))
        {
            ADD_MOVE(moves, x, y, x, 7, UPGRADE_ROOK);
            ADD_MOVE(moves, x, y, x, 7, UPGRADE_KNIGHT);
            ADD_MOVE(moves, x, y, x, 7, UPGRADE_BISHOP);
            ADD_MOVE(moves, x, y, x, 7, UPGRADE_QUEEN);
        }
        TRY_ADD_MOVE_NO_CAPTURE(moves, allPieces, currentColor, x, y, x, y - 1);
        TRY_ADD_MOVE_ONLY_CAPTURE(moves, allPieces, currentColor, x, y, x - 1, y - 1);
        TRY_ADD_MOVE_ONLY_CAPTURE(moves, allPieces, currentColor, x, y, x + 1, y - 1);
    }
}