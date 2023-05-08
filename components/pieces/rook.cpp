#include "rook.h"
#include "../Board.h"
// Maximum number of possible moves for a queen is 27.
#define MAX_MOVES 14

void rook::possibleMoves(uint8_t possibleMoves[MAX_MOVES], uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.

    uint8_t moveCount = 0;

    newX = x+1;
    // east
    for (moveCount = moveCount;newX < 8 && !(ownColorBoard & (1ULL << (y * 8 + (7 - newX)))); moveCount++)
    {
        possibleMoves[moveCount] = (newX << 3) | y;
        if (interferedBoard & ~ownColorBoard & (1ULL << (y * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newX++;
    }

    newX = x-1;
    //west
    for (moveCount = moveCount;newX < 255 && !(ownColorBoard & (1ULL << (y * 8 + (7 - newX)))); moveCount++)
    {
        possibleMoves[moveCount] = (newX << 3) | y;
        if (interferedBoard & ~ownColorBoard & (1ULL << (y * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newX--;
    }

    newY = y-1;
    //south
    for (moveCount = moveCount;newY < 255 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - x)))); moveCount++)
    {
        possibleMoves[moveCount] = (x << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - x)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newY--;
    }

    newY = y+1;
    for (moveCount = moveCount;newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - x)))); moveCount++)
    {
        possibleMoves[moveCount] = (x << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - x)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newY++;
    }

    if (moveCount < MAX_MOVES - 1) {
        possibleMoves[moveCount] = 0b01000000;
    }
}