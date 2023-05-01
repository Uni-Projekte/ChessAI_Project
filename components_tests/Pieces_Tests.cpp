#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../components/Board.h"
#include "../components/pieces/bishop.h"
#include <filesystem>
#include <bitset>
#include <string>
namespace fs = std::filesystem;

TEST(PiecesTest, PieceTest1) {
    std::filesystem::path path = "./bitboards.txt";

    BitBoardLoader loader = BitBoardLoader("./bitboards.txt");

    Board board("8/8/8/4b3/8/8/8/8");
    std::cout << board.ToString(loader);
    uint8_t expectedMoves[13] = {0b00101101,0b00110110,0b00111111
                                ,0b00101011,0b00110010,0b00111001
                                ,0b00011011,0b00010010,0b00001001,0b00000000
                                ,0b00011101,0b00010110,0b00001111};

    std::array<uint8_t, 13> y = bishop::possibleMoves(board.GetAllPieces(),board.GetWhitePieces(),board.GetPosition("e5"));

    for (int i = 0; i < 13; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]);
    }
}

