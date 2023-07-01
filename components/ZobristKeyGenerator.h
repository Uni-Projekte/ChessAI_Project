#ifndef ZOBRISTKEYGENERATOR_H
#define ZOBRISTKEYGENERATOR_H

#include "helper.h"
#include "random"


class ZobristKeyGenerator {
private:
    uint64_t randomKeyFields[8][8][12];
    /* 0. WKing
     * 1. WQueen
     * 2. WBishop
     * 3. WKnight
     * 4. WRooks
     * 5. WPawn
     * 6. BKing
     * 7. ...
     * */

public:
    ZobristKeyGenerator();
    void InitRandomFields();
    uint64_t CalculateZobristKey(uint64_t black, uint64_t white, uint64_t kings, uint64_t queens,
                                 uint64_t bishops, uint64_t knights, uint64_t rooks, uint64_t pawns);
};


#endif //ZOBRISTKEYGENERATOR_H