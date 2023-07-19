#include <chrono>
#include "MoveAlgorithms.h"

using namespace std;

MoveAlgorithms::MoveAlgorithms(Board *board,
                               std::unordered_map<uint64_t, TranspositionEntry> *transpositionTable,
                               ZobristKeyGenerator *keyGenerator,
                               bool useTranspositionTable,
                               bool copyUndo)
{
    this->board = board;
    this->transpositionTable = transpositionTable;
    this->keyGenerator = keyGenerator;
    this->useTranspositionTable = useTranspositionTable;
    this->copyUndo = copyUndo;
}

MOVE MoveAlgorithms::GetMoveNegamax(int maxTime, bool usePVS)
{
    NEW_MOVE_ARRAY(moves);
    this->board->GetMoves(moves);

    MOVE move = 0;
    if (this->board->GetMoveRights() & 1)
    {
        move = this->NegamaxIterative(moves, maxTime , usePVS, BLACK);
    }
    else
    {
        move = this->NegamaxIterative(moves, maxTime , usePVS , WHITE);
    }
    return move;
}

MOVE MoveAlgorithms::GetMoveAlphaBeta(int maxTime)
{
    NEW_MOVE_ARRAY(moves);
    this->board->GetMoves(moves);

    MOVE move = 0;
    if (this->board->GetMoveRights() & 1)
    {
        move = this->AlphaBetaIterative(moves, maxTime , BLACK);
    }
    else
    {
        move = this->AlphaBetaIterative(moves, maxTime , WHITE);
    }
    return move;
}

MOVE MoveAlgorithms::GetMoveMinMax(int maxTime)
{
    NEW_MOVE_ARRAY(moves);
    this->board->GetMoves(moves);
    MOVE move = 0;
    if (this->board->GetMoveRights() & 1)
    {
        move = this->MinMaxIterative(moves, maxTime, BLACK);
    }
    else
    {
        move = this->MinMaxIterative(moves, maxTime, WHITE);
    }
    return move;
}





int MoveAlgorithms::BoardRanking(COLOR player)
{
    int materialWorth = this->MaterialWorth();
    int attackedFields = this->AttackedFields();
    int pawnFileCounts = this->PawnFileCounts();
    int defence = this->Defense();
    int pawnStructure = this->PawnStructure();
    int pawnsInCenter = this->PawnsInCenter();
    return ((int) ((MaterialWorth() << 10) + (AttackedFields() <<7) *  + (PawnFileCounts() << 6) + (Defense() << 6) +
            (PawnStructure() << 6)  + (PawnsInCenter() << 6)));
}

MOVE MoveAlgorithms::NegamaxIterative(MOVE_ARRAY moves, int maxTime, bool usePVS, COLOR player)
{
    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    unsigned int searchDepth = 1;
    MOVE result;

    int64_t end;

    while (true)
    {
        int countStates = 0;
        if(usePVS)
        {
            this->NegamaxPVS(searchDepth, moves, countStates, INT_MIN, INT_MAX, &result, player);
        }
        else
        {
            this->Negamax(searchDepth, moves, countStates, INT_MIN, INT_MAX, &result, player);
        }
        searchDepth = searchDepth + 1;
        end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

        std::cout << std::endl;
        PrintMove(result);
        std::cout << "Depth:" << searchDepth-1 << std::endl;
        std::cout << "Time:" << end - start << std::endl;
        std::cout << "Max Time:" << maxTime << std::endl;
        std::cout << "States: "<< countStates<< std::endl;
        if (end - start > maxTime)
        {
            break;
        }
    }

    std::cout << "time is over iterations to depth:" << searchDepth << std::endl;

    return result;
}

bool MoveAlgorithms::isQuiet(Board board)
{
    MOVE_ARRAY moves;
    board.GetMoves(moves);

    for (int i = 1; i < moves[0]; ++i)
    {
        MOVE move = moves[i];
        Board newBoard(board);
        newBoard.DoMove(move);
        if (inCheck(newBoard) || (move & CAPTURE_FLAGS) != 0)
        {
            return false;
        }
    }
    return true;
}

