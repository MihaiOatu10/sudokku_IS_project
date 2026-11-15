#include "Board.h"

#include <stdexcept>

namespace sudoku
{

namespace
{
bool IsValidValue(int value)
{
    return value >= kMinValue && value <= kMaxValue;
}
}

int Board::GetValue(std::size_t row, std::size_t column) const
{
    return m_cells.at(row).at(column);
}

void Board::SetValue(std::size_t row, std::size_t column, int value)
{
    if (!IsValidValue(value))
    {
        throw std::invalid_argument("A cell value must be between 1 and 9");
    }

    m_cells.at(row).at(column) = value;
}

void Board::ClearValue(std::size_t row, std::size_t column)
{
    m_cells.at(row).at(column) = kEmptyValue;
}

bool Board::IsEmpty(std::size_t row, std::size_t column) const
{
    return GetValue(row, column) == kEmptyValue;
}

bool Board::CanPlace(std::size_t row, std::size_t column, int value) const
{
    if (!IsValidValue(value))
    {
        return false;
    }

    const std::size_t firstBoxRow = row / kBoxSize * kBoxSize;
    const std::size_t firstBoxColumn = column / kBoxSize * kBoxSize;

    for (std::size_t index = 0; index < kBoardSize; ++index)
    {
        const std::size_t boxRow = firstBoxRow + index / kBoxSize;
        const std::size_t boxColumn = firstBoxColumn + index % kBoxSize;

        if (IsOtherCellHolding(row, index, row, column, value) || IsOtherCellHolding(index, column, row, column, value) ||
            IsOtherCellHolding(boxRow, boxColumn, row, column, value))
        {
            return false;
        }
    }

    return true;
}

bool Board::IsOtherCellHolding(std::size_t otherRow, std::size_t otherColumn, std::size_t row, std::size_t column,
                               int value) const
{
    const bool isSameCell = otherRow == row && otherColumn == column;
    return !isSameCell && GetValue(otherRow, otherColumn) == value;
}

}
