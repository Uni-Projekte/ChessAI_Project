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
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[27] = {
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
        CREATE_MOVE(4, 4, 5, 4, 0),
        CREATE_MOVE(4, 4, 6, 4, 0),
        CREATE_MOVE(4, 4, 7, 4, 0),
        CREATE_MOVE(4, 4, 3, 4, 0),
        CREATE_MOVE(4, 4, 2, 4, 0),
        CREATE_MOVE(4, 4, 1, 4, 0),
        CREATE_MOVE(4, 4, 0, 4, 0),
        CREATE_MOVE(4, 4, 4, 3, 0),
        CREATE_MOVE(4, 4, 4, 2, 0),
        CREATE_MOVE(4, 4, 4, 1, 0),
        CREATE_MOVE(4, 4, 4, 0, 0),
        CREATE_MOVE(4, 4, 4, 5, 0),
        CREATE_MOVE(4, 4, 4, 6, 0),
        CREATE_MOVE(4, 4, 4, 7, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    queen::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest2) {
    Board board("8/8/8/4Q3/8/8/4r3/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[27] = {
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
        CREATE_MOVE(4, 4, 5, 4, 0),
        CREATE_MOVE(4, 4, 6, 4, 0),
        CREATE_MOVE(4, 4, 7, 4, 0),
        CREATE_MOVE(4, 4, 3, 4, 0),
        CREATE_MOVE(4, 4, 2, 4, 0),
        CREATE_MOVE(4, 4, 1, 4, 0),
        CREATE_MOVE(4, 4, 0, 4, 0),
        CREATE_MOVE(4, 4, 4, 3, 0),
        CREATE_MOVE(4, 4, 4, 2, 0),
        CREATE_MOVE(4, 4, 4, 1, CAPTURE),
        CREATE_MOVE(4, 4, 4, 5, 0),
        CREATE_MOVE(4, 4, 4, 6, 0),
        CREATE_MOVE(4, 4, 4, 7, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    queen::possibleMoves(moves, board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest3) {
    Board board("8/8/8/4Q3/8/8/4R3/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[27] = {
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
        CREATE_MOVE(4, 4, 5, 4, 0),
        CREATE_MOVE(4, 4, 6, 4, 0),
        CREATE_MOVE(4, 4, 7, 4, 0),
        CREATE_MOVE(4, 4, 3, 4, 0),
        CREATE_MOVE(4, 4, 2, 4, 0),
        CREATE_MOVE(4, 4, 1, 4, 0),
        CREATE_MOVE(4, 4, 0, 4, 0),
        CREATE_MOVE(4, 4, 4, 3, 0),
        CREATE_MOVE(4, 4, 4, 2, 0),
        CREATE_MOVE(4, 4, 4, 5, 0),
        CREATE_MOVE(4, 4, 4, 6, 0),
        CREATE_MOVE(4, 4, 4, 7, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    queen::possibleMoves(moves, board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest1) {
    Board board("r7/8/8/8/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[14] = {
        CREATE_MOVE(0, 7, 1, 7, 0),
        CREATE_MOVE(0, 7, 2, 7, 0),
        CREATE_MOVE(0, 7, 3, 7, 0),
        CREATE_MOVE(0, 7, 4, 7, 0),
        CREATE_MOVE(0, 7, 5, 7, 0),
        CREATE_MOVE(0, 7, 6, 7, 0),
        CREATE_MOVE(0, 7, 7, 7, 0),
        CREATE_MOVE(0, 7, 0, 6, 0),
        CREATE_MOVE(0, 7, 0, 5, 0),
        CREATE_MOVE(0, 7, 0, 4, 0),
        CREATE_MOVE(0, 7, 0, 3, 0),
        CREATE_MOVE(0, 7, 0, 2, 0),
        CREATE_MOVE(0, 7, 0, 1, 0),
        CREATE_MOVE(0, 7, 0, 0, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    rook::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest2) {
    Board board("r7/8/8/8/8/8/8/R7 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[14] = {
        CREATE_MOVE(0, 7, 1, 7, 0),
        CREATE_MOVE(0, 7, 2, 7, 0),
        CREATE_MOVE(0, 7, 3, 7, 0),
        CREATE_MOVE(0, 7, 4, 7, 0),
        CREATE_MOVE(0, 7, 5, 7, 0),
        CREATE_MOVE(0, 7, 6, 7, 0),
        CREATE_MOVE(0, 7, 7, 7, 0),
        CREATE_MOVE(0, 7, 0, 6, 0),
        CREATE_MOVE(0, 7, 0, 5, 0),
        CREATE_MOVE(0, 7, 0, 4, 0),
        CREATE_MOVE(0, 7, 0, 3, 0),
        CREATE_MOVE(0, 7, 0, 2, 0),
        CREATE_MOVE(0, 7, 0, 1, 0),
        CREATE_MOVE(0, 7, 0, 0, CAPTURE),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    rook::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest3) {
    Board board("r7/8/8/8/8/8/8/r7 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[14] = {
        CREATE_MOVE(0, 7, 1, 7, 0),
        CREATE_MOVE(0, 7, 2, 7, 0),
        CREATE_MOVE(0, 7, 3, 7, 0),
        CREATE_MOVE(0, 7, 4, 7, 0),
        CREATE_MOVE(0, 7, 5, 7, 0),
        CREATE_MOVE(0, 7, 6, 7, 0),
        CREATE_MOVE(0, 7, 7, 7, 0),
        CREATE_MOVE(0, 7, 0, 6, 0),
        CREATE_MOVE(0, 7, 0, 5, 0),
        CREATE_MOVE(0, 7, 0, 4, 0),
        CREATE_MOVE(0, 7, 0, 3, 0),
        CREATE_MOVE(0, 7, 0, 2, 0),
        CREATE_MOVE(0, 7, 0, 1, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    rook::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest1) {
    Board board("8/8/8/8/4n3/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[8] = {
        CREATE_MOVE(4, 3, 5, 5, 0),
        CREATE_MOVE(4, 3, 5, 1, 0),
        CREATE_MOVE(4, 3, 3, 5, 0),
        CREATE_MOVE(4, 3, 3, 1, 0),
        CREATE_MOVE(4, 3, 6, 4, 0),
        CREATE_MOVE(4, 3, 2, 4, 0),
        CREATE_MOVE(4, 3, 6, 2, 0),
        CREATE_MOVE(4, 3, 2, 2, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    knight::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e4") >> 3, board.GetPosition("e4") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest2) {
    Board board("8/1n6/8/2N5/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[8] = {
        CREATE_MOVE(1, 6, 2, 4, CAPTURE),
        CREATE_MOVE(1, 6, 0, 4, 0),
        CREATE_MOVE(1, 6, 3, 7, 0),
        CREATE_MOVE(1, 6, 3, 5, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    knight::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("b7") >> 3, board.GetPosition("b7") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        PRINT_MOVE(moves[i]);
        PRINT_MOVE(expectedMoves[i]);
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest3) {
    Board board("8/8/8/8/8/4q3/6n1/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[8] = {
        CREATE_MOVE(6, 1, 7, 3, 0),
        CREATE_MOVE(6, 1, 5, 3, 0),
        CREATE_MOVE(6, 1, 4, 0, 0),
    };

    std::vector<MOVE> moves = std::vector<MOVE>();
    knight::possibleMoves(moves, board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("g2") >> 3,board.GetPosition("g2") & 0b111);

    for (int i = 0; i < moves.size(); ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}