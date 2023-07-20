#include "Game.h"
#include <iostream>

void PlayGameWithItself() {
    Board board("7k/8/8/2q5/8/4N3/P7/K7 b - - 0 1");
    Presenter presenter = Presenter();

    board.MarkFields(BLACK);
    board.MarkFields(WHITE);

    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, false, true);
    MOVE recommendedMove;

    while (!board.IsCheckmate(WHITE) && !board.IsCheckmate(BLACK) && !board.End())
    {
        recommendedMove = moveCalc.GetMoveNegamax(1000, false);
        board.DoMove(recommendedMove);
        std::cout<< presenter.ToString(board) << std::endl;
        std::cout << MoveForGameServer(recommendedMove);
        int i = 0;
    }
}