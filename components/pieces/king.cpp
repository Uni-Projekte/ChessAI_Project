#include "king.h"


void king::possibleMoves(MOVE_ARRAY &moves, uint8_t moveRights, BOARD &attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t x, uint8_t y)
{
    uint64_t whiteKingStartPostition = 0b1000;
    uint64_t blackKingStartPostition = 0b100000000000000000000000000000000000000000000000000000000000;

    if(moveRights&0b10000000 && (whiteKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        uint64_t fieldsInBetweenWhiteKingSide = 0b110;
        if(!(fieldsInBetweenWhiteKingSide & allPieces) && !(fieldsInBetweenWhiteKingSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves,attackedFieldsEnemy,allPieces,currentColor,x,y,x+2,y);
        }
    }
    if(moveRights&0b01000000 && (whiteKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        uint64_t fieldsInBetweenWhiteQueenSide = 0b01110000;
        if(!(fieldsInBetweenWhiteQueenSide & allPieces) && !(fieldsInBetweenWhiteQueenSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves,attackedFieldsEnemy,allPieces,currentColor,x,y,x-2,y);
        }
    }
    if(moveRights&0b00100000 && (blackKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        uint64_t fieldsInBetweenBlackKingSide = 0b011000000000000000000000000000000000000000000000000000000000;
        if(!(fieldsInBetweenBlackKingSide & allPieces) && !(fieldsInBetweenBlackKingSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves,attackedFieldsEnemy,allPieces,currentColor,x,y,x+2,y);
        }
    }
    if(moveRights&0b00010000 && (blackKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        uint64_t fieldsInBetweenBlackQueenSide = 0b0111000000000000000000000000000000000000000000000000000000000000;
        if(!(fieldsInBetweenBlackQueenSide & allPieces) && !(fieldsInBetweenBlackQueenSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves,attackedFieldsEnemy,allPieces,currentColor,x,y,x-2,y);
        }
    }

    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x, y + 1);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x + 1, y + 1);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x + 1, y);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x + 1, y - 1);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x, y - 1);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x - 1, y - 1);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x - 1, y);
    TryAddMoveKing(moves, attackedFieldsEnemy, allPieces, currentColor, x, y, x - 1, y + 1);
}

// currently there is no check if the king run into a position where he can be captured
void king::markFields(BOARD &attackedFieldsOwn, uint8_t x, uint8_t y)
{
    TryMarkField(attackedFieldsOwn, x, y + 1);
    TryMarkField(attackedFieldsOwn, x + 1, y + 1);
    TryMarkField(attackedFieldsOwn, x + 1, y);
    TryMarkField(attackedFieldsOwn, x + 1, y - 1);
    TryMarkField(attackedFieldsOwn, x, y - 1);
    TryMarkField(attackedFieldsOwn, x - 1, y - 1);
    TryMarkField(attackedFieldsOwn, x - 1, y);
    TryMarkField(attackedFieldsOwn, x - 1, y + 1);
}
