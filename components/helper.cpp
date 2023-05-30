#include "helper.h"

uint64_t GetRowFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return BoardRow1;
    case 1:
        return BoardRow2;
    case 2:
        return BoardRow3;
    case 3:
        return BoardRow4;
    case 4:
        return BoardRow5;
    case 5:
        return BoardRow6;
    case 6:
        return BoardRow7;
    case 7:
        return BoardRow8;
    default:
        throw std::invalid_argument("index must be 0-7");
    }
}

uint64_t GetColumnFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return BoardColumnA;
    case 1:
        return BoardColumnB;
    case 2:
        return BoardColumnC;
    case 3:
        return BoardColumnD;
    case 4:
        return BoardColumnE;
    case 5:
        return BoardColumnF;
    case 6:
        return BoardColumnG;
    case 7:
        return BoardColumnH;
    default:
        throw std::invalid_argument("index must be 0-7");
    }
}

std::string GetColumnLetterFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return "A";
    case 1:
        return "B";
    case 2:
        return "C";
    case 3:
        return "D";
    case 4:
        return "E";
    case 5:
        return "F";
    case 6:
        return "G";
    case 7:
        return "H";
    default:
        throw std::invalid_argument("index must be 0-7");
    }
}

std::string StringMultiply(std::string src, unsigned int times)
{
    std::string out = "";
    for (int i = 0; i < times; i++)
    {
        out = out + src;
    }
    return out;
}

std::string Uint64ToString(uint64_t board)
{
    std::string out = "";
    for (int i = 0; i < 64; i = i + 1)
    {
        if (board & 1)
        {
            out = "1" + out;
        }
        else
        {
            out = "0" + out;
        }
        board = board >> 1;
    }
    return out;
}

std::string Uint32ToString(uint32_t board)
{
    std::string out = "";
    for (int i = 0; i < 32; i = i + 1)
    {
        if (board & 1)
        {
            out = "1" + out;
        }
        else
        {
            out = "0" + out;
        }
        board = board >> 1;
    }
    return out;
}

std::string Uint16ToString(uint16_t board)
{
    std::string out = "";
    for (int i = 0; i < 16; i = i + 1)
    {
        if (board & 1)
        {
            out = "1" + out;
        }
        else
        {
            out = "0" + out;
        }
        board = board >> 1;
    }
    return out;
}

std::string Uint8ToString(uint8_t board)
{
    std::string out = "";
    for (int i = 0; i < 8; i = i + 1)
    {
        if (board & 1)
        {
            out = "1" + out;
        }
        else
        {
            out = "0" + out;
        }
        board = board >> 1;
    }
    return out;
}

inline bool GetCapture(MOVE move)
{
    return (move & CAPTURE) && !(move & MOVE_FLAGS & ~CAPTURE);
}

inline bool GetCastling(MOVE move)
{
    return (move & CASTLING) && !(move & MOVE_FLAGS & ~CASTLING);
}

inline bool GetUpgradeRook(MOVE move)
{
    return (move & UPGRADE_ROOK) && !(move & MOVE_FLAGS & ~UPGRADE_ROOK);
}

inline bool GetUpgradeKnight(MOVE move)
{
    return (move & UPGRADE_KNIGHT) && !(move & MOVE_FLAGS & ~UPGRADE_KNIGHT);
}

inline bool GetUpgradeBishop(MOVE move)
{
    return (move & UPGRADE_BISHOP) && !(move & MOVE_FLAGS & ~UPGRADE_BISHOP);
}

inline bool GetUpgradeQueen(MOVE move)
{
    return (move & UPGRADE_QUEEN) && !(move & MOVE_FLAGS & ~UPGRADE_QUEEN);
}

inline uint8_t GetToX(MOVE move)
{
    return ~(move & MOVE_TO_X) & 0b111;
}

inline uint8_t GetToY(MOVE move)
{
    return (move & MOVE_TO_Y) >> 3;
}

inline uint8_t GetFromX(MOVE move)
{
    return ~((move & MOVE_FROM_X) >> 6) & 0b111;
}

inline uint8_t GetFromY(MOVE move)
{
    return (move & MOVE_FROM_Y) >> 9;
}

inline uint8_t FieldIndex(uint8_t x, uint8_t y)
{
    return (y << 3) | (~x & 0b111);
}

inline BOARD SingleBitBoard(uint8_t x, uint8_t y)
{
    return 1ULL << FieldIndex(x, y);
}


void PrintMove(MOVE move)
{
    std::cout << "FROM X: " << (int)GetFromX(move)
              << " FROM Y: " << (int)GetFromY(move)
              << " TO X: " << (int)GetToX(move)
              << " TO Y: " << (int)GetToY(move)
              << " CAPTURE: " << GetCapture(move)
              << " CASTLING: " << GetCastling(move)
              << " UPGRADE ROOK: " << GetUpgradeRook(move)
              << " UPGRADE KNIGHT: " << GetUpgradeKnight(move)
              << " UPGRADE BISHOP: " << GetUpgradeBishop(move)
              << " UPGRADE QUEEN: " << GetUpgradeQueen(move)
              << std::endl;
}

