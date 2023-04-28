//
// Created by Mateusz Pawelczyk on 28.04.2023.
//

#include "Board.h"
#include <stdexcept>

Board::Board(){
    this->black = 0xff;
    this->white = 0xff000000;
    this->pawns = 0x0f0000f0;
    size_t pos = 0;
    this->bishops = stoull(
            "00100100"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00100100",&pos, 2);
    this->kings =stoull(
            "00001000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00001000",&pos, 2);
    this->queens = stoull(
            "00010000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00010000",&pos, 2);
    this->towers = stoull(
            "10000001"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "10000001",&pos, 2);
    this->bishops = stoull(
            "00100100"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00100100",&pos, 2);
    this->knights = stoull(
            "01000010"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "00000000"
            "01000010",&pos, 2);
}

Board::Board(std::string fen) {
    size_t position = 0;
    string delimiter = "/";

    vector<string> tokens;

    while ((position = fen.find(delimiter)) != string::npos) {
        tokens.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }
    tokens.push_back(fen);
}

/**
 * @brief get black pawns
 * @return bitboard of black pawns as uint64_t
 */
uint64_t Board::GetBlackPawns() {
    return this->black & this->pawns;
}

/**
 * @brief get black queen
 * @return bitboard of black queen as uint64_t
 */
uint64_t Board::GetBlackQueen() {
    return this->black & this->queens;
}

/**
 * @brief get black king
 * @return bitset of black pawns as uint64_t
 */
uint64_t Board::GetBlackKing() {
    return this->black & this->kings;
}

uint64_t Board::GetBlackBishops() {
    return this->black & this->bishops;
}

uint64_t Board::GetBlackKnights() {
    return this->black & this->knights;
}

uint64_t Board::GetBlackTowers() {
    return this->black & this->towers;
}

uint64_t Board::GetWhitePawns() {
    return this->black & this->pawns;
}

uint64_t Board::GetWhiteQueen() {
    return this->black & this->queens;
}

uint64_t Board::GetWhiteKing() {
    return this->black & this->kings;
}

uint64_t Board::GetWhiteBishops() {
    return this->black & this->bishops;
}

uint64_t Board::GetWhiteKnights() {
    return this->black & this->knights;
}

uint64_t Board::GetWhiteTowers() {
    return this->black & this->towers;
}

string Board::ToString() {
    string board[64];
    string output = "";

    const uint64_t rowBlackKing = GetBlackKing() & 0xf * 1;
    const uint64_t columnBlackKing = GetBlackKing() % 2;

    for (int i = 0; i < 64; i++) {
        output = output + board[i];
    }
}

/**
 * @brief Converts FEN string to board
 * @param fen FEN string
 * @return Board
 */
string Board::fromFEN(string fen)
{
    size_t position = 0;
    string delimiter = "/";

    vector<string> rows;

    // split fen strings into the rows
    while ((position = fen.find(delimiter)) != string::npos) {
        rows.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }
    rows.push_back(fen);

    // convert fen rows to board
    int col = 0;

    for (int row = 0; row < 8; ++row)
    {
        for (auto &piece : rows[row])
        {
            if (isdigit(piece))
            {
                col += piece - '0';
            }
            else
            {
                uint64_t *color = getColor(piece);
                uint64_t *pieces = getPiece(piece);

                if (pieces == NULL) {
                    throw std::invalid_argument("Invalid FEN string");
                }

                uint64_t mask = 1ULL << ((row * 8) + col);
                *color |= mask;
                *pieces |= 1ULL << mask;
            }
        }

        if (col != 8) {
            throw std::invalid_argument("Invalid FEN string");
        }
    }
}

uint64_t* Board::getPiece(char piece) {
    piece = tolower(piece);
    switch (piece) {
        case 'p':
            return &this->pawns;
        case 'q':
            return &this->queens;
        case 'k':
            return &this->kings;
        case 'b':
            return &this->bishops;
        case 'n':
            return &this->knights;
        case 'r':
            return &this->towers;
        default:
            return NULL;
    }
}

uint64_t* Board::getColor(char piece)
{
    if (isupper(piece)) {
        return &this->white;
    } else {
        return &this->black;
    }
}