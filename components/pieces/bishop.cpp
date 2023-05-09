#include "bishop.h"

// Check for possible moves in the diagonal directions.
void bishop::possibleMoves(std::vector<MOVE> moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    // diagonal north east
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    while (newX < 8 && newY < 8 && !(currentColor & SINGLE_BIT_BOARD(newX, newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, x, y, newX, newY, CAPTURE);
            break;
        } else {
            ADD_MOVE(moves,x,y,newX,newY,0);
        }
        newX++;
        newY++;
    }

    // diagonal south east
    newX = x + 1;
    newY = y - 1;
    while (newX < 8 && newY < 255 && !(currentColor & SINGLE_BIT_BOARD(newX, newY)))
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
        newY--;
    }

    // diagonal south west
    newX = x - 1;
    newY = y - 1;
    while (newX < 255 && newY < 255 && !(currentColor & SINGLE_BIT_BOARD(newX, newY)))
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
        newY--;
    }

    // diagonal north west
    newX = x - 1;
    newY = y + 1;
    while (newX < 255 && newY < 8 && !(currentColor & SINGLE_BIT_BOARD(newX, newY)))
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
        newY++;
    }
}
