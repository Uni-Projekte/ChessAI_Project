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
    this->rooks = StartBoardRooks;
    this->pawns = StartBoardPawns;
    this->kings = StartBoardKings;
    this->knights = StartBoardKnights;
    this->move_rights = 0b11110000;
    this->en_passant_white = 0b00000000;
    this->en_passant_black = 0b00000000;
    this->halfmove_clock = 0;
    this->fullmove_number = 1;
}

Board::Board(std::string fen)
{
    this->black = 0;
    this->white = 0;
    this->pawns = 0;
    this->kings = 0;
    this->queens = 0;
    this->rooks = 0;
    this->bishops = 0;
    this->knights = 0;
    this->move_rights = 0b11110000;
    this->en_passant_white = 0b00000000;
    this->en_passant_black = 0b00000000;
    this->halfmove_clock = 0;
    this->fullmove_number = 1;

    this->fromFEN(std::move(fen));
}

uint8_t Board::GetEnPassantBlack() const
{
    return this->en_passant_black;
}

uint8_t Board::GetEnPassantWhite() const
{
    return this->en_passant_white;
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

#define KING_SIDE 0b00000010U
#define QUEEN_SIDE 0b00100000U
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

void Board::DoMove(MOVE move)
{
    const BOARD pieceBoard = GET_SINGLE_BIT_BOARD_FROM(move);
    const BOARD newPieceBoard = GET_SINGLE_BIT_BOARD_TO(move);
    const bool capture = GET_CAPTURE(move);
    const bool castling = GET_CASTLING(move);
    const BOARD allPieces = this->white | this->black;
    const BOARD white = this->white;
    const BOARD black = this->black;
    const BOARD pawns = this->pawns;
    const BOARD bishops = this->bishops;
    const BOARD queens = this->queens;
    const BOARD kings = this->kings;
    const BOARD rook = this->rooks;
    const BOARD knights = this->knights;

    // change player turn
    this->move_rights = this->move_rights ^ 0b1;

    // disable white castling when king moved
    this->move_rights = this->move_rights & (NO_WHITE_CASTLING | (!bool(white & this->kings & pieceBoard) << 6) | (!bool(white & this->kings & pieceBoard) << 7));
    // disable black castling when king moved
    this->move_rights = this->move_rights & (NO_BLACK_CASTLING | (!bool(black & this->kings & pieceBoard) << 4) | (!bool(black & this->kings & pieceBoard) << 5));

    // disable white kingside castling when white kingside-tower moved
    this->move_rights = this->move_rights & (bool(white & this->rooks & pieceBoard & WHITE_KINGSIDE_TOWER) << 7);
    // disable white queenside castling when white queenside-tower moved
    this->move_rights = this->move_rights & (bool(white & this->rooks & pieceBoard & WHITE_QUEENSIDE_TOWER) << 6);
    // disable black kingside castling when black kingside-tower moved
    this->move_rights = this->move_rights & (bool(black & this->rooks & pieceBoard & BLACK_KINGSIDE_TOWER) << 5);
    // disable black queenside castling when black queenside-tower moved
    this->move_rights = this->move_rights & (bool(black & this->rooks & pieceBoard & BLACK_QUEENSIDE_TOWER) << 4);

    // delete moved tower old pos when castling
    this->rooks = this->rooks & ~(BLACK_KINGSIDE_TOWER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->rooks = this->rooks & ~(BLACK_QUEENSIDE_TOWER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->rooks = this->rooks & ~(WHITE_KINGSIDE_TOWER * ((newPieceBoard & KING_SIDE) && castling));
    this->rooks = this->rooks & ~(WHITE_QUEENSIDE_TOWER * ((newPieceBoard & QUEEN_SIDE) && castling));
    this->white = this->white & ~(BLACK_KINGSIDE_TOWER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->white = this->white & ~(BLACK_QUEENSIDE_TOWER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->white = this->white & ~(WHITE_KINGSIDE_TOWER * ((newPieceBoard & KING_SIDE) && castling));
    this->white = this->white & ~(WHITE_QUEENSIDE_TOWER * ((newPieceBoard & QUEEN_SIDE) && castling));
    this->black = this->black & ~(BLACK_KINGSIDE_TOWER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->black = this->black & ~(BLACK_QUEENSIDE_TOWER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->black = this->black & ~(WHITE_KINGSIDE_TOWER * ((newPieceBoard & KING_SIDE) && castling));
    this->black = this->black & ~(WHITE_QUEENSIDE_TOWER * ((newPieceBoard & QUEEN_SIDE) && castling));
    // add moved tower new pos when castling
    this->rooks = this->rooks | (BLACK_KINGSIDE_TOWER_AFTER * ((newPieceBoard & (KING_SIDE << 56)) && castling));
    this->rooks = this->rooks | (BLACK_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & (QUEEN_SIDE << 56)) && castling));
    this->rooks = this->rooks | (WHITE_KINGSIDE_TOWER_AFTER * ((newPieceBoard & KING_SIDE) && castling));
    this->rooks = this->rooks | (WHITE_QUEENSIDE_TOWER_AFTER * ((newPieceBoard & QUEEN_SIDE) && castling));
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

    this->rooks = this->rooks | (newPieceBoard * bool(rook & pieceBoard));
    this->rooks = this->rooks & ~(newPieceBoard * ((capture && ((allPieces & ~rook) & pieceBoard))));
    this->rooks = this->rooks & ~pieceBoard;

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

    // white en_passant
    this->en_passant_white = (this->en_passant_white * bool(pieceBoard & black)) | ((0b10000000 | (pawns & pieceBoard & white)) * bool(pawns & pieceBoard & white));

    // black en_passant
    this->en_passant_black = (this->en_passant_white * bool(pieceBoard & white)) | ((0b10000000 | (pawns & pieceBoard & black)) * bool(pawns & pieceBoard & black));
}

void Board::DoStep()
{
    std::vector<MOVE> moves = std::vector<MOVE>();
    for (uint8_t x = 0; x < 8; x = x + 1)
    {
        for (uint8_t y = 0; y < 8; y = y + 1)
        {
            if (this->move_rights & 1)
            {
                if (this->bishops & this->black & SINGLE_BIT_BOARD(x, y))
                {
                    bishop::possibleMoves(moves, this->black | this->white, this->black, x, y);
                }
                if (this->kings & this->black & SINGLE_BIT_BOARD(x, y))
                {
                    king::possibleMoves(moves, this->black | this->white, this->black, x, y);
                }
                if (this->knights & this->black & SINGLE_BIT_BOARD(x, y))
                {
                    knight::possibleMoves(moves, this->black | this->white, this->black, x, y);
                }
                if (this->pawns & this->black & SINGLE_BIT_BOARD(x, y))
                {
                    pawn::possibleMoves(moves, this->black | this->white, this->black, x, y, BLACK);
                }
                if (this->rooks & this->black & SINGLE_BIT_BOARD(x, y))
                {
                    rook::possibleMoves(moves, this->black | this->white, this->black, x, y);
                }
                if (this->queens & this->black & SINGLE_BIT_BOARD(x, y))
                {
                    queen::possibleMoves(moves, this->black | this->white, this->black, x, y);
                }
            }
            else
            {
                if (this->bishops & this->white & SINGLE_BIT_BOARD(x, y))
                {
                    bishop::possibleMoves(moves, this->black | this->white, this->white, x, y);
                }
                if (this->kings & this->white & SINGLE_BIT_BOARD(x, y))
                {
                    king::possibleMoves(moves, this->black | this->white, this->white, x, y);
                }
                if (this->knights & this->white & SINGLE_BIT_BOARD(x, y))
                {
                    knight::possibleMoves(moves, this->black | this->white, this->white, x, y);
                }
                if (this->pawns & this->white & SINGLE_BIT_BOARD(x, y))
                {
                    pawn::possibleMoves(moves, this->black | this->white, this->white, x, y, WHITE);
                }
                if (this->rooks & this->white & SINGLE_BIT_BOARD(x, y))
                {
                    rook::possibleMoves(moves, this->black | this->white, this->white, x, y);
                }
                if (this->queens & this->white & SINGLE_BIT_BOARD(x, y))
                {
                    queen::possibleMoves(moves, this->black | this->white, this->white, x, y);
                }
            }
        }
    }
    std::cout << "NUMBER OF MOVES: " << moves.size() << std::endl;
    for (int i = 0; i < moves.size()-1; i++) {
        std::cout << moves[i] << ", ";
    }
    std::cout << moves[moves.size()-1] << std::endl;
    MOVE move = moves[rand() % moves.size()];
    std::cout << "PICKED MOVE: " << move << std::endl;
    std::cout << "FLAGS:" << ((move & 0b1111000000000000U) >> 12) << std::endl;
    std::cout << "FROM:" << GET_MOVE_FROM_X(move) << ", " << GET_MOVE_FROM_Y(move) << std::endl;
    std::cout << "TO:" << GET_MOVE_TO_X(move) << ", " << GET_MOVE_TO_Y(move) << std::endl;
    this->DoMove(move);
}