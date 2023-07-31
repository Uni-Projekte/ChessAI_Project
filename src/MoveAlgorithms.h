#ifndef CHESSAI_PROJECT_MOVEALGORITHMS_H
#define CHESSAI_PROJECT_MOVEALGORITHMS_H


#include "Board.h"
#include <unordered_map>
#include <bitset>
#include <bit>
#include "ZobristKeyGenerator.h"
#include "helper.h"
#include <vector>

class MoveAlgorithms {
private:
    Board *board;
    std::unordered_map<uint64_t , TranspositionEntry> *transpositionTable;//0. Best Move 1. Alpha 2. Beta
    std::unordered_map<uint64_t , std::tuple<uint8_t, MOVE>> historyMoves;
    std::unordered_map<uint64_t , std::vector<MOVE> > killerMoves;
    ZobristKeyGenerator *keyGenerator;
    bool useTranspositionTable;
    bool copyUndo;


public:
    MoveAlgorithms(Board *board,
                   std::unordered_map<uint64_t ,TranspositionEntry> *transpositionTable,
                   ZobristKeyGenerator *keyGenerator,
                   bool useTranspositionTable,
                   bool copyUndo = false);


    MOVE GetMoveNegamax(int maxTime = 1000, bool usePVS = true);
    MOVE GetMoveAlphaBeta(int maxTime = 1000);
    MOVE GetMoveMinMax(int maxTime = 1000);


    const int pawnValue = 100;
    const int knightValue = 300;
    const int bishopValue = 320;
    const int rookValue = 500;
    const int queenValue = 900;
    const int kingValue = 20000;
    const float endgameMaterialStart = rookValue * 2 + bishopValue + knightValue;

    float EndgamePhaseWeight(int materialCountWithoutPawns);
    int MaterialWorthWithoutPawns();
    int MaterialWorth();
    int AttackedFields();
    int PawnFileCounts();
    int Defense();
    int PawnStructure();
    int PawnsInCenter(COLOR player, int fullMoveNumber);
    int KingDistanceToCenter();
    int KingSafety();

    int BoardRanking(COLOR player);

    MOVE NegamaxIterative(MOVE_ARRAY moves, int maxTime, bool usePVS, COLOR player);

    bool isQuiet(Board board);
    bool inCheck(Board board);

    int QuiescenceSearch(int searchDepth,
                         MOVE_ARRAY moves,
                         int &states,
                         int alpha,
                         int beta,
                         MOVE *result,
                         COLOR player);

    int Negamax(
            int searchDepth,
            MOVE_ARRAY moves,
            int &states,
            int alpha,
            int beta,
            MOVE *result,
            COLOR player,
            bool root);

    void sortMoves(MOVE_ARRAY moves);
};

#endif //CHESSAI_PROJECT_MOVEALGORITHMS_H
