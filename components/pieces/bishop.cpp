#include "bishop.h"



uint8_t* bishop::possibleMoves(uint64_t interferedBoard, uint64_t colorBoard, uint8_t pos)
{
    const uint8_t MAX_MOVES = 13;

    // Array of possible moves. 13 is the maximum number of possible moves for a bishop
    uint8_t possibleMoves[MAX_MOVES];

    // x and y coordinates of the piece
    uint8_t x = pos & 0b00111000;
    uint8_t y = pos & 0b00000111;

    for(uint8_t i = 0; i<= 7; i++){
        /*if(7*){
            uint8_t newX = x-i;
            uint8_t newY = y+i;
        }
        if(x-i>7 && y+i<0){
            uint8_t newX = x-i;
            uint8_t newY = y+i;
        }
        if(x-i>0 && y+i<7){
            uint8_t newX = x-i;
            uint8_t newY = y+i;
        }
        if(x-i>0 && y+i<7){
            uint8_t newX = x-i;
            uint8_t newY = y+i;
        }*/
    }




    return possibleMoves;
}

// x+i y+j: pos <<

/*
 * 1 0 0 0 0 0 2 0
 * 0 1 0 0 0 1 0 0
 * 0 0 1 0 1 0 0 0
 * 0 0 0 * 0 0 0 0
 * 0 0 1 0 1 0 0 0
 * 0 1 0 0 0 2 0 0
 * 1 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 */