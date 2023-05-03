#include "bitBoardLoader.h"

/**
 * @brief create New BitBoardLoader
 * @return new BitBoardLoader
 */
BitBoardLoader::BitBoardLoader(std::string filename)
{
    std::size_t pos = 0;
    this->black = std::stoull(
        "11111111"
        "11111111"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->white = std::stoull(
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "11111111",
        &pos, 2);

    pos = 0;
    this->pawns = std::stoull(
        "00000000"
        "11111111"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "00000000",
        &pos, 2);

    pos = 0;
    this->towers = std::stoull(
        "10000001"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "10000001",
        &pos, 2);

    pos = 0;
    this->towers = std::stoull(
        "01000010"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "01000010",
        &pos, 2);

    pos = 0;
    this->kings = std::stoull(
        "00001000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00001000",
        &pos, 2);

    pos = 0;
    this->queens = std::stoull(
        "00010000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00010000",
        &pos, 2);

    pos = 0;
    this->bishops = std::stoull(
        "00100100"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00100100",
        &pos, 2);

    pos = 0;
    this->r8 = std::stoull(
        "11111111"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r7 = std::stoull(
        "00000000"
        "11111111"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r6 = std::stoull(
        "00000000"
        "00000000"
        "11111111"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r5 = std::stoull(
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "00000000"
        "00000000"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r4 = std::stoull(
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "00000000"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r3 = std::stoull(
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "00000000"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r2 = std::stoull(
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111"
        "00000000",
        &pos, 2);

    pos = 0;
    this->r1 = std::stoull(
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "00000000"
        "11111111",
        &pos, 2);

    pos = 0;
    this->a = std::stoull(
        "10000000"
        "10000000"
        "10000000"
        "10000000"
        "10000000"
        "10000000"
        "10000000"
        "10000000",
        &pos, 2);

    pos = 0;
    this->b = std::stoull(
        "01000000"
        "01000000"
        "01000000"
        "01000000"
        "01000000"
        "01000000"
        "01000000"
        "01000000",
        &pos, 2);

    pos = 0;
    this->c = std::stoull(
        "00100000"
        "00100000"
        "00100000"
        "00100000"
        "00100000"
        "00100000"
        "00100000"
        "00100000",
        &pos, 2);

    pos = 0;
    this->d = std::stoull(
        "00010000"
        "00010000"
        "00010000"
        "00010000"
        "00010000"
        "00010000"
        "00010000"
        "00010000",
        &pos, 2);

    pos = 0;
    this->e = std::stoull(
        "00001000"
        "00001000"
        "00001000"
        "00001000"
        "00001000"
        "00001000"
        "00001000"
        "00001000",
        &pos, 2);

    pos = 0;
    this->f = std::stoull(
        "00000100"
        "00000100"
        "00000100"
        "00000100"
        "00000100"
        "00000100"
        "00000100"
        "00000100",
        &pos, 2);

    pos = 0;
    this->g = std::stoull(
        "00000010"
        "00000010"
        "00000010"
        "00000010"
        "00000010"
        "00000010"
        "00000010"
        "00000010",
        &pos, 2);

    pos = 0;
    this->h = std::stoull(
        "00000001"
        "00000001"
        "00000001"
        "00000001"
        "00000001"
        "00000001"
        "00000001"
        "00000001",
        &pos, 2);
}

uint64_t BitBoardLoader::GetBlack()
{
    return this->black;
}

uint64_t BitBoardLoader::GetWhite()
{
    return this->white;
}

uint64_t BitBoardLoader::GetPawns()
{
    return this->pawns;
}

uint64_t BitBoardLoader::GetBishops()
{
    return this->bishops;
}

uint64_t BitBoardLoader::GetKings()
{
    return this->kings;
}

uint64_t BitBoardLoader::GetQueens()
{
    return this->queens;
}

uint64_t BitBoardLoader::GetKnights()
{
    return this->knights;
}

uint64_t BitBoardLoader::GetTowers()
{
    return this->towers;
}

uint64_t BitBoardLoader::GetR8()
{
    return this->r8;
}

uint64_t BitBoardLoader::GetR7()
{
    return this->r7;
}

uint64_t BitBoardLoader::GetR6()
{
    return this->r6;
}

uint64_t BitBoardLoader::GetR5()
{
    return this->r5;
}

uint64_t BitBoardLoader::GetR4()
{
    return this->r4;
}

uint64_t BitBoardLoader::GetR3()
{
    return this->r3;
}

uint64_t BitBoardLoader::GetR2()
{
    return this->r2;
}

uint64_t BitBoardLoader::GetR1()
{
    return this->r1;
}

uint64_t BitBoardLoader::GetA()
{
    return this->a;
}

uint64_t BitBoardLoader::GetB()
{
    return this->b;
}

uint64_t BitBoardLoader::GetC()
{
    return this->c;
}

uint64_t BitBoardLoader::GetD()
{
    return this->d;
}

uint64_t BitBoardLoader::GetE()
{
    return this->e;
}

uint64_t BitBoardLoader::GetF()
{
    return this->f;
}

uint64_t BitBoardLoader::GetG()
{
    return this->g;
}

uint64_t BitBoardLoader::GetH()
{
    return this->h;
}

/**
 * @brief get row bit-board from index
 * @param index: 0-7 representing row 1-8
 * @return row bit-board
 */
uint64_t BitBoardLoader::GetRowFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return this->r1;
    case 1:
        return this->r2;
    case 2:
        return this->r3;
    case 3:
        return this->r4;
    case 4:
        return this->r5;
    case 5:
        return this->r6;
    case 6:
        return this->r7;
    case 7:
        return this->r8;
    default:
        return 0;
    }
}

/**
 * @brief get column bit-board from index
 * @param index: 0-7 representing column a-h
 * @return column bit-board
 */
uint64_t BitBoardLoader::GetColumnFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return this->a;
    case 1:
        return this->b;
    case 2:
        return this->c;
    case 3:
        return this->d;
    case 4:
        return this->e;
    case 5:
        return this->f;
    case 6:
        return this->g;
    case 7:
        return this->h;
    default:
        return 0;
    }
}

/**
 * @brief get column letter from index
 * @param index: 0-7 representing column A-H
 * @return column letter
 */
std::string BitBoardLoader::GetColumnLetterFromIndex(int index)
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
        return "";
    }
}