#include "bishop.h"
#include <iostream>

// Check for possible moves in the diagonal directions.
void bishop::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    // diagonal north east
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    bool metKing = false;
    while (newX < 8 && newY < 8 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, newY))
        {
            if (SingleBitBoard(newX, newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        } else {
            if (metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
            }else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
            }
        }
        newX++;
        newY++;
    }

    // diagonal south east
    newX = x + 1;
    newY = y - 1;
    metKing = false;
    while (newX < 8 && newY < 255 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, newY))
        {
            if (SingleBitBoard(newX, newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if (metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
            }else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
            }
        }
        newX++;
        newY--;
    }

    // diagonal south west
    newX = x - 1;
    newY = y - 1;
    metKing = false;
    while (newX < 255 && newY < 255 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, newY))
        {
            if (SingleBitBoard(newX, newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        } else {
            if (metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
            }else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
            }
        }
        newX--;
        newY--;
    }

    // diagonal north west
    newX = x - 1;
    newY = y + 1;
    metKing = false;
    while (newX < 255 && newY < 8 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, newY))
        {
            if (SingleBitBoard(newX, newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        } else {
            if (metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, newY);
            }else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
            }
        }
        newX--;
        newY++;
    }
}
