#ifndef CHESSAI_PROJECT_KING_H
#define CHESSAI_PROJECT_KING_H

#include <vector>

class king {
    static void possibleMoves(std::vector<uint8_t> possibleMoves, uint64_t interferedBoard, uint64_t colorBoard, uint8_t x, uint8_t y);
};


#endif //CHESSAI_PROJECT_KING_H
