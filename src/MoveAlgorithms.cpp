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
    this->killerMoves = std::unordered_map<uint64_t , std::vector<MOVE> >();
    this->historyMoves = std::unordered_map<uint64_t , std::tuple<uint8_t, MOVE> >();
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
    int multiplierPiC = max(1,(3 - this->board->GetFullMoveNumber())*300);
    int pawnsInCenter   = this->PawnsInCenter(player, this->board->GetFullMoveNumber()) * multiplierPiC;
    int kingDistanceToCenter = this->KingDistanceToCenter();

    return ((int) ( materialWorth + attackedFields + pawnFileCounts + defence + pawnStructure + pawnsInCenter + kingDistanceToCenter));
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

/*int MoveAlgorithms::QuiescenceSearch(int searchDepth,
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
}*/

MOVE MoveAlgorithms::NegamaxIterative(MOVE_ARRAY moves, int maxTime, bool usePVS, COLOR player)
{
    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    int searchDepth = 1;
    MOVE result;
    int countStates = 0;


    int64_t end;
    uint64_t boardKey = 0;
    std::tuple<uint8_t, MOVE> historyMove;
    boardKey = this->keyGenerator->CalculateZobristKey(this->board);

    this->historyMoves.insert({boardKey, std::tuple<uint8_t, MOVE> {0, 0}});
    while (searchDepth <= 4)
    {
        this->Negamax(searchDepth, moves, countStates, INT_MIN + 1, INT_MAX-1, &result, player, true);

        boardKey = this->keyGenerator->CalculateZobristKey(this->board);

        historyMove = this->historyMoves.find(boardKey)->second;

        if (std::get<0>(historyMove) > searchDepth) {
            historyMove = std::tuple<uint8_t, MOVE> {searchDepth, result};
        }


        searchDepth = searchDepth + 1;
        end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();

        std::cout << std::endl;

        if (end - start > maxTime)
        {
            break;
        }

        std::cout << "Time:" << end - start << std::endl;
        std::cout <<  "States: "<< countStates<< std::endl;
        std::cout << "Max Time:" << maxTime << std::endl;

        std::cout << "time is over iterations to depth:" << searchDepth << std::endl;
    }

    this->Negamax(5, moves, countStates, INT_MIN + 1, INT_MAX-1, &result, player, true);

    boardKey = this->keyGenerator->CalculateZobristKey(this->board);
    historyMove = this->historyMoves.find(boardKey)->second;

    if (std::get<0>(historyMove) > searchDepth) {
        historyMove = std::tuple<uint8_t, MOVE> {searchDepth, result};
    }

    std::cout << "Time:" << end - start << std::endl;
    std::cout <<  "States: "<< countStates<< std::endl;
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
        COLOR player,
        bool root)
{
    states += 1;
    if (this->board->IsCheckmate(player))
    {
        return INT_MIN + 1;
    }
    if (searchDepth <= 0)
    {
        return (-2 * player + 1) * BoardRanking(player);
    }

    std::unordered_map<uint64_t, TranspositionEntry>::iterator entryA;
    uint64_t boardKey = 0;

    if (this->useTranspositionTable) {
        entryA = this->transpositionTable->find(boardKey);

        if (entryA != this->transpositionTable->end() && entryA->second.depth >= searchDepth) {
            TranspositionEntry &entry = entryA->second;
            boardKey = this->keyGenerator->CalculateZobristKey(this->board);
            // Check if we have a stored exact score
            if (entry.exactScore != 0) {
                return entry.exactScore;
            }

            // Check if we have a stored lower bound
            if (entry.lowerBound >= beta) {
                return entry.lowerBound; // Return the stored lower bound (beta cutoff)
            }

            // Check if we have a stored upper bound
            if (entry.upperBound <= alpha) {
                return entry.upperBound; // Return the stored upper bound (alpha cutoff)
            }

            // Update alpha and beta bounds with the stored values
            alpha = std::max(alpha, entry.lowerBound);
            beta = std::min(beta, entry.upperBound);
        }
    }
    int best = INT_MIN + 1;
    bool pvNode = (beta - alpha > 1); // Check if this is a PV (Principal Variation) node

    Board oldBoard(this->board);

    // Aspiration window search (first move)
    if (pvNode && moves[1] != 0)
    {
        this->board->DoMove(moves[1]); // do move with index 1
        NEW_MOVE_ARRAY(nextMoves);    // allocate memory for next moves
        sortMoves(nextMoves);
        this->board->GetMoves(nextMoves); // get all moves
        int val = -Negamax(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player), false);
        best = std::max(best, val);
        alpha = std::max(alpha, best);

        if (this->copyUndo)
        {
            *this->board = oldBoard;
        }

        if (!root && (val <= alpha || val >= beta)) // Check if aspiration window failed
        {
            // Perform a full window search with regular PVS
            val = -Negamax(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player), false);
            best = std::max(best, val);
            alpha = std::max(alpha, best);
        }
    }

    // Regular search (remaining moves)
    for (int i = 2; i < moves[0]; i++)
    {
        this->board->DoMove(moves[i]); // do move with index i
        NEW_MOVE_ARRAY(nextMoves);    // allocate memory for next moves
        sortMoves(nextMoves);
        this->board->GetMoves(nextMoves); // get all moves

        // Null window search
        int val = -Negamax(searchDepth - 1, nextMoves, states, -alpha - 1, -alpha, NULL, opponent(player), false);
        if (val > alpha && val < beta)
        {
            // If within the window, perform a full window search
            val = -Negamax(searchDepth - 1, nextMoves, states, -beta, -alpha, NULL, opponent(player), false);
        }

        if (val > best && result != NULL)
        {
            *result = moves[i];
        }
        best = std::max(best, val);
        alpha = std::max(alpha, best);

        if (this->copyUndo)
        {
            *this->board = oldBoard;
        }

        if (beta <= alpha)
        {
            if(boardKey == 0){
                boardKey = this->keyGenerator->CalculateZobristKey(this->board);;
            }
            if(this->killerMoves.find(boardKey) == this->killerMoves.end()){
                this->killerMoves.insert(std::pair<uint64_t, std::vector<MOVE>>(boardKey, std::vector<MOVE>()));
            }

            this->killerMoves.find(boardKey)->second.push_back(moves[i]);
        }
    }

    if (this->useTranspositionTable)
    {
        if (entryA == this->transpositionTable->end()) {
            boardKey = this->keyGenerator->CalculateZobristKey(this->board);
            // Entry not found in the table, create a new one
            TranspositionEntry newEntry{};
            newEntry.depth = searchDepth;

            // Update bounds and exact score
            if (best <= alpha) {
                newEntry.upperBound = best;
            } else if (best >= beta) {
                newEntry.lowerBound = best;
            } else {
                newEntry.exactScore = best;
                newEntry.lowerBound = best;
                newEntry.upperBound = best;
            }

            this->transpositionTable->insert({boardKey, newEntry});
        } else {
            // Update the existing entry with new bounds and exact score
            entryA->second.depth = searchDepth;

            if (best <= alpha) {
                entryA->second.upperBound = best;
            } else if (best >= beta) {
                entryA->second.lowerBound = best;
            } else {
                entryA->second.exactScore = best;
                entryA->second.lowerBound = best;
                entryA->second.upperBound = best;
            }
        }
    }

    return best;
}

