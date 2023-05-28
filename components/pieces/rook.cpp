#include "rook.h"

void rook::possibleMoves(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn , BOARD enemyKing , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.

    newX = x+1;
    // east
    bool metKing = false;
    while (newX < 8 && !(currentColor & SingleBitBoard(newX,y)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            if(SingleBitBoard(newX,y) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
                metKing = true;
            }
            else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, newX, y, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
            }
            else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, newX, y, 0);
            }
        }
        newX++;
    }

    newX = x-1;
    //west
    while (newX < 255 && !(currentColor & SingleBitBoard(newX, y)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            if(SingleBitBoard(newX,y) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
                metKing = true;
            }
            else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, newX, y, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(newX, y);
            }
            else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, newX, y, 0);
            }
        }
        newX--;
    }

    newY = y-1;
    //south
    metKing = false;
    while (newY < 255 && !(currentColor & SingleBitBoard(x, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(x, newY))
        {
            if(SingleBitBoard(x,newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(x,newY);
                metKing = true;
            } else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, x, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(x, newY);
            }
            else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, x, newY, 0);
            }
        }
        newY--;
    }

    newY = y+1;
    metKing = false;
    while (newY < 8 && !(currentColor & SingleBitBoard(x, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(x, newY))
        {
            if(SingleBitBoard(x,newY) & enemyKing){
                attackedFieldsOwn |= SingleBitBoard(x,newY);
                metKing = true;
            } else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, x, newY, CAPTURE);
                break;
            }
        }
        else
        {
            if(metKing){
                attackedFieldsOwn |= SingleBitBoard(x, newY);
            }
            else{
                AddMoveSlidingPiece(&moves, &attackedFieldsOwn, enemyKing, x, y, x, newY, 0);
            }
        }
        newY++;
    }
}