// Board.cpp - implementation file for the Board class
#include "Board.h"
#include <stdexcept>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include "presenter.h"
#include <chrono>

using namespace std;

/**
 * @brief create new standard board
 * @param loader: standard start configuration
 * @return new complete bit-board-collection
 */
Board::Board()
{
    this->black = StartBoardBlack;
    this->white = StartBoardWhite;
    this->attackedFromWhite = 0;
    this->attackedFromBlack = 0;
    this->pinnedWhitePieces = 0;
    this->pinnedBlackPieces = 0;
    this->bishops = StartBoardBishops;
    this->queens = StartBoardQueens;
    this->rooks = StartBoardRooks;
    this->pawns = StartBoardPawns;
    this->kings = StartBoardKings;
    this->knights = StartBoardKnights;
    this->move_rights = 0b11110000;
    this->en_passant = 0b00000000;
    this->halfmove_clock = 0;
    this->fullmove_number = 1;
}

Board::Board(std::unordered_map<uint64_t , TranspositionEntry> *transpositionTable, ZobristKeyGenerator *keyGenerator)
{
    this->transpositionTable = transpositionTable;
    this->keyGenerator = keyGenerator;
    this->black = StartBoardBlack;
    this->white = StartBoardWhite;
    this->attackedFromWhite = 0;
    this->attackedFromBlack = 0;
    this->pinnedWhitePieces = 0;
    this->pinnedBlackPieces = 0;
    this->bishops = StartBoardBishops;
    this->queens = StartBoardQueens;
    this->rooks = StartBoardRooks;
    this->pawns = StartBoardPawns;
    this->kings = StartBoardKings;
    this->knights = StartBoardKnights;
    this->move_rights = 0b11110000;
    this->en_passant = 0b00000000;
    this->halfmove_clock = 0;
    this->fullmove_number = 1;
}

Board::Board(Board *board)
{
    this->transpositionTable = board->transpositionTable;
    this->keyGenerator = board->keyGenerator;
    this->black = board->black;
    this->white = board->white;
    this->attackedFromWhite = board->attackedFromWhite;
    this->attackedFromBlack = board->attackedFromBlack;
    this->pinnedWhitePieces = board->pinnedWhitePieces;
    this->pinnedBlackPieces = board->pinnedBlackPieces;
    this->bishops = board->bishops;
    this->queens = board->queens;
    this->rooks = board->rooks;
    this->pawns = board->pawns;
    this->kings = board->kings;
    this->knights = board->knights;
    this->move_rights = board->move_rights;
    this->en_passant = board->en_passant;
    this->halfmove_clock = board->halfmove_clock;
    this->fullmove_number = board->fullmove_number;
}

Board::Board(std::string fen,std::unordered_map<uint64_t , TranspositionEntry> *transpositionTable, ZobristKeyGenerator *keyGenerator)
{
    this->transpositionTable = transpositionTable;
    this->keyGenerator = keyGenerator;
    this->black = 0;
    this->white = 0;
    this->attackedFromWhite = 0;
    this->attackedFromBlack = 0;
    this->pinnedWhitePieces = 0;
    this->pinnedBlackPieces = 0;
    this->pawns = 0;
    this->kings = 0;
    this->queens = 0;
    this->rooks = 0;
    this->bishops = 0;
    this->knights = 0;
    this->move_rights = 0b00000000;
    this->en_passant = 0b00000000;
    this->halfmove_clock = 0;
    this->fullmove_number = 1;

    this->fromFEN(std::move(fen));
}

Board::Board(std::string fen)
{
    this->black = 0;
    this->white = 0;
    this->attackedFromWhite = 0;
    this->attackedFromBlack = 0;
    this->pinnedWhitePieces = 0;
    this->pinnedBlackPieces = 0;
    this->pawns = 0;
    this->kings = 0;
    this->queens = 0;
    this->rooks = 0;
    this->bishops = 0;
    this->knights = 0;
    this->move_rights = 0b00000000;
    this->en_passant = 0b00000000;
    this->halfmove_clock = 0;
    this->fullmove_number = 1;

    this->fromFEN(std::move(fen));
}

uint8_t Board::GetEnPassant() const
{
    return this->en_passant;
}

uint8_t Board::GetMoveRights() const
{
    return this->move_rights;
}

uint8_t Board::GetHalfMoveClock() const
{
    return this->halfmove_clock;
}

uint16_t Board::GetFullMoveNumber() const
{
    return this->fullmove_number;
}

uint64_t Board::GetWhite() const
{
    return this->white;
}

uint64_t Board::GetBlack() const
{
    return this->black;
}

uint64_t Board::GetKings() const
{
    return this->kings;
}

uint64_t Board::GetQueens() const
{
    return this->queens;
}

uint64_t Board::GetBishops() const
{
    return this->bishops;
}

uint64_t Board::GetKnights() const
{
    return this->knights;
}

uint64_t Board::GetRooks() const
{
    return this->rooks;
}

uint64_t Board::GetPawns() const
{
    return this->pawns;
}

/**
 * @brief Get the bitboard of all pieces
 * @return new complete bit-board-collection
 */
uint64_t Board::GetAllPieces() const
{
    return this->black | this->white;
}

/**
 * @brief Get the bitboard of all white pieces
 * @return new complete bit-board-collection
 */
uint64_t Board::GetWhitePieces() const
{
    return this->white;
}

/**
 * @brief Get the bitboard of all black pieces
 * @return new complete bit-board-collection
 */
uint64_t Board::GetBlackPieces() const
{
    return this->black;
}

/**
 * @brief get bitboard of black pawns
 * @return bitboard of black pawns as uint64_t
 */
uint64_t Board::GetBlackPawns() const
{
    return this->black & this->pawns;
}

/**
 * @brief get bitboard of black queen
 * @return bitboard of black queen as uint64_t
 */
