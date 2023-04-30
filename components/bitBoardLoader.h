#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef BITBOARDLOADER_H
#define BITBOARDLOADER_H

class BitBoardLoader {
public:
    BitBoardLoader(std::string filename);

public:
    uint64_t GetBlack();
    uint64_t GetWhite();
    uint64_t GetPawns();
    uint64_t GetBishops();
    uint64_t GetKings();
    uint64_t GetQueens();
    uint64_t GetKnights();
    uint64_t GetTowers();
    uint64_t GetR8();
    uint64_t GetR7();
    uint64_t GetR6();
    uint64_t GetR5();
    uint64_t GetR4();
    uint64_t GetR3();
    uint64_t GetR2();
    uint64_t GetR1();
    uint64_t GetA();
    uint64_t GetB();
    uint64_t GetC();
    uint64_t GetD();
    uint64_t GetE();
    uint64_t GetF();
    uint64_t GetG();
    uint64_t GetH();
    uint64_t GetRowFromIndex(int index);
    uint64_t GetColumnFromIndex(int index);
    std::string GetColumnLetterFromIndex(int index);

private:
    void setBitBoard(std::string name, uint64_t bin);

private:
    uint64_t black = 0;
    uint64_t white = 0;
    uint64_t pawns = 0;
    uint64_t bishops = 0;
    uint64_t kings = 0;
    uint64_t queens = 0;
    uint64_t knights = 0;
    uint64_t towers = 0;
    uint64_t r8 = 0;
    uint64_t r7 = 0;
    uint64_t r6 = 0;
    uint64_t r5 = 0;
    uint64_t r4 = 0;
    uint64_t r3 = 0;
    uint64_t r2 = 0;
    uint64_t r1 = 0;
    uint64_t a = 0;
    uint64_t b = 0;
    uint64_t c = 0;
    uint64_t d = 0;
    uint64_t e = 0;
    uint64_t f = 0;
    uint64_t g = 0;
    uint64_t h = 0;
};

#endif // BITBOARDLOADER_H