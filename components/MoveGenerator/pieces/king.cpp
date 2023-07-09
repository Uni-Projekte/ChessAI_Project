#include "king.h"


void king::possibleMoves(MOVE_ARRAY &moves, Board *board, uint8_t x, uint8_t y)
{

    BOARD currentColor = board->GetCurrentColorBoard();
    BOARD allPieces = board->GetAllPieces();
    uint8_t moveRights = board->GetMoveRights();
    BOARD attackedFieldsEnemy;
    if (moveRights & 1){
        BOARD attackedFieldsEnemy = board->GetFromWhiteAttackedFields();
    }else{
        BOARD attackedFieldsEnemy = board->GetFromBlackAttackedFields();
    }

    BOARD whiteKingStartPostition = 0b1000;
    BOARD blackKingStartPostition = 0b100000000000000000000000000000000000000000000000000000000000;

    if(moveRights&0b10000000 && (whiteKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenWhiteKingSide = 0b110;
        if(!(fieldsInBetweenWhiteKingSide & allPieces) && !(fieldsInBetweenWhiteKingSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves, board,x,y,x+2,y);
        }
    }
    if(moveRights&0b01000000 && (whiteKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenWhiteQueenSide = 0b01110000;
        if(!(fieldsInBetweenWhiteQueenSide & allPieces) && !(fieldsInBetweenWhiteQueenSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves, board,x,y,x-2,y);
        }
    }
    if(moveRights&0b00100000 && (blackKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
        BOARD fieldsInBetweenBlackKingSide = 0b011000000000000000000000000000000000000000000000000000000000;
        if(!(fieldsInBetweenBlackKingSide & allPieces) && !(fieldsInBetweenBlackKingSide & attackedFieldsEnemy)){
            TryAddMoveKing(moves, board,x,y,x+2,y);
        }
    }
    if(moveRights&0b00010000 && (blackKingStartPostition & SingleBitBoard(x,y) & ~attackedFieldsEnemy)){
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
