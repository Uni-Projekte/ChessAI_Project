#ifndef CHESSAI_PROJECT_BISHOP_H
#define CHESSAI_PROJECT_BISHOP_H


#include <vector>

class bishop
{
public:
    static void possibleMoves(std::vector<uint8_t> possibleMoves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y);
};

#endif //CHESSAI_PROJECT_BISHOP_H
