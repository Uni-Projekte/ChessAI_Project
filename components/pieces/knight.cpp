#include "knight.h"
#include "../Board.h"
// Maximum number of possible moves for a queen is 27.
#define MAX_MOVES 8

void knight::possibleMoves(std::vector<uint8_t> moves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    //up right
    TryMove(moves, interferedBoard, ownColorBoard, x + 1, y + 2);
    TryMove(moves, interferedBoard, ownColorBoard, x + 1, y - 2);
    TryMove(moves, interferedBoard, ownColorBoard, x - 1, y + 2);
    TryMove(moves, interferedBoard, ownColorBoard, x - 1, y - 2);
    TryMove(moves, interferedBoard, ownColorBoard, x + 2, y + 1);
    TryMove(moves, interferedBoard, ownColorBoard, x - 2, y + 1);
    TryMove(moves, interferedBoard, ownColorBoard, x + 2, y - 1);
    TryMove(moves, interferedBoard, ownColorBoard, x - 2, y - 1);
}