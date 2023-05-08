#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../components/Board.h"
#include "../components/presenter.h"
#include "../components/pieces/bishop.h"
#include "../components/pieces/queen.h"
#include "../components/pieces/rook.h"
#include "../components/pieces/knight.h"
#include <filesystem>
#include <bitset>
#include <string>
namespace fs = std::filesystem;

TEST(PiecesTest, BishopTest1) {
    Board board("8/8/8/4b3/8/8/8/8");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    uint8_t expectedMoves[13] = {0b00101101,0b00110110,0b00111111
                                ,0b00101011,0b00110010,0b00111001
                                ,0b00011011,0b00010010,0b00001001,0b00000000
                                ,0b00011101,0b00010110,0b00001111};

    std::vector<uint8_t> moves = std::vector<uint8_t>();
    bishop::possibleMoves(moves, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, BishopTest2) {

    Board board("8/2r5/8/4b3/8/8/8/8");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    uint8_t expectedMoves[13] = {0b00101101,0b00110110,0b00111111
                                ,0b00101011,0b00110010,0b00111001
                                ,0b00011011,0b00010010,0b00001001,0b00000000
                                ,0b00011101,0b01000000};
    
    std::vector<uint8_t> moves = std::vector<uint8_t>();
    bishop::possibleMoves(moves, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 13 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i])<<"differs at index"<<i;
    }
}

