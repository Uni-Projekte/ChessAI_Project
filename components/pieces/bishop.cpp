#include "bishop.h"
#include "array"

// Maximum number of possible moves for a bishop is 13.
#define MAX_MOVES 13

std::array<uint8_t, MAX_MOVES> bishop::possibleMoves(uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t pos)
{
    // Array of possible moves.
    std::array<uint8_t, MAX_MOVES> possibleMoves;

    // x and y coordinates of the piece
    int8_t x = (pos & 0b00111000) >> 3;
    int8_t y = pos & 0b00000111;

    int8_t newX = x + 1;
    int8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.

    uint8_t moveCount = 0;
    // diagonal north east
    for (uint8_t i = 1; i < 8 && newX < 8 && newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + newX))); i++)
    {
        possibleMoves[moveCount] = ((newX << 3) | newY);
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + newX))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            break;
        }
        newX++;
        newY++;
        moveCount++;
    }


    newX = x + 1;
    newY = y - 1;
    // diagonal south east
    for (uint8_t i = 1; i < 8 && newX < 8 && newY >= 0 && !(ownColorBoard & (1ULL << (newY * 8 + newX))); i++)
    {
        possibleMoves[moveCount] = (newX << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + newX))) {
            possibleMoves[moveCount] |= 0b10000000;
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            break;
        }
        newX++;
        newY--;
        moveCount++;
    }

    newX = x - 1;
    newY = y - 1;
    // diagonal south west
    for (uint8_t i = 1; i < 8 && newX >= 0 && newY >= 0 && !(ownColorBoard & (1ULL << (newY * 8 + newX))); i++)
    {
        possibleMoves[moveCount] = (newX << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + newX))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            break;
        }
        newX--;
        newY--;
        moveCount++;
    }

    newX = x - 1;
    newY = y + 1;
    // diagonal north west
    for (uint8_t i = 1; i < 8 && newX >= 0 && newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + newX))); i++)
    {
        possibleMoves[moveCount] = (newX << 3) | newY;
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + newX))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
            break;
        }
        newX--;
        newY++;
        moveCount++;
    }


    return possibleMoves;
}
