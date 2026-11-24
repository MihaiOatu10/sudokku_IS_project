#include "Solver.h"

#include <algorithm>
#include <numeric>

namespace sudoku
{

Solver::Solver(unsigned seed) : m_random(std::mt19937(seed))
{
}

bool Solver::FillBoard(Board& board)
{
    std::size_t solutionCount = 0;
    return !HasConflicts(board) && Search(board, 1, solutionCount);
}

std::size_t Solver::CountSolutions(Board board, std::size_t limit)
{
    std::size_t solutionCount = 0;
    if (!HasConflicts(board))
    {
        Search(board, limit, solutionCount);
    }
    return solutionCount;
}

bool Solver::HasConflicts(const Board& board) const
{
    for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
    {
        const std::size_t row = cellIndex / kBoardSize;
        const std::size_t column = cellIndex % kBoardSize;

        if (!board.IsEmpty(row, column) && !board.CanPlace(row, column, board.GetValue(row, column)))
        {
            return true;
        }
    }
    return false;
}

bool Solver::Search(Board& board, std::size_t limit, std::size_t& solutionCount)
{
    const std::optional<std::size_t> cellIndex = FindEmptyCellWithFewestOptions(board);
    if (!cellIndex.has_value())
    {
        ++solutionCount;
        return solutionCount >= limit;
    }

    const std::size_t row = *cellIndex / kBoardSize;
    const std::size_t column = *cellIndex % kBoardSize;

    for (int value : GetValuesToTry())
    {
        if (board.CanPlace(row, column, value))
        {
            board.SetValue(row, column, value);
            if (Search(board, limit, solutionCount))
            {
                return true;
            }
            board.ClearValue(row, column);
        }
    }

    return false;
}

std::optional<std::size_t> Solver::FindEmptyCellWithFewestOptions(const Board& board) const
{
    std::optional<std::size_t> bestCellIndex;
    std::size_t fewestOptions = kBoardSize + 1;

    for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
    {
        const std::size_t row = cellIndex / kBoardSize;
        const std::size_t column = cellIndex % kBoardSize;

        if (board.IsEmpty(row, column))
        {
            const std::size_t options = CountOptions(board, row, column);
            if (options < fewestOptions)
            {
                fewestOptions = options;
                bestCellIndex = cellIndex;
            }
        }
    }

    return bestCellIndex;
}

std::size_t Solver::CountOptions(const Board& board, std::size_t row, std::size_t column) const
{
    std::size_t options = 0;
    for (int value = kMinValue; value <= kMaxValue; ++value)
    {
        if (board.CanPlace(row, column, value))
        {
            ++options;
        }
    }
    return options;
}

std::array<int, kBoardSize> Solver::GetValuesToTry()
{
    std::array<int, kBoardSize> values{};
    std::iota(values.begin(), values.end(), kMinValue);

    if (m_random.has_value())
    {
        std::ranges::shuffle(values, *m_random);
    }

    return values;
}

}
