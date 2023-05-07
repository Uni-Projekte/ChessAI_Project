#include "knight.h"

#include "../Board.h"
// Maximum number of possible moves for a queen is 27.
#define MAX_MOVES 8

void knight::possibleMoves(uint8_t possibleMoves[MAX_MOVES], uint64_t interferedBoard, uint64_t ownColorBoard, uint8_t x, uint8_t y)
{
    uint8_t moveCount = 0;
    //up right

    if(y+2<8 && (x+1)<8&& !(ownColorBoard & (1ULL << (y * 8 + (7 - x))))){
        possibleMoves[moveCount] = ((x+1) << 3) | (y+2);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y+2) * 8 + (7 - (x +1))))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    uint8_t newX = x-1;
    //up left
    if(y+2<8 && newX<255&& !(ownColorBoard & (1ULL << (y * 8 + (7 - newX))))){
        possibleMoves[moveCount] = ((x-1) << 3) | (y+2);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y+2) * 8 + (7 - (x -1))))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    //right up
    if(y+1<8 && x+2<8&& !(ownColorBoard & (1ULL << (y * 8 + (7 - x))))){
        possibleMoves[moveCount] = ((x+2) << 3) | (y+1);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y+1) * 8 + (7 - (x +2))))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    uint8_t newY = y-1;
    //right down
    bool test = !(ownColorBoard & (1ULL << (newY * 8 + (7 - x))));
    if(newY<255 && x+2<8&& !(ownColorBoard & (1ULL << (newY * 8 + (7 - x))))){
        possibleMoves[moveCount] = ((x+2) << 3) | (y-1);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y-1) * 8 + (7 - (x +2))))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    //down right
    newY = y-2;
    if(newY<255 && (x+1)<8&& !(ownColorBoard & (1ULL << (newY * 8 + (7 - x))))){
        possibleMoves[moveCount] = ((x+1) << 3) | (y-2);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y-2) * 8 + (7 - (x +1))))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    //down left
    if(newY<255 && newX<255&& !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX))))){
        possibleMoves[moveCount] = ((x-1) << 3) | (y-2);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y-2) * 8 + (7 - (x -1) )))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    newX = x-2;
    //left up
    if(y+1<8 && newX<255&& !(ownColorBoard & (1ULL << (y * 8 + (7 - newX))))){
        possibleMoves[moveCount] = ((x-2) << 3) | (y+1);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y+1) * 8 + (7 - (x -2))))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    newY = y-1;
    //left down
    if(newY<255 && newX<255 && !(ownColorBoard & (1ULL << (newY * 8 + (7 - newX))))){
        possibleMoves[moveCount] = ((x-2) << 3) | (y-1);
        if (interferedBoard & ~ownColorBoard & (1ULL << ((y-1) * 8 + (7 - (x -2) )))) {
            // Set the 8th bit to 1 to indicate that the move is a capture move.
            possibleMoves[moveCount] |= 0b10000000;
        }
        moveCount++;
    }

    if (moveCount < MAX_MOVES - 1) {
        possibleMoves[moveCount] = 0b01000000;
    }
}