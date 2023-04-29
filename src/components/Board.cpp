// Board.cpp - implementation file for the Board class
#include "Board.h"
#include <stdexcept>
#include <utility>

using namespace std;

// Constructor that initializes the chessboard to the standard starting position
Board::Board(){
    // Initialize bitboards to standard starting position
    this->black = 0xffff000000000000;
    this->white = 0xffff;
    this->pawns = 0x00ff00000000ff00;
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
    this->black = 0;
	this->white = 0;
	this->pawns = 0;
	this->kings = 0;
	this->queens = 0;
	this->towers = 0;
	this->bishops = 0;
	this->knights = 0;

    this->fromFEN(std::move(fen));
}

/**
 * @brief get bitboard of black pawns
 * @return bitboard of black pawns as uint64_t
 */
uint64_t Board::GetBlackPawns() const {
    return this->black & this->pawns;
}

/**
 * @brief get bitboard of black queen
 * @return bitboard of black queen as uint64_t
 */
uint64_t Board::GetBlackQueen() const {
    return this->black & this->queens;
}

/**
 * @brief get bitboard of black king
 * @return bitboard of black king as uint64_t
 */
uint64_t Board::GetBlackKing() const {
    return this->black & this->kings;
}

/**
 * @brief get bitboard of black bishops
 * @return bitboard of black bishops as uint64_t
 */
uint64_t Board::GetBlackBishops() const {
    return this->black & this->bishops;
}

/**
 * @brief get bitboard of black knights
 * @return bitboard of black knights as uint64_t
 */
uint64_t Board::GetBlackKnights() const {
    return this->black & this->knights;
}

/**
 * @brief get bitboard of black towers
 * @return bitboard of black towers as uint64_t
 */
uint64_t Board::GetBlackTowers() const {
    return this->black & this->towers;
}

/**
 * @brief get bitboard of white pawns
 * @return bitboard of white pawns as uint64_t
 */
uint64_t Board::GetWhitePawns() const {
    return this->white & this->pawns;
}

/**
 * @brief get bitboard of white queen
 * @return bitboard of white queen as uint64_t
 */
uint64_t Board::GetWhiteQueen() const {
    return this->white & this->queens;
}

/**
 * @brief get bitboard of white king
 * @return bitboard of white king as uint64_t
 */
uint64_t Board::GetWhiteKing() const {
    return this->white & this->kings;
}

/**
 * @brief get bitboard of white bishops
 * @return bitboard of white bishops as uint64_t
 */
uint64_t Board::GetWhiteBishops() const {
    return this->white & this->bishops;
}

/**
 * @brief get bitboard of white knights
 * @return bitboard of white knights as uint64_t
 */
uint64_t Board::GetWhiteKnights() const {
    return this->white & this->knights;
}

/**
 * @brief get bitboard of white towers
 * @return bitboard of white towers as uint64_t
 */
uint64_t Board::GetWhiteTowers() const {
    return this->white & this->towers;
}

/**
 * @brief convert the chessboard into a string
 * @return string representation of the chessboard
 */
string Board::ToString() const {
    string board[64];
    string output = "";

    const uint64_t rowBlackKing = GetBlackKing() & 0xf * 1;
    const uint64_t columnBlackKing = GetBlackKing() % 2;

    for (int i = 0; i < 64; i++) {
        output = output + board[i];
    }
    return output;
}

/**
 * @brief Converts a FEN string to a chessboard
 * @param fen FEN string representing the chessboard
 */
void Board::fromFEN(string fen)
{

    size_t position = 0;
    string delimiter = "/";
    vector<string> rows;

    // split fen strings into the rows
    while ((position = fen.find(delimiter)) != string::npos) {
        rows.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }

    if (((position = fen.find(" ")) != string::npos)) {
        rows.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }
    else
    {
        rows.push_back(fen);
    }

    // split the remaining part of the fen string into individual tokens
    delimiter = " ";
    vector<string> info;
    while ((position = fen.find(delimiter)) != string::npos) {
        info.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }
    info.push_back(fen);

    // convert fen rows to board
    int col = 0;

    // loop through each row on the chessboard
    for (int row = 0; row < 8; ++row)
    {
        col = 0;

        // loop through each character in the row of the FEN string
        for (auto& piece : rows[row])
        {
            // if the character represents a number, it means empty squares on the board
            if (isdigit(piece))
            {
				col += piece - '0'; // move the column pointer by the number of empty squares
            }
            else // the character represents a piece on the board
            {
                // get the color and piece variable of the current piece
                uint64_t* color = this->getColor(piece);
                uint64_t* pieces = getPiece(piece);

                // if the piece type is invalid, the FEN string is invalid
                if (pieces == NULL) {
                    throw std::invalid_argument("Invalid FEN string. Piece type not recognized.");
                }

                // chessboard rows start from bottom, opposite of the FEN string
                int row_on_board = 7 - row;
                // calculate the bit mask of the square on the board for the current piece
                uint64_t mask = 1ULL << ((row_on_board * 8) + (7 - col));
                // set the bit in both the color and piece bitboards
                *color |= mask;
                *pieces |= mask;
                ++col; // move the column pointer
            }
        }

		// if the column pointer is not at the end of the row, the FEN string is invalid
        if (col != 8) {
            throw std::invalid_argument("Invalid FEN string. Not enough columns in row.");
        }
    }
}


/**
 * @brief Returns a pointer to the corresponding piece bitboard
 *        based on the provided piece character
 * @param piece Character representing a chess piece
 * @return Pointer to the corresponding piece bitboard
 *         or NULL if piece character is not recognized
 */
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

/**
 * @brief Returns the color bitboard for a given piece
 * @param piece Piece in question
 * @return Color bitboard
 */
uint64_t* Board::getColor(char piece)
{
    if (isupper(piece)) {
        return &this->white;
    }
    else {
        return &this->black;
    }
}