int MoveAlgorithms::MaterialWorthWithoutPawns()
{
    int ranking = 0;

    ranking = ranking + kingValue   * popcount(this->board->GetWhiteKing());
    ranking = ranking + queenValue  * popcount(this->board->GetWhiteQueen());
    ranking = ranking + rookValue   * popcount(this->board->GetWhiteRooks());
    ranking = ranking + bishopValue * popcount(this->board->GetWhiteBishops());
    ranking = ranking + knightValue * popcount(this->board->GetWhiteKnights());
    ranking = ranking - kingValue   * popcount(this->board->GetBlackKing());
    ranking = ranking - queenValue  * popcount(this->board->GetBlackQueen());
    ranking = ranking - rookValue   * popcount(this->board->GetBlackRooks());
    ranking = ranking - bishopValue * popcount(this->board->GetBlackBishops());
    ranking = ranking - knightValue * popcount(this->board->GetBlackKnights());

    return ranking;
}

int MoveAlgorithms::MaterialWorth()
{
    int ranking = MaterialWorthWithoutPawns();

    ranking = ranking + pawnValue   * popcount(this->board->GetWhitePawns());
    ranking = ranking - pawnValue   * popcount(this->board->GetBlackPawns());

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

    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnA) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnB) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnC) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnD) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnE) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnF) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnG) - 1, 0));
    ranking = ranking - 40 * (max(popcount(whitePawns & BoardColumnH) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnA) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnB) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnC) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnD) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnE) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnF) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnG) - 1, 0));
    ranking = ranking + 40 * (max(popcount(blackPawns & BoardColumnH) - 1, 0));

    return ranking;
}

