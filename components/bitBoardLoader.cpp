#include "bitBoardLoader.h"

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

uint64_t inline SingleBitBoard(uint8_t x, uint8_t y)
{
    return (1ULL << ((uint64_t)y << 3) | (uint64_t)x);
}

uint8_t inline FieldIndex(uint8_t x, uint8_t y)
{
    return (((uint64_t)y << 3) | (uint64_t)x);
}

void inline TryMove(std::vector<uint8_t> moves, uint64_t allPiecesBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y) {
    if (SingleBitBoard(x, y) & allPiecesBoard & ~ownColorBoard)
    {
        moves.push_back(FieldIndex(x, y) | 0b10000000); // capture
    }
    else if (SingleBitBoard(x, y) & ~ownColorBoard)
    {
        moves.push_back(FieldIndex(x, y)); // normal move
    }
}