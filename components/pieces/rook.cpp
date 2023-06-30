#include "rook.h"

void rook::possibleMoves(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    // east
    uint8_t newX = x+1;
    while (newX < 8 && !(currentColor & SingleBitBoard(newX, y)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            AddMove(moves, x, y, newX, y, CAPTURE);
            break;
        } else {
            AddMove(moves, x, y, newX, y, 0);
        }
        newX++;
    }

    //west
    newX = x-1;
    while (newX < 255 && !(currentColor & SingleBitBoard(newX, y)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            AddMove(moves, x, y, newX, y, CAPTURE);
            break;
        } else {
            AddMove(moves, x, y, newX, y, 0);
        }
        newX--;
    }

    //south
    uint8_t newY = y-1;
    while (newY < 255 && !(currentColor & SingleBitBoard(x, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(x, newY))
        {
            AddMove(moves, x, y, x, newY, CAPTURE);
            break;
        } else {
            AddMove(moves, x, y, x, newY, 0);
        }
        newY--;
    }

    //north
    newY = y+1;
    while (newY < 8 && !(currentColor & SingleBitBoard(x, newY)))
    {
        if (allPieces & ~currentColor & SingleBitBoard(x, newY))
        {
            AddMove(moves, x, y, x, newY, CAPTURE);
            break;
        } else {
            AddMove(moves, x, y, x, newY, 0);
        }
        newY++;
    }
}

void rook::markFields(BOARD &attackedFieldsOwn, BOARD &pinnedEnemy, BOARD enemyKing , BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{

    // east
    /*bool attackFields = !(currentColor & SingleBitBoard(newX, y));
    bool pinFields = false;
    BOARD lastEnemy = 0;
    while (newX < 8 && (attackFields || pinFields))
    {
        if (allPieces & ~currentColor & SingleBitBoard(newX, y))
        {
            if(SingleBitBoard(newX,y) & enemyKing)
            {
                pinnedEnemy = lastEnemy;
                if (attackFields)
                {
                    attackedFieldsOwn |= SingleBitBoard(newX, y);
                }
                if (newX + 1 < 8 && !(SingleBitBoard(newX + 1, y) & currentColor))
                {
                    if (attackFields)
                    {
                        attackedFieldsOwn |= SingleBitBoard(newX, y);
                    }
                }
                break;
            }
            else{
                if (attackFields)
                {
                    attackedFieldsOwn |= SingleBitBoard(newX, y);
                }
                pinFields = attackFields;
                attackFields = false;
            }
        }
        else if (attackFields)
        {
            attackedFieldsOwn |= SingleBitBoard(newX, y);
        }
        newX++;
    }*/

    // east
    uint8_t newX = x+1;
    bool metKing = false;
    bool metEnemy = false;
    uint64_t metEnemyBoard = 0;
    uint64_t currentPosition;
    while (newX < 8 && !(currentColor & SingleBitBoard(newX, y)))
    {
        currentPosition = SingleBitBoard(newX, y);
        if(!metEnemy) attackedFieldsOwn |= currentPosition;

        if (metKing) break;

        if (allPieces & ~currentColor & currentPosition)
        {
            if (currentPosition & enemyKing){
                metKing = true;
                if(metEnemy){
                    pinnedEnemy |= metEnemyBoard;
                }
            }
            else{
                if(metEnemy) break;
                metEnemy = true;
                metEnemyBoard = currentPosition;
            }
        }
        newX++;
    }
    if (InBounds(newX,y)&&(currentColor & SingleBitBoard(newX, y)))
        attackedFieldsOwn |= SingleBitBoard(newX, y);

    //west
    newX = x-1;
    metKing = false;
    metEnemy = false;
    metEnemyBoard = 0;
    while (newX < 255 && !(currentColor & SingleBitBoard(newX, y)))
    {
        currentPosition = SingleBitBoard(newX, y);
        if(!metEnemy) attackedFieldsOwn |= currentPosition;

        if (metKing) break;

        if (allPieces & ~currentColor & currentPosition)
        {
            if (currentPosition & enemyKing){
                metKing = true;
                if(metEnemy){
                    pinnedEnemy |= metEnemyBoard;
                }
            }
            else{
                if(metEnemy) break;
                metEnemy = true;
                metEnemyBoard = currentPosition;
            }
        }
        newX--;
    }
    if (InBounds(newX,y)&&(currentColor & SingleBitBoard(newX, y)))
        attackedFieldsOwn |= SingleBitBoard(newX, y);

    //south
    uint8_t newY = y-1;
    metKing = false;
    metEnemy = false;
    metEnemyBoard = 0;
    while (newY < 255 && !(currentColor & SingleBitBoard(x, newY)))
    {
        currentPosition = SingleBitBoard(x, newY);
        if(!metEnemy) attackedFieldsOwn |= currentPosition;

        if (metKing) break;

        if (allPieces & ~currentColor & currentPosition)
        {
            if (currentPosition & enemyKing){
                metKing = true;
                if(metEnemy){
                    pinnedEnemy |= metEnemyBoard;
                }
            }
            else{
                if(metEnemy) break;
                metEnemy = true;
                metEnemyBoard = currentPosition;
            }
        }
        newY--;
    }
    if (InBounds(x,newY)&&(currentColor & SingleBitBoard(x, newY)))
        attackedFieldsOwn |= SingleBitBoard(x, newY);

    //north
    newY = y+1;
    metKing = false;
    metEnemy = false;
    metEnemyBoard = 0;
    while (newY < 8 && !(currentColor & SingleBitBoard(x, newY)))
    {
        currentPosition = SingleBitBoard(x, newY);
        if(!metEnemy) attackedFieldsOwn |= currentPosition;

        if (metKing) break;

        if (allPieces & ~currentColor & currentPosition)
        {
            if (currentPosition & enemyKing){
                metKing = true;
                if(metEnemy){
                    pinnedEnemy |= metEnemyBoard;
                }
            }
            else{
                if(metEnemy) break;
                metEnemy = true;
                metEnemyBoard = currentPosition;
            }
        }
        newY++;
    }
    if (InBounds(x,newY)&&(currentColor & SingleBitBoard(x, newY)))
        attackedFieldsOwn |= SingleBitBoard(x, newY);
}