#include "pawn.h"


void pawn::possibleMoves(MOVE_ARRAY &moves, Board* board, uint8_t x, uint8_t y, uint8_t en_passante)
{
    BOARD allPieces = board->GetAllPieces();
    BOARD currentColor = board->GetCurrentColorBoard();
    int color = board->GetCurrentColor();
    int newY = y - (2 * color - 1);

    if ((GetToX(en_passante) == x - 1 || GetToX(en_passante) == x + 1) && GetToY(en_passante) == newY && InBounds(GetToX(en_passante), newY))
    {
        AddMove(moves, x, y, GetToX(en_passante), newY, EN_PASSANTE);
    }

    TryAddMove(moves, board, x, y, x + 1, newY);
    TryAddMove(moves, board, x, y, x - 1, newY);

    if (SingleBitBoard(x, newY) & ~allPieces & InBounds(x, newY))
    {
        AddMove(moves, x, y, x, newY, 0);
    }
}

void pawn::markFields(BOARD &attackedFieldsOwn, uint8_t x, uint8_t y, bool color)
{
    if (color == WHITE)
    {
        TryMarkField(attackedFieldsOwn, x - 1, y + 1);
        TryMarkField(attackedFieldsOwn, x + 1, y + 1);
    }
    else
    {
        TryMarkField(attackedFieldsOwn, x - 1, y - 1);
        TryMarkField(attackedFieldsOwn, x + 1, y - 1);
    }
}