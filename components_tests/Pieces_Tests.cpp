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
    Board board("8/8/8/4b3/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);

    MOVE expectedMoves[13] = {
        CREATE_MOVE(4, 4, 5, 5, 0),
        CREATE_MOVE(4, 4, 6, 6, 0),
        CREATE_MOVE(4, 4, 7, 7, 0),
        CREATE_MOVE(4, 4, 5, 3, 0),
        CREATE_MOVE(4, 4, 6, 2, 0),
        CREATE_MOVE(4, 4, 7, 1, 0),
        CREATE_MOVE(4, 4, 3, 3, 0),
        CREATE_MOVE(4, 4, 2, 2, 0),
        CREATE_MOVE(4, 4, 1, 1, 0),
        CREATE_MOVE(4, 4, 0, 0, 0),
        CREATE_MOVE(4, 4, 3, 5, 0),
        CREATE_MOVE(4, 4, 2, 6, 0),
        CREATE_MOVE(4, 4, 1, 7, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    bishop::possibleMoves(moves, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, BishopTest2) {
    Board board("8/2r5/8/4b3/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[13] = {
        CREATE_MOVE(4, 4, 5, 5, 0),
        CREATE_MOVE(4, 4, 6, 6, 0),
        CREATE_MOVE(4, 4, 7, 7, 0),
        CREATE_MOVE(4, 4, 5, 3, 0),
        CREATE_MOVE(4, 4, 6, 2, 0),
        CREATE_MOVE(4, 4, 7, 1, 0),
        CREATE_MOVE(4, 4, 3, 3, 0),
        CREATE_MOVE(4, 4, 2, 2, 0),
        CREATE_MOVE(4, 4, 1, 1, 0),
        CREATE_MOVE(4, 4, 0, 0, 0),
        CREATE_MOVE(4, 4, 3, 5, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    bishop::possibleMoves(moves, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i])<<"differs at index"<<i;
    }
}

TEST(PiecesTest, BishopTest3) {
    Board board("8/8/8/8/3Q4/8/1b6/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[13] = {
        CREATE_MOVE(1, 1, 2, 2, 0),
        CREATE_MOVE(1, 1, 3, 3, CAPTURE),
        CREATE_MOVE(1, 1, 2, 0, 0),
        CREATE_MOVE(1, 1, 0, 0, 0),
        CREATE_MOVE(1, 1, 0, 2, 0),
    };
    std::vector<MOVE> moves = std::vector<MOVE>();
    bishop::possibleMoves(moves, board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("b2") >> 3, board.GetPosition("b2") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "differs at index "<< i;
    }
}

TEST(PiecesTest, QueenTest1) {
    Board board("8/8/8/4Q3/8/8/8/8 w - - 0 1");

    MOVE expectedMoves[27] = {board.GetPosition("f6"),board.GetPosition("g7"),board.GetPosition("h8"),
                                 board.GetPosition("f4"),board.GetPosition("g3"),board.GetPosition("h2"),
                                 board.GetPosition("d4"),board.GetPosition("c3"),board.GetPosition("b2"),board.GetPosition("a1"),
                                 board.GetPosition("d6"),board.GetPosition("c7"),board.GetPosition("b8"),
                                 board.GetPosition("f5"),board.GetPosition("g5"),board.GetPosition("h5"),
                                 board.GetPosition("d5"),board.GetPosition("c5"),board.GetPosition("b5"),board.GetPosition("a5"),
                                 board.GetPosition("e4"),board.GetPosition("e3"),board.GetPosition("e2"),board.GetPosition("e1"),
                                 board.GetPosition("e6"),board.GetPosition("e7"),board.GetPosition("e8")};
    std::vector<MOVE> moves = std::vector<MOVE>();
    queen::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        PRINT_MOVE(moves[i]);
        PRINT_MOVE(expectedMoves[i]);
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest2) {
    uint8_t captured = 0b10000000;
    Board board("8/8/8/4Q3/8/8/4r3/8 w - - 0 1");

    MOVE expectedMoves[27] = {board.GetPosition("f6"),board.GetPosition("g7"),board.GetPosition("h8"),
                                 board.GetPosition("f4"),board.GetPosition("g3"),board.GetPosition("h2"),
                                 board.GetPosition("d4"),board.GetPosition("c3"),board.GetPosition("b2"),board.GetPosition("a1"),
                                 board.GetPosition("d6"),board.GetPosition("c7"),board.GetPosition("b8"),
                                 board.GetPosition("f5"),board.GetPosition("g5"),board.GetPosition("h5"),
                                 board.GetPosition("d5"),board.GetPosition("c5"),board.GetPosition("b5"),board.GetPosition("a5"),
                                 board.GetPosition("e4"),board.GetPosition("e3"),static_cast<uint8_t>(captured|board.GetPosition("e2")),
                                 board.GetPosition("e6"),board.GetPosition("e7"),board.GetPosition("e8")};
    std::vector<MOVE> moves = std::vector<MOVE>();
    queen::possibleMoves(moves, board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest3) {
    uint8_t captured = 0b10000000;
    Board board("8/8/8/4Q3/8/8/4R3/8 w - - 0 1");

    MOVE expectedMoves[27] = {board.GetPosition("f6"),board.GetPosition("g7"),board.GetPosition("h8"),
                                board.GetPosition("f4"),board.GetPosition("g3"),board.GetPosition("h2"),
                                board.GetPosition("d4"),board.GetPosition("c3"),board.GetPosition("b2"),board.GetPosition("a1"),
                                board.GetPosition("d6"),board.GetPosition("c7"),board.GetPosition("b8"),
                                board.GetPosition("f5"),board.GetPosition("g5"),board.GetPosition("h5"),
                                board.GetPosition("d5"),board.GetPosition("c5"),board.GetPosition("b5"),board.GetPosition("a5"),
                                board.GetPosition("e4"),board.GetPosition("e3"),
                                board.GetPosition("e6"),board.GetPosition("e7"),board.GetPosition("e8"),0b01000000};;
    std::vector<MOVE> moves = std::vector<MOVE>();
    queen::possibleMoves(moves, board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3,
                         board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest1) {

    uint8_t captured = 0b10000000;
    Board board("r7/8/8/8/8/8/8/8 w - - 0 1");

    MOVE expectedMoves[14] = {board.GetPosition("b8"),board.GetPosition("c8"),board.GetPosition("d8"),board.GetPosition("e8"),board.GetPosition("f8"),board.GetPosition("g8"),board.GetPosition("h8"),
                                 board.GetPosition("a7"),board.GetPosition("a6"),board.GetPosition("a5"),board.GetPosition("a4"),board.GetPosition("a3"),board.GetPosition("a2"),board.GetPosition("a1")};
    std::vector<MOVE> moves = std::vector<MOVE>();
    rook::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest2) {

    uint8_t captured = 0b10000000;
    Board board("r7/8/8/8/8/8/8/R7 w - - 0 1");
    MOVE expectedMoves[14] = {board.GetPosition("b8"),board.GetPosition("c8"),board.GetPosition("d8"),board.GetPosition("e8"),board.GetPosition("f8"),board.GetPosition("g8"),board.GetPosition("h8"),
                                 board.GetPosition("a7"),board.GetPosition("a6"),board.GetPosition("a5"),board.GetPosition("a4"),board.GetPosition("a3"),board.GetPosition("a2"),static_cast<uint8_t>(captured|board.GetPosition("a1"))};
    std::vector<MOVE> moves = std::vector<MOVE>();
    rook::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest3) {

    Board board("r7/8/8/8/8/8/8/r7 w - - 0 1");
    MOVE expectedMoves[14] = {board.GetPosition("b8"),board.GetPosition("c8"),board.GetPosition("d8"),board.GetPosition("e8"),board.GetPosition("f8"),board.GetPosition("g8"),board.GetPosition("h8"),
                                 board.GetPosition("a7"),board.GetPosition("a6"),board.GetPosition("a5"),board.GetPosition("a4"),board.GetPosition("a3"),board.GetPosition("a2"),0b01000000};
    std::vector<MOVE> moves = std::vector<MOVE>();
    rook::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest1) {

    Board board("8/8/8/8/4n3/8/8/8 w - - 0 1");
    MOVE expectedMoves[8] = {board.GetPosition("f7"),board.GetPosition("d7"),
                                board.GetPosition("g6"),board.GetPosition("g4"),
                                board.GetPosition("f3"),board.GetPosition("d3"),
                                board.GetPosition("c6"),board.GetPosition("c4")};
    std::vector<MOVE> moves = std::vector<MOVE>();
    knight::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest2) {

    Board board("8/1n6/8/2N5/8/8/8/8 w - - 0 1");
    MOVE expectedMoves[8] = {board.GetPosition("d8"),board.GetPosition("d6"),
                                static_cast<uint8_t>(0b10000000|board.GetPosition("c5")),board.GetPosition("a5"),0b01000000};
    std::vector<MOVE> moves = std::vector<MOVE>();
    knight::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("b7") >> 3, board.GetPosition("b7") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest3) {
    Board board("8/8/8/8/8/4q3/6n1/8 w - - 0 1");
    MOVE expectedMoves[8] = {board.GetPosition("h4"),board.GetPosition("f4"),
                                board.GetPosition("e1"),0b01000000};
    std::vector<MOVE> moves = std::vector<MOVE>();
    knight::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("g2") >> 3,board.GetPosition("g2") & 0b111);

    for (int i = 0; i < moves.size() && expectedMoves[i] != 0b01000000; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}