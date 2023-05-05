#include <stdexcept>
#include <string>

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
    nullptr,2);

const uint64_t StartBoardWhite = std::stoull(
    "00000000"
    "11111111"
    "00000000"
    "00000000"
    "00000000"
    "00000000"
    "11111111"
    "00000000",
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

const uint64_t StartBoardTowers = std::stoull(
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

uint64_t GetRowFromIndex(int index);

uint64_t GetColumnFromIndex(int index);

std::string GetColumnLetterFromIndex(int index);

std::string StringMultiply(std::string src, unsigned int times);

std::string Uint64ToString(uint64_t board);

std::string Uint32ToString(uint32_t board);

std::string Uint16ToString(uint16_t board);

std::string Uint8ToString(uint8_t board);

#endif //CONSTANTBITBOARDS