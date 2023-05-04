#include "gtest/gtest.h"
#include "../components/Board.h"
#include <filesystem>
namespace fs = std::filesystem;

// Tests made bny RamRam
TEST(BoardTest, FromFENTestInitalBoard) {
    std::filesystem::path path = "./bitboards.txt";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    std::cout << "Absolute path for " << path << " is " << fs::absolute(path) << '\n';
    BitBoardLoader loader = BitBoardLoader("./bitboards.txt");
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    std::cout << board.ToString(loader);
    EXPECT_EQ(board.GetBlackPawns(), 0xff000000000000);
    EXPECT_EQ(board.GetBlackQueen(), 0x1000000000000000);
    EXPECT_EQ(board.GetBlackKing(), 0x800000000000000);
    EXPECT_EQ(board.GetBlackBishops(), 0x2400000000000000);
    EXPECT_EQ(board.GetBlackKnights(), 0x4200000000000000);
    EXPECT_EQ(board.GetBlackTowers(), 0x8100000000000000);
    EXPECT_EQ(board.GetWhitePawns(), 0xff00);
    EXPECT_EQ(board.GetWhiteQueen(), 0x10);
    EXPECT_EQ(board.GetWhiteKing(), 0x8);
    EXPECT_EQ(board.GetWhiteBishops(), 0x24);
    EXPECT_EQ(board.GetWhiteKnights(), 0x42);
    EXPECT_EQ(board.GetWhiteTowers(), 0x81);
    board.DoMove(3, 1, 3, 2, 0b00000000); // E2 - E3
    board.DoMove(4, 0, 1, 3, 0b00000000); // D1 - G4
    board.DoMove(6,1,6,3,0b00000000); //B2 - B4
    board.DoMove(6, 0, 7, 2, 0b00000000); // B1 - A3
    board.DoMove(5, 0, 6, 1, 0b00000000); // C1 - B2
    board.DoMove(3, 0, 5, 0, 0b01000000); // C1 - B2
    board.ToHTML(loader, "out.html");
    std::cout << std::endl << board.ToString(loader);
}

TEST(BoardTest, FromFENTestRandomBoard1) {
    //BitBoardLoader loader = BitBoardLoader("bitboards.txt");
    Board board("2rq3k/pB1P2pp/8/5b2/4p3/1PQ5/P4PPP/6K1");
    //std::cout << board.ToString(loader);
    EXPECT_EQ(board.GetBlackPawns(), 0x83000008000000);
    EXPECT_EQ(board.GetBlackQueen(), 0x1000000000000000);
    EXPECT_EQ(board.GetBlackKing(), 0x100000000000000);
    EXPECT_EQ(board.GetBlackBishops(), 0x400000000);
    EXPECT_EQ(board.GetBlackKnights(), 0x0);
    EXPECT_EQ(board.GetBlackTowers(), 0x2000000000000000);
    EXPECT_EQ(board.GetWhitePawns(), 0x10000000408700);
    EXPECT_EQ(board.GetWhiteQueen(), 0x200000);
    EXPECT_EQ(board.GetWhiteKing(), 0x2);
    EXPECT_EQ(board.GetWhiteBishops(), 0x40000000000000);
    EXPECT_EQ(board.GetWhiteKnights(), 0x0);
}

TEST(BoardTest, FromFENTestRandomBoard2) {
    //BitBoardLoader loader = BitBoardLoader("bitboards.txt");
    Board board("6k1/p5pp/8/8/8/3r1q2/6PK/8 w - - 0 1");
    //std::cout << board.ToString(loader);
    EXPECT_EQ(board.GetBlackPawns(), 0x83000000000000);
    EXPECT_EQ(board.GetBlackQueen(), 0x40000);
    EXPECT_EQ(board.GetBlackKing(), 0x200000000000000);
    EXPECT_EQ(board.GetBlackBishops(), 0x0);
    EXPECT_EQ(board.GetBlackKnights(), 0x0);
    EXPECT_EQ(board.GetBlackTowers(), 0x100000);
    EXPECT_EQ(board.GetWhitePawns(), 0x200);
    EXPECT_EQ(board.GetWhiteQueen(), 0x0);
    EXPECT_EQ(board.GetWhiteKing(), 0x100);
    EXPECT_EQ(board.GetWhiteBishops(), 0x0);
    EXPECT_EQ(board.GetWhiteKnights(), 0x0);
}