int MoveAlgorithms::Defense()
{
    int ranking = 0;

    uint64_t attackedFromWhite = this->board->GetFromWhiteAttackedFields();
    uint64_t attackedFromBlack = this->board->GetFromBlackAttackedFields();

    uint64_t white = this->board->GetWhite();
    uint64_t black = this->board->GetBlack();

    ranking = ranking + 60 * popcount(attackedFromWhite & white);

    ranking = ranking - 60 * popcount(attackedFromBlack & black);

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

int MoveAlgorithms::KingDistanceToCenter(){
    uint8_t posBlackKing = SingleBitboardToPosition(this->board->GetBlackKing());
    uint8_t posWhiteKing = SingleBitboardToPosition(this->board->GetWhiteKing());

    uint8_t posBlackKingX = (posBlackKing & 0b111000 >> 3);
    uint8_t posBlackKingY = (posBlackKing & 0b111);

    uint8_t posWhiteKingX = (posWhiteKing & 0b111000 >> 3);
    uint8_t posWhiteKingY = (posWhiteKing & 0b111);

    double blackKingDistanceUpperLeft = sqrt(pow(posBlackKingX - 3, 2) + pow(posBlackKingY - 4, 2));
    double blackKingDistanceUpperRight = sqrt(pow(posBlackKingX - 4, 2) + pow(posBlackKingY - 4, 2));
    double blackKingDistanceLowerLeft = sqrt(pow(posBlackKingX - 3, 2) + pow(posBlackKingY - 3, 2));
    double blackKingDistanceLowerRight = sqrt(pow(posBlackKingX - 4, 2) + pow(posBlackKingY - 3, 2));

    double whiteKingDistanceUpperLeft = sqrt(pow(posWhiteKingX - 3, 2) + pow(posWhiteKingY - 4, 2));
    double whiteKingDistanceUpperRight = sqrt(pow(posWhiteKingX - 4, 2) + pow(posWhiteKingY - 4, 2));
    double whiteKingDistanceLowerLeft = sqrt(pow(posWhiteKingX - 3, 2) + pow(posWhiteKingY - 3, 2));
    double whiteKingDistanceLowerRight = sqrt(pow(posWhiteKingX - 4, 2) + pow(posWhiteKingY - 3, 2));

    double blackKingDistance = std::min({blackKingDistanceUpperLeft, blackKingDistanceUpperRight, blackKingDistanceLowerLeft, blackKingDistanceLowerRight});
    double whiteKingDistance = std::min({whiteKingDistanceUpperLeft, whiteKingDistanceUpperRight, whiteKingDistanceLowerLeft, whiteKingDistanceLowerRight});

    int ranking = (int) (100 * (whiteKingDistance - blackKingDistance));

}

int MoveAlgorithms::KingSafety(){
    int amountPinnedBlackPieces = std::popcount(this->board->GetBlackPinnedPieces());
    int amountPinnedWhitePieces = std::popcount(this->board->GetWhitePinnedPieces());
    return 50 * (amountPinnedBlackPieces - amountPinnedWhitePieces);
}


void MoveAlgorithms::sortMoves(MOVE_ARRAY moves)
{
    int pointerSorted = 1;
    uint64_t zobristKey = this->keyGenerator->CalculateZobristKey(this->board);
    if(this->killerMoves.find(zobristKey) == this->killerMoves.end()){
        this->killerMoves.insert(std::pair<uint64_t, std::vector<MOVE>>(zobristKey, std::vector<MOVE>()));
    }
    std::vector<MOVE> kMoves = this->killerMoves.find(zobristKey)->second;
    bool useHistory = true;
    if(this->historyMoves.find(zobristKey) == this->historyMoves.end()){
        this->historyMoves.insert(std::pair<uint64_t, std::tuple<int, MOVE>>(zobristKey, std::tuple<int, MOVE>(0, 0)));
        useHistory = false;
    }
    std::tuple<int, MOVE> hMoves = this->historyMoves.find(zobristKey)->second;

    for(int i = 1; i < moves[0]; i++){
        if(std::find(kMoves.begin(), kMoves.end(), moves[i]) != kMoves.end()
                || (useHistory && std::get<1>(hMoves) == moves[i])){
            MOVE temp = moves[pointerSorted];
            moves[pointerSorted] = moves[i];
            moves[i] = temp;
            pointerSorted++;
        }
    }
}