uint64_t Board::GetBlackQueen() const
{
    return this->black & this->queens;
}

/**
 * @brief get bitboard of black king
 * @return bitboard of black king as uint64_t
 */
uint64_t Board::GetBlackKing() const
{
    return this->black & this->kings;
}

/**
 * @brief get bitboard of black bishops
 * @return bitboard of black bishops as uint64_t
 */
uint64_t Board::GetBlackBishops() const
{
    return this->black & this->bishops;
}

/**
 * @brief get bitboard of black knights
 * @return bitboard of black knights as uint64_t
 */
uint64_t Board::GetBlackKnights() const
{
    return this->black & this->knights;
}

/**
 * @brief get bitboard of black rook
 * @return bitboard of black rook as uint64_t
 */
uint64_t Board::GetBlackRooks() const
{
    return this->black & this->rooks;
}

/**
 * @brief get bitboard of white pawns
 * @return bitboard of white pawns as uint64_t
 */
uint64_t Board::GetWhitePawns() const
{
    return this->white & this->pawns;
}

/**
 * @brief get bitboard of white queen
 * @return bitboard of white queen as uint64_t
 */
uint64_t Board::GetWhiteQueen() const
{
    return this->white & this->queens;
}

/**
 * @brief get bitboard of white king
 * @return bitboard of white king as uint64_t
 */
uint64_t Board::GetWhiteKing() const
{
    return this->white & this->kings;
}

/**
 * @brief get bitboard of white bishops
 * @return bitboard of white bishops as uint64_t
 */
uint64_t Board::GetWhiteBishops() const
{
    return this->white & this->bishops;
}

/**
 * @brief get bitboard of white knights
 * @return bitboard of white knights as uint64_t
 */
uint64_t Board::GetWhiteKnights() const
{
    return this->white & this->knights;
}

/**
 * @brief get bitboard of white rook
 * @return bitboard of white rook as uint64_t
 */
uint64_t Board::GetWhiteRooks() const
{
    return this->white & this->rooks;
}

/**
 * @brief
 * @return bitboard of white rook as uint64_t
 */
uint64_t &Board::GetFromWhiteAttackedFields()
{
    return this->attackedFromWhite;
}

/**
 * @brief get bitboard of white rook
 * @return bitboard of white rook as uint64_t
 */
uint64_t &Board::GetFromBlackAttackedFields()
{
    return this->attackedFromBlack;
}

/**
 * @brief check if player's piece is on position with row and column
 * @param player: bit-board (white or black)
 * @param piece: bit-board (one of kings/queens/bishops/rook/knights/pawns)
 * @param row: bit-board (from 1-8)
 * @param column: bit-board (from a-h)
 * @return 0 (false) or >0 (true)
 */
