#include "pawn.h"

void pawn::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y, bool color, uint8_t en_passante)
{
    if (color == WHITE)
    {
        if (y == 6)
        {
            if (SingleBitBoard(x, 0) & ~allPieces)
            {
                AddMove(&moves, x, y, x, 0, UPGRADE_ROOK);
                AddMove(&moves, x, y, x, 0, UPGRADE_KNIGHT);
                AddMove(&moves, x, y, x, 0, UPGRADE_BISHOP);
                AddMove(&moves, x, y, x, 0, UPGRADE_QUEEN);
            }
            TryAddMoveOnlyCaptureUpgrade(&moves, allPieces, currentColor, x, y, x - 1, y + 1);
            TryAddMoveOnlyCaptureUpgrade(&moves, allPieces, currentColor, x, y, x + 1, y + 1);
        }
        else
        {
            TryAddMoveNoCapture(&moves, allPieces, currentColor, x, y, x, y + 1);
            TryAddMoveOnlyCapture(&moves, allPieces, currentColor, x, y, x - 1, y + 1);
            TryAddMoveOnlyCapture(&moves, allPieces, currentColor, x, y, x + 1, y + 1);
            if ((GetToX(en_passante) == x - 1 || GetToX(en_passante) == x + 1) && GetToY(en_passante) == y + 1)
            {
                AddMove(&moves, x, y, GetToX(en_passante), y + 1, CAPTURE);
            }

        }
    }
    else
    {
        if ((y == 6) && (SingleBitBoard(x, 7) & ~currentColor & ~allPieces))
        {
            AddMove(&moves, x, y, x, 7, UPGRADE_ROOK);
            AddMove(&moves, x, y, x, 7, UPGRADE_KNIGHT);
            AddMove(&moves, x, y, x, 7, UPGRADE_BISHOP);
            AddMove(&moves, x, y, x, 7, UPGRADE_QUEEN);
        }
        TryAddMoveNoCapture(&moves, allPieces, currentColor, x, y, x, y - 1);
        TryAddMoveOnlyCapture(&moves, allPieces, currentColor, x, y, x - 1, y - 1);
        TryAddMoveOnlyCapture(&moves, allPieces, currentColor, x, y, x + 1, y - 1);
    }
}