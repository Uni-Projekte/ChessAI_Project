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

TEST(PiecesTest, BishopTestManyMoves) {
    const std::string game[27] = {
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1",
            "rnbqkbnr/ppp1pppp/3p4/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
            "rnbqkbnr/ppp1pppp/3p4/8/3PP3/8/PPP2PPP/RNBQKBNR b KQkq - 0 2",
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

    MOVE expectedMoves[13] = {
            CREATE_MOVE(4, 1, 4, 3, 0),
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

}