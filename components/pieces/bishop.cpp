#include "bishop.h"
#include "../bitBoardLoader.h"

//abxxxyyy
//a - schlagzug
//b - rochade
//a&b - ende array

// Check for possible moves in the diagonal directions.
void bishop::possibleMoves(std::vector<uint8_t> possibleMoves, uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    // diagonal north east
    uint8_t newX = x + 1;
    uint8_t newY = y + 1;
    while (newX < 8 && newY < 8 && !(ownColorBoard & SingleBitBoard(newX,newY)))
    {
        possibleMoves.push_back((newX << 3) | newY);
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(newX, newY))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[0] |= (0b10000000);
            break;
        }
        newX++;
        newY++;
    }

    // diagonal south east
    newX = x + 1;
    newY = y - 1;
    while (newX < 8 && newY < 255 && !(ownColorBoard & SingleBitBoard(newX, newY)))
    {
        possibleMoves.push_back((newX << 3) | newY);
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(newX, newY))
        {
            possibleMoves[0] |= 0b10000000;
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            break;
        }
        newX++;
        newY--;
    }

    // diagonal south west
    newX = x - 1;
    newY = y - 1;
    while (newX < 255 && newY < 255 && !(ownColorBoard & SingleBitBoard(newX, newY)))
    {
        possibleMoves.push_back((newX << 3) | newY);
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(newX, newY))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[0] |= 0b10000000;
            break;
        }
        newX--;
        newY--;
    }

    // diagonal north west
    newX = x - 1;
    newY = y + 1;
    while (newX < 255 && newY < 8 && !(ownColorBoard & SingleBitBoard(newX, newY)))
    {
        possibleMoves.push_back((newX << 3) | newY);
        if (interferedBoard & ~ownColorBoard & SingleBitBoard(newX, newY))
        {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[0] |= 0b10000000;
            break;
        }
        newX--;
        newY++;
    }
}
