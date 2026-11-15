#include "Board.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace sudoku::test
{

class BoardTests : public ::testing::Test
{
protected:
    Board m_board;
};

TEST_F(BoardTests, NewBoardHasAllCellsEmpty)
{
    for (std::size_t row = 0; row < kBoardSize; ++row)
    {
        for (std::size_t column = 0; column < kBoardSize; ++column)
        {
            EXPECT_TRUE(m_board.IsEmpty(row, column));
        }
    }
}

TEST_F(BoardTests, SetValueStoresTheValue)
{
    m_board.SetValue(2, 7, 8);
    EXPECT_EQ(m_board.GetValue(2, 7), 8);
}

TEST_F(BoardTests, ClearValueEmptiesTheCell)
{
    m_board.SetValue(2, 7, 8);
    m_board.ClearValue(2, 7);
    EXPECT_TRUE(m_board.IsEmpty(2, 7));
}

TEST_F(BoardTests, ValueOutsideOneToNineCannotBeSet)
{
    EXPECT_THROW(m_board.SetValue(0, 0, 0), std::invalid_argument);
    EXPECT_THROW(m_board.SetValue(0, 0, 10), std::invalid_argument);
}

TEST_F(BoardTests, ReadingOutsideTheBoardThrows)
{
    EXPECT_THROW(m_board.GetValue(9, 0), std::out_of_range);
    EXPECT_THROW(m_board.GetValue(0, 9), std::out_of_range);
}

TEST_F(BoardTests, ValueOutsideOneToNineCannotBePlaced)
{
    EXPECT_FALSE(m_board.CanPlace(0, 0, 0));
    EXPECT_FALSE(m_board.CanPlace(0, 0, 10));
}

class BoardPlacementTests : public BoardTests
{
protected:
    BoardPlacementTests()
    {
        m_board.SetValue(4, 4, 5);
    }
};

TEST_F(BoardPlacementTests, ValueInTheSameRowCannotBePlaced)
{
    EXPECT_FALSE(m_board.CanPlace(4, 0, 5));
}

TEST_F(BoardPlacementTests, ValueInTheSameColumnCannotBePlaced)
{
    EXPECT_FALSE(m_board.CanPlace(0, 4, 5));
}

TEST_F(BoardPlacementTests, ValueInTheSameBoxCannotBePlaced)
{
    EXPECT_FALSE(m_board.CanPlace(3, 3, 5));
}

TEST_F(BoardPlacementTests, ValueInAnotherRowColumnAndBoxCanBePlaced)
{
    EXPECT_TRUE(m_board.CanPlace(0, 0, 5));
}

TEST_F(BoardPlacementTests, CellHoldingTheValueCanStillPlaceIt)
{
    EXPECT_TRUE(m_board.CanPlace(4, 4, 5));
}

}
