#include "Game.h"
#include "mocks/MockPuzzleGenerator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>

namespace sudoku::test
{

using ::testing::Return;
using ::testing::StrictMock;

class GameCreationTests : public ::testing::Test
{
protected:
    static constexpr EDifficulty kDifficulty = EDifficulty::Hard;

    std::unique_ptr<IGame> CreateGame(const Board& puzzle)
    {
        EXPECT_CALL(m_generator, Generate(kDifficulty)).Times(1).WillOnce(Return(puzzle));
        return std::make_unique<Game>(kDifficulty, m_generator);
    }

    StrictMock<MockPuzzleGenerator> m_generator;
};

TEST_F(GameCreationTests, PuzzleWithoutASolutionCannotStartAGame)
{
    Board puzzle;
    puzzle.SetValue(0, 0, 5);
    puzzle.SetValue(0, 1, 5);

    EXPECT_THROW(CreateGame(puzzle), std::invalid_argument);
}

class GameTests : public GameCreationTests
{
protected:
    GameTests()
    {
        m_puzzle.SetValue(0, 0, 5);
        m_puzzle.SetValue(8, 8, 3);

        m_game = CreateGame(m_puzzle);
    }

    Board m_puzzle;
    std::unique_ptr<IGame> m_game;
};

TEST_F(GameTests, GameAsksForOnePuzzleOfItsDifficulty)
{
}

TEST_F(GameTests, CellValuesComeFromThePuzzle)
{
    EXPECT_EQ(m_game->GetCellValue(0, 0), 5);
    EXPECT_EQ(m_game->GetCellValue(8, 8), 3);
    EXPECT_EQ(m_game->GetCellValue(4, 4), kEmptyValue);
}

TEST_F(GameTests, FilledCellIsGiven)
{
    EXPECT_TRUE(m_game->IsCellGiven(0, 0));
}

TEST_F(GameTests, EmptyCellIsNotGiven)
{
    EXPECT_FALSE(m_game->IsCellGiven(4, 4));
}

TEST_F(GameTests, GivenCellHasTheGivenState)
{
    EXPECT_EQ(m_game->GetCellState(0, 0), ECellState::Given);
}

TEST_F(GameTests, EmptyCellHasTheEmptyState)
{
    EXPECT_EQ(m_game->GetCellState(4, 4), ECellState::Empty);
}

TEST_F(GameTests, GameKeepsItsDifficulty)
{
    EXPECT_EQ(m_game->GetDifficulty(), kDifficulty);
}

class ProducedGameTests : public ::testing::Test
{
protected:
    std::unique_ptr<IGame> m_game = IGame::Produce(EDifficulty::Easy);
};

TEST_F(ProducedGameTests, ProducedGameHasTheRequestedDifficulty)
{
    EXPECT_EQ(m_game->GetDifficulty(), EDifficulty::Easy);
}

TEST_F(ProducedGameTests, ProducedEasyGameHasFortyGivenCells)
{
    std::size_t givenCellCount = 0;
    for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
    {
        if (m_game->IsCellGiven(cellIndex / kBoardSize, cellIndex % kBoardSize))
        {
            ++givenCellCount;
        }
    }
    EXPECT_EQ(givenCellCount, 40u);
}

}
