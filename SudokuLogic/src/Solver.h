#pragma once

#include "Board.h"

#include <array>
#include <cstddef>
#include <optional>
#include <random>

namespace sudoku
{

class Solver
{
public:
    Solver() = default;
    explicit Solver(unsigned seed);

    bool FillBoard(Board& board);
    std::size_t CountSolutions(Board board, std::size_t limit);

private:
    bool Search(Board& board, std::size_t limit, std::size_t& solutionCount);
    std::optional<std::size_t> FindEmptyCellWithFewestOptions(const Board& board) const;
    std::size_t CountOptions(const Board& board, std::size_t row, std::size_t column) const;
    std::array<int, kBoardSize> GetValuesToTry();

    std::optional<std::mt19937> m_random;
};

}
