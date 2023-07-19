// Board.h - header file for the Board class
#ifndef BOARD_H
#define BOARD_H

#include "helper.h"
#include <string>
#include <vector>




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
#define NO_END 0
#define WHITE_WIN 1
#define BLACK_WIN 2

class Board {
private:
    uint64_t black;  // bitboard representing black pieces
    uint64_t white;  // bitboard representing white pieces
    uint64_t attackedFromWhite; // bitboard representing from White attacked fields
    uint64_t attackedFromBlack; // bitboard representing from Black attacked fields
    uint64_t pinnedWhitePieces;
    uint64_t pinnedBlackPieces;
    uint64_t pawns;  // bitboard representing all pawns
    uint64_t kings;  // bitboard representing all kings
    uint64_t queens; // bitboard representing all queens
    uint64_t rooks; // bitboard representing all rook
    uint64_t bishops;// bitboard representing all bishops
    uint64_t knights;// bitboard representing all knight

    // bit sequence representing the en passant square.
    // first 3 bits are the file, next 3 bits are the rank.
    //on/off | c | yyy | xxx
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

    Board(Board *board);

    // Constructor that initializes the chessboard from a FEN string
    explicit Board(std::string fen);

    bool IsCheckmate(COLOR player);
    // Check if piece of player is on position with row and column
    uint64_t IsOnField(uint64_t player, uint64_t piece, uint64_t row, uint64_t column);

    // Converts a FEN string to a board configuration
    void fromFEN(std::string fen);

    // Converts a board configuration to a FEN string
    std::string toFEN();

    // Gets the piece variable from a piece as character
    uint64_t *getPiece(char piece);

    // Gets the color variable from a piece as character
    uint64_t *getColor(char piece);

    uint8_t GetPosition(std::string position) const;

    void DoMove(MOVE move);

    void UndoMove(MOVE move, uint8_t oldMoveRights, uint8_t oldEnPassent, uint8_t oldHalfmoveClock);

    void GetMoves(MOVE_ARRAY &moves);

    void MarkFields(COLOR currentColor);

    uint8_t GetEnPassant() const;
    uint8_t GetMoveRights() const;
    uint8_t GetHalfMoveClock() const;
    uint16_t GetFullMoveNumber() const;
    uint64_t GetCurrentColorBoard() const;
    COLOR GetCurrentColor() const;
    uint64_t GetWhite() const;
    uint64_t GetBlack() const;
    uint64_t GetKings() const;
    uint64_t GetQueens() const;
    uint64_t GetBishops() const;
    uint64_t GetKnights() const;
    uint64_t GetRooks() const;
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

    // Returns the bitboard representing black rook
    uint64_t GetBlackRooks() const;

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

    // Returns the bitboard representing white rook
    uint64_t GetWhiteRooks() const;

    // Returns the bitboard representing from White attacked fields
    uint64_t& GetFromWhiteAttackedFields();

    // Returns the bitboard representing from Black attacked fields
    uint64_t& GetFromBlackAttackedFields();

    bool Equals(Board other) const;

    uint64_t GetWhitePinnedPieces() const;

    uint64_t GetBlackPinnedPieces() const;

    void PlayGame();

    int End();



};

#endif // BOARD_H