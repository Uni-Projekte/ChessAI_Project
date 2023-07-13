#include <chrono>
#include "MoveAlgorithms.h"

using namespace std;

MoveAlgorithms::MoveAlgorithms(Board *board, std::unordered_map<uint64_t, TranspositionEntry> *transpositionTable,
                               ZobristKeyGenerator *keyGenerator)
{
    this->board = board;
    this->transpositionTable = transpositionTable;
    this->keyGenerator = keyGenerator;
}

MOVE MoveAlgorithms::GetMoveAlphaBeta()
{
    // std::cout << "NUMBER OF MOVES: " << moves.size() << std::endl;
    // for (int i = 0; i < moves.size()-1; i++) {
    //     std::cout << moves[i] << ", ";
    // }
    // std::cout << moves[moves.size()-1] << std::endl;
    NEW_MOVE_ARRAY(moves);
    this->board->GetMoves(moves);

    MOVE move = 0;
    if (this->board->GetMoveRights() & 1)
    {
        move = this->AlphaBetaIterative(moves, 1000 , BLACK);
    }
    else
    {
        move = this->AlphaBetaIterative(moves, 1000 , WHITE);
    }
    // std::cout << "PICKED MOVE: " << move << std::endl;
    // std::cout << "FLAGS:" << ((move & 0b1111000000000000U) >> 12) << std::endl;
    // std::cout << "FROM:" << GET_MOVE_FROM_X(move) << ", " << GET_MOVE_FROM_Y(move) << std::endl;
    // std::cout << "TO:" << GET_MOVE_TO_X(move) << ", " << GET_MOVE_TO_Y(move) << std::endl;
    return move;
}

MOVE MoveAlgorithms::GetMoveMinMax()
{
    // std::cout << "NUMBER OF MOVES: " << moves.size() << std::endl;
    // for (int i = 0; i < moves.size()-1; i++) {
    //     std::cout << moves[i] << ", ";
    // }
    // std::cout << moves[moves.size()-1] << std::endl;
    NEW_MOVE_ARRAY(moves);
    this->board->GetMoves(moves);
    MOVE move = 0;
    if (this->board->GetMoveRights() & 1)
    {
        move = this->MinMaxIterative(moves, 1000, BLACK);
    }
    else
    {
        move = this->MinMaxIterative(moves, 1000, WHITE);
    }
    // std::cout << "PICKED MOVE: " << move << std::endl;
    // std::cout << "FLAGS:" << ((move & 0b1111000000000000U) >> 12) << std::endl;
    // std::cout << "FROM:" << GET_MOVE_FROM_X(move) << ", " << GET_MOVE_FROM_Y(move) << std::endl;
    // std::cout << "TO:" << GET_MOVE_TO_X(move) << ", " << GET_MOVE_TO_Y(move) << std::endl;
    return move;
}





int MoveAlgorithms::BoardRanking(COLOR player)
{
    int materialWorth = this->MaterialWorth();
    int attackedFields = this->AttackedFields();
    int pawnFileCounts = this->PawnFileCounts();
    int defence = this->Defence();
    float materialWorthWeight = 0.5;
    return (int) (materialWorth * 0.45 + attackedFields * 0.30 + pawnFileCounts * 0.1 + defence * 0.15);
}

MOVE MoveAlgorithms::AlphaBetaIterative(MOVE_ARRAY moves, int maxTime, COLOR player)
{
    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    unsigned int searchDepth = 1;
    MOVE result;

    int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    while (true)
    {
        int countStates = 0;
        this->AlphaBetaMax(searchDepth, moves, countStates, INT_MIN, INT_MAX, &result, player);
        searchDepth = searchDepth + 1;
        end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

        PrintMove(result);
        std::cout << searchDepth-1 << std::endl;
        std::cout << end - start << std::endl;
        std::cout << maxTime << std::endl;
        std::cout << "States: "<<countStates<< std::endl;
        if (end - start > maxTime)
        {
            break;
        }
    }

    std::cout << "time is over iterations to depth:" << searchDepth << std::endl;

    return result;
}