TEST(PiecesTest, BishopTest3) {

    Board board("8/8/8/8/3Q4/8/1b6/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);
    uint8_t expectedMoves[13] = {0b00010010, 0b10011011, 0b00010000, 0b00000000, 0b00000010, 0b01000000};

    std::vector<uint8_t> moves = std::vector<uint8_t>();
    bishop::possibleMoves(moves, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("b2") >> 3, board.GetPosition("b2") & 0b111);

    for (int i = 0; i < 13 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "differs at index "<< i;
    }
}

TEST(PiecesTest, QueenTest1) {

    Board board("8/8/8/4Q3/8/8/8/8");

    uint8_t expectedMoves[27] = {board.GetPosition("f6"),board.GetPosition("g7"),board.GetPosition("h8"),
                                 board.GetPosition("f4"),board.GetPosition("g3"),board.GetPosition("h2"),
                                 board.GetPosition("d4"),board.GetPosition("c3"),board.GetPosition("b2"),board.GetPosition("a1"),
                                 board.GetPosition("d6"),board.GetPosition("c7"),board.GetPosition("b8"),
                                 board.GetPosition("f5"),board.GetPosition("g5"),board.GetPosition("h5"),
                                 board.GetPosition("d5"),board.GetPosition("c5"),board.GetPosition("b5"),board.GetPosition("a5"),
                                 board.GetPosition("e4"),board.GetPosition("e3"),board.GetPosition("e2"),board.GetPosition("e1"),
                                 board.GetPosition("e6"),board.GetPosition("e7"),board.GetPosition("e8")};
    uint8_t y[27];
    queen::possibleMoves(y, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 27; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest2) {

    uint8_t captured = 0b10000000;
    Board board("8/8/8/4Q3/8/8/4r3/8");

    uint8_t expectedMoves[27] = {board.GetPosition("f6"),board.GetPosition("g7"),board.GetPosition("h8"),
                                 board.GetPosition("f4"),board.GetPosition("g3"),board.GetPosition("h2"),
                                 board.GetPosition("d4"),board.GetPosition("c3"),board.GetPosition("b2"),board.GetPosition("a1"),
                                 board.GetPosition("d6"),board.GetPosition("c7"),board.GetPosition("b8"),
                                 board.GetPosition("f5"),board.GetPosition("g5"),board.GetPosition("h5"),
                                 board.GetPosition("d5"),board.GetPosition("c5"),board.GetPosition("b5"),board.GetPosition("a5"),
                                 board.GetPosition("e4"),board.GetPosition("e3"),static_cast<uint8_t>(captured|board.GetPosition("e2")),
                                 board.GetPosition("e6"),board.GetPosition("e7"),board.GetPosition("e8")};
    uint8_t y[27];
    queen::possibleMoves(y, board.GetAllPieces(),board.GetWhitePieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 27&& expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest3) {

    uint8_t captured = 0b10000000;
    Board board("8/8/8/4Q3/8/8/4R3/8");

    uint8_t expectedMoves[27] = {board.GetPosition("f6"),board.GetPosition("g7"),board.GetPosition("h8"),
                                board.GetPosition("f4"),board.GetPosition("g3"),board.GetPosition("h2"),
                                board.GetPosition("d4"),board.GetPosition("c3"),board.GetPosition("b2"),board.GetPosition("a1"),
                                board.GetPosition("d6"),board.GetPosition("c7"),board.GetPosition("b8"),
                                board.GetPosition("f5"),board.GetPosition("g5"),board.GetPosition("h5"),
                                board.GetPosition("d5"),board.GetPosition("c5"),board.GetPosition("b5"),board.GetPosition("a5"),
                                board.GetPosition("e4"),board.GetPosition("e3"),
                                board.GetPosition("e6"),board.GetPosition("e7"),board.GetPosition("e8"),0b01000000};;
    uint8_t y[27];
    queen::possibleMoves(y, board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3,
                         board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 27 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest1) {

    uint8_t captured = 0b10000000;
    Board board("r7/8/8/8/8/8/8/8");

    uint8_t expectedMoves[14] = {board.GetPosition("b8"),board.GetPosition("c8"),board.GetPosition("d8"),board.GetPosition("e8"),board.GetPosition("f8"),board.GetPosition("g8"),board.GetPosition("h8"),
                                 board.GetPosition("a7"),board.GetPosition("a6"),board.GetPosition("a5"),board.GetPosition("a4"),board.GetPosition("a3"),board.GetPosition("a2"),board.GetPosition("a1")};
    uint8_t y[14];
    rook::possibleMoves(y, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3,board.GetPosition("a8") & 0b111);

    for (int i = 0; i < 14 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest2) {

    uint8_t captured = 0b10000000;
    Board board("r7/8/8/8/8/8/8/R7");
    uint8_t expectedMoves[14] = {board.GetPosition("b8"),board.GetPosition("c8"),board.GetPosition("d8"),board.GetPosition("e8"),board.GetPosition("f8"),board.GetPosition("g8"),board.GetPosition("h8"),
                                 board.GetPosition("a7"),board.GetPosition("a6"),board.GetPosition("a5"),board.GetPosition("a4"),board.GetPosition("a3"),board.GetPosition("a2"),static_cast<uint8_t>(captured|board.GetPosition("a1"))};
    uint8_t y[14];
    rook::possibleMoves(y, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3,board.GetPosition("a8") & 0b111);

    for (int i = 0; i < 14 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest3) {

    Board board("r7/8/8/8/8/8/8/r7");
    uint8_t expectedMoves[14] = {board.GetPosition("b8"),board.GetPosition("c8"),board.GetPosition("d8"),board.GetPosition("e8"),board.GetPosition("f8"),board.GetPosition("g8"),board.GetPosition("h8"),
                                 board.GetPosition("a7"),board.GetPosition("a6"),board.GetPosition("a5"),board.GetPosition("a4"),board.GetPosition("a3"),board.GetPosition("a2"),0b01000000};
    uint8_t y[14];
    rook::possibleMoves(y, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3,board.GetPosition("a8") & 0b111);

    for (int i = 0; i < 14 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest1) {

    Board board("8/8/8/8/4n3/8/8/8");
    uint8_t expectedMoves[8] = {board.GetPosition("f7"),board.GetPosition("d7"),
                                board.GetPosition("g6"),board.GetPosition("g4"),
                                board.GetPosition("f3"),board.GetPosition("d3"),
                                board.GetPosition("c6"),board.GetPosition("c4")};
    uint8_t y[8];
    knight::possibleMoves(y, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e5") >> 3,board.GetPosition("e5") & 0b111);

    for (int i = 0; i < 8 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest2) {

    Board board("8/1n6/8/2N5/8/8/8/8");
    uint8_t expectedMoves[8] = {board.GetPosition("d8"),board.GetPosition("d6"),
                                static_cast<uint8_t>(0b10000000|board.GetPosition("c5")),board.GetPosition("a5"),0b01000000};
    uint8_t y[8];
    knight::possibleMoves(y, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("b7") >> 3,board.GetPosition("b7") & 0b111);

    for (int i = 0; i < 8 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest3) {
    Board board("8/8/8/8/8/4q3/6n1/8");
    uint8_t expectedMoves[8] = {board.GetPosition("h4"),board.GetPosition("f4"),
                                board.GetPosition("e1"),0b01000000};
    uint8_t y[8];
    knight::possibleMoves(y, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("g2") >> 3,board.GetPosition("g2") & 0b111);

    for (int i = 0; i < 8 && expectedMoves[i] != 0b01000000; ++i) {
        EXPECT_EQ(expectedMoves[i], y[i]) << "i = " << i << std::endl;
    }
}