#include "Game.h"
#include <iostream>

void PlayGameWithItself(int maxTime) {
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Presenter presenter = Presenter();

    ZobristKeyGenerator zobristKeyGenerator;
    std::unordered_map<uint64_t , TranspositionEntry> transpositionTable;

    zobristKeyGenerator.InitRandomFields();
    MoveAlgorithms moveCalc(&board, &transpositionTable, &zobristKeyGenerator, true);
    MOVE recommendedMove;
    std::cout << presenter.ToString(board) << std::endl;

    while (true)
    {
        recommendedMove = moveCalc.GetMoveNegamax(maxTime, false);
        board.DoMove(recommendedMove);
        std::cout << presenter.ToString(board) << std::endl;
        std::cout << recommendedMove;
    }


}