int MoveAlgorithms::AlphaBetaMax(
        int searchDepth,
        MOVE_ARRAY moves,
        int &states,
        int alpha,
        int beta,
        MOVE *result,
        COLOR player)
{
    states += 1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    uint64_t zobristKey = 0;

    zobristKey = this->keyGenerator->CalculateZobristKey(this->board);

    auto entryIt = this->transpositionTable->find(zobristKey);

    if (entryIt != this->transpositionTable->end() && entryIt->second.depth >= searchDepth)
    {
        TranspositionEntry &entry = entryIt->second;
        if (entry.score > alpha)
        {
            alpha = entry.score;
            if (result != nullptr)
            {
                *result = entry.bestMove;
            }
        }
        if (entry.score >= beta)
        {
            return entry.score;
        }
    }

    int best = INT_MIN;

    MOVE defaultMove;  // Default value for result if it's nullptr
    MOVE &currentMove = (result != nullptr) ? *result : defaultMove;

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves); // get all moves possible
        int val = AlphaBetaMin(searchDepth - 1, nextMoves, states, alpha, beta, &currentMove, player);
        if (val > best)
        {
            best = val;
            if (result != nullptr)
            {
                *result = currentMove;
            }
        }
        alpha = std::max(alpha, best);

        if (beta <= alpha)
        {
            break;
        }
    }

    if (this->transpositionTable->size() < 30000)
    {
        TranspositionEntry entry{};
        entry.depth = searchDepth;
        entry.score = best;
        if (result != nullptr)
        {
            entry.bestMove = *result;
        }
        this->transpositionTable->insert(std::make_pair(zobristKey, entry));
    }

    return best;
}

int MoveAlgorithms::AlphaBetaMin(
        int searchDepth,
        MOVE_ARRAY moves,
        int &states,
        int alpha,
        int beta,
        MOVE *result,
        COLOR player)
{
    states += 1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    // Check  if the current position is stored in the transposition table
    uint64_t zobristKey = this->keyGenerator->CalculateZobristKey(this->board);
    auto entryIt = this->transpositionTable->find(zobristKey);
    if (entryIt != this->transpositionTable->end() && entryIt->second.depth >= searchDepth)
    {
        TranspositionEntry &entry = entryIt->second;
        if (entry.score < beta)
        {
            beta = entry.score;
            if (result != nullptr)
            {
                *result = entry.bestMove;
            }
        }
        if (entry.score <= alpha)
        {
            return entry.score;
        }
    }


    int best = INT_MAX;

    MOVE defaultMove;  // Default value for result if it's nullptr
    MOVE& currentMove = (result != nullptr) ? *result : defaultMove;

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves); // get all moves possible
        int val = AlphaBetaMax(searchDepth - 1, nextMoves, states, alpha, beta, &currentMove, player);
        if (val < best)
        {
            best = val;
            if (result != nullptr)
            {
                *result = currentMove;
            }
        }
        beta = min(beta, best);

        if (beta <= alpha)
        {
            break;
        }
    }
    if (this->transpositionTable->size() < 30000)
    {
        TranspositionEntry entry{};
        entry.depth = searchDepth;
        entry.score = best;
        if (result != nullptr)
        {
            entry.bestMove = *result;
        }
        this->transpositionTable->insert(std::make_pair(zobristKey, entry));
    }

    return best;
}

MOVE MoveAlgorithms::MinMaxIterative(MOVE_ARRAY moves, int maxTime, COLOR player)
{
    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    unsigned int searchDepth = 1;
    MOVE result;

    int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    while (true)
    {
        int countStates = 0;
        this->MinMaxMax(searchDepth, moves, countStates,&result, player);
        searchDepth = searchDepth + 1;
        int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

        PrintMove(result);
        std::cout << searchDepth-1 << std::endl;
        std::cout << end - start << std::endl;
        std::cout << maxTime << std::endl;
        std::cout << "States: "<<countStates<< std::endl;

        if (end - start > maxTime)
        {
            break;
        }
    }

    std::cout << "time is over iterations to depth:" << searchDepth << std::endl;

    return result;
}

int MoveAlgorithms::MinMaxMax(
        int searchDepth,
        MOVE_ARRAY moves,
        int &states,
        MOVE *result,
        COLOR player)
{
    states +=1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    int best = INT_MIN;

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves possible
        int val = this->MinMaxMin(searchDepth - 1, nextMoves, states, NULL, player);
        if (val > best && result != NULL)
        {
            *result = moves[i];
            //std::cout << i << std::endl;
        }
        best = max(best, val);
    }
    return best;
}

int MoveAlgorithms::MinMaxMin(
        int searchDepth,
        MOVE_ARRAY moves,
        int &states,
        MOVE *result,
        COLOR player)
{
    states+=1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    int best = INT_MAX;

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves); // allocate memory for next moves
        this->board->GetMoves(nextMoves); // get all moves possible
        int val = this->MinMaxMax(searchDepth - 1, nextMoves, states, NULL, player);
        if (val < best && result != NULL)
        {
            *result = moves[i];
            //std::cout << i << std::endl;
        }
        best = min(best, val);
    }
    return best;
}

