#include "MoveGeneratorHelper.h"

PIECE GetCapturedPiece(Board* board, BOARD to_bitboard)
{
    BOARD currentColor = board->GetCurrentColorBoard();
    uint64_t allPieces = board->GetAllPieces();
    BOARD enemy_pieces = allPieces & ~currentColor;

    // bitboards of enemy pieces
    BOARD pawns = board->GetPawns() & enemy_pieces;
    BOARD rooks = board->GetRooks() & enemy_pieces;
    BOARD knights = board->GetKnights() & enemy_pieces;
    BOARD bishops = board->GetBishops() & enemy_pieces;
    BOARD queens = board->GetQueens() & enemy_pieces;

    PIECE capture_piece = NO_PIECE;

    if (to_bitboard & pawns)
    {
        capture_piece = PAWN;
    }
    else if (to_bitboard & rooks)
    {
        capture_piece = ROOK;
    }
    else if (to_bitboard & knights)
    {
        capture_piece = KNIGHT;
    }
    else if (to_bitboard & bishops)
    {
        capture_piece = BISHOP;
    }
    else if (to_bitboard & queens)
    {
        capture_piece = QUEEN;
    }

    return capture_piece;
}

int GetCastlingFlag(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo){
    if(xFrom+2 == xTo || xFrom-2 == xTo){
        return CASTLING;
    }
    return 0;
}

void AddMove(MOVE_ARRAY &moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, int flags)
{
    moves[moves[0]] = CreateMove(xFrom, yFrom, xTo, yTo, flags);
    moves[0] = moves[0] + 1;
}

void TryAddMove(MOVE_ARRAY &moves, Board* board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo) {
    if (!InBounds(xTo, yTo) || (SingleBitBoard(xTo, yTo) & board->GetCurrentColorBoard()))
    {
        return;
    }

    BOARD from_bitboard = SingleBitBoard(xFrom, yFrom);
    BOARD to_bitboard = SingleBitBoard(xTo, yTo);

    PIECE capture_piece = GetCapturedPiece(board, to_bitboard);

    int capture_flag = capture_piece << 15;

    if (((yTo == 0 && board->GetCurrentColor() == BLACK) || (yTo == 7 && board->GetCurrentColor() == WHITE)) && from_bitboard & board->GetPawns()) {
        AddMove(moves, xFrom, yFrom, xTo, yTo, capture_flag | UPGRADE_ROOK);
        AddMove(moves, xFrom, yFrom, xTo, yTo, capture_flag | UPGRADE_KNIGHT);
        AddMove(moves, xFrom, yFrom, xTo, yTo, capture_flag | UPGRADE_BISHOP);
        AddMove(moves, xFrom, yFrom, xTo, yTo, capture_flag | UPGRADE_QUEEN);
    }
    else
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, capture_flag);
    }
}

void AddMoveKing(MOVE_ARRAY &moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, int flags)
{
    moves[moves[0]] = CreateMove(xFrom, yFrom, xTo, yTo, flags);
    moves[0] = moves[0] + 1;
}

bool TryAddMoveNoCaptureKing(MOVE_ARRAY &moves, Board *board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo))
    {
        BOARD currentColor = board->GetCurrentColorBoard();
        BOARD allPieces = board->GetAllPieces();
        BOARD attackedFieldsEnemy;
        if (board->GetCurrentColor()){
            attackedFieldsEnemy = board->GetFromWhiteAttackedFields();
        }else{
            attackedFieldsEnemy = board->GetFromBlackAttackedFields();
        }

        if (~attackedFieldsEnemy & SingleBitBoard(xTo, yTo) & ~allPieces & ~currentColor)
        {
            AddMoveKing(moves, xFrom, yFrom, xTo, yTo, GetCastlingFlag(xFrom, yFrom, xTo, yTo));
            return true;
        }
    }
    return false;
}

bool TryAddMoveOnlyCaptureKing(MOVE_ARRAY &moves, Board *board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo))
    {
        BOARD currentColor = board->GetCurrentColorBoard();
        BOARD allPieces = board->GetAllPieces();
        uint8_t moveRights = board->GetMoveRights();
        BOARD attackedFieldsEnemy;
        if (moveRights & 1){
            attackedFieldsEnemy = board->GetFromWhiteAttackedFields();
        }else{
            attackedFieldsEnemy = board->GetFromBlackAttackedFields();
        }
        if (~attackedFieldsEnemy & SingleBitBoard(xTo, yTo) & ~currentColor & allPieces)
        {
            int capture_flag = GetCapturedPiece(board, SingleBitBoard(xTo, yTo)) << 15;
            AddMoveKing(moves, xFrom, yFrom, xTo, yTo, capture_flag);
            return true;
        }
    }
    return false;
}

bool TryAddMoveKing(MOVE_ARRAY &moves, Board *board, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (TryAddMoveNoCaptureKing(moves, board, xFrom, yFrom, xTo, yTo))
    {
        return true;
    }
    return TryAddMoveOnlyCaptureKing(moves, board, xFrom, yFrom, xTo, yTo);
}

bool TryMarkField(BOARD &attackedFieldsOwn, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo))
    {
        attackedFieldsOwn = attackedFieldsOwn | SingleBitBoard(xTo,yTo);
        return true;
    }
    return false;
}