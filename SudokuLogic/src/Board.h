#pragma once

#include "SudokuLogic/BoardConstants.h"

#include <array>
#include <cstddef>

namespace sudoku
{

class Board
{
public:
    int GetValue(std::size_t row, std::size_t column) const;
    void SetValue(std::size_t row, std::size_t column, int value);
    void ClearValue(std::size_t row, std::size_t column);
    bool IsEmpty(std::size_t row, std::size_t column) const;
    bool CanPlace(std::size_t row, std::size_t column, int value) const;

private:
    bool IsOtherCellHolding(std::size_t otherRow, std::size_t otherColumn, std::size_t row, std::size_t column,
                            int value) const;

    std::array<std::array<int, kBoardSize>, kBoardSize> m_cells{};
};

}
