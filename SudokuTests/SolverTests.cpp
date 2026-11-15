#include "Solver.h"
#include "helpers/BoardHelpers.h"

#include <gtest/gtest.h>

namespace sudoku::test
{

class SolverTests : public ::testing::Test
{
protected:
    static constexpr unsigned kSeed = 7;
    static constexpr unsigned kOtherSeed = 13;

    static Board CreateFilledBoard(unsigned seed)
    {
        Board board;
        Solver(seed).FillBoard(board);
        return board;
    }

    static Board CreateUnsolvableBoard()
    {
        Board board;
        for (std::size_t column = 0; column < kBoardSize - 1; ++column)
        {
            board.SetValue(0, column, static_cast<int>(column) + kMinValue);
        }
        board.SetValue(1, kBoardSize - 1, kMaxValue);
        return board;
    }
};

TEST_F(SolverTests, FillBoardFillsAnEmptyBoardCompletely)
{
    Board board;
    EXPECT_TRUE(Solver(kSeed).FillBoard(board));
    EXPECT_EQ(CountFilledCells(board), kCellCount);
}

TEST_F(SolverTests, FilledBoardFollowsTheRules)
{
    EXPECT_TRUE(FollowsTheRules(CreateFilledBoard(kSeed)));
}

TEST_F(SolverTests, SameSeedFillsTheSameBoard)
{
    EXPECT_EQ(GetValues(CreateFilledBoard(kSeed)), GetValues(CreateFilledBoard(kSeed)));
}

TEST_F(SolverTests, DifferentSeedsFillDifferentBoards)
{
    EXPECT_NE(GetValues(CreateFilledBoard(kSeed)), GetValues(CreateFilledBoard(kOtherSeed)));
}

TEST_F(SolverTests, FilledBoardHasOneSolution)
{
    EXPECT_EQ(Solver().CountSolutions(CreateFilledBoard(kSeed), 2), 1u);
}

TEST_F(SolverTests, EmptyBoardReachesTheSolutionLimit)
{
    EXPECT_EQ(Solver().CountSolutions(Board(), 2), 2u);
}

TEST_F(SolverTests, FillBoardKeepsTheExistingValues)
{
    Board board;
    board.SetValue(4, 4, 5);
    Solver(kSeed).FillBoard(board);
    EXPECT_EQ(board.GetValue(4, 4), 5);
}

TEST_F(SolverTests, UnsolvableBoardCannotBeFilled)
{
    Board board = CreateUnsolvableBoard();
    EXPECT_FALSE(Solver(kSeed).FillBoard(board));
}

TEST_F(SolverTests, UnsolvableBoardHasNoSolution)
{
    EXPECT_EQ(Solver().CountSolutions(CreateUnsolvableBoard(), 2), 0u);
}

}
