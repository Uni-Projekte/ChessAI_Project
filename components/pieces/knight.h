#ifndef CHESSAI_PROJECT_KNIGHT_H
#define CHESSAI_PROJECT_KNIGHT_H

#include <cstdint>

class knight {
    public:
        static void possibleMoves(uint8_t possibleMoves[8], uint64_t interferedBoard, uint64_t colorBoard, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_KNIGHT_H
