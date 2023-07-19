#include "helper.h"
#include <sstream>
#include <string>


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

char GetColumnLetterFromIndex(int index)
{
    return static_cast<char>('A' +   index);
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

COLOR opponent(COLOR color)
{
    return color ? WHITE : BLACK;
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
    std::string out;
    for (int i = 0; i < 8; i = i + 1)
    {
        if (board & 1)
        {
            out.append("1");
        }
        else
        {
            out.append("0");
        }
        board = board >> 1;
    }
    return out;
}

std::string MoveForGameServer(MOVE move) {
    uint8_t xFrom = 7-((move & 0b000111000000) >> 6);
    uint8_t yFrom = (move & 0b111000000000) >> 9;
    uint8_t xTo = 7-(move & 0b000000000111);
    uint8_t yTo = (move & 0b000000111000) >> 3;

    std::string out = "";

    out.push_back(std::tolower(GetColumnLetterFromIndex(xFrom)));
    out.append((std::to_string(yFrom + 1)));
    out.push_back(std::tolower(GetColumnLetterFromIndex(xTo)));
    out.append(std::to_string(yTo + 1));
    out.push_back('\n');

    return out;
}

inline PIECE GetCapture(MOVE move)
{
    return (PIECE) ((move & CAPTURE_FLAGS) >> 15);
}

inline bool GetMoveEnPassante(MOVE move)
{
    return move & EN_PASSANTE;
}

inline bool GetCastling(MOVE move)
{
    return move & CASTLING;
}

inline bool GetUpgradeRook(MOVE move)
{
    return (move & UPGRADE_FLAGS) == UPGRADE_ROOK;
}

inline bool GetUpgradeKnight(MOVE move)
{
    return (move & UPGRADE_FLAGS) == UPGRADE_KNIGHT;
}

inline bool GetUpgradeBishop(MOVE move)
{
    return (move & UPGRADE_FLAGS) == UPGRADE_BISHOP;
}

inline bool GetUpgradeQueen(MOVE move)
{
    return (move & UPGRADE_FLAGS) == UPGRADE_QUEEN;
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

uint8_t FieldIndex(uint8_t x, uint8_t y)
{
    return (y << 3) | (~x & 0b111);
}

BOARD SingleBitBoard(uint8_t x, uint8_t y)
{
    return 1ULL << FieldIndex(x, y);
}


void PrintMove(MOVE move)
{
    std::cout << MoveToString(move);
}

std::string MoveToString(MOVE move)
{
    std::stringstream ss;
    ss << "FROM X: " << (int)GetFromX(move)
       << " FROM Y: " << (int)GetFromY(move)
       << " TO X: " << (int)GetToX(move)
       << " TO Y: " << (int)GetToY(move)
       << " CAPTURE: " << GetCapture(move)
       << " CASTLING: " << GetCastling(move)
       << " UPGRADE ROOK: " << GetUpgradeRook(move)
       << " UPGRADE KNIGHT: " << GetUpgradeKnight(move)
       << " UPGRADE BISHOP: " << GetUpgradeBishop(move)
       << " UPGRADE QUEEN: " << GetUpgradeQueen(move)
       << " EN PASSANT: " << GetMoveEnPassante(move)
       << std::endl;

    std::string result = ss.str();
    return result;
}

void showDifference(const std::unordered_set<int>& set1, const std::unordered_set<int>& set2) {
    std::unordered_set<int> difference;

    for (const auto& element : set1) {
        if (set2.find(element) == set2.end()) {
            difference.insert(element);
        }
    }

    for (const MOVE element : difference) {
        PrintMove(element);
    }

    std::cout << std::endl;
}

MOVE CreateMove(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, int flags)
{
    return (flags | ((uint16_t)(FieldIndex(xFrom, yFrom)) << 6) | FieldIndex(xTo, yTo));
}

bool InBounds(uint8_t x, uint8_t y)
{
    return !((x | y) & ~0b111U);
}

uint8_t SingleBitboardToPosition(BOARD board)
{
    uint8_t y = 0;
    if(board<=(1ULL<<7))y=0;
    else if(board <= (1ULL<<15))y=1;
    else if(board <= (1ULL<<23))y=2;
    else if(board <= (1ULL<<31))y=3;
    else if(board <= (1ULL<<39))y=4;
    else if(board <= (1ULL<<47))y=5;
    else if(board <= (1ULL<<55))y=6;
    else if(board <= (1ULL<<63))y=7;

    board = board >> (y*8);

    uint8_t x = 0;
    if(board==1)x=0;
    else if(board==2)x=1;
    else if(board==4)x=2;
    else if(board==8)x=3;
    else if(board==16)x=4;
    else if(board==32)x=5;
    else if(board==64)x=6;
    else if(board==128)x=7;

    return (x<<3)|y;
}

uint8_t GetDirection(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo)
{
    if (xFrom == xTo)
    {
        return 1;
    }
    else if (yFrom == yTo)
    {
        return 2;
    }
    else if ((xFrom < xTo && yFrom < yTo) || (xFrom > xTo && yFrom > yTo))
    {
        return 3;
    }
    else
    {
        return 4;
    }
}