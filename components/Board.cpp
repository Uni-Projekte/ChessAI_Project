// Board.cpp - implementation file for the Board class
#include "Board.h"
#include <stdexcept>
#include <utility>

using namespace std;

/**
 * @brief create new standard board
 * @param loader: standard start configuration
 * @return new complete bit-board-collection
 */
Board::Board(BitBoardLoader &loader)
{
    this->black = loader.GetBlack();
    this->white = loader.GetWhite();
    this->bishops = loader.GetBishops();
    this->queens = loader.GetQueens();
    this->towers = loader.GetTowers();
    this->pawns = loader.GetPawns();
    this->kings = loader.GetKings();
    this->knights = loader.GetKnights();
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
 * @brief check if player's piece is on position with row and column
 * @param player: bit-board (white or black)
 * @param piece: bit-board (one of kings/queens/bishops/towers/knights/pawns)
 * @param row: bit-board (from 1-8)
 * @param column: bit-board (from a-h)
 * @return 0 (false) or >0 (true)
 */
uint64_t Board::IsOnField(uint64_t player, uint64_t piece, uint64_t row, uint64_t column)
{
    return player & piece & row & column;
}

/**
 * @brief multiply string
 * @param src: string to multiply
 * @param times: number of multiplication
 * @return new string src x times
 */
string stringMultiply(string src, unsigned int times)
{
    string out = "";
    for (int i = 0; i < times; i++)
    {
        out = out + src;
    }
    return out;
}

/**
 * @brief generate string representation of the board
 * @param loader: access to constant boards needed
 * @return new string string representation of the board
 */
string Board::ToString(BitBoardLoader &loader)
{
    string board[64];
    string output = "";

    int maxWidth = 0;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            int i = ((7 - r) << 3) + c;
            if (this->IsOnField(this->white, this->kings, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("WKING");
            }
            if (this->IsOnField(this->white, this->queens, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("WQUEEN");
            }
            if (this->IsOnField(this->white, this->pawns, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("WPAWN");
            }
            if (this->IsOnField(this->white, this->towers, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("WTOWER");
            }
            if (this->IsOnField(this->white, this->knights, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("WKNIGHT");
            }
            if (this->IsOnField(this->white, this->bishops, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("WBISHOP");
            }
            if (this->IsOnField(this->black, this->kings, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("BKING");
            }
            if (this->IsOnField(this->black, this->queens, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("BQUEEN");
            }
            if (this->IsOnField(this->black, this->pawns, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("BPAWN");
            }
            if (this->IsOnField(this->black, this->towers, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("BTOWER");
            }
            if (this->IsOnField(this->black, this->knights, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("BKNIGHT");
            }
            if (this->IsOnField(this->black, this->bishops, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("BBISHOP");
            }
            if (board[i].length() > maxWidth)
            {
                maxWidth = board[i].length();
            }
        }
    }

    string line = stringMultiply("-", maxWidth + 2);
    output = output + " +" + stringMultiply(line + "+", 7) + line + "+\r\n";
    for (int r = 0; r < 7; r++)
    {
        output = output + std::to_string((7 - r) + 1);
        for (int c = 0; c < 8; c++)
        {

            output = output + "| ";
            output = output + stringMultiply(" ", (maxWidth - board[(r << 3) + c].length()) / 2);
            output = output + board[(r << 3) + c];
            output = output + stringMultiply(" ", (maxWidth - board[(r << 3) + c].length() + 1) / 2);
            output = output + " ";
        }
        output = output + "|\r\n";

        output = output + " +" + stringMultiply(line + "+", 7) + line + "+\r\n";
    }
    output = output + "1";
    for (int c = 0; c < 8; c++)
    {
        output = output + "| ";
        output = output + stringMultiply(" ", (maxWidth - board[(7 << 3) + c].length()) / 2);
        output = output + board[(7 << 3) + c];
        output = output + stringMultiply(" ", (maxWidth - board[(7 << 3) + c].length() + 1) / 2);
        output = output + " ";
    }
    output = output + "|\r\n";
    output = output + " +" + stringMultiply(line + "+", 7) + line + "+\r\n";
    output = output + " ";
    for (int c = 0; c < 8; c++)
    {
        output = output + stringMultiply(" ", (maxWidth + 3) / 2);
        output = output + loader.GetColumnLetterFromIndex(c);
        output = output + stringMultiply(" ", (maxWidth + 2) / 2);
    }
    output = output + " \r\n";
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