uint64_t Board::IsOnField(uint64_t player, uint64_t piece, uint64_t row, uint64_t column)
{
    return player & piece & row & column;
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
    while ((position = fen.find(delimiter)) != string::npos)
    {
        rows.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }

    if (((position = fen.find(" ")) != string::npos))
    {
        rows.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }
    else
    {
        throw std::invalid_argument("Invalid FEN string. Missing board information.");
    }

    // split the remaining part of the fen string into individual tokens
    delimiter = " ";
    vector<string> info;
    while ((position = fen.find(delimiter)) != string::npos)
    {
        info.push_back(fen.substr(0, position));
        fen.erase(0, position + delimiter.length());
    }
    info.push_back(fen);

    // store all the information about the board

    // store the castling rights
    if (info[0] == "w")
    {
        this->move_rights &= 0b11111110;
    }
    else if (info[0] == "b")
    {
        this->move_rights |= 0b00000001;
    }
    else
    {
        throw std::invalid_argument("Invalid FEN string. Missing turn information.");
    }

    if (info[1] == "-")
    {
        this->move_rights &= 0b00000001;
    }
    else
    {
        for (auto &c : info[1])
        {
            switch (c)
            {
            case 'K':
                this->move_rights |= 0b10000000;
                break;
            case 'Q':
                this->move_rights |= 0b01000000;
                break;
            case 'k':
                this->move_rights |= 0b00100000;
                break;
            case 'q':
                this->move_rights |= 0b00010000;
                break;
            default:
                throw std::invalid_argument("Invalid FEN string. Invalid castling rights.");
            }
        }
    }

    // store the en passant square
    if (info[2] == "-")
    {
        this->en_passant = 0;
    }
    else
    {
        // check if the en passant square position is valid
        if (info[2].length() != 2)
        {
            throw std::invalid_argument("Invalid FEN string. Invalid en passant square.");
        }
        else
        {
            int row = info[2][1] - '0';
            int col = 7 - (info[2][0] - 'a');

            if (row < 1 || row > 8 || col < 0 || col > 8)
            {
                throw std::invalid_argument("Invalid FEN string. Invalid en passant square.");
            }
            else
            {
                if (move_rights & 1)
                {
                    this->en_passant = 0b00000000 | (row << 3) | col;
                }
                else
                {
                    this->en_passant = 0b10000000 | (row << 3) | col;
                }
            }
        }
    }

    // store the halfmove clock
    this->halfmove_clock = stoi(info[3]);

    // store the fullmove number
    this->fullmove_number = stoi(info[4]);

    // convert fen rows to board
    int col = 0;

    // loop through each row on the chessboard
    for (int row = 0; row < 8; ++row)
    {
        col = 0;

        // loop through each character in the row of the FEN string
        for (auto &piece : rows[row])
        {
            // if the character represents a number, it means empty squares on the board
            if (isdigit(piece))
            {
                col += piece - '0'; // move the column pointer by the number of empty squares
            }
            else // the character represents a piece on the board
            {
                // get the color and piece variable of the current piece
                uint64_t *color = this->getColor(piece);
                uint64_t *pieces = getPiece(piece);

                // if the piece type is invalid, the FEN string is invalid
                if (pieces == NULL)
                {
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
        if (col != 8)
        {
            throw std::invalid_argument("Invalid FEN string. Not enough columns in row.");
        }
    }
}

/**
 * @brief Returns a FEN string representation of the current board
 * @details The FEN string is a standard notation for describing a chess position.
 *          For more information, see https://de.wikipedia.org/wiki/Forsyth-Edwards-Notation
 * @return FEN string representation of the current board
 */
string Board::toFEN()
{
    string fen = "";
    int emptyCounter = 0;
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 7; j >= 0; --j)
        {
            uint64_t pos = 1ULL << (i * 8 + j);

            if (pos & this->white)
            {
                if (emptyCounter > 0)
                {
                    fen += to_string(emptyCounter);
                    emptyCounter = 0;
                }
                if (pos & this->pawns)
                {
                    fen.push_back('P');
                }
                else if (pos & this->queens)
                {
                    fen.push_back('Q');
                }
                else if (pos & this->kings)
                {
                    fen.push_back('K');
                }
                else if (pos & this->bishops)
                {
                    fen.push_back('B');
                }
                else if (pos & this->knights)
                {
                    fen.push_back('N');
                }
                else if (pos & this->rooks)
                {
                    fen.push_back('R');
                }
            }
            else if (pos & this->black)
            {
                if (emptyCounter > 0)
                {
                    fen += to_string(emptyCounter);
                    emptyCounter = 0;
                }
                if (pos & this->pawns)
                {
                    fen.push_back('p');
                }
                else if (pos & this->queens)
                {
                    fen.push_back('q');
                }
                else if (pos & this->kings)
                {
                    fen.push_back('k');
                }
                else if (pos & this->bishops)
                {
                    fen.push_back('b');
                }
                else if (pos & this->knights)
                {
                    fen.push_back('n');
                }
                else if (pos & this->rooks)
                {
                    fen.push_back('r');
                }
            }
            else
            {
                ++emptyCounter;
            }
            if (emptyCounter > 0 && j == 0)
            {
                fen += to_string(emptyCounter);
                emptyCounter = 0;
            }
            if (j == 0 && i != 0)
            {

                fen.push_back('/');
            }
        }
    }

    fen.push_back(' ');
    if (this->move_rights & 1)
    {
        fen.push_back('b');
    }
    else
    {
        fen.push_back('w');
    }

    fen.push_back(' ');

    if (this->move_rights & 0b10000000)
    {
        fen.push_back('K');
    }
    if (this->move_rights & 0b01000000)
    {
        fen.push_back('Q');
    }
    if (this->move_rights & 0b00100000)
    {
        fen.push_back('k');
    }
    if (this->move_rights & 0b00010000)
    {
        fen.push_back('q');
    }
    if (!(this->move_rights & 0b11110000))
    {
        fen.push_back('-');
    }

    fen.push_back(' ');
    // cout << (int)this->en_passant << endl;
    if ((this->en_passant & 0b10000000) && (this->en_passant & 0b01000000))
    {
        fen.push_back('a' + (7 - (this->en_passant & 0b00000111)));
        fen.push_back('3');
    }
    else if ((this->en_passant & 0b10000000) && !(this->en_passant & 0b01000000))
    {
        fen.push_back('a' + (7 - (this->en_passant & 0b00000111)));
        fen.push_back('6');
    }
    else
    {
        fen.push_back('-');
    }

    fen.push_back(' ');

    string to_s = std::to_string(this->halfmove_clock);

    for (auto &c : to_s)
    {
        fen.push_back(c);
    }

    fen.push_back(' ');

    to_s = std::to_string(this->fullmove_number);

    for (auto &c : to_s)
    {
        fen.push_back(c);
    }

    return fen;
}

/**
 * @brief Returns a pointer to the corresponding piece bitboard
 *        based on the provided piece character
 * @param piece Character representing a chess piece
 * @return Pointer to the corresponding piece bitboard
 *         or NULL if piece character is not recognized
 */
uint64_t *Board::getPiece(char piece)
{
    piece = tolower(piece);
    switch (piece)
    {
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
        return &this->rooks;
    default:
        return NULL;
    }
}

/**
 * @brief Returns the color bitboard for a given piece
 * @param piece Piece in question
 * @return Color bitboard
 */
uint64_t *Board::getColor(char piece)
{
    if (isupper(piece))
    {
        return &this->white;
    }
    else
    {
        return &this->black;
    }
}

/**
 * @brief Returns the position of a piece on the board
 * @param position Position of the piece in algebraic notation
 * @return Position of the piece on the board as a integer
 */
uint8_t Board::GetPosition(string position) const
{
    uint8_t col = position[0] - 'a';
    uint8_t row = position[1] - '1';

    return (col << 3) | row;
}

#define WHITE_KING_SIDE 0b00000010U
#define WHITE_QUEEN_SIDE 0b00100000U
#define BLACK_KING_SIDE (WHITE_KING_SIDE << 56ULL)
#define BLACK_QUEEN_SIDE (WHITE_QUEEN_SIDE << 56ULL)
#define MOVE_X_MASK 0b00111000U
#define MOVE_Y_MASK 0b00000111U
#define NO_WHITE_CASTLING 0b00111111U
#define NO_BLACK_CASTLING 0b11001111U
#define BLACK_KINGSIDE_TOWER (1ULL << 56ULL)
#define BLACK_QUEENSIDE_TOWER (1ULL << 63ULL)
#define WHITE_KINGSIDE_TOWER (1ULL)
#define WHITE_QUEENSIDE_TOWER (1ULL << 7ULL)
#define BLACK_KINGSIDE_TOWER_AFTER (1ULL << 58ULL)
#define BLACK_QUEENSIDE_TOWER_AFTER (1ULL << 60ULL)
#define WHITE_KINGSIDE_TOWER_AFTER (1ULL << 3ULL)
#define WHITE_QUEENSIDE_TOWER_AFTER (1ULL << 4ULL)
#define ROW_1_AND_8 0xff000000000000ffULL
#define NOT_ROW_1_AND_8 0x00ffffffffffff00ULL
#include <bitset>
#include <bit>

void Board::DoMove(MOVE move)
{

    const BOARD from = GetSingleBitBoardFrom(move);
    const BOARD to = GetSingleBitBoardTo(move);
    const bool capture = GetCapture(move);
    const bool castling = GetCastling(move);
    const BOARD allPieces = this->white | this->black;
    const BOARD white = this->white;
    const BOARD black = this->black;
    const BOARD pawns = this->pawns;
    const BOARD bishops = this->bishops;
    const BOARD queens = this->queens;
    const BOARD kings = this->kings;
    const BOARD rook = this->rooks;
    const BOARD knights = this->knights;

    // change player turn (x xor 1 = !x)
    this->move_rights = this->move_rights ^ 0b1U;

    // disable white castling when king moved
    this->move_rights = this->move_rights & (NO_WHITE_CASTLING | (!bool(white & this->kings & from) << 6) | (!bool(white & this->kings & from) << 7));
    // disable black castling when king moved
    this->move_rights = this->move_rights & (NO_BLACK_CASTLING | (!bool(black & this->kings & from) << 4) | (!bool(black & this->kings & from) << 5));

    // disable white kingside castling when white kingside-tower moved
    this->move_rights = this->move_rights & ~(bool(white & this->rooks & from & WHITE_KINGSIDE_TOWER) << 7);
    // disable white queenside castling when white queenside-tower moved
    this->move_rights = this->move_rights & ~(bool(white & this->rooks & from & WHITE_QUEENSIDE_TOWER) << 6);
    // disable black kingside castling when black kingside-tower moved
    this->move_rights = this->move_rights & ~(bool(black & this->rooks & from & BLACK_KINGSIDE_TOWER) << 5);
    // disable black queenside castling when black queenside-tower moved
    this->move_rights = this->move_rights & ~(bool(black & this->rooks & from & BLACK_QUEENSIDE_TOWER) << 4);

    // delete moved tower old pos when castling
    this->rooks = this->rooks & ~(BLACK_KINGSIDE_TOWER * ((to & BLACK_KING_SIDE) && castling)); // ~(((to & BLACK_KING_SIDE) & (castling << 57)));
    this->rooks = this->rooks & ~(BLACK_QUEENSIDE_TOWER * ((to & BLACK_QUEEN_SIDE) && castling));
    this->rooks = this->rooks & ~(WHITE_KINGSIDE_TOWER * ((to & WHITE_KING_SIDE) && castling));
    this->rooks = this->rooks & ~(WHITE_QUEENSIDE_TOWER * ((to & WHITE_QUEEN_SIDE) && castling));
    this->white = this->white & ~(BLACK_KINGSIDE_TOWER * ((to & BLACK_KING_SIDE) && castling));
    this->white = this->white & ~(BLACK_QUEENSIDE_TOWER * ((to & BLACK_QUEEN_SIDE) && castling));
    this->white = this->white & ~(WHITE_KINGSIDE_TOWER * ((to & WHITE_KING_SIDE) && castling));
    this->white = this->white & ~(WHITE_QUEENSIDE_TOWER * ((to & WHITE_QUEEN_SIDE) && castling));
    this->black = this->black & ~(BLACK_KINGSIDE_TOWER * ((to & BLACK_KING_SIDE) && castling));
    this->black = this->black & ~(BLACK_QUEENSIDE_TOWER * ((to & BLACK_QUEEN_SIDE) && castling));
    this->black = this->black & ~(WHITE_KINGSIDE_TOWER * ((to & WHITE_KING_SIDE) && castling));
    this->black = this->black & ~(WHITE_QUEENSIDE_TOWER * ((to & WHITE_QUEEN_SIDE) && castling));
    // add moved tower new pos when castling
    this->rooks = this->rooks | (BLACK_KINGSIDE_TOWER_AFTER * ((to & BLACK_KING_SIDE) && castling));
    this->rooks = this->rooks | (BLACK_QUEENSIDE_TOWER_AFTER * ((to & BLACK_QUEEN_SIDE) && castling));
    this->rooks = this->rooks | (WHITE_KINGSIDE_TOWER_AFTER * ((to & WHITE_KING_SIDE) && castling));
    this->rooks = this->rooks | (WHITE_QUEENSIDE_TOWER_AFTER * ((to & WHITE_QUEEN_SIDE) && castling));
    this->white = this->white | (BLACK_KINGSIDE_TOWER_AFTER * ((to & BLACK_KING_SIDE) && castling && (from & white)));
    this->white = this->white | (BLACK_QUEENSIDE_TOWER_AFTER * ((to & BLACK_QUEEN_SIDE) && castling && (from & white)));
    this->white = this->white | (WHITE_KINGSIDE_TOWER_AFTER * ((to & WHITE_KING_SIDE) && castling && (from & white)));
    this->white = this->white | (WHITE_QUEENSIDE_TOWER_AFTER * ((to & WHITE_QUEEN_SIDE) && castling && (from & white)));
    this->black = this->black | (BLACK_KINGSIDE_TOWER_AFTER * ((to & BLACK_KING_SIDE) && castling && (from & black)));
    this->black = this->black | (BLACK_QUEENSIDE_TOWER_AFTER * ((to & BLACK_QUEEN_SIDE) && castling && (from & black)));
    this->black = this->black | (WHITE_KINGSIDE_TOWER_AFTER * ((to & WHITE_KING_SIDE) && castling && (from & black)));
    this->black = this->black | (WHITE_QUEENSIDE_TOWER_AFTER * ((to & WHITE_QUEEN_SIDE) && castling && (from & black)));

    // add moved piece new pos
    this->black = this->black | (to * bool(black & from));
    // delete captured piece pos
    this->black = this->black & ~(to * ((capture && (white & from))));
    this->black = this->black & ~((uint64_t)(GetSingleBitBoardTo(this->en_passant) / ((((move & 0b111111) > 31) * 65535 + 1.0) / 256)) * bool((this->en_passant & 0b10000000) && capture)); // delete en passant pawn
    // delete moved piece old pos
    this->black = this->black & ~from;

    this->white = this->white | (to * bool(white & from));
    this->white = this->white & ~(to * ((capture && (black & from))));
    this->white = this->white & ~((uint64_t)(GetSingleBitBoardTo(this->en_passant) / ((((move & 0b111111) > 31) * 65535 + 1.0) / 256)) * bool((this->en_passant & 0b10000000) && capture)); // delete en passant pawn
    this->white = this->white & ~from;

    this->pawns = this->pawns | (to * bool(pawns & from)); // add moved pawn new pos
    this->pawns = this->pawns & ~(to * ((capture && ((allPieces & ~pawns) & from))));
    this->pawns = this->pawns & ~((uint64_t)(GetSingleBitBoardTo(this->en_passant) / ((((move & 0b111111) > 31) * 65535 + 1.0) / 256)) * bool((this->en_passant & 0b10000000) && capture)); // delete en passant pawn
    this->pawns = this->pawns & ~from;
    // cout << "en_passant: " << std::bitset<8>(this->en_passant).to_string() << endl;

    this->bishops = this->bishops | (to * bool(bishops & from));
    this->bishops = this->bishops & ~(to * ((capture && ((allPieces & ~bishops) & from))));
    this->bishops = this->bishops & ~from;

    this->queens = this->queens | (to * bool(queens & from));
    this->queens = this->queens & ~(to * ((capture && ((allPieces & ~queens) & from))));
    this->queens = this->queens & ~from;

    this->kings = this->kings | (to * bool(kings & from));
    this->kings = this->kings & ~(to * ((capture && ((allPieces & ~kings) & from))));
    this->kings = this->kings & ~from;

    this->rooks = this->rooks | (to * bool(rook & from));
    this->rooks = this->rooks & ~(to * ((capture && ((allPieces & ~rook) & from))));
    this->rooks = this->rooks & ~from;

    this->knights = this->knights | (to * bool(knights & from));
    this->knights = this->knights & ~(to * ((capture && ((allPieces & ~knights) & from))));
    this->knights = this->knights & ~from;

    // add half-move clock move every move
    this->halfmove_clock = this->halfmove_clock + 1;
    // reset half-move clock when pawn moved or a piece was captured
    this->halfmove_clock = this->halfmove_clock * !bool((pawns & from) | capture);

    // add full-move when black moved
    this->fullmove_number = this->fullmove_number + bool(black & from);

    // add queen if pawns reached one of the ends
    this->queens = this->queens | ((this->pawns & ROW_1_AND_8) * bool(move & 0b111100000000U == UPGRADE_QUEEN));
    // add knight if pawns reached one of the ends
    this->knights = this->knights | ((this->pawns & ROW_1_AND_8) * bool(move & 0b111100000000U == UPGRADE_KNIGHT));
    // add bishop if pawns reached one of the ends
    this->bishops = this->bishops | ((this->pawns & ROW_1_AND_8) * bool(move & 0b111100000000U == UPGRADE_BISHOP));
    // add rook if pawns reached one of the ends
    this->rooks = this->rooks | ((this->pawns & ROW_1_AND_8) * bool(move & 0b111100000000U == UPGRADE_ROOK));
    // delete pawns that reached one of the ends
    this->pawns = this->pawns & NOT_ROW_1_AND_8;

    // en_passant
    this->en_passant = ((pawns & from) && (to == from << 16 || from == to << 16) && ((((pawns & (to << 1)) && (to != A4 && to != A5)) || ((pawns & (to >> 1)) && (to != H4 && to != H5))))) * (0b10000000 | ((move & 0b111111) + ((((move & 0b111111) > 31) * 2 - 1) * 8)) | (bool(white & from) << 6));

    MarkFields();
}

void Board::MarkFields(){
    if(this->move_rights&1){
        this->pinnedWhitePieces = 0;
        this->attackedFromBlack = 0;
    }
    else{
        this->pinnedBlackPieces = 0;
        this->attackedFromWhite = 0;
    }
    for (uint8_t x = 0; x < 8; x = x + 1)
    {
        for (uint8_t y = 0; y < 8; y = y + 1)
        {
            if (this->move_rights & 1)
            {
                if (this->bishops & this->black & SingleBitBoard(x, y))
                {
                    bishop::markFields(this->attackedFromBlack, this->pinnedWhitePieces, this->kings & this->white, this->white | this->black, this->black, x, y);
                }
                if (this->kings & this->black & SingleBitBoard(x, y))
                {
                    king::markFields(this->attackedFromBlack, x, y);
                }
                if (this->knights & this->black & SingleBitBoard(x, y))
                {
                    knight::markFields(this->attackedFromBlack, x, y);
                }
                if (this->pawns & this->black & SingleBitBoard(x, y))
                {
                    pawn::markFields(this->attackedFromBlack, x, y, true);
                }
                if (this->rooks & this->black & SingleBitBoard(x, y))
                {
                    rook::markFields(this->attackedFromBlack, this->pinnedWhitePieces, this->kings & this->white, this->white | this->black, this->black, x, y);
                }
                if (this->queens & this->black & SingleBitBoard(x, y))
                {
                    queen::markFields(this->attackedFromBlack, this->pinnedWhitePieces, this->kings & this->white, this->white | this->black, this->black, x, y);
                }
            }
            else
            {
                if (this->bishops & this->white & SingleBitBoard(x, y))
                {
                    bishop::markFields(this->attackedFromWhite, this->pinnedBlackPieces, this->kings & this->black, this->white | this->black, this->white, x, y);
                }
                if (this->kings & this->white & SingleBitBoard(x, y))
                {
                    king::markFields(this->attackedFromBlack, x, y);
                }
                if (this->knights & this->white & SingleBitBoard(x, y))
                {
                    knight::markFields(this->attackedFromBlack, x, y);
                }
                if (this->pawns & this->white & SingleBitBoard(x, y))
                {
                    pawn::markFields(this->attackedFromBlack, x, y, 0);
                }
                if (this->rooks & this->white & SingleBitBoard(x, y))
                {
                    rook::markFields(this->attackedFromWhite, this->pinnedBlackPieces, this->kings & this->black, this->white | this->black, this->white, x, y);
                }
                if (this->queens & this->white & SingleBitBoard(x, y))
                {
                    queen::markFields(this->attackedFromWhite, this->pinnedBlackPieces, this->kings & this->black, this->white | this->black, this->white, x, y);
                }
            }
        }
    }
}

void Board::GetMoves(MOVE_ARRAY &moves)
{
    uint8_t whiteKingPostition = SingleBitboardToPosition(this->kings & this->white);
    uint8_t blackKingPostition = SingleBitboardToPosition(this->kings & this->black);

    uint8_t whiteKingX = whiteKingPostition >> 3;
    uint8_t whiteKingY = whiteKingPostition & 0b111;

    uint8_t blackKingX = blackKingPostition >> 3;
    uint8_t blackKingY = blackKingPostition & 0b111;


    for (uint8_t x = 0; x < 8; x = x + 1)
    {
        for (uint8_t y = 0; y < 8; y = y + 1)
        {
            uint8_t direction = 0;
            uint64_t currentField = SingleBitBoard(x, y);
            if (this->move_rights & 1)
            {
                if(currentField & this->pinnedBlackPieces) direction = GetDirection(blackKingX, blackKingY, x, y);
                uint64_t isBlack = this->black & currentField;
                if (this->bishops & isBlack)
                {
                    bishop::possibleMoves(moves, this->black | this->white, this->black, x, y, direction);
                }
                if (this->kings & isBlack)
                {
                    king::possibleMoves(moves, this->move_rights, this->attackedFromWhite, this->black | this->white, this->black, x, y);
                }
                if (this->knights & isBlack)
                {
                    knight::possibleMoves(moves, this->black | this->white, this->black, x, y);
                }
                if (this->pawns & isBlack)
                {
                    pawn::possibleMoves(moves, this->black | this->white, this->black, x, y, BLACK, this->en_passant);
                }
                if (this->rooks & isBlack)
                {
                    rook::possibleMoves(moves, this->black | this->white, this->black, x, y, direction);
                }
                if (this->queens & isBlack)
                {
                    queen::possibleMoves(moves,  this->black | this->white, this->black, x, y, direction);
                }
            }
            else
            {
                uint64_t isWhite = this->white & currentField;
                if(currentField & this->pinnedWhitePieces) direction = GetDirection(whiteKingX, whiteKingY, x, y);
                if (this->bishops & isWhite)
                {
                    bishop::possibleMoves(moves, this->black | this->white, this->white, x, y, direction);
                }
                if (this->kings & isWhite)
                {
                    king::possibleMoves(moves, this->move_rights, this->attackedFromBlack, this->black | this->white, this->white, x, y);
                }
                if (this->knights & isWhite)
                {
                    knight::possibleMoves(moves, this->black | this->white, this->white, x, y);
                }
                if (this->pawns & isWhite)
                {
                    pawn::possibleMoves(moves, this->black | this->white, this->white, x, y, WHITE, this->en_passant);
                }
                if (this->rooks & isWhite)
                {
                    rook::possibleMoves(moves, this->black | this->white, this->white, x, y,direction);
                }
                if (this->queens & isWhite)
                {
                    queen::possibleMoves(moves, this->black | this->white, this->white, x, y, direction);
                }
            }
        }
    }
}

MOVE Board::GetMove()
{
    // std::cout << "NUMBER OF MOVES: " << moves.size() << std::endl;
    // for (int i = 0; i < moves.size()-1; i++) {
    //     std::cout << moves[i] << ", ";
    // }
    // std::cout << moves[moves.size()-1] << std::endl;
    NEW_MOVE_ARRAY(moves);
    this->GetMoves(moves);

    MOVE move = 0;
    if (this->move_rights & 1)
    {
        move = this->AlphaBetaIterative(moves, 1000 , BLACK);
    }
    else
    {
        move = this->AlphaBetaIterative(moves, 1000 , WHITE);
    }
    // std::cout << "PICKED MOVE: " << move << std::endl;
    // std::cout << "FLAGS:" << ((move & 0b1111000000000000U) >> 12) << std::endl;
    // std::cout << "FROM:" << GET_MOVE_FROM_X(move) << ", " << GET_MOVE_FROM_Y(move) << std::endl;
    // std::cout << "TO:" << GET_MOVE_TO_X(move) << ", " << GET_MOVE_TO_Y(move) << std::endl;
    return move;
}

MOVE Board::GetMoveMinMax()
{
    // std::cout << "NUMBER OF MOVES: " << moves.size() << std::endl;
    // for (int i = 0; i < moves.size()-1; i++) {
    //     std::cout << moves[i] << ", ";
    // }
    // std::cout << moves[moves.size()-1] << std::endl;
    NEW_MOVE_ARRAY(moves);
    this->GetMoves(moves);
    MOVE move = 0;
    if (this->move_rights & 1)
    {
        move = this->MiniMaxIterative(moves, 1000, BLACK);
    }
    else
    {
        move = this->MiniMaxIterative(moves, 1000, WHITE);
    }
    // std::cout << "PICKED MOVE: " << move << std::endl;
    // std::cout << "FLAGS:" << ((move & 0b1111000000000000U) >> 12) << std::endl;
    // std::cout << "FROM:" << GET_MOVE_FROM_X(move) << ", " << GET_MOVE_FROM_Y(move) << std::endl;
    // std::cout << "TO:" << GET_MOVE_TO_X(move) << ", " << GET_MOVE_TO_Y(move) << std::endl;
    return move;
}



int Board::MaterialWorth()
{
    int ranking = 0;

    ranking = ranking + 10000 * popcount(this->GetWhiteKing());
    ranking = ranking + 900 * popcount(this->GetWhiteQueen());
    ranking = ranking + 500 * popcount(this->GetWhiteRooks());
    ranking = ranking + 300 * popcount(this->GetWhiteBishops());
    ranking = ranking + 300 * popcount(this->GetWhiteKnights());
    ranking = ranking + 100 * popcount(this->GetWhitePawns());
    ranking = ranking - 10000 * popcount(this->GetBlackKing());
    ranking = ranking - 900 * popcount(this->GetBlackQueen());
    ranking = ranking - 500 * popcount(this->GetBlackRooks());
    ranking = ranking - 300 * popcount(this->GetBlackBishops());
    ranking = ranking - 300 * popcount(this->GetBlackKnights());
    ranking = ranking - 100 * popcount(this->GetBlackPawns());

    return ranking;
}

int Board::AttackedFields()
{
    int ranking = 0;

    ranking = ranking + 10000 * popcount(this->attackedFromWhite & this->GetBlackKing());
    ranking = ranking + 900 * popcount(this->attackedFromWhite & this->GetBlackQueen());
    ranking = ranking + 500 * popcount(this->attackedFromWhite & this->GetBlackRooks());
    ranking = ranking + 300 * popcount(this->attackedFromWhite & this->GetBlackBishops());
    ranking = ranking + 300 * popcount(this->attackedFromWhite & this->GetBlackKnights());
    ranking = ranking + 100 * popcount(this->attackedFromWhite & this->GetBlackPawns());

    ranking = ranking - 10000 * popcount(this->attackedFromBlack & this->GetWhiteKing());
    ranking = ranking - 900 * popcount(this->attackedFromBlack & this->GetWhiteQueen());
    ranking = ranking - 500 * popcount(this->attackedFromBlack & this->GetWhiteRooks());
    ranking = ranking - 300 * popcount(this->attackedFromBlack & this->GetWhiteBishops());
    ranking = ranking - 300 * popcount(this->attackedFromBlack & this->GetWhiteKnights());
    ranking = ranking - 100 * popcount(this->attackedFromBlack & this->GetWhitePawns());

    return ranking;
}

int Board::PawnFileCounts()
{
    int ranking = 0;

    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnA) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnB) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnC) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnD) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnE) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnF) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnG) - 1);
    ranking = ranking - 400 * (popcount(this->GetWhitePawns() & BoardColumnH) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnA) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnB) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnC) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnD) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnE) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnF) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnG) - 1);
    ranking = ranking + 400 * (popcount(this->GetBlackPawns() & BoardColumnH) - 1);

    return ranking;
}

