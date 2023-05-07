#ifndef CHESSAI_PROJECT_QUEEN_H
#define CHESSAI_PROJECT_QUEEN_H


#include <cstdint>

class queen {
public:
    static void possibleMoves(uint8_t possibleMoves[13], uint64_t interferedBoard, uint64_t colorBoard, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_QUEEN_H
