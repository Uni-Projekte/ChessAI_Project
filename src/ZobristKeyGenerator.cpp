#include "ZobristKeyGenerator.h"

ZobristKeyGenerator::ZobristKeyGenerator()
{
    this->InitRandomFields();
}

void ZobristKeyGenerator::InitRandomFields(){
    std::random_device rd;                          // Obtain a random seed from the hardware
    std::mt19937_64 eng(rd());                       // Seed the random number engine
    std::uniform_int_distribution<uint64_t> distr;   // Distribution for uint64_t

    for(int row = 0; row < 8; row++){
        for(int column = 0; column < 8; column++){
            for(int field = 0; field < 12; field++){
                this->randomKeyFields[row][column][field] = distr(eng);
            }
        }
    }

    for(int i = 0; i<7; i++){
        this->randomRights[i] = distr(eng);
    }
}

uint64_t ZobristKeyGenerator::CalculateZobristKey(Board board){

     uint64_t zobristKey = 0;

    uint64_t black = board.GetBlack();
    uint64_t white = board.GetWhite();
    uint64_t kings = board.GetKings();
    uint64_t queens = board.GetQueens();
    uint64_t bishops = board.GetBishops();
    uint64_t knights = board.GetKnights();
    uint64_t rooks = board.GetRooks();
    uint64_t pawns = board.GetPawns();

    uint8_t moveRights = board.GetMoveRights();
    uint8_t enPassant = board.GetEnPassant();
    COLOR playerTurn = board.GetCurrentColor();

    switch (playerTurn) {
        case WHITE:
            zobristKey ^= this->randomRights[0];
            break;
        case BLACK:
            zobristKey ^= this->randomRights[1];
            break;
        default:
            break;
    }

    if(moveRights & 0b10000000){
        zobristKey ^= this->randomRights[2];
    }
    if(moveRights & 0b01000000){
        zobristKey ^= this->randomRights[3];
    }
    if(moveRights & 0b00100000){
        zobristKey ^= this->randomRights[4];
    }
    if(moveRights & 0b00010000){
        zobristKey ^= this->randomRights[5];
    }

    if(enPassant & 0b10000000){
        zobristKey ^= this->randomRights[6];
    }


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
                    //zobristKey ^= SingleBitBoard(x,y);

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

/*uint64_t ZobristKeyGenerator::updateZobristKey(std::uint64_t key, const Board board, const MOVE move) {

    const BOARD from = GetSingleBitBoardFrom(move);
    const BOARD to = GetSingleBitBoardTo(move);
    COLOR player = board.GetCurrentColor();
    const bool castling = GetCastling(move);

    uint8_t xFrom = (move & 0b000111000000) >> 6;
    uint8_t yFrom = (move & 0b111000000000) >> 9;
    uint8_t xTo = (move & 0b000000000111);
    uint8_t yTo = (move & 0b000000111000) >> 3;

    if (board.GetKings() & to)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yTo][xTo][6];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yTo][xTo][0];
                break;
        }
    }
    else if (board.GetQueens() & to)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yTo][xTo][7];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yTo][xTo][1];
                break;
        }
    }
    else if (board.GetBishops() & to)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yTo][xTo][8];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yTo][xTo][2];
                break;
        }
    }
    else if (board.GetKnights() & to)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yTo][xTo][9];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yTo][xTo][3];
                break;
        }
    }
    else if (board.GetRooks() & to)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yTo][xTo][10];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yTo][xTo][4];
                break;
        }
    }
    else if (board.GetPawns() & to)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yTo][xTo][11];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yTo][xTo][5];
                break;
        }
    }


    if (board.GetKings() & from)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yFrom][xFrom][0];
                key ^= this->randomKeyFields[yTo][xTo][0];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yFrom][xFrom][6];
                key ^= this->randomKeyFields[yTo][xTo][6];
                break;
        }
    }
    else if (board.GetQueens() & from)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yFrom][xFrom][1];
                key ^= this->randomKeyFields[yTo][xTo][1];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yFrom][xFrom][7];
                key ^= this->randomKeyFields[yTo][xTo][7];
                break;
        }
    }
    else if (board.GetBishops() & from)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yFrom][xFrom][2];
                key ^= this->randomKeyFields[yTo][xTo][2];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yFrom][xFrom][8];
                key ^= this->randomKeyFields[yTo][xTo][8];
                break;
        }
    }
    else if (board.GetKnights() & from)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yFrom][xFrom][3];
                key ^= this->randomKeyFields[yTo][xTo][3];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yFrom][xFrom][9];
                key ^= this->randomKeyFields[yTo][xTo][9];
                break;
        }
    }
    else if (board.GetRooks() & from)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yFrom][xFrom][4];
                key ^= this->randomKeyFields[yTo][xTo][4];
                break;
            case BLACK:
                key ^= this->randomKeyFields[yFrom][xFrom][10];
                key ^= this->randomKeyFields[yTo][xTo][10];
                break;
        }
    }
    else if (board.GetPawns() & from)
    {
        switch(player){
            case WHITE:
                key ^= this->randomKeyFields[yFrom][xFrom][5];
                switch (move & UPGRADE_FLAGS) {
                    case UPGRADE_ROOK:
                        key ^= this->randomKeyFields[yTo][xTo][4];
                        break;
                    case UPGRADE_BISHOP:
                        key ^= this->randomKeyFields[yTo][xTo][2];
                        break;
                    case UPGRADE_KNIGHT:
                        key ^= this->randomKeyFields[yTo][xTo][3];
                        break;
                    case UPGRADE_QUEEN:
                        key ^= this->randomKeyFields[yTo][xTo][1];
                        break;
                    default:
                        key ^= this->randomKeyFields[yTo][xTo][5];
                        break;
                }
                break;
            case BLACK:
                key ^= this->randomKeyFields[yFrom][xFrom][11];
                switch (move & UPGRADE_FLAGS) {
                    case UPGRADE_ROOK:
                        key ^= this->randomKeyFields[yTo][xTo][10];
                        break;
                    case UPGRADE_BISHOP:
                        key ^= this->randomKeyFields[yTo][xTo][9];
                        break;
                    case UPGRADE_KNIGHT:
                        key ^= this->randomKeyFields[yTo][xTo][8];
                        break;
                    case UPGRADE_QUEEN:
                        key ^= this->randomKeyFields[yTo][xTo][7];
                        break;
                    default:
                        key ^= this->randomKeyFields[yTo][xTo][11];
                        break;
                }
                break;
        }
    }

    if(castling){
        if(xTo == 2){
            switch(player){
                case WHITE:
                    key ^= this->randomKeyFields[7][3][4];
                    break;
                case BLACK:
                    key ^= this->randomKeyFields[0][3][10];
                    break;
            }
        }
        else if(xTo == 6){
            switch(player){
                case WHITE:
                    key ^= this->randomKeyFields[7][5][4];
                    break;
                case BLACK:
                    key ^= this->randomKeyFields[0][5][10];
                    break;
            }
        }
    }


    return key;
}*/