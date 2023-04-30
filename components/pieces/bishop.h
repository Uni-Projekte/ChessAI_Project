#ifndef CHESSAI_PROJECT_BISHOP_H
#define CHESSAI_PROJECT_BISHOP_H


#include <cstdint>
#include <array>

class bishop {
    public:
        static uint8_t*  possibleMoves(uint64_t interferedBoard, uint64_t colorBoard, uint8_t pos);
};


#endif //CHESSAI_PROJECT_BISHOP_H
