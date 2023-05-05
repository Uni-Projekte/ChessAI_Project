#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../components/Board.h"
#include "../components/presenter.h"
#include "../components/pieces/bishop.h"
#include <filesystem>
#include <bitset>
#include <string>
namespace fs = std::filesystem;

TEST(PiecesTest, PieceTest1) {
    Board board("8/8/8/4b3/8/8/8/8");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    uint8_t expectedMoves[13] = {0b00101101,0b00110110,0b00111111
                                ,0b00101011,0b00110010,0b00111001
                                ,0b00011011,0b00010010,0b00001001,0b00000000
                                ,0b00011101,0b00010110,0b00001111};

    uint8_t y[13];
    bishop::possibleMoves(y, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 13; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, PieceTest2) {

    Board board("8/2r5/8/4b3/8/8/8/8");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);

    uint8_t expectedMoves[13] = {0b00101101,0b00110110,0b00111111
                                ,0b00101011,0b00110010,0b00111001
                                ,0b00011011,0b00010010,0b00001001,0b00000000
                                ,0b00011101,0b01000000};
    uint8_t y[13];
    bishop::possibleMoves(y, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 13 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i])<<"differs at index"<<i;
    }
}

TEST(PiecesTest, PieceTest3) {
    std::filesystem::path path = "./bitboards.txt";

    Board board("8/8/8/8/3Q4/8/1b6/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    uint8_t expectedMoves[13] = {0b00010010, 0b10011011, 0b00010000, 0b00000000, 0b00000010, 0b01000000};

    uint8_t y[13];
    bishop::possibleMoves(y, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("b2") >> 3, board.GetPosition("b2") & 0b111);

    for (int i = 0; i < 13 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "differs at index "<< i;
    }
}
