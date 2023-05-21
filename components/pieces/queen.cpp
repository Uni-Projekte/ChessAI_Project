#include "queen.h"

void queen::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    bool metKing = false;
    // Check for possible moves in the diagonal direction.
    while (newX < 8 && newY < 8 && !(currentColor & SINGLE_BIT_BOARD(newX,newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            if (SINGLE_BIT_BOARD(newX, newY) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        } else {
            if (metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
            }else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
            }
        }
        newX++;
        newY++;
    }

    newX = x + 1;
    newY = y - 1;
    metKing = false;
    // diagonal south east
    while (newX < 8 && newY < 255 && !(currentColor & SINGLE_BIT_BOARD(newX, newY)))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            if (SINGLE_BIT_BOARD(newX, newY) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if (metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
            }else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
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
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            if (SINGLE_BIT_BOARD(newX, newY) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        } else {
            if (metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
            }else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
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
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, newY))
        {
            if (SINGLE_BIT_BOARD(newX, newY) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
                metKing = true;
            }
            else if (!metKing){
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, CAPTURE);
                break;
            }
        } else {
            if (metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, newY);
            }else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, enemyKing, x, y, newX, newY, 0);
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
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, y))
        {
            if(SINGLE_BIT_BOARD(newX,y) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, y);
                metKing = true;
            }
            else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, newX, y, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, y);
            }
            else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, newX, y, 0);
            }
        }
        newX++;
    }

    newX = x-1;
    metKing = false;
    //west
    while (newX < 255 && !(currentColor & (1ULL << (y * 8 + (7 - newX)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(newX, y))
        {
            if(SINGLE_BIT_BOARD(newX,y) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, y);
                metKing = true;
            }
            else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, newX, y, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(newX, y);
            }
            else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, newX, y, 0);
            }
        }
        newX--;
    }

    newY = y-1;
    metKing = false;
    //south
    while (newY < 255 && !(currentColor & (1ULL << (newY * 8 + (7 - x)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(x, newY))
        {
            if(SINGLE_BIT_BOARD(x,newY) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(x,newY);
                metKing = true;
            } else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, x, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(x, newY);
            }
            else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, x, newY, 0);
            }
        }
        newY--;
    }

    newY = y+1;
    metKing = false;
    while (newY < 8 && !(currentColor & (1ULL << (newY * 8 + (7 - x)))))
    {
        if (allPieces & ~currentColor & SINGLE_BIT_BOARD(x, newY))
        {
            if(SINGLE_BIT_BOARD(x,newY) & enemyKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(x,newY);
                metKing = true;
            } else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, x, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SINGLE_BIT_BOARD(x, newY);
            }
            else{
                ADD_MOVE_SLIDING_PIECE(moves, attackedFieldsOwn, attackedFieldsEnemy, x, y, x, newY, 0);
            }
        }
        newY++;
    }
}