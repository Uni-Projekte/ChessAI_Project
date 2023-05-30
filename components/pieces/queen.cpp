#include "queen.h"

void queen::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    bool metKing = false;
    // Check for possible moves in the diagonal direction.
    while (newX < 8 && newY < 8 && !(currentColor & SingleBitBoard(newX,newY)))
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

    newX = x + 1;
    newY = y - 1;
    metKing = false;
    // diagonal south east
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

    newX = x - 1;
    newY = y - 1;
    metKing = false;
    // diagonal south west
    while (newX < 255 && newY < 255 && !(currentColor & (1ULL << (newY * 8 + (7 - newX)))))
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

    newX = x - 1;
    newY = y + 1;
    metKing = false;
    // diagonal north west
    while (newX < 255 && newY < 8 && !(currentColor & (1ULL << (newY * 8 + (7 - newX)))))
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

    newX = x+1;
    // east
    metKing = false;
    while (newX < 8 && !(currentColor & (1ULL << (y * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            if(SingleBitBoard(newX,y) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
                metKing = true;
            }
            else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
            }
            else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, 0);
            }
        }
        newX++;
    }

    newX = x-1;
    metKing = false;
    //west
    while (newX < 255 && !(currentColor & (1ULL << (y * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            if(SingleBitBoard(newX,y) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
                metKing = true;
            }
            else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
            }
            else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, newX, y, 0);
            }
        }
        newX--;
    }

    newY = y-1;
    metKing = false;
    //south
    while (newY < 255 && !(currentColor & (1ULL << (newY * 8 + (7 - x)))))
    {
        if (allPieces & ~currentColor & SingleBitBoard(x, newY))
        {
            if(SingleBitBoard(x,newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(x,newY);
                metKing = true;
            } else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(x, newY);
            }
            else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, 0);
            }
        }
        newY--;
    }

    newY = y+1;
    metKing = false;
    while (newY < 8 && !(currentColor & (1ULL << (newY * 8 + (7 - x)))))
    {
        if (allPieces & ~currentColor & SingleBitBoard(x, newY))
        {
            if(SingleBitBoard(x,newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(x,newY);
                metKing = true;
            } else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(x, newY);
            }
            else{
                AddMoveSlidingPiece(moves, attackedFieldsOwn, enemyKing, x, y, x, newY, 0);
            }
        }
        newY++;
    }
}