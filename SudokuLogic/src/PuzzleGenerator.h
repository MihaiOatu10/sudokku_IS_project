#pragma once

#include "IPuzzleGenerator.h"

#include <cstddef>
#include <random>

namespace sudoku
{

class PuzzleGenerator : public IPuzzleGenerator
{
public:
    explicit PuzzleGenerator(unsigned seed);

    Board Generate(EDifficulty difficulty) override;

    static std::size_t GetGivenCellCount(EDifficulty difficulty);

private:
    Board CreateSolvedBoard();
    bool TryRemoveValuesKeepingOneSolution(Board& board, std::size_t givenCellCount);

    std::mt19937 m_random;
};

}
