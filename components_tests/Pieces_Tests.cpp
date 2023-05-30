#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../components/Board.h"
#include "../components/presenter.h"
#include "../components/pieces/bishop.h"
#include "../components/pieces/queen.h"
#include "../components/pieces/rook.h"
#include "../components/pieces/knight.h"
#include "../components/pieces/king.h"
#include <filesystem>
#include <bitset>
#include <string>
namespace fs = std::filesystem;

TEST(PiecesTest, BishopTest1) {
    Board board("8/8/8/4b3/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);

    MOVE expectedMoves[14] = {
        14,
        CreateMove(4, 4, 5, 5, 0),
        CreateMove(4, 4, 6, 6, 0),
        CreateMove(4, 4, 7, 7, 0),
        CreateMove(4, 4, 5, 3, 0),
        CreateMove(4, 4, 6, 2, 0),
        CreateMove(4, 4, 7, 1, 0),
        CreateMove(4, 4, 3, 3, 0),
        CreateMove(4, 4, 2, 2, 0),
        CreateMove(4, 4, 1, 1, 0),
        CreateMove(4, 4, 0, 0, 0),
        CreateMove(4, 4, 3, 5, 0),
        CreateMove(4, 4, 2, 6, 0),
        CreateMove(4, 4, 1, 7, 0),
    };

    NEW_MOVE_ARRAY(moves);
    bishop::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(),board.GetBlackPieces(),board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves[0]; ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, BishopTest2) {
    Board board("8/2r5/8/4b3/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[12] = {
        12,
        CreateMove(4, 4, 5, 5, 0),
        CreateMove(4, 4, 6, 6, 0),
        CreateMove(4, 4, 7, 7, 0),
        CreateMove(4, 4, 5, 3, 0),
        CreateMove(4, 4, 6, 2, 0),
        CreateMove(4, 4, 7, 1, 0),
        CreateMove(4, 4, 3, 3, 0),
        CreateMove(4, 4, 2, 2, 0),
        CreateMove(4, 4, 1, 1, 0),
        CreateMove(4, 4, 0, 0, 0),
        CreateMove(4, 4, 3, 5, 0),
    };

    NEW_MOVE_ARRAY(moves);
    bishop::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves[0]; ++i) {
        EXPECT_EQ(expectedMoves[i], moves[i])<<"differs at index"<<i;
    }
}

TEST(PiecesTest, BishopTest3) {
    Board board("8/8/8/8/3Q4/8/1b6/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[6] = {
        6,
        CreateMove(1, 1, 2, 2, 0),
        CreateMove(1, 1, 3, 3, CAPTURE),
        CreateMove(1, 1, 2, 0, 0),
        CreateMove(1, 1, 0, 0, 0),
        CreateMove(1, 1, 0, 2, 0),
    };
    NEW_MOVE_ARRAY(moves);
    bishop::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("b2") >> 3, board.GetPosition("b2") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "differs at index "<< i;
    }
}

