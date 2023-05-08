// Board.cpp - implementation file for the Board class
#include "Board.h"
#include <stdexcept>
#include <utility>
#include <string>
#include <fstream>

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
    this->bishops = StartBoardBishops;
    this->queens = StartBoardQueens;
    this->towers = StartBoardTowers;
    this->pawns = StartBoardPawns;
    this->kings = StartBoardKings;
    this->knights = StartBoardKnights;
}

Board::Board(std::string fen)
{
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

uint64_t Board::GetTowers() const
{
    return this->towers;
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
 * @brief get bitboard of black towers
 * @return bitboard of black towers as uint64_t
 */
uint64_t Board::GetBlackTowers() const
{
    return this->black & this->towers;
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
 * @brief get bitboard of white towers
 * @return bitboard of white towers as uint64_t
 */
uint64_t Board::GetWhiteTowers() const
{
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
        rows.push_back(fen);
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

#define KING_SIDE 0b00000010U
#define QUEEN_SIDE 0b00100000U
#define CAPTURE 0b10000000U
#define CASTLING 0b01000000U
#define LAST_MOVE 0b11000000U
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

void Board::DoMove(uint8_t x, uint8_t y, uint8_t newX, uint8_t newY, uint8_t flags)
{
    const uint64_t pieceBoard = 1ULL << (uint64_t(x) + (uint64_t(y) << 3ULL));
    const uint64_t newPieceBoard = 1ULL << (newX + (newY << 3ULL));
    const uint8_t capture = flags & CAPTURE;
    const uint8_t castling = flags & CASTLING;
    const uint64_t allPieces = this->white | this->black;
    const uint64_t white = this->white;
    const uint64_t black = this->black;
    const uint64_t pawns = this->pawns;
    const uint64_t bishops = this->bishops;
    const uint64_t queens = this->queens;
    const uint64_t kings = this->kings;
    const uint64_t towers = this->towers;
    const uint64_t knights = this->knights;

    // COMMENT: EN_PASSENTE IS MISSING

    // clear CASTLING and CAPTURE if both set, because it is a LAST_MOVE
    flags = flags & ~(LAST_MOVE * bool(flags & LAST_MOVE));

    // change player turn
    this->move_rights = this->move_rights ^ 0b1;

    // disable white castling when king moved
    this->move_rights = this->move_rights & (NO_WHITE_CASTLING | (!bool(white & this->kings & pieceBoard) << 6) | (!bool(white & this->kings & pieceBoard) << 7));
    // disable black castling when king moved
    this->move_rights = this->move_rights & (NO_BLACK_CASTLING | (!bool(black & this->kings & pieceBoard) << 4) | (!bool(black & this->kings & pieceBoard) << 5));

    // disable white kingside castling when white kingside-tower moved
    this->move_rights = this->move_rights & (bool(white & this->towers & pieceBoard & WHITE_KINGSIDE_TOWER) << 7);
    // disable white queenside castling when white queenside-tower moved
    this->move_rights = this->move_rights & (bool(white & this->towers & pieceBoard & WHITE_QUEENSIDE_TOWER) << 6);
    // disable black kingside castling when black kingside-tower moved
    this->move_rights = this->move_rights & (bool(black & this->towers & pieceBoard & BLACK_KINGSIDE_TOWER) << 5);
    // disable black queenside castling when black queenside-tower moved
    this->move_rights = this->move_rights & (bool(black & this->towers & pieceBoard & BLACK_QUEENSIDE_TOWER) << 4);

    // delete moved tower old pos when castling
    this->towers = this->towers & ~(BLACK_KINGSIDE_TOWER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->towers = this->towers & ~(BLACK_QUEENSIDE_TOWER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->towers = this->towers & ~(WHITE_KINGSIDE_TOWER * ((newPieceBoard & KING_SIDE) && castling));
    this->towers = this->towers & ~(WHITE_QUEENSIDE_TOWER * ((newPieceBoard & QUEEN_SIDE) && castling));
    this->white = this->white & ~(BLACK_KINGSIDE_TOWER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->white = this->white & ~(BLACK_QUEENSIDE_TOWER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->white = this->white & ~(WHITE_KINGSIDE_TOWER * ((newPieceBoard & KING_SIDE) && castling));
    this->white = this->white & ~(WHITE_QUEENSIDE_TOWER * ((newPieceBoard & QUEEN_SIDE) && castling));
    this->black = this->black & ~(BLACK_KINGSIDE_TOWER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->black = this->black & ~(BLACK_QUEENSIDE_TOWER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->black = this->black & ~(WHITE_KINGSIDE_TOWER * ((newPieceBoard & KING_SIDE) && castling));
    this->black = this->black & ~(WHITE_QUEENSIDE_TOWER * ((newPieceBoard & QUEEN_SIDE) && castling));
    // add moved tower new pos when castling
    this->towers = this->towers | (BLACK_KINGSIDE_TOWER_AFTER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->towers = this->towers | (BLACK_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->towers = this->towers | (WHITE_KINGSIDE_TOWER_AFTER * ((newPieceBoard & KING_SIDE) && castling));
    this->towers = this->towers | (WHITE_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & QUEEN_SIDE) && castling));
    this->white = this->white | (BLACK_KINGSIDE_TOWER_AFTER * ((newPieceBoard & (KING_SIDE << 56)) && castling && (pieceBoard & white)));
    this->white = this->white | (BLACK_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling && (pieceBoard & white)));
    this->white = this->white | (WHITE_KINGSIDE_TOWER_AFTER * ((newPieceBoard & KING_SIDE) && castling && (pieceBoard & white)));
    this->white = this->white | (WHITE_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & QUEEN_SIDE) && castling && (pieceBoard & white)));
    this->black = this->black | (BLACK_KINGSIDE_TOWER_AFTER * ((newPieceBoard & (KING_SIDE << 56)) && castling && (pieceBoard & black)));
    this->black = this->black | (BLACK_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling && (pieceBoard & black)));
    this->black = this->black | (WHITE_KINGSIDE_TOWER_AFTER * ((newPieceBoard & KING_SIDE) && castling && (pieceBoard & black)));
    this->black = this->black | (WHITE_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & QUEEN_SIDE) && castling && (pieceBoard & black)));

    // add moved piece new pos
    this->black = this->black | (newPieceBoard * bool(black & pieceBoard));
    // delete captured piece pos
    this->black = this->black & ~(newPieceBoard * ((capture && (white & pieceBoard))));
    // delete moved piece old pos
    this->black = this->black & ~pieceBoard;

    this->white = this->white | (newPieceBoard * bool(white & pieceBoard));
    this->white = this->white & ~(newPieceBoard * ((capture && (black & pieceBoard))));
    this->white = this->white & ~pieceBoard;

    this->pawns = this->pawns | (newPieceBoard * bool(pawns & pieceBoard));
    this->pawns = this->pawns & ~(newPieceBoard * ((capture && ((allPieces & ~pawns) & pieceBoard))));
    this->pawns = this->pawns & ~pieceBoard;

    this->bishops = this->bishops | (newPieceBoard * bool(bishops & pieceBoard));
    this->bishops = this->bishops & ~(newPieceBoard * ((capture && ((allPieces & ~bishops) & pieceBoard))));
    this->bishops = this->bishops & ~pieceBoard;

    this->queens = this->queens | (newPieceBoard * bool(queens & pieceBoard));
    this->queens = this->queens & ~(newPieceBoard * ((capture && ((allPieces & ~queens) & pieceBoard))));
    this->queens = this->queens & ~pieceBoard;

    this->kings = this->kings | (newPieceBoard * bool(kings & pieceBoard));
    this->kings = this->kings & ~(newPieceBoard * ((capture && ((allPieces & ~kings) & pieceBoard))));
    this->kings = this->kings & ~pieceBoard;

    this->towers = this->towers | (newPieceBoard * bool(towers & pieceBoard));
    this->towers = this->towers & ~(newPieceBoard * ((capture && ((allPieces & ~towers) & pieceBoard))));
    this->towers = this->towers & ~pieceBoard;

    this->knights = this->knights | (newPieceBoard * bool(knights & pieceBoard));
    this->knights = this->knights & ~(newPieceBoard * ((capture && ((allPieces & ~knights) & pieceBoard))));
    this->knights = this->knights & ~pieceBoard;

    // add half-move clock move every move
    this->halfmove_clock = this->halfmove_clock + 1;
    // reset half-move clock when pawn moved or a piece was captured
    this->halfmove_clock = this->halfmove_clock * bool((pawns & pieceBoard) | capture);

    // add full-move when black moved
    this->fullmove_number = this->fullmove_number + bool(black & pieceBoard);

    // add queen if pawns reached one of the ends
    this->queens = this->queens | (this->pawns & ROW_1_AND_8);
    // delete pawns that reached one of the ends
    this->pawns = this->pawns & NOT_ROW_1_AND_8;
}