bool MoveAlgorithms::inCheck(Board board)
{
    COLOR currentColor = board.GetCurrentColor();
    BOARD attackedFields;
    BOARD king;

    if (currentColor == WHITE)
    {
        attackedFields = board.GetFromBlackAttackedFields();
        king = board.GetWhiteKing();
    }
    else
    {
        attackedFields = board.GetFromWhiteAttackedFields();
        king = board.GetBlackKing();
    }

    bool in_check = attackedFields & king;
    return in_check;
}

int MoveAlgorithms::QuiescenceSearch(int searchDepth,
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

    std::unordered_map<uint64_t, TranspositionEntry>::iterator entryA;
    uint64_t boardKey = 0;

    if(this->useTranspositionTable){
        boardKey = this->keyGenerator->CalculateZobristKey(this->board);
        entryA = this->transpositionTable->find(boardKey);
        if(entryA != this->transpositionTable->end() && entryA->second.depth >= searchDepth) {
            TranspositionEntry &entry = entryA->second;
            if (entry.alpha >= beta) {
                return entry.alpha;
            }
            if (entry.beta <= alpha) {
                return entry.beta;
            }
            alpha = std::max(alpha, entry.alpha);
            beta = std::min(beta, entry.beta);
        }
    }

    int best = INT_MIN;

    Board oldBoard (this->board);
    uint8_t oldMoveRights = this->board->GetMoveRights();
    uint8_t oldEnpassent = this->board->GetEnPassant();
    uint8_t oldHalfMoveClock = this->board->GetHalfMoveClock();

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves
        int val = Negamax(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player));
        if (val > best && result != NULL)
        {
            *result = moves[i];
        }
        best = std::max(best, val);
        alpha = std::max(alpha, best);

        if (this->copyUndo) {
            *this->board = oldBoard;
        } else {
            this->board->UndoMove(moves[i], oldMoveRights, oldEnpassent, oldHalfMoveClock);
        }

        if (beta <= alpha)
        {
            break;
        }
    }

    if(this->useTranspositionTable){
        if(entryA == this->transpositionTable->end() && this->transpositionTable->size() < 500000){
            TranspositionEntry newEntry{};
            newEntry.depth = searchDepth;
            newEntry.alpha = best;
            newEntry.beta = best;
            this->transpositionTable->insert({boardKey, newEntry});
        }
        else if(entryA != this->transpositionTable->end() && entryA->second.depth < searchDepth && entryA->second.alpha > best){
            entryA->second.depth = searchDepth;
            entryA->second.alpha = best;
            entryA->second.beta = best;
        }
    }

    return best;
}

int MoveAlgorithms::Negamax(
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

    std::unordered_map<uint64_t, TranspositionEntry>::iterator entryA;
    uint64_t boardKey = 0;

    if(this->useTranspositionTable){
        boardKey = this->keyGenerator->CalculateZobristKey(this->board);
        entryA = this->transpositionTable->find(boardKey);
        if(entryA != this->transpositionTable->end() && entryA->second.depth >= searchDepth) {
            TranspositionEntry &entry = entryA->second;
            if (entry.alpha >= beta) {
                return entry.alpha;
            }
            if (entry.beta <= alpha) {
                return entry.beta;
            }
            alpha = std::max(alpha, entry.alpha);
            beta = std::min(beta, entry.beta);
        }
    }

    /*if (isQuiet(this->board))
    {
        int value = QuiescenceSearch(3, moves, states, beta, alpha, NULL, player);
        return value;
    }*/

    int best = INT_MIN;

    Board oldBoard (this->board);
    uint8_t oldMoveRights = this->board->GetMoveRights();
    uint8_t oldEnpassent = this->board->GetEnPassant();
    uint8_t oldHalfMoveClock = this->board->GetHalfMoveClock();

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves
        int val = Negamax(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player));
        if (val > best && result != NULL)
        {
            *result = moves[i];
        }
        best = std::max(best, val);
        alpha = std::max(alpha, best);

        if (this->copyUndo) {
            *this->board = oldBoard;
        } else {
            this->board->UndoMove(moves[i], oldMoveRights, oldEnpassent, oldHalfMoveClock);
        }

        if (beta <= alpha)
        {
            break;
        }
    }

    if(this->useTranspositionTable){
        if(entryA == this->transpositionTable->end() && this->transpositionTable->size() < 500000){
            TranspositionEntry newEntry{};
            newEntry.depth = searchDepth;
            newEntry.alpha = best;
            newEntry.beta = best;
            this->transpositionTable->insert({boardKey, newEntry});
        }
        else if(entryA != this->transpositionTable->end() && entryA->second.depth < searchDepth && entryA->second.alpha > best){
            entryA->second.depth = searchDepth;
            entryA->second.alpha = best;
            entryA->second.beta = best;
        }
    }

    return best;
}


