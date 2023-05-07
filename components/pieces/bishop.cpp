#include "bishop.h"
#include "../Board.h"
// Maximum number of possible moves for a bishop is 13.
#define MAX_MOVES 13

void bishop::possibleMoves(uint8_t possibleMoves[MAX_MOVES], uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    std::cout<<x;
    std::cout<<y;

    // Check for possible moves in the diagonal direction.

    uint8_t moveCount = 0;
    // diagonal north east

    for (moveCount = moveCount; newX < 8 && newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))); moveCount++)
    {
        possibleMoves[moveCount] = ((newX << 3) | newY);
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newX++;
        newY++;
    }

    newX = x + 1;
    newY = y - 1;
    // diagonal south east
    for (moveCount = moveCount;  newX < 8 && newY < 255  && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))); moveCount++)
    {
        possibleMoves[moveCount] = (newX << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            possibleMoves[moveCount] |= 0b10000000;
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moveCount++;
            break;
        }
        newX++;
        newY--;
    }

    newX = x - 1;
    newY = y - 1;
    // diagonal south west
    for (moveCount = moveCount; newX < 255 && newY < 255 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))); moveCount++)
    {
        possibleMoves[moveCount] = (newX << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newX--;
        newY--;
    }

    newX = x - 1;
    newY = y + 1;
    // diagonal north west
    for (moveCount = moveCount; newX < 255 && newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))); moveCount++)
    {
        possibleMoves[moveCount] = (newX << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            moveCount++;
            break;
        }
        newX--;
        newY++;
    }

    if (moveCount < MAX_MOVES - 1) {
        possibleMoves[moveCount] = 0b01000000;
    }
}
