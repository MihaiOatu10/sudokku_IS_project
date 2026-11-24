#include "Solver.h"
#include "helpers/BoardHelpers.h"

#include <gtest/gtest.h>

#include <string>
#include <string_view>

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

    static Board CreatePartiallyFilledBoard()
    {
        Board board = CreateFilledBoard(kOtherSeed);
        for (std::size_t cellIndex = kBoxSize * kBoardSize; cellIndex < kCellCount; ++cellIndex)
        {
            board.ClearValue(cellIndex / kBoardSize, cellIndex % kBoardSize);
        }
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
    EXPECT_EQ(Solver().CountSolutions(CreateFilledBoard(kSeed), kSolutionLimit), 1u);
}

TEST_F(SolverTests, EmptyBoardReachesTheSolutionLimit)
{
    EXPECT_EQ(Solver().CountSolutions(Board(), kSolutionLimit), kSolutionLimit);
}

TEST_F(SolverTests, FillBoardKeepsTheExistingValues)
{
    Board board;
    board.SetValue(4, 4, 5);
    Solver(kSeed).FillBoard(board);
    EXPECT_EQ(board.GetValue(4, 4), 5);
}

TEST_F(SolverTests, FillBoardCompletesAPartiallyFilledBoardFollowingTheRules)
{
    Board board = CreatePartiallyFilledBoard();
    EXPECT_TRUE(Solver(kSeed).FillBoard(board));
    EXPECT_EQ(CountFilledCells(board), kCellCount);
    EXPECT_TRUE(FollowsTheRules(board));
}

TEST_F(SolverTests, UnsolvableBoardCannotBeFilled)
{
    Board board = CreateUnsolvableBoard();
    EXPECT_FALSE(Solver(kSeed).FillBoard(board));
}

TEST_F(SolverTests, UnsolvableBoardHasNoSolution)
{
    EXPECT_EQ(Solver().CountSolutions(CreateUnsolvableBoard(), kSolutionLimit), 0u);
}

TEST_F(SolverTests, FullBoardWithConflictingValuesIsNotASolution)
{
    Board board = CreateFilledBoard(kSeed);
    board.SetValue(0, 1, board.GetValue(0, 0));

    EXPECT_EQ(Solver().CountSolutions(board, kSolutionLimit), 0u);
    EXPECT_FALSE(Solver(kSeed).FillBoard(board));
}

struct ConflictingCell
{
    std::string_view name;
    std::size_t row;
    std::size_t column;
};

class SolverConflictTests : public SolverTests, public ::testing::WithParamInterface<ConflictingCell>
{
protected:
    static constexpr std::size_t kCellRow = 4;
    static constexpr std::size_t kCellColumn = 4;
    static constexpr int kValue = 5;

    SolverConflictTests()
    {
        m_board.SetValue(kCellRow, kCellColumn, kValue);
        m_board.SetValue(GetParam().row, GetParam().column, kValue);
    }

    Board m_board;
};

TEST_P(SolverConflictTests, BoardHasNoSolution)
{
    EXPECT_EQ(Solver().CountSolutions(m_board, kSolutionLimit), 0u);
}

TEST_P(SolverConflictTests, BoardCannotBeFilled)
{
    EXPECT_FALSE(Solver(kSeed).FillBoard(m_board));
}

INSTANTIATE_TEST_SUITE_P(SameValue, SolverConflictTests,
                         ::testing::Values(ConflictingCell{"InTheSameRow", 4, 0},
                                           ConflictingCell{"InTheSameColumn", 0, 4},
                                           ConflictingCell{"InTheSameBox", 3, 3}),
                         [](const ::testing::TestParamInfo<ConflictingCell>& info) {
                             return std::string(info.param.name);
                         });

}