int MoveAlgorithms::NegamaxPVS(
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

    std::unordered_map<uint64_t, TranspositionEntry>::iterator entryA;
    uint64_t boardKey = 0;

    if (this->useTranspositionTable)
    {
        boardKey = this->keyGenerator->CalculateZobristKey(this->board);
        entryA = this->transpositionTable->find(boardKey);

        if (entryA != this->transpositionTable->end() && entryA->second.depth >= searchDepth)
        {
            TranspositionEntry &entry = entryA->second;

            if (result != nullptr) *result = player ? entry.bestMoveAlpha : entry.bestMoveBeta;

            if (entry.alpha >= beta)
            {
                return entry.alpha;
            }

            if (entry.beta <= alpha)
            {
                return entry.beta;
            }

            alpha = std::max(alpha, entry.alpha);
            beta = std::min(beta, entry.beta);
        }
    }

    int best = INT_MIN;

    Board oldBoard (this->board);
    uint8_t oldMoveRights = this->board->GetMoveRights();
    uint8_t oldEnpassent = this->board->GetEnPassant();
    uint8_t oldHalfMoveClock = this->board->GetHalfMoveClock();

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves possible

        int val;
        if (i == 1) // Principal Variation Search (PVS) with first move searched thoroughly
        {
            val = -NegamaxPVS(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player));
        }
        else // Null window search for other moves with narrow alpha-beta window
        {
            val = -NegamaxPVS(searchDepth - 1, nextMoves, states, -alpha - 1, -alpha, NULL, opponent(player));

            if (val > alpha && val < beta) // Re-search with full-width window
            {
                val = -NegamaxPVS(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player));
            }
        }

        if (this->copyUndo) {
            *this->board = oldBoard;
        } else {
            this->board->UndoMove(moves[i], oldMoveRights, oldEnpassent, oldHalfMoveClock);
        }


        if (val > best && result != NULL)
        {
            *result = moves[i];
        }

        best = std::max(best, val);
        alpha = std::max(alpha, val);

        if (alpha >= beta) // Beta cutoff (pruning)
        {
            break;
        }
    }

    if (this->useTranspositionTable)
    {
        if (entryA == this->transpositionTable->end() && this->transpositionTable->size() < 500000)
        {
            TranspositionEntry newEntry{};
            newEntry.depth = searchDepth;
            newEntry.alpha = best;
            newEntry.beta = best;

            if (result != nullptr)
            {
                newEntry.bestMoveAlpha = *result;
                newEntry.bestMoveBeta = *result;
            }

            this->transpositionTable->insert({boardKey, newEntry});
        }
        else if (entryA != this->transpositionTable->end() && entryA->second.depth < searchDepth && entryA->second.alpha > best)
        {
            entryA->second.depth = searchDepth;
            entryA->second.alpha = best;
            entryA->second.beta = best;

            if (result != nullptr)
            {
                entryA->second.bestMoveAlpha = *result;
                entryA->second.bestMoveBeta = *result;
            }
        }
    }

    return best;
}



