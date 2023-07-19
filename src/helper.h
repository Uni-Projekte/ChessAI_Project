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



#define MAX_MOVES (8 * 8 * 8)

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
    int exactScore;
    int lowerBound;
    int upperBound;
};


std::string MoveForGameServer(MOVE move);

COLOR opponent(COLOR color);

inline PIECE GetCapture(MOVE move);

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