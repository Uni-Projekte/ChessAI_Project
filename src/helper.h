#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

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

char GetColumnLetterFromIndex(int index);

std::string StringMultiply(std::string src, unsigned int times);

std::string Uint64ToString(uint64_t board);

std::string Uint32ToString(uint32_t board);

std::string Uint16ToString(uint16_t board);

std::string Uint8ToString(uint8_t board);



#define MAX_MOVES (8 * 8 * 16)

typedef uint64_t BOARD;
// Capture (or Upgrade) | Castling (or Upgrade) | Upgrade | Upgrade | FROM_YYY | FROM_XXX | TO_YYY | TO_XXX
typedef unsigned int MOVE;
typedef MOVE MOVE_ARRAY[MAX_MOVES];

enum COLOR {
    WHITE,
    BLACK
};

enum PIECE {
    NO_PIECE,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
};


#define UPGRADE_FLAGS 0b111U << 12
#define CAPTURE_FLAGS 0b111U << 15
#define MOVE_TO 0b0000000000111111U
#define MOVE_TO_X 0b0000000000000111U
#define MOVE_TO_Y 0b0000000000111000U
#define MOVE_FROM 0b0000111111000000U
#define MOVE_FROM_X 0b0000000111000000U
#define MOVE_FROM_Y 0b0000111000000000U

// #define CAPTURE 0b1000000000000000U
#define UPGRADE_ROOK    ROOK << 12
#define UPGRADE_KNIGHT  KNIGHT << 12
#define UPGRADE_BISHOP  BISHOP << 12
#define UPGRADE_QUEEN   QUEEN << 12
#define CAPTURE_PAWN    PAWN << 15
#define CAPTURE_ROOK    ROOK << 15
#define CAPTURE_KNIGHT  KNIGHT << 15
#define CAPTURE_BISHOP  BISHOP << 15
#define CAPTURE_QUEEN   QUEEN << 15
#define EN_PASSANTE     1U << 18
#define CASTLING        1U << 19

enum FlagEntry {
    EXACT,
    LOWERBOUND,
    UPPERBOUND
};

// Define a type for the transposition table entry
struct TranspositionEntry {
    int depth;
    int alpha;
    int beta;
    MOVE bestMoveAlpha;
    MOVE bestMoveBeta;
};

struct TranspositionEntryNegamax {
    int depth;
    int value;
    FlagEntry flag;
    MOVE bestMove;
};

COLOR opponent(COLOR color);

inline PIECE GetCapture(MOVE move);

std::string MoveForGameServer(MOVE move);

inline bool GetMoveEnPassante(MOVE move);

inline bool GetCastling(MOVE move);

inline bool GetUpgradeRook(MOVE move);

inline bool GetUpgradeKnight(MOVE move);

inline bool GetUpgradeBishop(MOVE move);

inline bool GetUpgradeQueen(MOVE move);

inline uint8_t GetToX(MOVE move);

inline uint8_t GetToY(MOVE move);

inline uint8_t GetFromX(MOVE move);

inline uint8_t GetFromY(MOVE move);

uint8_t FieldIndex(uint8_t x, uint8_t y);

BOARD SingleBitBoard(uint8_t x, uint8_t y);

inline BOARD GetSingleBitBoardTo(MOVE move)
{
    return 1ULL << (move & MOVE_TO);
}

inline BOARD GetSingleBitBoardFrom(MOVE move)
{
    return 1ULL << ((move & MOVE_FROM) >> 6);
}

void PrintMove(MOVE move);

MOVE CreateMove(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo, int flags);

bool InBounds(uint8_t x, uint8_t y);

void showDifference(const std::unordered_set<int>& set1, const std::unordered_set<int>& set2);

uint8_t SingleBitboardToPosition(BOARD board);

uint8_t GetDirection(uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo);

std::string MoveToString(MOVE move);

#define NEW_MOVE_ARRAY(VARNAME) \
    MOVE_ARRAY VARNAME;         \
    VARNAME[0] = 1;

#define FIELD_H1 (1ULL)
#define FIELD_G1 (1ULL << 1)
#define FIELD_F1 (1ULL << 2)
#define FIELD_E1 (1ULL << 3)
#define FIELD_D1 (1ULL << 4)
#define FIELD_C1 (1ULL << 5)
#define FIELD_B1 (1ULL << 6)
#define FIELD_A1 (1ULL << 7)
#define FIELD_H2 (1ULL << 8)
#define FIELD_G2 (1ULL << 9)
#define FIELD_F2 (1ULL << 10)
#define FIELD_E2 (1ULL << 11)
#define FIELD_D2 (1ULL << 12)
#define FIELD_C2 (1ULL << 13)
#define FIELD_B2 (1ULL << 14)
#define FIELD_A2 (1ULL << 15)
#define FIELD_H3 (1ULL << 16)
#define FIELD_G3 (1ULL << 17)
#define FIELD_F3 (1ULL << 18)
#define FIELD_E3 (1ULL << 19)
#define FIELD_D3 (1ULL << 20)
#define FIELD_C3 (1ULL << 21)
#define FIELD_B3 (1ULL << 22)
#define FIELD_A3 (1ULL << 23)
#define FIELD_H4 (1ULL << 24)
#define FIELD_G4 (1ULL << 25)
#define FIELD_F4 (1ULL << 26)
#define FIELD_E4 (1ULL << 27)
#define FIELD_D4 (1ULL << 28)
#define FIELD_C4 (1ULL << 29)
#define FIELD_B4 (1ULL << 30)
#define FIELD_A4 (1ULL << 31)
#define FIELD_H5 (1ULL << 32)
#define FIELD_G5 (1ULL << 33)
#define FIELD_F5 (1ULL << 34)
#define FIELD_E5 (1ULL << 35)
#define FIELD_D5 (1ULL << 36)
#define FIELD_C5 (1ULL << 37)
#define FIELD_B5 (1ULL << 38)
#define FIELD_A5 (1ULL << 39)
#define FIELD_H6 (1ULL << 40)
#define FIELD_G6 (1ULL << 41)
#define FIELD_F6 (1ULL << 42)
#define FIELD_E6 (1ULL << 43)
#define FIELD_D6 (1ULL << 44)
#define FIELD_C6 (1ULL << 45)
#define FIELD_B6 (1ULL << 46)
#define FIELD_A6 (1ULL << 47)
#define FIELD_H7 (1ULL << 48)
#define FIELD_G7 (1ULL << 49)
#define FIELD_F7 (1ULL << 50)
#define FIELD_E7 (1ULL << 51)
#define FIELD_D7 (1ULL << 52)
#define FIELD_C7 (1ULL << 53)
#define FIELD_B7 (1ULL << 54)
#define FIELD_A7 (1ULL << 55)
#define FIELD_H8 (1ULL << 56)
#define FIELD_G8 (1ULL << 57)
#define FIELD_F8 (1ULL << 58)
#define FIELD_E8 (1ULL << 59)
#define FIELD_D8 (1ULL << 60)
#define FIELD_C8 (1ULL << 61)
#define FIELD_B8 (1ULL << 62)
#define FIELD_A8 (1ULL << 63)

#endif // CONSTANTBITBOARDS