MOVE MoveAlgorithms::AlphaBetaIterative(MOVE_ARRAY moves, int maxTime, COLOR player)
{
    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    unsigned int searchDepth = 1;
    MOVE result;

    int64_t end;

    while (true)
    {
        int countStates = 0;
        this->AlphaBetaMax(searchDepth, moves, countStates, INT_MIN, INT_MAX, &result, player);
        searchDepth = searchDepth + 1;
        end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

        //std::cout << std::endl;
        //PrintMove(result);
        //std::cout << "Depth:" << searchDepth-1 << std::endl;
        //std::cout << "Time:" << end - start << std::endl;
        //std::cout << "Max Time:" << maxTime << std::endl;
        //std::cout << "States: "<< countStates<< std::endl;
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
    std::unordered_map<uint64_t, TranspositionEntry>::iterator entryA;
    uint64_t boardKey = 0;

    if(this->useTranspositionTable){
        boardKey = this->keyGenerator->CalculateZobristKey(this->board);
        entryA = this->transpositionTable->find(boardKey);
        if(entryA != this->transpositionTable->end() && entryA->second.depth >= searchDepth) {
            TranspositionEntry &entry = entryA->second;
            if (result != nullptr) *result = entry.bestMoveAlpha;
            if (entry.alpha >= beta) {
                return entry.alpha;
            }
            alpha = std::max(alpha, entry.alpha);
        }
    }

    int best = INT_MIN;

    Board oldBoard (this->board);
    uint8_t oldMoveRights = this->board->GetMoveRights();
    uint8_t oldEnpassent = this->board->GetEnPassant();
    uint8_t oldHalfMoveClock = this->board->GetHalfMoveClock();

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves possible
        int val = AlphaBetaMin(searchDepth - 1, nextMoves, states, alpha, beta, NULL, player);
        if (val > best && result != NULL)
        {
            *result = moves[i];
        }
        best = std::max(best, val);
        alpha = std::max(alpha, val);

        if (this->copyUndo) {
            *this->board = oldBoard;
        } else {
            this->board->UndoMove(moves[i], oldMoveRights, oldEnpassent, oldHalfMoveClock);
        }


        if (beta <= alpha)
        {
            break;
        }
    }

    if(this->useTranspositionTable){
        if(entryA == this->transpositionTable->end() && this->transpositionTable->size() < 500000){
            TranspositionEntry newEntry{};
            newEntry.depth = searchDepth;
            newEntry.alpha = best;
            if(result != NULL) newEntry.bestMoveAlpha = *result;
            this->transpositionTable->insert({boardKey, newEntry});
        }
        else if(entryA != this->transpositionTable->end() && entryA->second.depth < searchDepth && entryA->second.alpha > best){
            entryA->second.depth = searchDepth;
            entryA->second.alpha = best;
            if (result != NULL) entryA->second.bestMoveAlpha = *result;
        }
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
    std::unordered_map<uint64_t, TranspositionEntry>::iterator entryA;
    uint64_t boardKey = 0;

    if(this->useTranspositionTable){
        boardKey = this->keyGenerator->CalculateZobristKey(this->board);
        entryA = this->transpositionTable->find(boardKey);
        if(entryA != this->transpositionTable->end() && entryA->second.depth >= searchDepth) {
            TranspositionEntry &entry = entryA->second;
            if (result != nullptr) *result = entry.bestMoveBeta;
            if (entry.beta <= alpha) {
                return entry.beta;
            }
            beta = std::min(beta, entry.beta);
        }
    }

    int best = INT_MAX;

    Board oldBoard (this->board);
    uint8_t oldMoveRights = this->board->GetMoveRights();
    uint8_t oldEnpassent = this->board->GetEnPassant();
    uint8_t oldHalfMoveClock = this->board->GetHalfMoveClock();

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves possible
        int val = AlphaBetaMax(searchDepth - 1, nextMoves, states, alpha, beta, result, player);
        if (val < best && result != NULL)
        {
            *result = moves[i];
        }
        best = std::min(best, val);
        beta = std::min(beta, val);

        if (this->copyUndo) {
            *this->board = oldBoard;
        } else {
            this->board->UndoMove(moves[i], oldMoveRights, oldEnpassent, oldHalfMoveClock);
        }

        if (beta <= alpha)
        {
            break;
        }
    }

    if(this->useTranspositionTable){
        if(entryA == this->transpositionTable->end() && this->transpositionTable->size() < 500000){
            TranspositionEntry newEntry{};
            newEntry.depth = searchDepth;
            newEntry.beta = best;
            if(result != NULL) newEntry.bestMoveBeta = *result;
            this->transpositionTable->insert({boardKey, newEntry});
        }
        else if(entryA != this->transpositionTable->end() && entryA->second.depth < searchDepth && entryA->second.beta < best){
            entryA->second.depth = searchDepth;
            entryA->second.beta = best;
            if (result != NULL) entryA->second.bestMoveBeta = *result;
        }
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

    ranking = ranking + 10 * popcount(whiteKing);
    ranking = ranking + 9 * popcount(whiteQueen);
    ranking = ranking + 5 * popcount(whiteRooks);
    ranking = ranking + 3 * popcount(whiteBishops);
    ranking = ranking + 3 * popcount(whiteKnights);
    ranking = ranking + 1 * popcount(whitePawns);
    ranking = ranking - 10 * popcount(blackKing);
    ranking = ranking - 9 * popcount(blackQueen);
    ranking = ranking - 5 * popcount(blackRooks);
    ranking = ranking - 3 * popcount(blackBishops);
    ranking = ranking - 3 * popcount(blackKnights);
    ranking = ranking - 1 * popcount(blackBishops);

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


    ranking = ranking + 1000 * popcount(attackedFromWhite & blackKing);
    ranking = ranking + 9 * popcount(attackedFromWhite & blackQueen);
    ranking = ranking + 5 * popcount(attackedFromWhite & blackRooks);
    ranking = ranking + 3 * popcount(attackedFromWhite & blackBishops);
    ranking = ranking + 3 * popcount(attackedFromWhite & blackKnights);
    ranking = ranking + 1 * popcount(attackedFromWhite & blackPawns);

    ranking = ranking - 1000 * popcount(attackedFromBlack & whiteKing);
    ranking = ranking - 9 * popcount(attackedFromBlack & whiteQueen);
    ranking = ranking - 5 * popcount(attackedFromBlack & whiteRooks);
    ranking = ranking - 3 * popcount(attackedFromBlack & whiteBishops);
    ranking = ranking - 3 * popcount(attackedFromBlack & whiteKnights);
    ranking = ranking - 1 * popcount(attackedFromBlack & whitePawns);

    return ranking;
}

int MoveAlgorithms::PawnFileCounts()
{
    int ranking = 0;

    uint64_t whitePawns = this->board->GetWhitePawns();
    uint64_t blackPawns = this->board->GetBlackPawns();

    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnA) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnB) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnC) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnD) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnE) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnF) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnG) - 1);
    ranking = ranking - 4 * (popcount(whitePawns & BoardColumnH) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnA) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnB) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnC) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnD) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnE) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnF) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnG) - 1);
    ranking = ranking + 4 * (popcount(blackPawns & BoardColumnH) - 1);

    return ranking;
}

int MoveAlgorithms::Defense()
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

int MoveAlgorithms::PawnsInCenter()
{
    int ranking = 0;

    uint64_t midFields = 0b0001100000011000<<24;

    uint64_t pawns = this->board->GetPawns();

    uint64_t white = this->board->GetWhite();
    uint64_t black = this->board->GetBlack();

    ranking = ranking + popcount(pawns & midFields & white);

    ranking = ranking - popcount(pawns & midFields & black);

    return ranking;
}

int MoveAlgorithms::PawnStructure()
{
    int ranking = 0;

    uint64_t pawns = this->board->GetPawns();

    uint64_t white = this->board->GetWhite();
    uint64_t black = this->board->GetBlack();

    uint64_t whiteAttacked = this->board->GetFromWhiteAttackedFields();
    uint64_t blackAttacked = this->board->GetFromBlackAttackedFields();


    ranking = ranking + popcount(pawns & white & whiteAttacked);

    ranking = ranking - popcount(pawns & black & blackAttacked);

    return ranking;
}

