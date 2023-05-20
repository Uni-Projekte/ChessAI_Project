#include "queen.h"

void queen::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD &enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.
    while (newX < 8 && newY < 8 && !(currentColor & SINGLE_BIT_BOARD(newX,newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
        }
        newX++;
        newY++;
    }

    newX = x + 1;
    newY = y - 1;
    // diagonal south east
    while (newX < 8 && newY < 255 && !(currentColor & SINGLE_BIT_BOARD(newX, newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
        }
        newX++;
        newY--;
    }

    newX = x - 1;
    newY = y - 1;
    // diagonal south west
    while (newX < 255 && newY < 255 && !(currentColor & (1ULL << (newY * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
        }
        newX--;
        newY--;
    }

    newX = x - 1;
    newY = y + 1;
    // diagonal north west
    while (newX < 255 && newY < 8 && !(currentColor & (1ULL << (newY * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
        }
        newX--;
        newY++;
    }

    newX = x+1;
    // east
    while (newX < 8 && !(currentColor & (1ULL << (y * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, y))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, 0);
        }
        newX++;
    }

    newX = x-1;
    //west
    while (newX < 255 && !(currentColor & (1ULL << (y * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, y))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, 0);
        }
        newX--;
    }

    newY = y-1;
    //south
    while (newY < 255 && !(currentColor & (1ULL << (newY * 8 + (7 - x)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(x, newY))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, 0);
        }
        newY--;
    }

    newY = y+1;
    while (newY < 8 && !(currentColor & (1ULL << (newY * 8 + (7 - x)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(x, newY))
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, CAPTURE);
            break;
        }
        else
        {
            ADD_MOVE(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, 0);
        }
        newY++;
    }
}