TEST(PiecesTest, QueenTest1) {
    Board board("8/8/8/4Q3/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[28] = {
        28,
        CreateMove(4, 4, 5, 5, 0),
        CreateMove(4, 4, 6, 6, 0),
        CreateMove(4, 4, 7, 7, 0),
        CreateMove(4, 4, 5, 3, 0),
        CreateMove(4, 4, 6, 2, 0),
        CreateMove(4, 4, 7, 1, 0),
        CreateMove(4, 4, 3, 3, 0),
        CreateMove(4, 4, 2, 2, 0),
        CreateMove(4, 4, 1, 1, 0),
        CreateMove(4, 4, 0, 0, 0),
        CreateMove(4, 4, 3, 5, 0),
        CreateMove(4, 4, 2, 6, 0),
        CreateMove(4, 4, 1, 7, 0),
        CreateMove(4, 4, 5, 4, 0),
        CreateMove(4, 4, 6, 4, 0),
        CreateMove(4, 4, 7, 4, 0),
        CreateMove(4, 4, 3, 4, 0),
        CreateMove(4, 4, 2, 4, 0),
        CreateMove(4, 4, 1, 4, 0),
        CreateMove(4, 4, 0, 4, 0),
        CreateMove(4, 4, 4, 3, 0),
        CreateMove(4, 4, 4, 2, 0),
        CreateMove(4, 4, 4, 1, 0),
        CreateMove(4, 4, 4, 0, 0),
        CreateMove(4, 4, 4, 5, 0),
        CreateMove(4, 4, 4, 6, 0),
        CreateMove(4, 4, 4, 7, 0),
    };

    NEW_MOVE_ARRAY(moves);
    queen::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest2) {
    Board board("8/8/8/4Q3/8/8/4r3/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[27] = {
        27,
        CreateMove(4, 4, 5, 5, 0),
        CreateMove(4, 4, 6, 6, 0),
        CreateMove(4, 4, 7, 7, 0),
        CreateMove(4, 4, 5, 3, 0),
        CreateMove(4, 4, 6, 2, 0),
        CreateMove(4, 4, 7, 1, 0),
        CreateMove(4, 4, 3, 3, 0),
        CreateMove(4, 4, 2, 2, 0),
        CreateMove(4, 4, 1, 1, 0),
        CreateMove(4, 4, 0, 0, 0),
        CreateMove(4, 4, 3, 5, 0),
        CreateMove(4, 4, 2, 6, 0),
        CreateMove(4, 4, 1, 7, 0),
        CreateMove(4, 4, 5, 4, 0),
        CreateMove(4, 4, 6, 4, 0),
        CreateMove(4, 4, 7, 4, 0),
        CreateMove(4, 4, 3, 4, 0),
        CreateMove(4, 4, 2, 4, 0),
        CreateMove(4, 4, 1, 4, 0),
        CreateMove(4, 4, 0, 4, 0),
        CreateMove(4, 4, 4, 3, 0),
        CreateMove(4, 4, 4, 2, 0),
        CreateMove(4, 4, 4, 1, CAPTURE),
        CreateMove(4, 4, 4, 5, 0),
        CreateMove(4, 4, 4, 6, 0),
        CreateMove(4, 4, 4, 7, 0),
    };

    NEW_MOVE_ARRAY(moves);
    queen::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, QueenTest3) {
    Board board("8/8/8/4Q3/8/8/4R3/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[26] = {
        26,
        CreateMove(4, 4, 5, 5, 0),
        CreateMove(4, 4, 6, 6, 0),
        CreateMove(4, 4, 7, 7, 0),
        CreateMove(4, 4, 5, 3, 0),
        CreateMove(4, 4, 6, 2, 0),
        CreateMove(4, 4, 7, 1, 0),
        CreateMove(4, 4, 3, 3, 0),
        CreateMove(4, 4, 2, 2, 0),
        CreateMove(4, 4, 1, 1, 0),
        CreateMove(4, 4, 0, 0, 0),
        CreateMove(4, 4, 3, 5, 0),
        CreateMove(4, 4, 2, 6, 0),
        CreateMove(4, 4, 1, 7, 0),
        CreateMove(4, 4, 5, 4, 0),
        CreateMove(4, 4, 6, 4, 0),
        CreateMove(4, 4, 7, 4, 0),
        CreateMove(4, 4, 3, 4, 0),
        CreateMove(4, 4, 2, 4, 0),
        CreateMove(4, 4, 1, 4, 0),
        CreateMove(4, 4, 0, 4, 0),
        CreateMove(4, 4, 4, 3, 0),
        CreateMove(4, 4, 4, 2, 0),
        CreateMove(4, 4, 4, 5, 0),
        CreateMove(4, 4, 4, 6, 0),
        CreateMove(4, 4, 4, 7, 0),
    };

    NEW_MOVE_ARRAY(moves);
    queen::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetWhitePieces(), board.GetPosition("e5") >> 3, board.GetPosition("e5") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest1) {
    Board board("r7/8/8/8/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[15] = {
        15,
        CreateMove(0, 7, 1, 7, 0),
        CreateMove(0, 7, 2, 7, 0),
        CreateMove(0, 7, 3, 7, 0),
        CreateMove(0, 7, 4, 7, 0),
        CreateMove(0, 7, 5, 7, 0),
        CreateMove(0, 7, 6, 7, 0),
        CreateMove(0, 7, 7, 7, 0),
        CreateMove(0, 7, 0, 6, 0),
        CreateMove(0, 7, 0, 5, 0),
        CreateMove(0, 7, 0, 4, 0),
        CreateMove(0, 7, 0, 3, 0),
        CreateMove(0, 7, 0, 2, 0),
        CreateMove(0, 7, 0, 1, 0),
        CreateMove(0, 7, 0, 0, 0),
    };

    NEW_MOVE_ARRAY(moves);
    rook::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest2) {
    Board board("r7/8/8/8/8/8/8/R7 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[15] = {
        15,
        CreateMove(0, 7, 1, 7, 0),
        CreateMove(0, 7, 2, 7, 0),
        CreateMove(0, 7, 3, 7, 0),
        CreateMove(0, 7, 4, 7, 0),
        CreateMove(0, 7, 5, 7, 0),
        CreateMove(0, 7, 6, 7, 0),
        CreateMove(0, 7, 7, 7, 0),
        CreateMove(0, 7, 0, 6, 0),
        CreateMove(0, 7, 0, 5, 0),
        CreateMove(0, 7, 0, 4, 0),
        CreateMove(0, 7, 0, 3, 0),
        CreateMove(0, 7, 0, 2, 0),
        CreateMove(0, 7, 0, 1, 0),
        CreateMove(0, 7, 0, 0, CAPTURE),
    };

    NEW_MOVE_ARRAY(moves);
    rook::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, RookTest3) {
    Board board("r7/8/8/8/8/8/8/r7 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[14] = {
        14,
        CreateMove(0, 7, 1, 7, 0),
        CreateMove(0, 7, 2, 7, 0),
        CreateMove(0, 7, 3, 7, 0),
        CreateMove(0, 7, 4, 7, 0),
        CreateMove(0, 7, 5, 7, 0),
        CreateMove(0, 7, 6, 7, 0),
        CreateMove(0, 7, 7, 7, 0),
        CreateMove(0, 7, 0, 6, 0),
        CreateMove(0, 7, 0, 5, 0),
        CreateMove(0, 7, 0, 4, 0),
        CreateMove(0, 7, 0, 3, 0),
        CreateMove(0, 7, 0, 2, 0),
        CreateMove(0, 7, 0, 1, 0),
    };

    NEW_MOVE_ARRAY(moves);
    rook::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetFromWhiteAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("a8") >> 3, board.GetPosition("a8") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest1) {
    Board board("8/8/8/8/4n3/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[9] = {
        9,
        CreateMove(4, 3, 5, 5, 0),
        CreateMove(4, 3, 5, 1, 0),
        CreateMove(4, 3, 3, 5, 0),
        CreateMove(4, 3, 3, 1, 0),
        CreateMove(4, 3, 6, 4, 0),
        CreateMove(4, 3, 2, 4, 0),
        CreateMove(4, 3, 6, 2, 0),
        CreateMove(4, 3, 2, 2, 0),
    };

    NEW_MOVE_ARRAY(moves);
    knight::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e4") >> 3, board.GetPosition("e4") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest2) {
    Board board("8/1n6/8/2N5/8/8/8/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[5] = {
        5,
        CreateMove(1, 6, 2, 4, CAPTURE),
        CreateMove(1, 6, 0, 4, 0),
        CreateMove(1, 6, 3, 7, 0),
        CreateMove(1, 6, 3, 5, 0),
    };

    NEW_MOVE_ARRAY(moves);
    knight::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("b7") >> 3, board.GetPosition("b7") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, KnightTest3) {
    Board board("8/8/8/8/8/4q3/6n1/8 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[4] = {
        4,
        CreateMove(6, 1, 7, 3, 0),
        CreateMove(6, 1, 5, 3, 0),
        CreateMove(6, 1, 4, 0, 0),
    };

    NEW_MOVE_ARRAY(moves);
    knight::possibleMoves(moves, board.GetFromBlackAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("g2") >> 3,board.GetPosition("g2") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }
}

