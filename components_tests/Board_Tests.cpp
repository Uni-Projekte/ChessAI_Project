#include "gtest/gtest.h"
#include "../components/Board.h"
#include "../components/presenter.h"
#include <filesystem>
namespace fs = std::filesystem;

// Tests made bny RamRam
TEST(BoardTest, FromFENTestInitalBoard) {
    std::filesystem::path path = "./bitboards.txt";
    std::cout << "Current path is " << std::filesystem::current_path() << '\n';
    std::cout << "Absolute path for " << path << " is " << fs::absolute(path) << '\n';
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    EXPECT_EQ(board.GetBlackPawns(), 0xff000000000000);
    EXPECT_EQ(board.GetBlackQueen(), 0x1000000000000000);
    EXPECT_EQ(board.GetBlackKing(), 0x800000000000000);
    EXPECT_EQ(board.GetBlackBishops(), 0x2400000000000000);
    EXPECT_EQ(board.GetBlackKnights(), 0x4200000000000000);
    EXPECT_EQ(board.GetBlackRooks(), 0x8100000000000000);
    EXPECT_EQ(board.GetWhitePawns(), 0xff00);
    EXPECT_EQ(board.GetWhiteQueen(), 0x10);
    EXPECT_EQ(board.GetWhiteKing(), 0x8);
    EXPECT_EQ(board.GetWhiteBishops(), 0x24);
    EXPECT_EQ(board.GetWhiteKnights(), 0x42);
    EXPECT_EQ(board.GetWhiteRooks(), 0x81);
    board.DoMove(CREATE_MOVE(3, 1, 3, 2, 0)); // E2 - E3
    board.DoMove(CREATE_MOVE(4, 0, 1, 3, 0)); // D1 - G4
    board.DoMove(CREATE_MOVE(6,1,6,3,0)); //B2 - B4
    board.DoMove(CREATE_MOVE(6, 0, 7, 2, 0)); // B1 - A3
    board.DoMove(CREATE_MOVE(5, 0, 6, 1, 0)); // C1 - B2
    board.DoMove(CREATE_MOVE(3, 0, 5, 0, CASTLING)); // C1 - B2
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);
    presenter.HTMLFromBoard(board, "out.html");
}

TEST(BoardTest, FromFENTestRandomBoard1) {
    Board board("2rq3k/pB1P2pp/8/5b2/4p3/1PQ5/P4PPP/6K1");
    EXPECT_EQ(board.GetBlackPawns(), 0x83000008000000);
    EXPECT_EQ(board.GetBlackQueen(), 0x1000000000000000);
    EXPECT_EQ(board.GetBlackKing(), 0x100000000000000);
    EXPECT_EQ(board.GetBlackBishops(), 0x400000000);
    EXPECT_EQ(board.GetBlackKnights(), 0x0);
    EXPECT_EQ(board.GetBlackRooks(), 0x2000000000000000);
    EXPECT_EQ(board.GetWhitePawns(), 0x10000000408700);
    EXPECT_EQ(board.GetWhiteQueen(), 0x200000);
    EXPECT_EQ(board.GetWhiteKing(), 0x2);
    EXPECT_EQ(board.GetWhiteBishops(), 0x40000000000000);
    EXPECT_EQ(board.GetWhiteRooks(), 0x0);
}

TEST(BoardTest, FromFENTestRandomBoard2) {
    Board board("6k1/p5pp/8/8/8/3r1q2/6PK/8 w - - 0 1");
    EXPECT_EQ(board.GetBlackPawns(), 0x83000000000000);
    EXPECT_EQ(board.GetBlackQueen(), 0x40000);
    EXPECT_EQ(board.GetBlackKing(), 0x200000000000000);
    EXPECT_EQ(board.GetBlackBishops(), 0x0);
    EXPECT_EQ(board.GetBlackKnights(), 0x0);
    EXPECT_EQ(board.GetBlackRooks(), 0x100000);
    EXPECT_EQ(board.GetWhitePawns(), 0x200);
    EXPECT_EQ(board.GetWhiteQueen(), 0x0);
    EXPECT_EQ(board.GetWhiteKing(), 0x100);
    EXPECT_EQ(board.GetWhiteBishops(), 0x0);
    EXPECT_EQ(board.GetWhiteKnights(), 0x0);
}
