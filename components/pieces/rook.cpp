#include "rook.h"

void rook::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn , BOARD enemyKing , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.

    newX = x+1;
    // east
    bool metKing = false;
    while (newX < 8 && !(currentColor & SINGLE_BIT_BOARD(newX,y)))
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
    //west
    while (newX < 255 && !(currentColor & SINGLE_BIT_BOARD(newX, y)))
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
    //south
    metKing = false;
    while (newY < 255 && !(currentColor & SINGLE_BIT_BOARD(x, newY)))
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
    while (newY < 8 && !(currentColor & SINGLE_BIT_BOARD(x, newY)))
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