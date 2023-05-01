#ifndef CHESSAI_PROJECT_BISHOP_H
#define CHESSAI_PROJECT_BISHOP_H


#include <cstdint>
#include <array>

// Maximum number of possible moves for a bishop is 13.
#define MAX_MOVES 13

class bishop {
public:
    static std::array<uint8_t, MAX_MOVES>  possibleMoves(uint64_t interferedBoard, uint64_t colorBoard, uint8_t pos);
};


#endif //CHESSAI_PROJECT_BISHOP_H
