#include "queen.h"
#include "../Board.h"

void queen::possibleMoves(std::vector<uint8_t> moves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.
    while (newX < 8 && newY < 8 && !(ownColorBoard & SingleBitBoard(newX,newY)))
    {
        moves.push_back(FieldIndex(newX, newY));
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX++;
        newY++;
    }

    newX = x + 1;
    newY = y - 1;
    // diagonal south east
    while (newX < 8 && newY < 255 && !(ownColorBoard & SingleBitBoard(newX, newY)))
    {
        moves.push_back(FieldIndex(newX, newY));
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            moves[0] |= 0b10000000;
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            break;
        }
        newX++;
        newY--;
    }

    newX = x - 1;
    newY = y - 1;
    // diagonal south west
    while (newX < 255 && newY < 255 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))))
    {
        moves.push_back(FieldIndex(newX, newY));
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX--;
        newY--;
    }

    newX = x - 1;
    newY = y + 1;
    // diagonal north west
    while (newX < 255 && newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))))
    {
        moves.push_back(FieldIndex(newX, newY));
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX--;
        newY++;
    }

    newX = x+1;
    // east
    while (newX < 8 && !(ownColorBoard & (1ULL << (y * 8 + (7 - newX)))))
    {
        moves.push_back(FieldIndex(newX, y));
        if (interferedBoard & ~ownColorBoard & (1ULL << (y * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX++;
    }

    newX = x-1;
    //west
    while (newX < 255 && !(ownColorBoard & (1ULL << (y * 8 + (7 - newX)))))
    {
        moves.push_back(FieldIndex(newX, y));
        if (interferedBoard & ~ownColorBoard & (1ULL << (y * 8 + (7 - newX)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX--;
    }

    newY = y-1;
    //south
    while (newY < 255 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - x)))))
    {
        moves.push_back(FieldIndex(x, newY));
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - x)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newY--;
    }

    newY = y+1;
    while (newY < 8 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - x)))))
    {
        moves.push_back(FieldIndex(x, newY));
        if (interferedBoard & ~ownColorBoard & (1ULL << (newY * 8 + (7 - x)))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newY++;
    }
}