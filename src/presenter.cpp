#include "presenter.h"
#include <stdexcept>
#include <utility>
#include <string>
#include <fstream>
#include <bitset>
#include <iostream>

/**
 * @brief generate string representation of the board
 * @param loader: access to constant boards needed
 * @return new string string representation of the board
 */
std::string Presenter::ToString(Board &board)
{
    std::string boards[64];
    std::string output = "";

    int maxWidth = 0;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            int i = ((7 - r) << 3) + c;
            if (board.IsOnField(board.GetWhite(), board.GetWhite(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("W");
            }
            if (board.IsOnField(board.GetBlack(), board.GetBlack(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("B");
            }
            if (board.IsOnField(board.GetPawns(), board.GetPawns(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("PAWN");
            }
            if (board.IsOnField(board.GetRooks(), board.GetRooks(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("ROOK");
            }
            if (board.IsOnField(board.GetKnights(), board.GetKnights(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("KNIGHT");
            }
            if (board.IsOnField(board.GetBishops(), board.GetBishops(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("BISHOP");
            }
            if (board.IsOnField(board.GetKings(), board.GetKings(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("KING");
            }
            if (board.IsOnField(board.GetQueens(), board.GetQueens(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("QUEEN");
            }
            if (boards[i].length() > maxWidth)
            {
                maxWidth = boards[i].length();
            }
        }
    }

    std::string line = StringMultiply("-", maxWidth + 2);
    output = output + " +" + StringMultiply(line + "+", 7) + line + "+\r\n";
    for (int r = 0; r < 7; r++)
    {
        output = output + std::to_string((7 - r) + 1);
        for (int c = 0; c < 8; c++)
        {

            output = output + "| ";
            output = output + StringMultiply(" ", (maxWidth - boards[(r << 3) + c].length()) / 2);
            output = output + boards[(r << 3) + c];
            output = output + StringMultiply(" ", (maxWidth - boards[(r << 3) + c].length() + 1) / 2);
            output = output + " ";
        }
        output = output + "|\r\n";

        output = output + " +" + StringMultiply(line + "+", 7) + line + "+\r\n";
    }
    output = output + "1";
    for (int c = 0; c < 8; c++)
    {
        output = output + "| ";
        output = output + StringMultiply(" ", (maxWidth - boards[(7 << 3) + c].length()) / 2);
        output = output + boards[(7 << 3) + c];
        output = output + StringMultiply(" ", (maxWidth - boards[(7 << 3) + c].length() + 1) / 2);
        output = output + " ";
    }
    output = output + "|\r\n";
    output = output + " +" + StringMultiply(line + "+", 7) + line + "+\r\n";
    output = output + " ";
    for (int c = 0; c < 8; c++)
    {
        output = output + StringMultiply(" ", (maxWidth + 3) / 2);
        output = output + GetColumnLetterFromIndex(c);
        output = output + StringMultiply(" ", (maxWidth + 2) / 2);
    }
    output = output + " \r\n";
    return output;
}

void Presenter::HTMLFromBoard(Board &board, std::string filename)
{
    std::string boards[64];
    std::string output = "";

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            int i = ((7 - r) << 3) + c;
            if (board.IsOnField(board.GetWhite(), board.GetKings(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♔");
            }
            if (board.IsOnField(board.GetWhite(), board.GetQueens(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♕");
            }
            if (board.IsOnField(board.GetWhite(), board.GetPawns(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♙");
            }
            if (board.IsOnField(board.GetWhite(), board.GetRooks(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♖");
            }
            if (board.IsOnField(board.GetWhite(), board.GetKnights(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♘");
            }
            if (board.IsOnField(board.GetWhite(), board.GetBishops(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♗");
            }
            if (board.IsOnField(board.GetBlack(), board.GetKings(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♚");
            }
            if (board.IsOnField(board.GetBlack(), board.GetQueens(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♛");
            }
            if (board.IsOnField(board.GetBlack(), board.GetPawns(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♟");
            }
            if (board.IsOnField(board.GetBlack(), board.GetRooks(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♜");
            }
            if (board.IsOnField(board.GetBlack(), board.GetKnights(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♞");
            }
            if (board.IsOnField(board.GetBlack(), board.GetBishops(), GetRowFromIndex(r), GetColumnFromIndex(c)) > 0)
            {
                boards[i] = boards[i].append("♝");
            }
        }
    }

    std::ofstream file(filename);

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
    file << "grid-template-columns: repeat(10, 1fr);" << std::endl;
    file << "grid-template-rows: repeat(10, 1fr);" << std::endl;
    file << "font-size: 64px;";
    file << "}" << std::endl;

    file << ".black {" << std::endl;
    file << "width: min(10vh,10vw);" << std::endl;
    file << "height: min(10vh,10vw);" << std::endl;
    file << "background-color: #888888;" << std::endl;
    file << "display: grid;" << std::endl;
    file << "grid-template-rows: 1fr 1fr 1fr;" << std::endl;
    file << "grid-template-columns: 1fr;" << std::endl;
    file << "grid-template-areas: \"1\" \"2\" \"3\";" << std::endl;
    file << "border-style: solid;" << std::endl;
    file << "border-width: 1px;" << std::endl;
    file << "border-color: #000;" << std::endl;
    file << "}" << std::endl;

    file << ".white {" << std::endl;
    file << "width: min(10vh,10vw);" << std::endl;
    file << "height: min(10vh,10vw);" << std::endl;
    file << "display: grid;" << std::endl;
    file << "grid-template-rows: 1fr 1fr 1fr;" << std::endl;
    file << "grid-template-columns: 1fr;" << std::endl;
    file << "grid-template-areas: \"1\" \"2\" \"3\";" << std::endl;
    file << "border-style: solid;" << std::endl;
    file << "border-width: 1px;" << std::endl;
    file << "border-color: #000;" << std::endl;
    file << "}" << std::endl;

    file << ".piece {" << std::endl;
    file << "align-self: center;" << std::endl;
    file << "justify-self: center;" << std::endl;
    file << "grid-area: 2;" << std::endl;
    file << "}" << std::endl;

    file << ".number {" << std::endl;
    file << "align-self: end;" << std::endl;
    file << "justify-self: right;" << std::endl;
    file << "font-size: 32px;" << std::endl;
    file << "grid-area: 3;" << std::endl;
    file << "}" << std::endl;

    file << ".left-index {" << std::endl;
    file << "align-self: center;" << std::endl;
    file << "justify-self: right;" << std::endl;
    file << "}" << std::endl;

    file << ".bottom-index {" << std::endl;
    file << "align-self: start;" << std::endl;
    file << "justify-self: center;" << std::endl;
    file << "}" << std::endl;

    file << ".right-info {" << std::endl;
    file << "align-self: center;" << std::endl;
    file << "justify-self: left;" << std::endl;
    file << "font-size: 16px;" << std::endl;
    file << "}" << std::endl;

    file << ".boards {" << std::endl;
    file << "width: min(10vh,10vw);" << std::endl;
    file << "height: min(10vh,10vw);" << std::endl;
    file << "display: grid;" << std::endl;
    file << "justify-self: center;" << std::endl;
    file << "justify-items: center;" << std::endl;
    file << "grid-template-rows: repeat(8,1fr);" << std::endl;
    file << "grid-template-columns: 1fr;" << std::endl;
    file << "font-size: 16px;" << std::endl;
    file << "}" << std::endl;

    file << "</style>" << std::endl;
    file << "</head>" << std::endl;
    file << "<body>" << std::endl;
    file << "<div class=\"board\">" << std::endl;

    file << "<div class=\"border\">" << std::endl;
    file << "</div>" << std::endl;

    uint64_t bitboards[8] = {board.GetBlack(), board.GetWhite(), board.GetKings(), board.GetQueens(), board.GetBishops(), board.GetKnights(), board.GetRooks(), board.GetPawns()};

    for (int c = 0; c < 8; c++)
    {
        file << "<div class=\"boards\">" << std::endl;
        std::string board = Uint64ToString(bitboards[c]);
        for (unsigned int c = 0; c < 8; c++)
        {
            file << "<p>" << std::endl;
            file << board.substr(c << 3, 8) << std::endl;
            file << "</p>" << std::endl;
        }
        file << "</div>" << std::endl;
    }

    file << "<div class=\"border\">" << std::endl;
    file << "</div>" << std::endl;

    for (int r = 0; r < 8; r++)
    {
        file << "<div class=\"left-index\">" << std::endl;
        file << "<p>" << std::endl;
        file << std::to_string(8 - r) << std::endl;
        file << "</p>" << std::endl;
        file << "</div>" << std::endl;
        for (int c = 0; c < 8; c++)
        {
            std::string color = "white";
            if ((~r & ~c & 0b1) | (r & c & 0b1))
            {
                color = "black";
            }
            int i = (r << 3) + c;
            file << "<div class=\"" + color + "\">" << std::endl;
            file << "<p class=\"piece\">" << std::endl;
            file << boards[i] << std::endl;
            file << "</p>" << std::endl;
            file << "<p class=\"number\">" << std::endl;
            file << std::to_string(63 - i) << std::endl;
            file << "</p>" << std::endl;
            file << "</div>" << std::endl;
        }

        switch (r)
        {
        case 1:
            file << "<div class=\"right-info\">" << std::endl;
            file << "<p>" << std::endl;
            file << "MOVE RIGHTS" << std::endl;
            file << "</p>" << std::endl;
            file << "<p>" << std::endl;
            file << Uint8ToString(board.GetMoveRights()) << std::endl;
            file << "</p>" << std::endl;
            file << "</div>" << std::endl;
            break;
        case 2:
            file << "<div class=\"right-info\">" << std::endl;
            file << "<p>" << std::endl;
            file << "EN PASSANT WHITE" << std::endl;
            file << "</p>" << std::endl;
            file << "<p>" << std::endl;
            file << Uint8ToString(board.GetEnPassant()) << std::endl;
            file << "</p>" << std::endl;
            file << "</div>" << std::endl;
            break;
        case 3:
            file << "<div class=\"right-info\">" << std::endl;
            file << "<p>" << std::endl;
            file << "HALF MOVE CLOCK" << std::endl;
            file << "</p>" << std::endl;
            file << "<p>" << std::endl;
            file << Uint8ToString(board.GetHalfMoveClock()) << std::endl;
            file << "</p>" << std::endl;
            file << "</div>" << std::endl;
            break;
        case 4:
            file << "<div class=\"right-info\">" << std::endl;
            file << "<p>" << std::endl;
            file << "FULL MOVE NUMBER" << std::endl;
            file << "</p>" << std::endl;
            file << "<p>" << std::endl;
            file << Uint16ToString(board.GetFullMoveNumber()) << std::endl;
            file << "</p>" << std::endl;
            file << "</div>" << std::endl;
            break;
        default:
            file << "<div class=\"border\">" << std::endl;
            file << "</div>" << std::endl;
            break;
        }
    }

    file << "<div class=\"border\">" << std::endl;
    file << "</div>" << std::endl;

    for (int c = 0; c < 8; c++)
    {
        file << "<div class=\"bottom-index\">" << std::endl;
        file << "<p>" << std::endl;
        file << GetColumnLetterFromIndex(c) << std::endl;
        file << "</p>" << std::endl;
        file << "</div>" << std::endl;
    }

    file << "<div class=\"border\">" << std::endl;
    file << "</div>" << std::endl;

    // file << "</div>" << std::endl;
    // file << "<a href=\"./out2.html\">" << std::endl;
    // file << "next" << std::endl;
    file << "</a>" << std::endl;
    file << "</body>" << std::endl;
    file << "</html>" << std::endl;

    file.close();
}


void Presenter::displayUINT64(uint64_t number) {
    std::bitset<64> bits(number);

    // Display column letters
    std::cout << "    A   B   C   D   E   F   G   H" << std::endl;

    std::cout << "  - - - - - - - - - - - - - - - - -" << std::endl;
    for (int row = 7; row >= 0; --row) {
        // Display row number
        std::cout << row + 1 << " ";

        std::cout << "| ";
        for (int col = 0; col < 8; ++col) {
            int index = row * 8 +(7 - col);
            if (bits.test(index)) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }

            // Display grid
            std::cout << "| ";
        }

        std::cout << std::endl;

        // Display grid
        std::cout << "  - - - - - - - - - - - - - - - - -" << std::endl;
    }
}
