#include "bitBoardLoader.h"

/**
 * @brief set BitBoardLoader bit board from name
 * @param name: bit board name
 * @param bin: bit board binaries
 * @return void
 */
void BitBoardLoader::setBitBoard(std::string name, uint64_t bin)
{
    if (name.compare("BLACK") == 0)
    {
        this->black = bin;
        return;
    }
    if (name.compare("WHITE") == 0)
    {
        this->white = bin;
        return;
    }
    if (name.compare("PAWNS") == 0)
    {
        this->pawns = bin;
        return;
    }
    if (name.compare("TOWERS") == 0)
    {
        this->towers = bin;
        return;
    }
    if (name.compare("KNIGHTS") == 0)
    {
        this->knights = bin;
        return;
    }
    if (name.compare("KINGS") == 0)
    {
        this->kings = bin;
        return;
    }
    if (name.compare("QUEENS") == 0)
    {
        this->queens = bin;
        return;
    }
    if (name.compare("BISHOPS") == 0)
    {
        this->bishops = bin;
        return;
    }
    if (name.compare("8") == 0)
    {
        this->r8 = bin;
        return;
    }
    if (name.compare("7") == 0)
    {
        this->r7 = bin;
        return;
    }
    if (name.compare("6") == 0)
    {
        this->r6 = bin;
        return;
    }
    if (name.compare("5") == 0)
    {
        this->r5 = bin;
        return;
    }
    if (name.compare("4") == 0)
    {
        this->r4 = bin;
        return;
    }
    if (name.compare("3") == 0)
    {
        this->r3 = bin;
        return;
    }
    if (name.compare("2") == 0)
    {
        this->r2 = bin;
        return;
    }
    if (name.compare("1") == 0)
    {
        this->r1 = bin;
        return;
    }
    if (name.compare("A") == 0)
    {
        this->a = bin;
        return;
    }
    if (name.compare("B") == 0)
    {
        this->b = bin;
        return;
    }
    if (name.compare("C") == 0)
    {
        this->c = bin;
        return;
    }
    if (name.compare("D") == 0)
    {
        this->d = bin;
        return;
    }
    if (name.compare("E") == 0)
    {
        this->e = bin;
        return;
    }
    if (name.compare("F") == 0)
    {
        this->f = bin;
        return;
    }
    if (name.compare("G") == 0)
    {
        this->g = bin;
        return;
    }
    if (name.compare("H") == 0)
    {
        this->h = bin;
        return;
    }
}

/**
 * @brief create New BitBoardLoader and load bit-boards contained in file
 * @param filename: name of file to load
 * @return new BitBoardLoader
 */
BitBoardLoader::BitBoardLoader(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    std::string line = "";
    std::string bin = "";
    std::string name = "";
    int numLines = 0;

    while (!file.fail() && !file.eof())
    {
        file >> line;
        if (file.fail() || file.eof()) break;
        if (line.find("//") != std::string::npos)
        {
            if (numLines != 0)
            {
                std::size_t pos = 0;
                setBitBoard(name, std::stoull(bin, &pos, 2));
                bin = "";
            }
            line.erase(0, 2);
            name = line;
        }
        else
        {
            bin = bin.append(line);
        }
        numLines = numLines + 1;
    }

    std::size_t pos = 0;
    setBitBoard(name, std::stoull(bin, &pos, 2));

    file.close();
}

uint64_t BitBoardLoader::GetBlack()
{
    return this->black;
}

uint64_t BitBoardLoader::GetWhite()
{
    return this->white;
}

uint64_t BitBoardLoader::GetPawns()
{
    return this->pawns;
}

uint64_t BitBoardLoader::GetBishops()
{
    return this->bishops;
}

uint64_t BitBoardLoader::GetKings()
{
    return this->kings;
}

uint64_t BitBoardLoader::GetQueens()
{
    return this->queens;
}

uint64_t BitBoardLoader::GetKnights()
{
    return this->knights;
}

uint64_t BitBoardLoader::GetTowers()
{
    return this->towers;
}

uint64_t BitBoardLoader::GetR8()
{
    return this->r8;
}

uint64_t BitBoardLoader::GetR7()
{
    return this->r7;
}

uint64_t BitBoardLoader::GetR6()
{
    return this->r6;
}

uint64_t BitBoardLoader::GetR5()
{
    return this->r5;
}

uint64_t BitBoardLoader::GetR4()
{
    return this->r4;
}

uint64_t BitBoardLoader::GetR3()
{
    return this->r3;
}

uint64_t BitBoardLoader::GetR2()
{
    return this->r2;
}

uint64_t BitBoardLoader::GetR1()
{
    return this->r1;
}

uint64_t BitBoardLoader::GetA()
{
    return this->a;
}

uint64_t BitBoardLoader::GetB()
{
    return this->b;
}

uint64_t BitBoardLoader::GetC()
{
    return this->c;
}

uint64_t BitBoardLoader::GetD()
{
    return this->d;
}

uint64_t BitBoardLoader::GetE()
{
    return this->e;
}

uint64_t BitBoardLoader::GetF()
{
    return this->f;
}

uint64_t BitBoardLoader::GetG()
{
    return this->g;
}

uint64_t BitBoardLoader::GetH()
{
    return this->h;
}

/**
 * @brief get row bit-board from index
 * @param index: 0-7 representing row 1-8
 * @return row bit-board
 */
uint64_t BitBoardLoader::GetRowFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return this->r1;
    case 1:
        return this->r2;
    case 2:
        return this->r3;
    case 3:
        return this->r4;
    case 4:
        return this->r5;
    case 5:
        return this->r6;
    case 6:
        return this->r7;
    case 7:
        return this->r8;
    default:
        return 0;
    }
}

/**
 * @brief get column bit-board from index
 * @param index: 0-7 representing column a-h
 * @return column bit-board
 */
uint64_t BitBoardLoader::GetColumnFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return this->a;
    case 1:
        return this->b;
    case 2:
        return this->c;
    case 3:
        return this->d;
    case 4:
        return this->e;
    case 5:
        return this->f;
    case 6:
        return this->g;
    case 7:
        return this->h;
    default:
        return 0;
    }
}

/**
 * @brief get column letter from index
 * @param index: 0-7 representing column A-H
 * @return column letter
 */
std::string BitBoardLoader::GetColumnLetterFromIndex(int index)
{
    switch (index)
    {
    case 0:
        return "A";
    case 1:
        return "B";
    case 2:
        return "C";
    case 3:
        return "D";
    case 4:
        return "E";
    case 5:
        return "F";
    case 6:
        return "G";
    case 7:
        return "H";
    default:
        return "";
    }
}