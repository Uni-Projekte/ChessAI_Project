#ifndef ZOBRISTKEYGENERATOR_H
#define ZOBRISTKEYGENERATOR_H

#include "helper.h"
#include "random"
#include "Board.h"


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
    uint64_t randomRights[7];

    /*
     * 0. White
     * 1. Black
     * 2. En passent
     * 3. Kingside White
     * 4. Queenside White
     * 5. Kingside Black
     * 6. Queenside Black*/


public:
    ZobristKeyGenerator();
    void InitRandomFields();
    uint64_t CalculateZobristKey(Board board);
};


#endif //ZOBRISTKEYGENERATOR_H