#include "ZobristKeyGenerator.h"


ZobristKeyGenerator::ZobristKeyGenerator()
{
    this->InitRandomFields();
}

void ZobristKeyGenerator::InitRandomFields(){
    std::random_device rd;                          // Obtain a random seed from the hardware
    std::mt19937_64 eng(rd());                       // Seed the random number engine
    std::uniform_int_distribution<uint64_t> distr;   // Distribution for uint64_t

    for(int row = 0; row <= 7; row++){
        for(int column = 0; column <=7; column++){
            for(int field = 0; field <= 11; field++){
                this->randomKeyFields[row][column][field] = distr(eng);
            }
        }
    }
}

uint64_t ZobristKeyGenerator::CalculateZobristKey(uint64_t black, uint64_t white, uint64_t kings, uint64_t queens,
                                                  uint64_t bishops, uint64_t knights, uint64_t rooks,
                                                  uint64_t pawns){

    uint64_t zobristKey = 0;

    for (uint8_t x = 0; x < 8; x = x + 1)
    {
        for (uint8_t y = 0; y < 8; y = y + 1)
        {
            uint64_t currentPosition = SingleBitBoard(x, y);
            if (currentPosition & black)
            {
                if (kings & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][6];
                }
                else if (queens & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][7];
                }
                else if (bishops & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][8];
                }
                else if (knights & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][9];
                }
                else if (rooks & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][10];
                }
                else if (pawns & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][11];
                }
            }
            else if (currentPosition & white)
            {
                if (kings & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][0];
                }
                else if (queens & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][1];
                }
                else if (bishops & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][2];
                }
                else if (knights & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][3];
                }
                else if (rooks & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][4];
                }
                else if (pawns & currentPosition)
                {
                    zobristKey ^= this->randomKeyFields[y][x][5];
                }
            }
        }
    }
    return zobristKey;
}