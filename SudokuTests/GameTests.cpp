#include "Game.h"
#include "mocks/MockPuzzleGenerator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace sudoku::test
{

using ::testing::Return;
using ::testing::StrictMock;

class GameTests : public ::testing::Test
{
protected:
    GameTests()
    {
        m_puzzle.SetValue(0, 0, 5);
        m_puzzle.SetValue(8, 8, 3);

        EXPECT_CALL(m_generator, Generate(EDifficulty::Hard)).Times(1).WillOnce(Return(m_puzzle));
        m_game = std::make_unique<Game>(EDifficulty::Hard, m_generator);
    }

    Board m_puzzle;
    StrictMock<MockPuzzleGenerator> m_generator;
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

TEST_F(GameTests, GameKeepsItsDifficulty)
{
    EXPECT_EQ(m_game->GetDifficulty(), EDifficulty::Hard);
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
