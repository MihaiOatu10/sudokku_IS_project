#include "SudokuLogic/EDifficulty.h"

#include <gtest/gtest.h>

namespace sudoku::test
{

TEST(DifficultyTests, ThereAreFourDifficulties)
{
    EXPECT_EQ(kAllDifficulties.size(), 4u);
}

TEST(DifficultyTests, DifficultiesGoFromEasiestToHardest)
{
    EXPECT_EQ(kAllDifficulties[0], EDifficulty::Easy);
    EXPECT_EQ(kAllDifficulties[1], EDifficulty::Medium);
    EXPECT_EQ(kAllDifficulties[2], EDifficulty::Hard);
    EXPECT_EQ(kAllDifficulties[3], EDifficulty::Expert);
}

TEST(DifficultyTests, EachDifficultyHasItsName)
{
    EXPECT_EQ(GetDifficultyName(EDifficulty::Easy), "Easy");
    EXPECT_EQ(GetDifficultyName(EDifficulty::Medium), "Medium");
    EXPECT_EQ(GetDifficultyName(EDifficulty::Hard), "Hard");
    EXPECT_EQ(GetDifficultyName(EDifficulty::Expert), "Expert");
}

}