inline MOVE CreateMove(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags)
{
    return (flags | ((uint16_t)(FieldIndex(xFrom, yFrom)) << 6) | FieldIndex(xTo, yTo));
}

bool InBounds(uint8_t x, uint8_t y)
{
    return !((x | y) & ~0b111U);
}

void AddMoveSlidingPiece(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD enemyKind, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags)
{
    attackedFieldsOwn = attackedFieldsOwn | SingleBitBoard(xTo, yTo);
    moves[moves[0]] = CreateMove(xFrom, yFrom, xTo, yTo, flags);
    moves[0] = moves[0] + 1;
}

void AddMove(MOVE_ARRAY &moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags)
{
    moves[moves[0]] = CreateMove(xFrom, yFrom, xTo, yTo, flags);
    moves[0] = moves[0] + 1;
}

bool TryAddMove(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (TryAddMoveNoCapture(moves, allPieces, currentColor, xFrom, yFrom, xTo, yTo))
    {
        return true;
    }
    return TryAddMoveOnlyCapture(moves, allPieces, currentColor, xFrom, yFrom, xTo, yTo);
}

bool TryAddMoveNoCapture(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo) && (SingleBitBoard(xTo, yTo) & ~allPieces))
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, 0);
        return true;
    }
    return false;
}

bool TryAddMoveOnlyCapture(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo) && (SingleBitBoard(xTo, yTo) & ~currentColor & allPieces))
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, CAPTURE);
        return true;
    }
    return false;
}

void TryAddMoveNoCaptureUpgrade(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo) && (SingleBitBoard(xTo, yTo) & ~allPieces) && (yTo == 0 || yTo == 7))
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, UPGRADE_ROOK);
        AddMove(moves, xFrom, yFrom, xTo, yTo, UPGRADE_KNIGHT);
        AddMove(moves, xFrom, yFrom, xTo, yTo, UPGRADE_BISHOP);
        AddMove(moves, xFrom, yFrom, xTo, yTo, UPGRADE_QUEEN);
    }
    else if (InBounds(xTo, yTo) && (SingleBitBoard(xTo, yTo) & ~allPieces))
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, 0);
    }
}

void TryAddMoveOnlyCaptureUpgrade(MOVE_ARRAY &moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo) && (SingleBitBoard(xTo, yTo) & ~currentColor & allPieces) && (yTo == 0 || yTo == 7))
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, CAPTURE | UPGRADE_ROOK);
        AddMove(moves, xFrom, yFrom, xTo, yTo, CAPTURE | UPGRADE_KNIGHT);
        AddMove(moves, xFrom, yFrom, xTo, yTo, CAPTURE | UPGRADE_BISHOP);
        AddMove(moves, xFrom, yFrom, xTo, yTo, CAPTURE | UPGRADE_QUEEN);
    }
    else if (InBounds(xTo, yTo) && (SingleBitBoard(xTo, yTo) & ~currentColor & allPieces))
    {
        AddMove(moves, xFrom, yFrom, xTo, yTo, CAPTURE);
    }
}

bool TryAddMoveKing(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (TryAddMoveNoCaptureKing(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, xFrom, yFrom, xTo, yTo))
    {
        return true;
    }
    return TryAddMoveOnlyCaptureKing(moves, attackedFieldsOwn, attackedFieldsEnemy, allPieces, currentColor, xFrom, yFrom, xTo, yTo);
}

bool TryAddMoveNoCaptureKing(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo))
    {
        attackedFieldsOwn = attackedFieldsOwn | SingleBitBoard(xTo, yTo);
        if (~attackedFieldsEnemy & SingleBitBoard(xTo, yTo) & ~allPieces & ~currentColor)
        {
            AddMoveKing(moves, xFrom, yFrom, xTo, yTo, 0);
            return true;
        }
    }
    return false;
}

bool TryAddMoveOnlyCaptureKing(MOVE_ARRAY &moves, BOARD &attackedFieldsOwn, BOARD attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (InBounds(xTo, yTo))
    {
        attackedFieldsOwn = attackedFieldsOwn | SingleBitBoard(xTo, yTo);
        if (~attackedFieldsEnemy & SingleBitBoard(xTo, yTo) & ~currentColor & allPieces)
        {
            AddMoveKing(moves, xFrom, yFrom, xTo, yTo, CAPTURE);
            return true;
        }
    }
    return false;
}

void AddMoveKing(MOVE_ARRAY &moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags)
{
    moves[moves[0]] = CreateMove(xFrom, yFrom, xTo, yTo, flags);
    moves[0] = moves[0] + 1;
}