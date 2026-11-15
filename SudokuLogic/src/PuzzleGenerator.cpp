#include "PuzzleGenerator.h"

#include "Solver.h"

#include <algorithm>
#include <array>
#include <numeric>

namespace sudoku
{

namespace
{
constexpr std::array<std::size_t, kAllDifficulties.size()> kGivenCellCounts{40, 34, 30, 26};
constexpr std::size_t kOneSolution = 1;
constexpr std::size_t kSolutionLimit = 2;
}

PuzzleGenerator::PuzzleGenerator(unsigned seed) : m_random(seed)
{
}

Board PuzzleGenerator::Generate(EDifficulty difficulty)
{
    while (true)
    {
        Board board = CreateSolvedBoard();
        if (TryRemoveValuesKeepingOneSolution(board, GetGivenCellCount(difficulty)))
        {
            return board;
        }
    }
}

std::size_t PuzzleGenerator::GetGivenCellCount(EDifficulty difficulty)
{
    return kGivenCellCounts[static_cast<std::size_t>(difficulty)];
}

Board PuzzleGenerator::CreateSolvedBoard()
{
    Board board;
    Solver(m_random()).FillBoard(board);
    return board;
}

bool PuzzleGenerator::TryRemoveValuesKeepingOneSolution(Board& board, std::size_t givenCellCount)
{
    std::array<std::size_t, kCellCount> cellIndexes{};
    std::iota(cellIndexes.begin(), cellIndexes.end(), 0);
    std::ranges::shuffle(cellIndexes, m_random);

    Solver solutionCounter;
    std::size_t filledCellCount = kCellCount;

    for (std::size_t cellIndex : cellIndexes)
    {
        if (filledCellCount == givenCellCount)
        {
            return true;
        }

        const std::size_t row = cellIndex / kBoardSize;
        const std::size_t column = cellIndex % kBoardSize;
        const int removedValue = board.GetValue(row, column);

        board.ClearValue(row, column);
        if (solutionCounter.CountSolutions(board, kSolutionLimit) == kOneSolution)
        {
            --filledCellCount;
        }
        else
        {
            board.SetValue(row, column, removedValue);
        }
    }

    return filledCellCount == givenCellCount;
}

}
