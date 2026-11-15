#pragma once

#include "Board.h"
#include "SudokuLogic/EDifficulty.h"

namespace sudoku
{

class IPuzzleGenerator
{
public:
    virtual ~IPuzzleGenerator() = default;

    virtual Board Generate(EDifficulty difficulty) = 0;
};

}
