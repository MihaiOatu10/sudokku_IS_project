#include "PuzzleGenerator.h"
#include "Solver.h"
#include "helpers/BoardHelpers.h"

#include <gtest/gtest.h>

#include <map>

namespace sudoku::test
{

class PuzzleGeneratorTests : public ::testing::Test
{
protected:
    static constexpr unsigned kSeed = 7;
    static constexpr unsigned kOtherSeed = 13;

    static Board CreateEasyPuzzle(unsigned seed)
    {
        return PuzzleGenerator(seed).Generate(EDifficulty::Easy);
    }

    static void SetUpTestSuite()
    {
        PuzzleGenerator generator(kSeed);
        for (EDifficulty difficulty : kAllDifficulties)
        {
            s_puzzles[difficulty] = generator.Generate(difficulty);
        }
    }

    static inline std::map<EDifficulty, Board> s_puzzles;
};

TEST_F(PuzzleGeneratorTests, EachDifficultyHasItsGivenCellCount)
{
    EXPECT_EQ(PuzzleGenerator::GetGivenCellCount(EDifficulty::Easy), 40u);
    EXPECT_EQ(PuzzleGenerator::GetGivenCellCount(EDifficulty::Medium), 34u);
    EXPECT_EQ(PuzzleGenerator::GetGivenCellCount(EDifficulty::Hard), 30u);
    EXPECT_EQ(PuzzleGenerator::GetGivenCellCount(EDifficulty::Expert), 26u);
}

TEST_F(PuzzleGeneratorTests, HarderDifficultiesGiveFewerCells)
{
    for (std::size_t index = 1; index < kAllDifficulties.size(); ++index)
    {
        EXPECT_LT(PuzzleGenerator::GetGivenCellCount(kAllDifficulties[index]),
                  PuzzleGenerator::GetGivenCellCount(kAllDifficulties[index - 1]));
    }
}

TEST_F(PuzzleGeneratorTests, PuzzleHasTheGivenCellCountOfItsDifficulty)
{
    for (const auto& [difficulty, puzzle] : s_puzzles)
    {
        EXPECT_EQ(CountFilledCells(puzzle), PuzzleGenerator::GetGivenCellCount(difficulty));
    }
}

TEST_F(PuzzleGeneratorTests, PuzzleFollowsTheRules)
{
    for (const auto& [difficulty, puzzle] : s_puzzles)
    {
        EXPECT_TRUE(FollowsTheRules(puzzle));
    }
}

TEST_F(PuzzleGeneratorTests, PuzzleHasOneSolution)
{
    for (const auto& [difficulty, puzzle] : s_puzzles)
    {
        EXPECT_EQ(Solver().CountSolutions(puzzle, kSolutionLimit), 1u);
    }
}

TEST_F(PuzzleGeneratorTests, SameSeedGivesTheSamePuzzle)
{
    EXPECT_EQ(GetValues(CreateEasyPuzzle(kSeed)), GetValues(CreateEasyPuzzle(kSeed)));
}

TEST_F(PuzzleGeneratorTests, DifferentSeedsGiveDifferentPuzzles)
{
    EXPECT_NE(GetValues(CreateEasyPuzzle(kSeed)), GetValues(CreateEasyPuzzle(kOtherSeed)));
}

}
