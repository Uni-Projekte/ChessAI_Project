#ifndef CHESSAI_PROJECT_ROOK_H
#define CHESSAI_PROJECT_ROOK_H

#include <cstdint>

class rook {
public:
    static void possibleMoves(uint8_t possibleMoves[14], uint64_t interferedBoard, uint64_t colorBoard, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_ROOK_H
