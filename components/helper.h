#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

#ifndef CONSTANTBITBOARDS
#define CONSTANTBITBOARDS

const uint64_t StartBoardBlack = std::stoull(
    "11111111"
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t StartBoardWhite = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "11111111",
    nullptr, 2);

const uint64_t StartBoardPawns = std::stoull(
    "00000000"
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "00000000",
    nullptr, 2);

const uint64_t StartBoardRooks = std::stoull(
    "10000001"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "10000001",
    nullptr, 2);

const uint64_t StartBoardKnights = std::stoull(
    "01000010"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "01000010",
    nullptr, 2);

const uint64_t StartBoardBishops = std::stoull(
    "00100100"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00100100",
    nullptr, 2);

const uint64_t StartBoardKings = std::stoull(
    "00001000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00001000",
    nullptr, 2);

const uint64_t StartBoardQueens = std::stoull(
    "00010000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00010000",
    nullptr, 2);

const uint64_t BoardRow8 = std::stoull(
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow7 = std::stoull(
    "00000000"
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow6 = std::stoull(
    "00000000"
    "00000000"
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow5 = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow4 = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow3 = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "00000000"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow2 = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "00000000",
    nullptr, 2);

const uint64_t BoardRow1 = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111",
    nullptr, 2);

const uint64_t BoardColumnA = std::stoull(
    "10000000"
    "10000000"
    "10000000"
    "10000000"
    "10000000"
    "10000000"
    "10000000"
    "10000000",
    nullptr, 2);

const uint64_t BoardColumnB = std::stoull(
    "01000000"
    "01000000"
    "01000000"
    "01000000"
    "01000000"
    "01000000"
    "01000000"
    "01000000",
    nullptr, 2);

const uint64_t BoardColumnC = std::stoull(
    "00100000"
    "00100000"
    "00100000"
    "00100000"
    "00100000"
    "00100000"
    "00100000"
    "00100000",
    nullptr, 2);

const uint64_t BoardColumnD = std::stoull(
    "00010000"
    "00010000"
    "00010000"
    "00010000"
    "00010000"
    "00010000"
    "00010000"
    "00010000",
    nullptr, 2);

const uint64_t BoardColumnE = std::stoull(
    "00001000"
    "00001000"
    "00001000"
    "00001000"
    "00001000"
    "00001000"
    "00001000"
    "00001000",
    nullptr, 2);

const uint64_t BoardColumnF = std::stoull(
    "00000100"
    "00000100"
    "00000100"
    "00000100"
    "00000100"
    "00000100"
    "00000100"
    "00000100",
    nullptr, 2);

const uint64_t BoardColumnG = std::stoull(
    "00000010"
    "00000010"
    "00000010"
    "00000010"
    "00000010"
    "00000010"
    "00000010"
    "00000010",
    nullptr, 2);

const uint64_t BoardColumnH = std::stoull(
    "00000001"
    "00000001"
    "00000001"
    "00000001"
    "00000001"
    "00000001"
    "00000001"
    "00000001",
    nullptr, 2);

const uint64_t KingWinPosition = std::stoull(
    "00000000"
    "00000000"
    "00000000"
    "00011000"
    "00011000"
    "00000000"
    "00000000"
    "00000000",
    nullptr, 2);

uint64_t GetRowFromIndex(int index);

uint64_t GetColumnFromIndex(int index);

std::string GetColumnLetterFromIndex(int index);

std::string StringMultiply(std::string src, unsigned int times);

std::string Uint64ToString(uint64_t board);

std::string Uint32ToString(uint32_t board);

std::string Uint16ToString(uint16_t board);

std::string Uint8ToString(uint8_t board);

#define PLAYER bool
#define WHITE false
#define BLACK true

#define MAX_MOVES (8 * 8 * 16)

typedef uint64_t BOARD;
typedef uint16_t MOVE;
typedef MOVE MOVE_ARRAY[MAX_MOVES];

#define CAPTURE 0b1000000000000000U
#define CASTLING 0b0100000000000000U
#define UPGRADE_ROOK 0b1100000000000000U
#define UPGRADE_KNIGHT 0b1101000000000000U
#define UPGRADE_BISHOP 0b1110000000000000U
#define UPGRADE_QUEEN 0b1111000000000000U

#define MOVE_FLAGS 0b1111000000000000U
#define MOVE_TO 0b0000000000111111U
#define MOVE_TO_X 0b0000000000000111U
#define MOVE_TO_Y 0b0000000000111000U
#define MOVE_FROM 0b0000111111000000U
#define MOVE_FROM_X 0b0000000111000000U
#define MOVE_FROM_Y 0b0000111000000000U

bool GetCapture(MOVE move);

bool GetCastling(MOVE move);

bool GetUpgradeRook(MOVE move);

bool GetUpgradeKnight(MOVE move);

bool GetUpgradeBishop(MOVE move);

bool GetUpgradeQueen(MOVE move);

 uint8_t GetToX(MOVE move);

 uint8_t GetToY(MOVE move);

 uint8_t GetFromX(MOVE move);

 uint8_t GetFromY(MOVE move);

 uint8_t FieldIndex(uint8_t x, uint8_t y);

 BOARD SingleBitBoard(uint8_t x, uint8_t y);

 BOARD GetSingleBitBoardTo(MOVE move);

 BOARD GetSingleBitBoardFrom(MOVE move);

 void PrintMove(MOVE move);

 MOVE CreateMove(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags);

 MOVE_ARRAY *NewMoveArray();

 bool InBounds(uint8_t x, uint8_t y);

 void AddMoveSlidingPiece(MOVE_ARRAY *moves, BOARD *attackedFieldsOwn, BOARD enemyKind, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags);

 void AddMove(MOVE_ARRAY *moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags);

 bool TryAddMove(MOVE_ARRAY *moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 bool TryAddMoveNoCapture(MOVE_ARRAY *moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 bool TryAddMoveOnlyCapture(MOVE_ARRAY *moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 void TryAddMoveNoCaptureUpgrade(MOVE_ARRAY *moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 void TryAddMoveOnlyCaptureUpgrade(MOVE_ARRAY *moves, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 bool TryAddMoveKing(MOVE_ARRAY *moves, BOARD *attackedFieldsOwn, BOARD attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 bool TryAddMoveNoCaptureKing(MOVE_ARRAY *moves, BOARD *attackedFieldsOwn, BOARD attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 bool TryAddMoveOnlyCaptureKing(MOVE_ARRAY *moves, BOARD *attackedFieldsOwn, BOARD attackedFieldsEnemy, BOARD allPieces, BOARD currentColor, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

 void AddMoveKing(MOVE_ARRAY *moves, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, uint16_t flags);

// #define GET_CAPTURE(M) (((M)&CAPTURE) && !((M)&(CAPTURE >> 1)))
// #define GET_CASTLING(M) (((M)&CASTLING) && !((M)&(CASTLING << 1)))
// #define GET_UPGRADE_ROOK(M) !(((M) >> 12) & 0b11 )
// #define GET_UPGRADE_KNIGHT(M) bool(((M)&0b0001000000000000U) & ~(((M)&0010000000000000U) >> 1))
// #define GET_UPGRADE_BISHOP(M) bool(((M)&0b0010000000000000U) & ~((M)&0b0001000000000000U) << 1)
// #define GET_UPGRADE_QUEEN(M) !(((M) >> 12) ^ 0b11)
// #define GET_MOVE_TO_X(M) (7 - ((M)&MOVE_TO_X))
// #define GET_MOVE_TO_Y(M) (((M)&MOVE_TO_Y) >> 3)
// #define GET_MOVE_FROM_X(M) (7 - (((M)&MOVE_FROM_X) >> 6))
// #define GET_MOVE_FROM_Y(M) (((M)&MOVE_FROM_Y) >> 9)

// #define GET_SINGLE_BIT_BOARD_TO(M) SINGLE_BIT_BOARD(GET_MOVE_TO_X(M), GET_MOVE_TO_Y(M))
// #define GET_SINGLE_BIT_BOARD_FROM(M) SINGLE_BIT_BOARD(GET_MOVE_FROM_X(M), GET_MOVE_FROM_Y(M))
// #define PRINT_MOVE(M) std::cout << "FROM: X:" << GET_MOVE_FROM_X(M) << " Y:" << GET_MOVE_FROM_Y(M) \
//                                 << " TO: X:" << GET_MOVE_TO_X(M) << " Y:" << GET_MOVE_TO_Y(M)      \
//                                 << " FLAGS:" << ((M & 0b1111000000000000) >> 12) << std::endl;

// #define NEW_MOVE_ARRAY(VARNAME) \
//     MOVE_ARRAY VARNAME;         \
//     VARNAME[0] = 1;

// #define FIELD_INDEX(X, Y) (((Y) << 3) | (7 - (X)))

// #define SINGLE_BIT_BOARD(X, Y) (1ULL << (FIELD_INDEX(X, Y)))

// #define CREATE_MOVE(X_FROM, Y_FROM, X_TO, Y_TO, FLAGS) \
//     (MOVE)(FLAGS | (FIELD_INDEX(X_FROM, Y_FROM) << 6) | FIELD_INDEX(X_TO, Y_TO))

// #define IF_IN_BOUNDS(X, Y, DO)                      \
//     if ((X) < 8 && (Y) < 8 && (X) >= 0 && (Y) >= 0) \
//     {                                               \
//         DO;                                          \
//     }

// #define ADD_MOVE_SLIDING_PIECE(MOVES, ATTACKEDFIELDSOWN, ENEMYKING, X_FROM, Y_FROM, X_TO, Y_TO, FLAGS) \
//     ATTACKEDFIELDSOWN |= SINGLE_BIT_BOARD(X_TO, Y_TO)                   ;                      \
//     MOVES[MOVES[0]] = (CREATE_MOVE(X_FROM, Y_FROM, X_TO, Y_TO, FLAGS)); \
//     MOVES[0] = MOVES[0] + 1;

// #define ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, FLAGS) \
//     MOVES[MOVES[0]] = (CREATE_MOVE(X_FROM, Y_FROM, X_TO, Y_TO, FLAGS)); \
//     MOVES[0] = MOVES[0] + 1;

// #define TRY_ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     TRY_ADD_MOVE_NO_CAPTURE(MOVES, ATTACKEDFIELDSOWN, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     TRY_ADD_MOVE_ONLY_CAPTURE(MOVES, ATTACKEDFIELDSOWN, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO)

// #define TRY_ADD_MOVE_NO_CAPTURE(MOVES, ATTACKEDFIELDSOWN, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     IF_IN_BOUNDS(                                                                             \
//         X_TO, Y_TO,                                                                                                         \
//         if (SINGLE_BIT_BOARD(X_TO, Y_TO) & ~ALL_PIECES){                                      \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, 0)})

// #define TRY_ADD_MOVE_ONLY_CAPTURE(MOVES, ATTACKEDFIELDSOWN, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     IF_IN_BOUNDS(                                                                               \
//         X_TO, Y_TO,                                                                             \
//         if (SINGLE_BIT_BOARD(X_TO, Y_TO) & ~CURRENT_COLOR & ALL_PIECES){                        \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE)})

// #define TRY_ADD_MOVE_UPGRADE(MOVES, ATTACKEDFIELDSOWN, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     IF_IN_BOUNDS(                                                                          \
//         X_TO, Y_TO,                                                                         \
//         if (SINGLE_BIT_BOARD(X_TO, Y_TO) & ~CURRENT_COLOR) { \
//             if (Y_TO % 7 < 2) \
//         { \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE | UPGRADE_ROOK); \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE | UPGRADE_KNIGHT); \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE | UPGRADE_BISHOP); \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE | UPGRADE_QUEEN); \
//         } \
//         else \
//         { \
//             ADD_MOVE(MOVES, ATTACKEDFIELDSOWN, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE); \
//         } })


// // Operations for King

// #define TRY_ADD_MOVE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO)  \
//     TRY_ADD_MOVE_NO_CAPTURE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     TRY_ADD_MOVE_ONLY_CAPTURE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY,ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO)

// #define TRY_ADD_MOVE_NO_CAPTURE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     IF_IN_BOUNDS(                                                                                                                          \
//         X_TO, Y_TO,                                                                                                                        \
//         ATTACKEDFIELDSOWN |= SINGLE_BIT_BOARD(X_TO, Y_TO);                                                                                 \
//         if (~ATTACKEDFIELDSENEMY & SINGLE_BIT_BOARD(X_TO, Y_TO) & ~ALL_PIECES){                                      \
//             ADD_MOVE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, X_FROM, Y_FROM, X_TO, Y_TO, 0)})

// #define TRY_ADD_MOVE_ONLY_CAPTURE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, ALL_PIECES, CURRENT_COLOR, X_FROM, Y_FROM, X_TO, Y_TO) \
//     IF_IN_BOUNDS(                                                                               \
//         X_TO, Y_TO,                                                                             \
//         ATTACKEDFIELDSOWN |= SINGLE_BIT_BOARD(X_TO, Y_TO);\
//         if (~ATTACKEDFIELDSENEMY & SINGLE_BIT_BOARD(X_TO, Y_TO) & ~CURRENT_COLOR & ALL_PIECES){                        \
//             ADD_MOVE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, X_FROM, Y_FROM, X_TO, Y_TO, CAPTURE)})

// #define ADD_MOVE_KING(MOVES, ATTACKEDFIELDSOWN, ATTACKEDFIELDSENEMY, X_FROM, Y_FROM, X_TO, Y_TO, FLAGS) \
//     MOVES[MOVES[0]] = (CREATE_MOVE(X_FROM, Y_FROM, X_TO, Y_TO, FLAGS)); \
//     MOVES[0] = MOVES[0] + 1;

#define H1 (1ULL)
#define G1 (1ULL << 1)
#define F1 (1ULL << 2)
#define E1 (1ULL << 3)
#define D1 (1ULL << 4)
#define C1 (1ULL << 5)
#define B1 (1ULL << 6)
#define A1 (1ULL << 7)
#define H2 (1ULL << 8)
#define G2 (1ULL << 9)
#define F2 (1ULL << 10)
#define E2 (1ULL << 11)
#define D2 (1ULL << 12)
#define C2 (1ULL << 13)
#define B2 (1ULL << 14)
#define A2 (1ULL << 15)
#define H3 (1ULL << 16)
#define G3 (1ULL << 17)
#define F3 (1ULL << 18)
#define E3 (1ULL << 19)
#define D3 (1ULL << 20)
#define C3 (1ULL << 21)
#define B3 (1ULL << 22)
#define A3 (1ULL << 23)
#define H4 (1ULL << 24)
#define G4 (1ULL << 25)
#define F4 (1ULL << 26)
#define E4 (1ULL << 27)
#define D4 (1ULL << 28)
#define C4 (1ULL << 29)
#define B4 (1ULL << 30)
#define A4 (1ULL << 31)
#define H5 (1ULL << 32)
#define G5 (1ULL << 33)
#define F5 (1ULL << 34)
#define E5 (1ULL << 35)
#define D5 (1ULL << 36)
#define C5 (1ULL << 37)
#define B5 (1ULL << 38)
#define A5 (1ULL << 39)
#define H6 (1ULL << 40)
#define G6 (1ULL << 41)
#define F6 (1ULL << 42)
#define E6 (1ULL << 43)
#define D6 (1ULL << 44)
#define C6 (1ULL << 45)
#define B6 (1ULL << 46)
#define A6 (1ULL << 47)
#define H7 (1ULL << 48)
#define G7 (1ULL << 49)
#define F7 (1ULL << 50)
#define E7 (1ULL << 51)
#define D7 (1ULL << 52)
#define C7 (1ULL << 53)
#define B7 (1ULL << 54)
#define A7 (1ULL << 55)
#define H8 (1ULL << 56)
#define G8 (1ULL << 57)
#define F8 (1ULL << 58)
#define E8 (1ULL << 59)
#define D8 (1ULL << 60)
#define C8 (1ULL << 61)
#define B8 (1ULL << 62)
#define A8 (1ULL << 63)

#endif // CONSTANTBITBOARDS