int MoveAlgorithms::MaterialWorth()
{
    int ranking = 0;

    uint64_t whiteKing = this->board->GetWhiteKing();
    uint64_t whiteQueen = this->board->GetWhiteQueen();
    uint64_t whiteRooks = this->board->GetWhiteRooks();
    uint64_t whiteBishops = this->board->GetWhiteBishops();
    uint64_t whiteKnights = this->board->GetWhiteKnights();
    uint64_t whitePawns = this->board->GetWhitePawns();

    uint64_t blackKing = this->board->GetBlackKing();
    uint64_t blackQueen = this->board->GetBlackQueen();
    uint64_t blackRooks = this->board->GetBlackRooks();
    uint64_t blackBishops = this->board->GetBlackBishops();
    uint64_t blackKnights = this->board->GetBlackKnights();
    uint64_t blackPawns = this->board->GetBlackPawns();

    ranking = ranking + 10000 * popcount(whiteKing);
    ranking = ranking + 900 * popcount(whiteQueen);
    ranking = ranking + 500 * popcount(whiteRooks);
    ranking = ranking + 300 * popcount(whiteBishops);
    ranking = ranking + 300 * popcount(whiteKnights);
    ranking = ranking + 100 * popcount(whitePawns);
    ranking = ranking - 10000 * popcount(blackKing);
    ranking = ranking - 900 * popcount(blackQueen);
    ranking = ranking - 500 * popcount(blackRooks);
    ranking = ranking - 300 * popcount(blackBishops);
    ranking = ranking - 300 * popcount(blackKnights);
    ranking = ranking - 100 * popcount(blackBishops);

    return ranking;
}

int MoveAlgorithms::AttackedFields()
{
    int ranking = 0;

    uint64_t attackedFromWhite = this->board->GetFromWhiteAttackedFields();
    uint64_t attackedFromBlack = this->board->GetFromBlackAttackedFields();

    uint64_t whiteKing = this->board->GetWhiteKing();
    uint64_t whiteQueen = this->board->GetWhiteQueen();
    uint64_t whiteRooks = this->board->GetWhiteRooks();
    uint64_t whiteBishops = this->board->GetWhiteBishops();
    uint64_t whiteKnights = this->board->GetWhiteKnights();
    uint64_t whitePawns = this->board->GetWhitePawns();

    uint64_t blackKing = this->board->GetBlackKing();
    uint64_t blackQueen = this->board->GetBlackQueen();
    uint64_t blackRooks = this->board->GetBlackRooks();
    uint64_t blackBishops = this->board->GetBlackBishops();
    uint64_t blackKnights = this->board->GetBlackKnights();
    uint64_t blackPawns = this->board->GetBlackPawns();


    ranking = ranking + 10000 * popcount(attackedFromWhite & blackKing);
    ranking = ranking + 900 * popcount(attackedFromWhite & blackQueen);
    ranking = ranking + 500 * popcount(attackedFromWhite & blackRooks);
    ranking = ranking + 300 * popcount(attackedFromWhite & blackBishops);
    ranking = ranking + 300 * popcount(attackedFromWhite & blackKnights);
    ranking = ranking + 100 * popcount(attackedFromWhite & blackPawns);

    ranking = ranking - 10000 * popcount(attackedFromBlack & whiteKing);
    ranking = ranking - 900 * popcount(attackedFromBlack & whiteQueen);
    ranking = ranking - 500 * popcount(attackedFromBlack & whiteRooks);
    ranking = ranking - 300 * popcount(attackedFromBlack & whiteBishops);
    ranking = ranking - 300 * popcount(attackedFromBlack & whiteKnights);
    ranking = ranking - 100 * popcount(attackedFromBlack & whitePawns);

    return ranking;
}

int MoveAlgorithms::PawnFileCounts()
{
    int ranking = 0;

    uint64_t whitePawns = this->board->GetWhitePawns();
    uint64_t blackPawns = this->board->GetBlackPawns();

    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnA) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnB) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnC) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnD) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnE) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnF) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnG) - 1);
    ranking = ranking - 400 * (popcount(whitePawns & BoardColumnH) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnA) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnB) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnC) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnD) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnE) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnF) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnG) - 1);
    ranking = ranking + 400 * (popcount(blackPawns & BoardColumnH) - 1);

    return ranking;
}

int MoveAlgorithms::Defence()
{
    int ranking = 0;

    uint64_t attackedFromWhite = this->board->GetFromWhiteAttackedFields();
    uint64_t attackedFromBlack = this->board->GetFromBlackAttackedFields();

    uint64_t white = this->board->GetWhite();
    uint64_t black = this->board->GetBlack();

    ranking = ranking + popcount(attackedFromWhite & white);

    ranking = ranking - popcount(attackedFromBlack & black);

    return ranking;
}

