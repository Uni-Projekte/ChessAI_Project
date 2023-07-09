#include "bishop.h"
#include <iostream>

// Check for possible moves in the diagonal directions.
void bishop::possibleMoves(MOVE_ARRAY &moves, Board* board, uint8_t x, uint8_t y, uint8_t direction)
{
    uint8_t newX;
    uint8_t newY;

    BOARD currentColor = board->GetCurrentColorBoard();
    BOARD allPieces = board->GetAllPieces();

    if(direction == 3 || direction == 0) {
        // Check for possible moves in the diagonal direction.
        uint8_t newX = x + 1;
        uint8_t newY = y + 1;
        while (newX < 8 && newY < 8 && !(currentColor & SingleBitBoard(newX, newY)))
        {
            BOARD toBitboard = SingleBitBoard(newX, newY);
            if (allPieces & ~currentColor & toBitboard){
                PIECE capturePiece = GetCapturedPiece(board, toBitboard);
                int captureFlag = capturePiece << 15;
                AddMove(moves, x, y, newX, newY, captureFlag);
                break;
            } else {
                AddMove(moves, x, y, newX, newY, 0);
            }
            newX++;
            newY++;
        }

        // diagonal south west
        newX = x - 1;
        newY = y - 1;
        while (newX < 255 && newY < 255 && !(currentColor & SingleBitBoard(newX, newY)))
        {

            BOARD toBitboard = SingleBitBoard(newX, newY);
            if (allPieces & ~currentColor & toBitboard){
                PIECE capturePiece = GetCapturedPiece(board, toBitboard);
                int captureFlag = capturePiece << 15;
                AddMove(moves, x, y, newX, newY, captureFlag);
                break;
            } else {
                AddMove(moves, x, y, newX, newY, 0);
            }
            newX--;
            newY--;
        }
    }


    if(direction == 4 || direction == 0){
        // diagonal south east
        newX = x + 1;
        newY = y - 1;
        while (newX < 8 && newY < 255 && !(currentColor & SingleBitBoard(newX, newY)))
        {
            BOARD toBitboard = SingleBitBoard(newX, newY);
            if (allPieces & ~currentColor & toBitboard){
                PIECE capturePiece = GetCapturedPiece(board, toBitboard);
                int captureFlag = capturePiece << 15;
                AddMove(moves, x, y, newX, newY, captureFlag);
                break;
            } else {
                AddMove(moves, x, y, newX, newY, 0);
            }
            newX++;
            newY--;
        }

        // diagonal north west
        newX = x - 1;
        newY = y + 1;
        while (newX < 255 && newY < 8 && !(currentColor & SingleBitBoard(newX, newY)))
        {
            BOARD toBitboard = SingleBitBoard(newX, newY);
            if (allPieces & ~currentColor & toBitboard){
                PIECE capturePiece = GetCapturedPiece(board, toBitboard);
                int captureFlag = capturePiece << 15;
                AddMove(moves, x, y, newX, newY, captureFlag);
                break;
            } else {
                AddMove(moves, x, y, newX, newY, 0);
            }
            newX--;
            newY++;
        }
    }

}


void bishop::markFields(BOARD &attackedFieldsOwn, BOARD &pinnedEnemy, BOARD enemyKing, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    // diagonal north east
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    bool metKing = false;
    bool metEnemy = false;
    uint64_t metEnemyBoard = 0;
    uint64_t currentPosition;
    while (newX < 8 && newY < 8 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        currentPosition = SingleBitBoard(newX, newY);
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
        newY++;
    }
    if (InBounds(newX,newY)&&(currentColor & SingleBitBoard(newX, newY)))
        attackedFieldsOwn |= SingleBitBoard(newX, newY);

    // diagonal south east
    newX = x + 1;
    newY = y - 1;
    metKing = false;
    metEnemy = false;
    metEnemyBoard = 0;
    while (newX < 8 && newY < 255 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        currentPosition = SingleBitBoard(newX, newY);
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
        newY--;
    }
    if (InBounds(newX,newY)&&(currentColor & SingleBitBoard(newX, newY)))
        attackedFieldsOwn |= SingleBitBoard(newX, newY);

    // diagonal south west
    newX = x - 1;
    newY = y - 1;
    metKing = false;
    metEnemy = false;
    metEnemyBoard = 0;
    while (newX < 255 && newY < 255 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        currentPosition = SingleBitBoard(newX, newY);
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
        newY--;
    }
    if (InBounds(newX,newY)&&(currentColor & SingleBitBoard(newX, newY)))
        attackedFieldsOwn |= SingleBitBoard(newX, newY);

    // diagonal north west
    newX = x - 1;
    newY = y + 1;
    metKing = false;
    metEnemy = false;
    metEnemyBoard = 0;
    while (newX < 255 && newY < 8 && !(currentColor & SingleBitBoard(newX, newY)))
    {
        currentPosition = SingleBitBoard(newX, newY);
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
        newY++;
    }
    if (InBounds(newX,newY)&&(currentColor & SingleBitBoard(newX, newY)))
        attackedFieldsOwn |= SingleBitBoard(newX, newY);
}
