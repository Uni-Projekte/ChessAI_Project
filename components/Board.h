// Board.h - header file for the Board class
#ifndef BOARD_H
#define BOARD_H

#include "bitBoardLoader.h"
#include <string>
#include <vector>
#define H1 (1ULL)
#define G1 (1ULL<<1)
#define F1 (1ULL<<2)
#define E1 (1ULL<<3)
#define D1 (1ULL<<4)
#define C1 (1ULL<<5)
#define B1 (1ULL<<6)
#define A1 (1ULL<<7)
#define H2 (1ULL<<8)
#define G2 (1ULL<<9)
#define F2 (1ULL<<10)
#define E2 (1ULL<<11)
#define D2 (1ULL<<12)
#define C2 (1ULL<<13)
#define B2 (1ULL<<14)
#define A2 (1ULL<<15)
#define H3 (1ULL<<16)
#define G3 (1ULL<<17)
#define F3 (1ULL<<18)
#define E3 (1ULL<<19)
#define D3 (1ULL<<20)
#define C3 (1ULL<<21)
#define B3 (1ULL<<22)
#define A3 (1ULL<<23)
#define H4 (1ULL<<24)
#define G4 (1ULL<<25)
#define F4 (1ULL<<26)
#define E4 (1ULL<<27)
#define D4 (1ULL<<28)
#define C4 (1ULL<<29)
#define B4 (1ULL<<30)
#define A4 (1ULL<<31)
#define H5 (1ULL<<32)
#define G5 (1ULL<<33)
#define F5 (1ULL<<34)
#define E5 (1ULL<<35)
#define D5 (1ULL<<36)
#define C5 (1ULL<<37)
#define B5 (1ULL<<38)
#define A5 (1ULL<<39)
#define H6 (1ULL<<40)
#define G6 (1ULL<<41)
#define F6 (1ULL<<42)
#define E6 (1ULL<<43)
#define D6 (1ULL<<44)
#define C6 (1ULL<<45)
#define B6 (1ULL<<46)
#define A6 (1ULL<<47)
#define H7 (1ULL<<48)
#define G7 (1ULL<<49)
#define F7 (1ULL<<50)
#define E7 (1ULL<<51)
#define D7 (1ULL<<52)
#define C7 (1ULL<<53)
#define B7 (1ULL<<54)
#define A7 (1ULL<<55)
#define H8 (1ULL<<56)
#define G8 (1ULL<<57)
#define F8 (1ULL<<58)
#define E8 (1ULL<<59)
#define D8 (1ULL<<60)
#define C8 (1ULL<<61)
#define B8 (1ULL<<62)
#define A8 1ULL<<63


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

    // bit sequence representing the turn and castling rights.
    // 1st bit is white kingside, 2nd bit is white queenside, 3rd bit is black kingside, 4th bit is black queenside.
    // Last bit is turn. 0 is white, 1 is black.
    uint8_t move_rights;

    // bit sequence representing the en passant square.
    // first 3 bits are the file, next 3 bits are the rank.
    uint8_t en_passant;

    // number representing half-moves played since the last pawn move or capture of a piece
    // 0 is the starting value.
    uint8_t halfmove_clock;

    // number representing the full moves played in the game
    // 1 is the starting value.
    uint16_t fullmove_number;
public:
    // Constructor that initializes the chessboard to the standard starting position
    Board(BitBoardLoader &loader);

    // Constructor that initializes the chessboard from a FEN string
    explicit Board(std::string fen);

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

    // Converts the board to a string representation
    std::string ToString(BitBoardLoader &loader);

    // Converts the board to a string representation
    void ToHTML(BitBoardLoader &loader, std::string filename);

    // Check if piece of player is on position with row and column
    uint64_t IsOnField(uint64_t player, uint64_t piece, uint64_t row, uint64_t column);

    // Converts a FEN string to a board configuration
    void fromFEN(std::string fen);

    // Gets the piece variable from a piece as character
    uint64_t *getPiece(char piece);

    // Gets the color variable from a piece as character
    uint64_t *getColor(char piece);

    uint8_t GetPosition(std::string position) const;

};

#endif // BOARD_H