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

void Board::ToHTML(BitBoardLoader &loader, std::string filename)
{
    string board[64];
    string output = "";

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            int i = ((7 - r) << 3) + c;
            if (this->IsOnField(this->white, this->kings, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♔");
            }
            if (this->IsOnField(this->white, this->queens, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♕");
            }
            if (this->IsOnField(this->white, this->pawns, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♙");
            }
            if (this->IsOnField(this->white, this->towers, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♖");
            }
            if (this->IsOnField(this->white, this->knights, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♘");
            }
            if (this->IsOnField(this->white, this->bishops, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♗");
            }
            if (this->IsOnField(this->black, this->kings, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♚");
            }
            if (this->IsOnField(this->black, this->queens, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♛");
            }
            if (this->IsOnField(this->black, this->pawns, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♟");
            }
            if (this->IsOnField(this->black, this->towers, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♜");
            }
            if (this->IsOnField(this->black, this->knights, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♞");
            }
            if (this->IsOnField(this->black, this->bishops, loader.GetRowFromIndex(r), loader.GetColumnFromIndex(c)) > 0)
            {
                board[i] = board[i].append("♝");
            }
        }
    }

    ofstream file(filename);

    file << "<!DOCTYPE html>" << std::endl;
    file << " <html lang=\"en\">" << std::endl;
    file << "<head>" << std::endl;
    file << "<head>" << std::endl;
    file << "<meta charset = \"UTF-8\">" << std::endl;
    file << "<meta http-equiv = \"X-UA-Compatible\" content = \"IE=edge\">" << std::endl;
    file << "<meta name=\"viewport\" content = \"width=device-width, initial-scale=1.0\">" << std::endl;
    file << "<title> Document </title>" << std::endl;
    file << "<style>" << std::endl;
    file << "* {" << std::endl;
    file << "box-sizing: border-box;" << std::endl;
    file << "margin: 0;" << std::endl;
    file << "padding: 0;" << std::endl;
    file << "}" << std::endl;
    file << ".board {" << std::endl;
    file << "display: grid;" << std::endl;
    file << "width: min(100vh,100vw);" << std::endl;
    file << "height: min(100vh,100vw);" << std::endl;
    file << "grid-template-columns: repeat(8, 1fr);" << std::endl;
    file << "grid-template-rows: repeat(8, 1fr);" << std::endl;
    file << "font-size: 64px;";
    file << "}" << std::endl;
    file << ".black {" << std::endl;
    file << "background-color: #888888;" << std::endl;
    file << "display: flex;" << std::endl;
    file << "align-content: center;" << std::endl;
    file << "justify-content: center;" << std::endl;
    file << "}" << std::endl;
    file << ".white {" << std::endl;
    file << "display: flex;" << std::endl;
    file << "align-content: center;" << std::endl;
    file << "justify-content: center;" << std::endl;
    file << "}" << std::endl;
    file << "p {" << std::endl;
    file << "align-self: center;" << std::endl;
    file << "}" << std::endl;
    file << "</style>" << std::endl;
    file << "</head>" << std::endl;
    file << "<body>" << std::endl;
    file << "<div class=\"board\">" << std::endl;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            string color = "white";
            if ((~r & ~c & 0b1) | (r & c & 0b1))
            {
                color = "black";
            }
            int i = (r << 3) + c;
            file << "<div class=\"" + color + "\">" << std::endl;
            file << "<p>" << std::endl;
            file << board[i];
            file << "</p>" << std::endl;
            file << "</div>" << std::endl;
        }
    }

    file << "</div>";
    file << "</body>";
    file << "</html>";

    file.close();
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

    return (row << 3) | col;
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
    const uint8_t castling =  flags & CASTLING;
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
    this->halfmove_clock = this->halfmove_clock * bool(pawns & pieceBoard | capture);

    // add full-move when black moved
    this->fullmove_number = this->fullmove_number + bool(black & pieceBoard);

    // add queen if pawns reached one of the ends
    this->queens = this->queens | (this->pawns & ROW_1_AND_8);
    // delete pawns that reached one of the ends
    this->pawns = this->pawns & NOT_ROW_1_AND_8;
}