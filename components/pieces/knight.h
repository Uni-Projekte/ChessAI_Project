#ifndef CHESSAI_PROJECT_KNIGHT_H
#define CHESSAI_PROJECT_KNIGHT_H

#include <cstdint>
#include <vector>

class knight {
    public:
        static void possibleMoves(std::vector<uint8_t> moves, uint64_t interferedBoard, uint64_t colorBoard, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_KNIGHT_H
