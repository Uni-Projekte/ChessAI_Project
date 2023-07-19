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





int MoveAlgorithms::BoardRanking(COLOR player)
{
    int materialWorth   = this->MaterialWorth();
    int attackedFields  = this->AttackedFields();
    int pawnFileCounts  = this->PawnFileCounts();
    int defence         = this->Defense();
    int pawnStructure   = this->PawnStructure();
    int multiplierPiC = max(1, 30000 - this->board->GetFullMoveNumber());
    int pawnsInCenter   = this->PawnsInCenter(player, this->board->GetFullMoveNumber()) * multiplierPiC;

    return ((int) ( materialWorth + attackedFields + pawnFileCounts + defence + pawnStructure + pawnsInCenter));
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
        if (val >= best && result != NULL)
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

MOVE MoveAlgorithms::NegamaxIterative(MOVE_ARRAY moves, int maxTime, bool usePVS, COLOR player)
{
    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    int searchDepth = 1;
    MOVE result;
    int countStates = 0;


    int64_t end;

    while (true)
    {
        this->Negamax(searchDepth, moves, countStates, INT_MIN + 1, INT_MAX-1, &result, player);

        searchDepth = searchDepth + 1;
        end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

        std::cout << std::endl;

        if (end - start > maxTime)
        {
            break;
        }
    }

    std::cout << "Time:" << end - start << std::endl;
    std:cout <<  "States: "<< countStates<< std::endl;
    std::cout << "Max Time:" << maxTime << std::endl;

    std::cout << "time is over iterations to depth:" << searchDepth << std::endl;

    return result;
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
        return (-2 * player + 1) * BoardRanking(player);
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

    int best = INT_MIN+1;

    Board oldBoard (this->board);
    uint8_t oldMoveRights = this->board->GetMoveRights();
    uint8_t oldEnpassent = this->board->GetEnPassant();
    uint8_t oldHalfMoveClock = this->board->GetHalfMoveClock();

    for (int i = 1; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        this->board->GetMoves(nextMoves);             // get all moves
        int val = -Negamax(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player));
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

    ranking = ranking + 20000 * popcount(whiteKing);
    ranking = ranking + 900 * popcount(whiteQueen);
    ranking = ranking + 500 * popcount(whiteRooks);
    ranking = ranking + 300 * popcount(whiteBishops);
    ranking = ranking + 300 * popcount(whiteKnights);
    ranking = ranking + 100 * popcount(whitePawns);
    ranking = ranking - 20000 * popcount(blackKing);
    ranking = ranking - 900 * popcount(blackQueen);
    ranking = ranking - 500 * popcount(blackRooks);
    ranking = ranking - 300 * popcount(blackBishops);
    ranking = ranking - 300 * popcount(blackKnights);
    ranking = ranking - 100 * popcount(blackPawns);

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


    ranking = ranking + 200 * popcount(attackedFromWhite & blackKing);
    ranking = ranking + 90 * popcount(attackedFromWhite & blackQueen);
    ranking = ranking + 50 * popcount(attackedFromWhite & blackRooks);
    ranking = ranking + 30 * popcount(attackedFromWhite & blackBishops);
    ranking = ranking + 30 * popcount(attackedFromWhite & blackKnights);
    ranking = ranking + 10 * popcount(attackedFromWhite & blackPawns);

    ranking = ranking - 200 * popcount(attackedFromBlack & whiteKing);
    ranking = ranking - 90 * popcount(attackedFromBlack & whiteQueen);
    ranking = ranking - 50 * popcount(attackedFromBlack & whiteRooks);
    ranking = ranking - 30 * popcount(attackedFromBlack & whiteBishops);
    ranking = ranking - 30 * popcount(attackedFromBlack & whiteKnights);
    ranking = ranking - 10 * popcount(attackedFromBlack & whitePawns);

    return ranking;
}

int MoveAlgorithms::PawnFileCounts()
{
    int ranking = 0;

    uint64_t whitePawns = this->board->GetWhitePawns();
    uint64_t blackPawns = this->board->GetBlackPawns();

    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnA) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnB) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnC) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnD) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnE) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnF) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnG) - 1);
    ranking = ranking - 40 * (popcount(whitePawns & BoardColumnH) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnA) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnB) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnC) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnD) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnE) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnF) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnG) - 1);
    ranking = ranking + 40 * (popcount(blackPawns & BoardColumnH) - 1);

    return ranking;
}

int MoveAlgorithms::Defense()
{
    int ranking = 0;

    uint64_t attackedFromWhite = this->board->GetFromWhiteAttackedFields();
    uint64_t attackedFromBlack = this->board->GetFromBlackAttackedFields();

    uint64_t white = this->board->GetWhite();
    uint64_t black = this->board->GetBlack();

    ranking = ranking + 40 * popcount(attackedFromWhite & white);

    ranking = ranking - 40 * popcount(attackedFromBlack & black);

    return ranking;
}

int MoveAlgorithms::PawnsInCenter(COLOR player, int fullMoveNumber)
{

    int ranking = 0;

    uint64_t midFields = 0b0001100000011000<<24;

    uint64_t pawns = this->board->GetPawns();

    uint64_t white = this->board->GetWhite();
    uint64_t black = this->board->GetBlack();

    ranking = ranking + 80 * popcount(pawns & midFields & white);
    ranking = ranking - 80 * popcount(pawns & midFields & black);

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


    ranking = ranking + 40 * popcount(pawns & white & whiteAttacked);

    ranking = ranking - 40 * popcount(pawns & black & blackAttacked);

    return ranking;
}