int Board::Defence()
{
    int ranking = 0;

    ranking = ranking + 10000 * popcount(this->attackedFromWhite & this->GetWhiteKing());
    ranking = ranking + 900 * popcount(this->attackedFromWhite & this->GetWhiteQueen());
    ranking = ranking + 500 * popcount(this->attackedFromWhite & this->GetWhiteRooks());
    ranking = ranking + 300 * popcount(this->attackedFromWhite & this->GetWhiteBishops());
    ranking = ranking + 300 * popcount(this->attackedFromWhite & this->GetWhiteKnights());
    ranking = ranking + 100 * popcount(this->attackedFromWhite & this->GetWhitePawns());

    ranking = ranking - 10000 * popcount(this->attackedFromBlack & this->GetBlackKing());
    ranking = ranking - 900 * popcount(this->attackedFromBlack & this->GetBlackQueen());
    ranking = ranking - 500 * popcount(this->attackedFromBlack & this->GetBlackRooks());
    ranking = ranking - 300 * popcount(this->attackedFromBlack & this->GetBlackBishops());
    ranking = ranking - 300 * popcount(this->attackedFromBlack & this->GetBlackKnights());
    ranking = ranking - 100 * popcount(this->attackedFromBlack & this->GetBlackPawns());

    return ranking;
}

