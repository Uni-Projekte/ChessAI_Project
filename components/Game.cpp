#include "Game.h"
#include <iostream>

void PlayGameWithItself() {
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();

    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, false, true);
    MOVE recommendedMove;

    while (!board.End())
    {
        recommendedMove = moveCalc.GetMoveAlphaBeta(500);
        board.DoMove(recommendedMove);
        std::cout<< presenter.ToString(board) << std::endl;
        int i = 0;
        std::cout << recommendedMove;
    }


}