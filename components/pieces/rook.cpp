#include "rook.h"
#include "../Board.h"

void rook::possibleMoves(std::vector<uint8_t> moves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;

    // Check for possible moves in the diagonal direction.

    newX = x+1;
    // east
    while (newX < 8 && !(ownColorBoard & SingleBitBoard(newX,y)))
    {
        moves.push_back(FieldIndex(newX, y));
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(newX, y))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX++;
    }

    newX = x-1;
    //west
    while (newX < 255 && !(ownColorBoard & SingleBitBoard(newX, y)))
    {
        moves.push_back(FieldIndex(newX, y));
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(newX, y))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newX--;
    }

    newY = y-1;
    //south
    while (newY < 255 && !(ownColorBoard & SingleBitBoard(x, newY)))
    {
        moves.push_back(FieldIndex(x, newY));
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(x, newY))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newY--;
    }

    newY = y+1;
    while (newY < 8 && !(ownColorBoard & SingleBitBoard(x, newY)))
    {
        moves.push_back(FieldIndex(x, newY));
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(x, newY))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            moves[0] |= 0b10000000;
            break;
        }
        newY++;
    }
}