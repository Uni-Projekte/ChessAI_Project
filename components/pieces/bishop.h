#ifndef CHESSAI_PROJECT_BISHOP_H
#define CHESSAI_PROJECT_BISHOP_H


#include <cstdint>
#include <array>

// Maximum number of possible moves for a bishop is 13.
#define MAX_MOVES 13

class bishop
{
public:
    static void possibleMoves(uint8_t possibleMoves[13], uint64_t interferedBoard, uint64_t colorBoard, uint8_t x, uint8_t y);
};

#endif //CHESSAI_PROJECT_BISHOP_H
