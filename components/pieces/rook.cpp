#include "rook.h"

void rook::possibleMoves(std::vector<MOVE> moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.

    newX = x+1;
    // east
    while (newX < 8 && !(currentColor & SINGLE_BIT_BOARD(newX,y)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, x, y, newX, newY, 0);
        }
        newX++;
    }

    newX = x-1;
    //west
    while (newX < 255 && !(currentColor & SINGLE_BIT_BOARD(newX, y)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, x, y, newX, newY, 0);
        }
        newX--;
    }

    newY = y-1;
    //south
    while (newY < 255 && !(currentColor & SINGLE_BIT_BOARD(x, newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, x, y, newX, newY, 0);
        }
        newY--;
    }

    newY = y+1;
    while (newY < 8 && !(currentColor & SINGLE_BIT_BOARD(x, newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, x, y, newX, newY, 0);
        }
        newY++;
    }
}