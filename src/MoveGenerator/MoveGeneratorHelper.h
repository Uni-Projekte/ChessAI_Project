#ifndef MOVEGENERATORHELPER_H
#define MOVEGENERATORHELPER_H

#include "../Board.h"


void AddMove(MOVE_ARRAY &moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, int flags);

void TryAddMove(MOVE_ARRAY &moves, Board* board , uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

bool TryAddMoveKing(MOVE_ARRAY &moves, Board* board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

bool TryAddMoveNoCaptureKing(MOVE_ARRAY &moves, Board* board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

bool TryAddMoveOnlyCaptureKing(MOVE_ARRAY &moves, Board* board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

void AddMoveKing(MOVE_ARRAY &moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, int flags);

bool TryMarkField(BOARD &attackedFieldsOwn, uint8_t xTo, uint8_t yTo);

PIECE GetCapturedPiece(Board* board, BOARD to_bitboard);




#endif //CHESSAI_PROJECT_MOVEGENERATORHELPER_H
