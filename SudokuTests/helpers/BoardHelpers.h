#pragma once

#include "Board.h"
#include "Solver.h"

#include <algorithm>
#include <array>
#include <cstddef>

namespace sudoku::test
{

constexpr std::size_t kSolutionLimit = 2;

inline std::array<int, kCellCount> GetValues(const Board& board)
{
    std::array<int, kCellCount> values{};
    for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
    {
        values[cellIndex] = board.GetValue(cellIndex / kBoardSize, cellIndex % kBoardSize);
    }
    return values;
}

inline std::size_t CountFilledCells(const Board& board)
{
    return kCellCount - static_cast<std::size_t>(std::ranges::count(GetValues(board), kEmptyValue));
}

inline bool FollowsTheRules(const Board& board)
{
    for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
    {
        const std::size_t row = cellIndex / kBoardSize;
        const std::size_t column = cellIndex % kBoardSize;

        if (!board.IsEmpty(row, column) && !board.CanPlace(row, column, board.GetValue(row, column)))
        {
            return false;
        }
    }
    return true;
}

inline Board GetSolution(Board puzzle)
{
    Solver().FillBoard(puzzle);
    return puzzle;
}

}
