#include "gtest/gtest.h"
#include "../components/Board.h"
#include "../components/presenter.h"
#include <filesystem>
namespace fs = std::filesystem;

// Tests made bny RamRam
TEST(BoardTest, FromFENTestInitalBoard) {
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

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
}

TEST(BoardTest, FromFENTestRandomBoard1) {
    Board board("2rq3k/pB1P2pp/8/5b2/4p3/1PQ5/P4PPP/6K1 w - - 0 1");
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

TEST(BoardTest, PlayGame)
{
    Board board = Board();
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);
    //board.PlayGame();
}

TEST(BoardTest, DoMoveBenchmarkStart)
{
    Board board("rnbqk1nr/pp1p1ppp/2p5/2b1p1B1/8/3P1N2/PPP1PPPP/RN1QKB1R w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    for (int i = 0; i < 1; i++) {
        board.GetMove();
    }
}

TEST(BoardTest, StartRanking)
{
    Board board("rnbqk1nr/pp1p1ppp/2p5/2b1p1B1/8/3P1N2/PPP1PPPP/RN1QKB1R w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    std::cout << board.BoardRanking(WHITE) << std::endl;
}

TEST(BoardTest, DoMoveBenchmarkMiddle)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    for (int i = 0; i < 1; i++)
    {
        board.GetMove();
    }
    std::cout << board.GetMove();
}

TEST(BoardTest, DoMoveBenchmarkEnd)
{
    Board board("r3k3/5p1p/n7/6B1/8/8/P7/K1R5 w q - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    for (int i = 0; i < 1; i++)
    {
        board.GetMove();
    }
}

TEST(BoardTest, GetMoveAlphaBetaBenchmark)
{
Board board("r3k3/5p1p/n7/6B1/8/8/P7/K1R5 w q - 0 1");
Presenter presenter = Presenter();
std::cout << std::endl
<< presenter.ToString(board);
for (int i = 0; i < 1; i++)
{
board.GetMove();
}
}


