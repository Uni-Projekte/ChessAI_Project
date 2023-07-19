#include "gtest/gtest.h"
#include "../src/Board.h"
#include "../src/MoveAlgorithms.h"
#include "../src/presenter.h"
#include "../src/Game.h"
#include <filesystem>
namespace fs = std::filesystem;

// Tests made bny RamRam
/*TEST(BoardTest, FromFENTestInitalBoard) {
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
}*/

TEST(BoardTest, PlayGame)
{

    Board board = Board();
    Presenter presenter = Presenter();
    std::cout << std::endl << presenter.ToString(board);
    //board.PlayGame();
}

/*TEST(BoardTest, StartRanking)
{
    Board board("rnbqk1nr/pp1p1ppp/2p5/2b1p1B1/8/3P1N2/PPP1PPPP/RN1QKB1R w KQkq - 0 1");
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, false);
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    std::cout << moveCalc.BoardRanking(WHITE) << std::endl;
}


TEST(BoardTest, DoMoveBenchmarkStart)
{
    Board board("rnbqk1nr/pp1p1ppp/2p5/2b1p1B1/8/3P1N2/PPP1PPPP/RN1QKB1R w KQkq - 0 1");
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, true);
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    std::cout << moveCalc.GetMoveAlphaBeta();
}

TEST(BoardTest, UndoMove){
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
    board.MarkFields(BLACK);
    board.MarkFields(WHITE);
    board.GetMoves(nextMoves); // get all moves possible
    for(int i = 1; i < nextMoves[0];i=i+1) {
        uint8_t oldMoveRights = board.GetMoveRights();
        uint8_t oldHalfmoveClock = board.GetHalfMoveClock();
        uint8_t oldEnPassent = board.GetEnPassant();
        Board oldBoard(board);
        board.DoMove(nextMoves[i]);
        Board movedBoard(board);
        std::cout << std::endl
                  << presenter.ToString(movedBoard);
        board.UndoMove(nextMoves[i], oldMoveRights, oldEnPassent, oldHalfmoveClock);
        EXPECT_EQ(board.Equals(oldBoard),true) << "N-TH MOVE: " << i << "---" << MoveToString(nextMoves[i]) << std::endl
        << presenter.ToString(oldBoard) << std::endl
        << "MOVE-RIGHTS: " << Uint8ToString(oldBoard.GetMoveRights()) << std::endl
        << "HALFMOVE:    " << Uint8ToString(oldBoard.GetHalfMoveClock()) << std::endl
        << "EN-PASSENT:  " << Uint8ToString(oldBoard.GetEnPassant()) << std::endl
        << "F-W-ATTACK:  " << oldBoard.GetFromWhiteAttackedFields() << std::endl
        << "F-B-ATTACK:  " << oldBoard.GetFromBlackAttackedFields() << std::endl
        << "W-PINNED:    " << oldBoard.GetWhitePinnedPieces() << std::endl << std::endl
        << "B-PINNED:    " << oldBoard.GetBlackPinnedPieces() << std::endl << std::endl
        << "FULL-MOVE:   " << oldBoard.GetFullMoveNumber() << std::endl
        << presenter.ToString(movedBoard) << std::endl
        << presenter.ToString(board)<< std::endl
        << "MOVE-RIGHTS: " << Uint8ToString(board.GetMoveRights()) << std::endl
        << "HALFMOVE:    " << Uint8ToString(board.GetHalfMoveClock()) << std::endl
        << "EN-PASSENT:  " << Uint8ToString(board.GetEnPassant()) << std::endl
        << "F-W-ATTACK:  " << board.GetFromWhiteAttackedFields() << std::endl
        << "F-B-ATTACK:  " << board.GetFromBlackAttackedFields() << std::endl
        << "W-PINNED:    " << board.GetWhitePinnedPieces() << std::endl << std::endl
        << "B-PINNED:    " << board.GetBlackPinnedPieces() << std::endl << std::endl
        << "FULL-MOVE:   " << board.GetFullMoveNumber() << std::endl;
        board = oldBoard;
    }
}

TEST(BoardTest, UndoMoveEnPassent){
    Board board("8/8/8/P6p/6pP/8/8/8 b - h4 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
    board.MarkFields(BLACK);
    board.MarkFields(WHITE);
    board.GetMoves(nextMoves); // get all moves possible
    EXPECT_EQ(3,nextMoves[0]);
    for(int i = 1; i < nextMoves[0];i=i+1) {
        uint8_t oldMoveRights = board.GetMoveRights();
        uint8_t oldHalfmoveClock = board.GetHalfMoveClock();
        uint8_t oldEnPassent = board.GetEnPassant();
        Board oldBoard(board);
        board.DoMove(nextMoves[i]);
        Board movedBoard(board);
        board.UndoMove(nextMoves[i], oldMoveRights, oldEnPassent, oldHalfmoveClock);
        EXPECT_EQ(board.Equals(oldBoard),true) << "N-TH MOVE: " << i << "---" << MoveToString(nextMoves[i]) << std::endl
                                               << presenter.ToString(oldBoard) << std::endl
                                               << "MOVE-RIGHTS: " << Uint8ToString(oldBoard.GetMoveRights()) << std::endl
                                               << "HALFMOVE:    " << Uint8ToString(oldBoard.GetHalfMoveClock()) << std::endl
                                               << "EN-PASSENT:  " << Uint8ToString(oldBoard.GetEnPassant()) << std::endl
                                               << "F-W-ATTACK:  " << oldBoard.GetFromWhiteAttackedFields() << std::endl
                                               << "F-B-ATTACK:  " << oldBoard.GetFromBlackAttackedFields() << std::endl
                                               << "W-PINNED:    " << oldBoard.GetWhitePinnedPieces() << std::endl << std::endl
                                               << "B-PINNED:    " << oldBoard.GetBlackPinnedPieces() << std::endl << std::endl
                                               << "FULL-MOVE:   " << oldBoard.GetFullMoveNumber() << std::endl
                                               << presenter.ToString(movedBoard) << std::endl
                                               << presenter.ToString(board)<< std::endl
                                               << "MOVE-RIGHTS: " << Uint8ToString(board.GetMoveRights()) << std::endl
                                               << "HALFMOVE:    " << Uint8ToString(board.GetHalfMoveClock()) << std::endl
                                               << "EN-PASSENT:  " << Uint8ToString(board.GetEnPassant()) << std::endl
                                               << "F-W-ATTACK:  " << board.GetFromWhiteAttackedFields() << std::endl
                                               << "F-B-ATTACK:  " << board.GetFromBlackAttackedFields() << std::endl
                                               << "W-PINNED:    " << board.GetWhitePinnedPieces() << std::endl << std::endl
                                               << "B-PINNED:    " << board.GetBlackPinnedPieces() << std::endl << std::endl
                                               << "FULL-MOVE:   " << board.GetFullMoveNumber() << std::endl;
        board = oldBoard;
    }
}

TEST(BoardTest, AlphaBetaMiddleWithTranspostionTable)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveAlphaBeta(10000);
    }
    std::cout << recommendedMove;
}



TEST(BoardTest, NegamaxMiddleWithTranspostionTableNoPVS)
{
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(1000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxMiddleWithTranspostionTablePVS)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(1000, true);
    }
    std::cout << recommendedMove;
}


TEST(BoardTest, DoMoveBenchmarkEnd)
{
    Board board("r3k3/5p1p/n7/6B1/8/8/P7/K1R5 w q - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator,true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveAlphaBeta();
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, BenchmarkStartMinMax)
{
Board board("rnbqk1nr/pp1p1ppp/2p5/2b1p1B1/8/3P1N2/PPP1PPPP/RN1QKB1R w KQkq - 0 1");
Presenter presenter = Presenter();
std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveMinMax();
    }
    std::cout << recommendedMove;
}


TEST(BoardTest, BenchmarkMiddleMinMax)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveMinMax();
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, DoMoveBenchmarkEndMinMax)
{
    Board board("r3k3/5p1p/n7/6B1/8/8/P7/K1R5 w q - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveMinMax();
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, DoMoveBenchmarkEndAlphaBeta2)
{
    Board board("r2qk2r/p1ppn1pp/bpnb1p2/4p3/4P3/2NPBN2/PPP1BPPP/R2Q1RK1 w Qkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveMinMax();
    }
    std::cout << recommendedMove;
}
*/
TEST(BoardTest, PlayGameTest)
{
    PlayGameWithItself();
}

