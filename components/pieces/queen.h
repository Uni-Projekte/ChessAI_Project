#ifndef CHESSAI_PROJECT_QUEEN_H
#define CHESSAI_PROJECT_QUEEN_H


#include <cstdint>
#include <vector>

class queen {
public:
    static void possibleMoves(std::vector<uint8_t> moves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_QUEEN_H
