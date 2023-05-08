#include "king.h"
#include "../bitBoardLoader.h"

//currently there is no check if the king run into a position where he can be captured
void king::possibleMoves(std::vector<uint8_t> moves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    TryMove(moves, interferedBoard, ownColorBoard, x + 1, y + 1);
    TryMove(moves, interferedBoard, ownColorBoard, x + 1, y);
    TryMove(moves, interferedBoard, ownColorBoard, x + 1, y - 1);
    TryMove(moves, interferedBoard, ownColorBoard, x, y + 1);
    TryMove(moves, interferedBoard, ownColorBoard, x, y - 1);
    TryMove(moves, interferedBoard, ownColorBoard, x - 1, y + 1);
    TryMove(moves, interferedBoard, ownColorBoard, x - 1, y);
    TryMove(moves, interferedBoard, ownColorBoard, x - 1, y - 1);
}