TEST(PiecesTest, PawnEatsPawnTest)
{
    Board board("3k4/8/8/3p4/4P3/8/8/4K3 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    board.DoMove(CreateMove(4, 3, 3, 4, CAPTURE));
    std::cout << std::endl << presenter.ToString(board);
    EXPECT_EQ("3k4/8/8/3P4/8/8/8/4K3 b - - 0 1", board.toFEN());
}

TEST(PiecesTest, EnPassantTest)
{
    Board board("2k5/8/8/8/6p1/8/5P2/3K4 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    board.DoMove(CreateMove(5, 1, 5, 3, 0));
    EXPECT_EQ("2k5/8/8/8/5Pp1/8/8/3K4 b - f3 0 1", board.toFEN());
    board.DoMove(CreateMove(6, 3, 5, 2, CAPTURE));
    std::cout << std::endl << presenter.ToString(board);
    EXPECT_EQ("2k5/8/8/8/8/5p2/8/3K4 w - - 0 2", board.toFEN());
}

TEST(PiecesTest, EnPassantTest2)
{
    Board board("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");

    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    board.DoMove(CreateMove(5, 6, 5, 4, 0));
    EXPECT_EQ("rnbqkbnr/1pppp1pp/p7/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3", board.toFEN());

    board.DoMove(CreateMove(4, 4, 5, 5, CAPTURE));
    std::cout << std::endl << presenter.ToString(board);
    EXPECT_EQ("rnbqkbnr/1pppp1pp/p4P2/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 3", board.toFEN());
}

TEST(PiecesTest, KingMoveInCheckedField1)
{
    Board board("4r3/8/8/8/8/3K4/8/8 w - - 0 1");

    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[6] = {
            6,
            CreateMove(3, 2, 3, 3, 0),
            CreateMove(3, 2, 3, 1, 0),
            CreateMove(3, 2, 2, 1, 0),
            CreateMove(3, 2, 2, 2, 0),
            CreateMove(3, 2, 2, 3, 0),
    };

    NEW_MOVE_ARRAY(moves1);
    rook::possibleMoves(moves1, board.GetFromBlackAttackedFields(), board.GetWhiteKing(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e8") >> 3, board.GetPosition("e8") & 0b111);

    NEW_MOVE_ARRAY(moves);
    king::possibleMoves(moves, board.GetFromWhiteAttackedFields(),board.GetFromBlackAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("d3") >> 3, board.GetPosition("d3") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
    }

    presenter.displayUINT64(board.GetFromBlackAttackedFields());
}

TEST(PiecesTest, KingMoveInCheckedField2)
{
    Board board("4r3/8/8/8/2q5/3K4/8/8 w - - 0 1");

    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);

    MOVE expectedMoves[3] = {
            3,
            CreateMove(3, 2, 3, 1, 0),
            CreateMove(3, 2, 2, 3, CAPTURE),
    };

    NEW_MOVE_ARRAY(moves1);
    rook::possibleMoves(moves1, board.GetFromBlackAttackedFields(), board.GetWhiteKing(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("e8")>>3, board.GetPosition("e8") & 0b111);

    NEW_MOVE_ARRAY(moves2);
    queen::possibleMoves(moves2, board.GetFromBlackAttackedFields(), board.GetWhiteKing(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("c4")>>3, board.GetPosition("c4") & 0b111);

    NEW_MOVE_ARRAY(moves);
    king::possibleMoves(moves, board.GetFromWhiteAttackedFields(),board.GetFromBlackAttackedFields(), board.GetAllPieces(), board.GetBlackPieces(), board.GetPosition("d3") >> 3, board.GetPosition("d3") & 0b111);

    for (int i = 0; i < moves[0]; ++i)
    {
        EXPECT_EQ(expectedMoves[i], moves[i]) << "i = " << i << std::endl;
        PrintMove(moves[i]);
    }

    std::cout << moves[0] << std::endl;


    presenter.displayUINT64(board.GetFromBlackAttackedFields());
}


TEST(PiecesTest, BishopTestManyMoves) {
    const std::string game[27] = {
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
            "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
            "rnbqkbnr/ppp1pppp/3p4/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
            "rnbqkbnr/ppp1pppp/3p4/8/3PP3/8/PPP2PPP/RNBQKBNR b KQkq d3 0 2",
            "rnbqkb1r/ppp1pppp/3p1n2/8/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 1 3",
            "rnbqkb1r/ppp1pppp/3p1n2/8/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 2 3",
            "r1bqkb1r/pppnpppp/3p1n2/8/3PP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 3 4",
            "r1bqkb1r/pppnpppp/3p1n2/8/3PP3/3B1N2/PPP2PPP/RNBQK2R b KQkq - 4 4",
            "r1bqkb1r/pppn1ppp/3p1n2/4p3/3PP3/3B1N2/PPP2PPP/RNBQK2R w KQkq - 0 5",
            "r1bqkb1r/pppn1ppp/3p1n2/4P3/4P3/3B1N2/PPP2PPP/RNBQK2R b KQkq - 0 5",
            "r1bqkb1r/pppn1ppp/5n2/4p3/4P3/3B1N2/PPP2PPP/RNBQK2R w KQkq - 0 6",
            "r1bqkb1r/pppn1ppp/5n2/4p3/4P3/2NB1N2/PPP2PPP/R1BQK2R b KQkq - 1 6",
            "r1bqk2r/pppn1ppp/3b1n2/4p3/4P3/2NB1N2/PPP2PPP/R1BQK2R w KQkq - 2 7",
            "r1bqk2r/pppn1ppp/3b1n2/4p3/4P3/2NB1N2/PPP2PPP/R1BQ1RK1 b kq - 3 7",
            "r1bq1rk1/pppn1ppp/3b1n2/4p3/4P3/2NB1N2/PPP2PPP/R1BQ1RK1 w - - 4 8",
            "r1bq1rk1/pppn1ppp/3b1n2/4p3/4P3/2NB1N1P/PPP2PP1/R1BQ1RK1 b - - 0 8",
            "r1bq1rk1/pppn1pp1/3b1n1p/4p3/4P3/2NB1N1P/PPP2PP1/R1BQ1RK1 w - - 0 9",
            "r1bq1rk1/pppn1pp1/3b1n1p/4p3/4P3/2NBBN1P/PPP2PP1/R2Q1RK1 b - - 1 9",
            "r1bq1rk1/ppp2pp1/3b1n1p/2n1p3/4P3/2NBBN1P/PPP2PP1/R2Q1RK1 w - - 2 10",
            "r1bq1rk1/ppp2pp1/3b1n1p/2n1p3/4P3/2NBBN1P/PPP1QPP1/R4RK1 b - - 3 10",
            "r1bq1rk1/ppp2pp1/3bnn1p/4p3/4P3/2NBBN1P/PPP1QPP1/R4RK1 w - - 4 11",
            "r1bq1rk1/ppp2pp1/3bnn1p/4p3/4P3/2NBBN1P/PPPQ1PP1/R4RK1 b - - 5 11",
            "r1bq1rk1/ppp2pp1/3b1n1p/4p3/4Pn2/2NBBN1P/PPPQ1PP1/R4RK1 w - - 6 12",
            "r1bq1rk1/ppp2pp1/3b1n1p/4p3/4PB2/2NB1N1P/PPPQ1PP1/R4RK1 b - - 0 12",
            "r1bq1rk1/ppp2pp1/3b1n1p/8/4Pp2/2NB1N1P/PPPQ1PP1/R4RK1 w - - 0 13",
            "r1bq1rk1/ppp2pp1/3b1n1p/8/4PQ2/2NB1N1P/PPP2PP1/R4RK1 b - - 0 13",
            "r1bq1rk1/ppp2pp1/5n1p/8/4Pb2/2NB1N1P/PPP2PP1/R4RK1 w - - 0 14",
    };

    Board board(game[0]);

    MOVE moves[13] = {
            CreateMove(4, 1, 4, 3, 0),
            CreateMove(3, 6, 3, 5, 0),
            CreateMove(3, 1, 3, 3, 0),
            CreateMove(6, 7, 5, 5, 0),
            CreateMove(6, 0, 5, 2, 0),
            CreateMove(1, 7, 3, 6, 0),
            CreateMove(5, 0, 3, 2, 0),
            CreateMove(4, 6, 4, 4, 0),
            CreateMove(3, 3, 4, 4, CAPTURE),
            CreateMove(3, 5, 4, 4, CAPTURE),
            CreateMove(1, 0, 2, 2, 0),
    };

    for (int i = 0; i < 11; i++) {
        EXPECT_EQ(board.toFEN(), game[i]) << "Move " << i << " failed";
        board.DoMove(moves[i]);
    }

}
