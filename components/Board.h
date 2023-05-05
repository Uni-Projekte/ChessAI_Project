// Board.h - header file for the Board class
#ifndef BOARD_H
#define BOARD_H

#include "bitBoardLoader.h"
#include <string>
#include <vector>

class Board {
private:
    uint64_t black;  // bitboard representing black pieces
    uint64_t white;  // bitboard representing white pieces
    uint64_t pawns;  // bitboard representing all pawns
    uint64_t kings;  // bitboard representing all kings
    uint64_t queens; // bitboard representing all queens
    uint64_t towers; // bitboard representing all towers
    uint64_t bishops;// bitboard representing all bishops
    uint64_t knights;// bitboard representing all knights

    // bit sequence representing the en passant square.
    // first 3 bits are the file, next 3 bits are the rank.
    uint8_t en_passant;

    // bit sequence representing the turn and castling rights.
    // 1st bit is white kingside, 2nd bit is white queenside, 3rd bit is black kingside, 4th bit is black queenside.
    // Last bit is turn. 0 is white, 1 is black.
    uint8_t move_rights;

    // number representing half-moves played since the last pawn move or capture of a piece
    // 0 is the starting value.
    uint8_t halfmove_clock;

    // number representing the full moves played in the game
    // 1 is the starting value.
    uint16_t fullmove_number;

public:
    // Constructor that initializes the chessboard to the standard starting position
    Board();

    // Constructor that initializes the chessboard from a FEN string
    explicit Board(std::string fen);

    uint8_t GetEnPassant() const;
    uint8_t GetMoveRights() const;
    uint8_t GetHalfMoveClock() const;
    uint16_t GetFullMoveNumber() const;
    uint64_t GetWhite() const;
    uint64_t GetBlack() const;
    uint64_t GetKings() const;
    uint64_t GetQueens() const;
    uint64_t GetBishops() const;
    uint64_t GetKnights() const;
    uint64_t GetTowers() const;
    uint64_t GetPawns() const;

    // Returns the bitboard representing all pieces
    uint64_t GetAllPieces() const;

    // Returns the bitboard representing all black pieces
    uint64_t GetBlackPieces() const;

    // Returns the bitboard representing all white pieces
    uint64_t GetWhitePieces() const;

    // Returns the bitboard representing black pawns
    uint64_t GetBlackPawns() const;

    // Returns the bitboard representing black queen
    uint64_t GetBlackQueen() const;

    // Returns the bitboard representing black king
    uint64_t GetBlackKing() const;

    // Returns the bitboard representing black bishops
    uint64_t GetBlackBishops() const;

    // Returns the bitboard representing black knights
    uint64_t GetBlackKnights() const;

    // Returns the bitboard representing black towers
    uint64_t GetBlackTowers() const;

    // Returns the bitboard representing white pawns
    uint64_t GetWhitePawns() const;

    // Returns the bitboard representing white queen
    uint64_t GetWhiteQueen() const;

    // Returns the bitboard representing white king
    uint64_t GetWhiteKing() const;

    // Returns the bitboard representing white bishops
    uint64_t GetWhiteBishops() const;

    // Returns the bitboard representing white knights
    uint64_t GetWhiteKnights() const;

    // Returns the bitboard representing white towers
    uint64_t GetWhiteTowers() const;

    // Check if piece of player is on position with row and column
    uint64_t IsOnField(uint64_t player, uint64_t piece, uint64_t row, uint64_t column);

    // Converts a FEN string to a board configuration
    void fromFEN(std::string fen);

    // Gets the piece variable from a piece as character
    uint64_t *getPiece(char piece);

    // Gets the color variable from a piece as character
    uint64_t *getColor(char piece);

    uint8_t GetPosition(std::string position) const;

    void DoMove(uint8_t x, uint8_t y, uint8_t newX, uint8_t newY, uint8_t flags);
};

#endif // BOARD_H