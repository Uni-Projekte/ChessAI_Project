#ifndef CHESSAI_PROJECT_MOVEALGORITHMS_H
#define CHESSAI_PROJECT_MOVEALGORITHMS_H


#include "Board.h"
#include <unordered_map>
#include <bitset>
#include <bit>
#include "ZobristKeyGenerator.h"

class MoveAlgorithms {
private:
    Board *board;
    std::unordered_map<uint64_t , TranspositionEntry> *transpositionTable;//0. Best Move 1. Alpha 2. Beta
    ZobristKeyGenerator *keyGenerator;

public:
    MoveAlgorithms(Board *board, std::unordered_map<uint64_t ,
                   TranspositionEntry> *transpositionTable,
                   ZobristKeyGenerator *keyGenerator);
    MOVE GetMoveAlphaBeta();
    MOVE GetMoveMinMax();

    int MaterialWorth();
    int AttackedFields();
    int PawnFileCounts();
    int Defense();

    int BoardRanking(COLOR player);

    MOVE AlphaBetaIterative(MOVE_ARRAY moves,
                            int maxTime,
                            COLOR player);

    int AlphaBetaMax(int searchDepth,
                     MOVE_ARRAY moves,
                     int &states,
                     int alpha,
                     int beta,
                     MOVE *result,
                     COLOR player);

    int AlphaBetaMin(int searchDepth,
                     MOVE_ARRAY moves,
                     int &states,
                     int alpha,
                     int beta,
                     MOVE *result,
                     COLOR player);

    MOVE MinMaxIterative(MOVE_ARRAY moves,
                         int maxTime,
                         COLOR player);

    int MinMaxMax(int searchDepth,
                  MOVE_ARRAY moves,
                  int &states,
                  MOVE *result,
                  COLOR player);

    int MinMaxMin(int searchDepth,
                  MOVE_ARRAY moves,
                  int &states,
                  MOVE *result,
                  COLOR player);

};

#endif //CHESSAI_PROJECT_MOVEALGORITHMS_H