TEST(BoardTest, Checkmate)
{
    Board board("8/8/8/8/4N3/8/P7/K1q5 w - - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl
              << presenter.ToString(board);
    board.MarkFields(BLACK);
    board.MarkFields(WHITE);
    EXPECT_EQ(board.IsCheckmate(board.GetCurrentColor()), true);
}


/*TEST(BoardTest, NegamaxStartNoTNoP)
{
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, false, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxStartWithTWithP)
{
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, true);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxStartWithTnoP)
{
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxMiddleNoTNoP)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, false, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxMiddleWithTWithP)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, true);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxMiddleWithTnoP)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxEndNoTNoP)
{
    Board board("r3k3/p6p/2n2q2/4p3/1B4P1/4N3/3P4/Q3K2R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, false, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxEndWithTWithP)
{
    Board board("r3k3/p6p/2n2q2/4p3/1B4P1/4N3/3P4/Q3K2R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, true);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, NegamaxEndWithTnoP)
{
    Board board("r3k3/p6p/2n2q2/4p3/1B4P1/4N3/3P4/Q3K2R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true, true);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveNegamax(3000, false);
    }
    std::cout << recommendedMove;
}

TEST(BoardTest, AlphaBetaWithoutTranspostionTable)
{
    Board board("r3k3/p4ppp/n1p2q1n/2b1p1B1/4P3/N7/P1PQ2PP/K1R2B1R w Kq - 0 1");
    Presenter presenter = Presenter();
    std::cout << std::endl<< presenter.ToString(board);
    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;
    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable,  &zobristKeyGenerator, false);
    MOVE recommendedMove;
    for (int i = 0; i < 1; i++)
    {
        recommendedMove = moveCalc.GetMoveAlphaBeta(5000);
    }
    std::cout << recommendedMove;
}*/