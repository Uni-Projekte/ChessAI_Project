#include "king.h"


void king::possibleMoves(MOVE_ARRAY &moves, Board *board, uint8_t x, uint8_t y)
{
    BOARD allPieces = board->GetAllPieces();
    uint8_t moveRights = board->GetMoveRights();
    BOARD attackedFieldsEnemy;
    if (moveRights & 1){
        attackedFieldsEnemy = board->GetFromWhiteAttackedFields();
    }else{
        attackedFieldsEnemy = board->GetFromBlackAttackedFields();
    }

    BOARD whiteKingStartPosition = 0b1000;
    BOARD blackKingStartPosition = 0b100000000000000000000000000000000000000000000000000000000000;

    //WhiteKingSideCastle
    if(moveRights&0b10000000 && (whiteKingStartPosition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenWhiteKingSide = 0b110;
        if(!(fieldsInBetweenWhiteKingSide & allPieces) && !(fieldsInBetweenWhiteKingSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves, board,x,y,x+2,y);
        }
    }
    //WhiteQueenSideCastle
    if(moveRights&0b01000000 && (whiteKingStartPosition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenWhiteQueenSide = 0b01110000;
        if(!(fieldsInBetweenWhiteQueenSide & allPieces) && !(fieldsInBetweenWhiteQueenSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves, board,x,y,x-2,y);
        }
    }
    //BlackKingSideCastle
    if(moveRights&0b00100000 && (blackKingStartPosition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenBlackKingSide = 0b011000000000000000000000000000000000000000000000000000000000;
        if(!(fieldsInBetweenBlackKingSide & allPieces) && !(fieldsInBetweenBlackKingSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves, board,x,y,x+2,y);
        }
    }
    //BlackQueenSideCastle
    if(moveRights&0b00010000 && (blackKingStartPosition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenBlackQueenSide = 0b0111000000000000000000000000000000000000000000000000000000000000;
        if(!(fieldsInBetweenBlackQueenSide & allPieces) && !(fieldsInBetweenBlackQueenSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves,board,x,y,x-2,y);
        }
    }

    TryAddMoveKing(moves, board, x, y, x, y + 1);
    TryAddMoveKing(moves, board, x, y, x + 1, y + 1);
    TryAddMoveKing(moves, board, x, y, x + 1, y);
    TryAddMoveKing(moves, board, x, y, x + 1, y - 1);
    TryAddMoveKing(moves, board, x, y, x, y - 1);
    TryAddMoveKing(moves, board, x, y, x - 1, y - 1);
    TryAddMoveKing(moves, board, x, y, x - 1, y);
    TryAddMoveKing(moves, board, x, y, x - 1, y + 1);
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
