#include "PuzzleGenerator.h"
#include "helpers/BoardHelpers.h"
#include "helpers/GameCreationTests.h"

#include <gtest/gtest.h>

#include <array>
#include <stdexcept>
#include <vector>

namespace sudoku::test
{

class GameMoveTests : public GameCreationTests
{
protected:
    static constexpr unsigned kSeed = 7;

    static void SetUpTestSuite()
    {
        s_puzzle = PuzzleGenerator(kSeed).Generate(kDifficulty);
        s_solution = GetSolution(s_puzzle);

        std::vector<std::size_t> emptyCellIndexes;
        for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
        {
            if (s_puzzle.IsEmpty(cellIndex / kBoardSize, cellIndex % kBoardSize))
            {
                emptyCellIndexes.push_back(cellIndex);
            }
            else
            {
                s_givenCellIndex = cellIndex;
            }
        }
        s_emptyCellIndexes = emptyCellIndexes;
    }

    static int GetCorrectValue(std::size_t cellIndex)
    {
        return s_solution.GetValue(cellIndex / kBoardSize, cellIndex % kBoardSize);
    }

    static int GetWrongValue(std::size_t cellIndex)
    {
        return GetCorrectValue(cellIndex) % kMaxValue + kMinValue;
    }

    void SelectCell(std::size_t cellIndex)
    {
        m_game->SelectCell(cellIndex / kBoardSize, cellIndex % kBoardSize);
    }

    void EnterValue(std::size_t cellIndex, int value)
    {
        SelectCell(cellIndex);
        m_game->EnterValue(value);
    }

    void MakeMistake(std::size_t mistake)
    {
        EnterValue(s_emptyCellIndexes[mistake], GetWrongValue(s_emptyCellIndexes[mistake]));
    }

    void MakeMaxMistakes()
    {
        for (std::size_t mistake = 0; mistake < kMaxMistakes; ++mistake)
        {
            MakeMistake(mistake);
        }
    }

    int GetCellValue(std::size_t cellIndex) const
    {
        return m_game->GetCellValue(cellIndex / kBoardSize, cellIndex % kBoardSize);
    }

    ECellState GetCellState(std::size_t cellIndex) const
    {
        return m_game->GetCellState(cellIndex / kBoardSize, cellIndex % kBoardSize);
    }

    std::array<int, kCellCount> GetGameValues() const
    {
        std::array<int, kCellCount> values{};
        for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
        {
            values[cellIndex] = GetCellValue(cellIndex);
        }
        return values;
    }

    static inline Board s_puzzle;
    static inline Board s_solution;
    static inline std::vector<std::size_t> s_emptyCellIndexes;
    static inline std::size_t s_givenCellIndex = 0;

    std::unique_ptr<IGame> m_game = CreateGame(s_puzzle);
    const std::size_t m_cellIndex = s_emptyCellIndexes.front();
};

TEST_F(GameMoveTests, SelectingACellSelectsOnlyThatCell)
{
    SelectCell(s_emptyCellIndexes.back());
    SelectCell(m_cellIndex);

    for (std::size_t cellIndex = 0; cellIndex < kCellCount; ++cellIndex)
    {
        EXPECT_EQ(m_game->IsCellSelected(cellIndex / kBoardSize, cellIndex % kBoardSize), cellIndex == m_cellIndex);
    }
}

TEST_F(GameMoveTests, SelectingACellOutsideTheBoardThrows)
{
    EXPECT_THROW(m_game->SelectCell(kBoardSize, 0), std::out_of_range);
    EXPECT_THROW(m_game->SelectCell(0, kBoardSize), std::out_of_range);
}

TEST_F(GameMoveTests, EnteringAValueWithoutASelectedCellChangesNothing)
{
    m_game->EnterValue(GetCorrectValue(m_cellIndex));

    EXPECT_EQ(GetGameValues(), GetValues(s_puzzle));
    EXPECT_EQ(m_game->GetMistakeCount(), 0u);
}

TEST_F(GameMoveTests, CorrectValueMakesTheCellCorrectWithoutAMistake)
{
    EnterValue(m_cellIndex, GetCorrectValue(m_cellIndex));

    EXPECT_EQ(GetCellState(m_cellIndex), ECellState::Correct);
    EXPECT_EQ(m_game->GetMistakeCount(), 0u);
}

TEST_F(GameMoveTests, WrongValueStaysOnTheBoardAsAMistake)
{
    EnterValue(m_cellIndex, GetWrongValue(m_cellIndex));

    EXPECT_EQ(GetCellState(m_cellIndex), ECellState::Wrong);
    EXPECT_EQ(GetCellValue(m_cellIndex), GetWrongValue(m_cellIndex));
    EXPECT_EQ(m_game->GetMistakeCount(), 1u);
}

TEST_F(GameMoveTests, EnteringTheSameWrongValueAgainIsNotANewMistake)
{
    EnterValue(m_cellIndex, GetWrongValue(m_cellIndex));
    EnterValue(m_cellIndex, GetWrongValue(m_cellIndex));

    EXPECT_EQ(m_game->GetMistakeCount(), 1u);
}

TEST_F(GameMoveTests, WrongValueCanBeReplacedByTheCorrectOne)
{
    EnterValue(m_cellIndex, GetWrongValue(m_cellIndex));
    EnterValue(m_cellIndex, GetCorrectValue(m_cellIndex));

    EXPECT_EQ(GetCellState(m_cellIndex), ECellState::Correct);
}

TEST_F(GameMoveTests, GivenCellCannotBeChanged)
{
    EnterValue(s_givenCellIndex, GetWrongValue(s_givenCellIndex));

    EXPECT_EQ(GetCellValue(s_givenCellIndex), GetCorrectValue(s_givenCellIndex));
    EXPECT_EQ(m_game->GetMistakeCount(), 0u);
}

TEST_F(GameMoveTests, CorrectCellCannotBeChanged)
{
    EnterValue(m_cellIndex, GetCorrectValue(m_cellIndex));
    EnterValue(m_cellIndex, GetWrongValue(m_cellIndex));

    EXPECT_EQ(GetCellValue(m_cellIndex), GetCorrectValue(m_cellIndex));
    EXPECT_EQ(m_game->GetMistakeCount(), 0u);
}

TEST_F(GameMoveTests, GameIsLostOnlyAtTheMaximumNumberOfMistakes)
{
    for (std::size_t mistake = 0; mistake < kMaxMistakes; ++mistake)
    {
        EXPECT_EQ(m_game->GetState(), EGameState::InProgress);
        MakeMistake(mistake);
    }

    EXPECT_EQ(m_game->GetState(), EGameState::Lost);
}

TEST_F(GameMoveTests, NoValueCanBeEnteredAfterTheGameIsLost)
{
    MakeMaxMistakes();
    const std::size_t cellIndex = s_emptyCellIndexes[kMaxMistakes];

    EnterValue(cellIndex, GetCorrectValue(cellIndex));

    EXPECT_EQ(GetCellState(cellIndex), ECellState::Empty);
}

TEST_F(GameMoveTests, FillingEveryEmptyCellCorrectlyWinsTheGame)
{
    for (std::size_t cellIndex : s_emptyCellIndexes)
    {
        EXPECT_EQ(m_game->GetState(), EGameState::InProgress);
        EnterValue(cellIndex, GetCorrectValue(cellIndex));
    }

    EXPECT_EQ(m_game->GetState(), EGameState::Won);
}

}