int Board::BoardRanking(PLAYER player)
{
    int materialWorth = this->MaterialWorth();
    int attackedFields = this->AttackedFields();
    int pawnFileCounts = this->PawnFileCounts();
    int defence = this->Defence();
    float materialWorthWeight = 0.5;
    return (int) (materialWorth * 0.45 + attackedFields * 0.30 + pawnFileCounts * 0.1 + defence * 0.15);
}

MOVE Board::AlphaBetaIterative(MOVE_ARRAY moves, int maxTime, PLAYER player)
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
        this->AlphaBetaMax(searchDepth, moves, countStates,INT_MIN, INT_MAX, &result, player);
        searchDepth = searchDepth + 1;
        end = std::chrono::duration_cast<std::chrono::milliseconds>(
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

int Board::AlphaBetaMax(
    int searchDepth,
    MOVE_ARRAY moves,
    int &states,
    int alpha,
    int beta,
    MOVE *result,
    PLAYER player)
{
    states += 1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    uint64_t zobristKey = 0;

    if(this->transpositionTable && this->keyGenerator){
        zobristKey = keyGenerator->CalculateZobristKey(this->black,this->white,this->kings,this->queens,this->bishops,
                                                       this->knights,this->rooks,this->pawns);

        // Check if the current position is already evaluated in the transposition table
        auto entryIt = transpositionTable->find(zobristKey);

        if (entryIt != transpositionTable->end() && entryIt->second.depth >= searchDepth) {
            TranspositionEntry& entry = entryIt->second;
            if (entry.score > alpha) {
                alpha = entry.score;
                if (result != NULL) {
                    *result = entry.bestMove;
                }
            }
            if (entry.score >= beta) {
                return entry.score;
            }
        }
    }

    int best = INT_MIN;

    for (int i = 1; i < moves[0]; i++)
    {
        Board copyBoard = Board(this); // copy board, because we have no move undo
        copyBoard.DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        copyBoard.GetMoves(nextMoves);             // get all moves possible
        int val = copyBoard.AlphaBetaMin(searchDepth - 1, nextMoves, states, alpha, beta, NULL, player);
        if (val > best && result != NULL)
        {
            *result = moves[i];
            //std::cout << i << std::endl;
        }
        best = max(best, val);
        alpha = max(alpha, best);

        if (beta <= alpha)
        {
            break;
        }
    }

    if(this->transpositionTable && this->keyGenerator && this->transpositionTable->size() < 30000) {
        TranspositionEntry entry;
        entry.depth = searchDepth;
        entry.score = best;
        entry.bestMove = *result;
        transpositionTable->insert(std::make_pair(zobristKey, entry));
    }

    return best;
}

int Board::AlphaBetaMin(
    int searchDepth,
    MOVE_ARRAY moves,
    int &states,
    int alpha,
    int beta,
    MOVE *result,
    PLAYER player)
{
    states +=1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    uint64_t zobristKey = 0;

    if(this->transpositionTable && this->keyGenerator) {
        // Check if the current position is stored in the transposition table
        uint64_t zobristKey = this->keyGenerator->CalculateZobristKey(this->black, this->white, this->kings,
                                                                      this->queens, this->bishops,
                                                                      this->knights, this->rooks, this->pawns);
        auto entryIt = this->transpositionTable->find(zobristKey);
        if (entryIt != this->transpositionTable->end() && entryIt->second.depth >= searchDepth) {
            TranspositionEntry &entry = entryIt->second;
            if (entry.score < beta) {
                beta = entry.score;
                if (result != NULL) {
                    *result = entry.bestMove;
                }
            }
            if (entry.score <= alpha) {
                return entry.score;
            }
        }
    }

    int best = INT_MAX;

    for (int i = 1; i < moves[0]; i++)
    {
        Board copyBoard = Board(this); // copy board, because we have no move undo
        copyBoard.DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves); // allocate memory for next moves<
        copyBoard.GetMoves(nextMoves); // get all moves possible
        int val = copyBoard.AlphaBetaMax(searchDepth - 1, nextMoves, states, alpha, beta, NULL, player);
        if (val < best && result != NULL)
        {
            *result = moves[i];
            //std::cout << i << std::endl;
        }
        best = min(best, val);
        beta = min(beta, best);

        if (beta <= alpha)
        {
            break;
        }
    }
    if(this->transpositionTable && this->keyGenerator && this->transpositionTable->size() < 30000) {
        TranspositionEntry entry;
        entry.depth = searchDepth;
        entry.score = best;
        entry.bestMove = *result;
        transpositionTable->insert(std::make_pair(zobristKey, entry));
    }

    return best;
}


MOVE Board::MiniMaxIterative(MOVE_ARRAY moves, int maxTime, PLAYER player)
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
        this->MiniMaxMax(searchDepth, moves, countStates,&result, player);
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

int Board::MiniMaxMax(
        int searchDepth,
        MOVE_ARRAY moves,
        int &states,
        MOVE *result,
        PLAYER player)
{
    states +=1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    int best = INT_MIN;

    for (int i = 1; i < moves[0]; i++)
    {
        Board copyBoard = Board(this); // copy board, because we have no move undo
        copyBoard.DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);     // allocate memory for next moves
        copyBoard.GetMoves(nextMoves);             // get all moves possible
        int val = copyBoard.MiniMaxMin(searchDepth - 1, nextMoves, states, NULL, player);
        if (val > best && result != NULL)
        {
            *result = moves[i];
            //std::cout << i << std::endl;
        }
        best = max(best, val);
    }
    return best;
}

int Board::MiniMaxMin(
        int searchDepth,
        MOVE_ARRAY moves,
        int &states,
        MOVE *result,
        PLAYER player)
{
    states+=1;
    if (searchDepth <= 0)
    {
        return BoardRanking(player);
    }

    int best = INT_MAX;

    for (int i = 1; i < moves[0]; i++)
    {
        Board copyBoard = Board(this); // copy board, because we have no move undo
        copyBoard.DoMove(moves[i]);    // do move with index i
        NEW_MOVE_ARRAY(nextMoves);; // allocate memory for next moves
        copyBoard.GetMoves(nextMoves); // get all moves possible
        int val = copyBoard.MiniMaxMax(searchDepth - 1, nextMoves, states, NULL, player);
        if (val < best && result != NULL)
        {
            *result = moves[i];
            //std::cout << i << std::endl;
        }
        best = min(best, val);
    }
    return best;
}

#define NO_END 0
#define WHITE_WIN 1
#define BLACK_WIN 2

void Board::PlayGame()
{
    Presenter presenter = Presenter();
    while (this->End() == NO_END)
    {

        this->DoMove(this->GetMove());
        std::cout << presenter.ToString(*this) << std::endl;
    }
}

int Board::End()
{
    if (KingWinPosition & this->kings & this->white)
    {
        return WHITE_WIN; // WHITE KING IN 4 WIN POSITION
    }
    if (KingWinPosition & this->kings & this->black)
    {
        return BLACK_WIN; // BLACK KING IN 4 WIN POSITION
    }
    if ((this->kings & this->black) == 0)
    {
        return WHITE_WIN; // BLACK KING IS NOT ON FIELD
    }
    if ((this->kings & this->white) == 0)
    {
        return BLACK_WIN; // WHITE KING IS NOT ON FIELD
    }
    return NO_END;
}