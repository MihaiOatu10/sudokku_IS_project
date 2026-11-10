#include "SudokuLogic/IMenu.h"

#include <gtest/gtest.h>

namespace sudoku::test
{

class MenuTests : public ::testing::Test
{
protected:
    std::unique_ptr<IMenu> m_menu = IMenu::Produce();
};

TEST_F(MenuTests, NoDifficultyIsSelectedAtStart)
{
    EXPECT_FALSE(m_menu->GetSelectedDifficulty().has_value());
}

TEST_F(MenuTests, PlayIsLockedAtStart)
{
    EXPECT_FALSE(m_menu->IsPlayUnlocked());
}

TEST_F(MenuTests, SelectingADifficultyRemembersIt)
{
    for (EDifficulty difficulty : kAllDifficulties)
    {
        m_menu->SelectDifficulty(difficulty);
        EXPECT_EQ(m_menu->GetSelectedDifficulty(), difficulty);
    }
}

TEST_F(MenuTests, SelectingADifficultyUnlocksPlay)
{
    m_menu->SelectDifficulty(EDifficulty::Easy);
    EXPECT_TRUE(m_menu->IsPlayUnlocked());
}

TEST_F(MenuTests, SelectingAnotherDifficultyReplacesThePreviousOne)
{
    m_menu->SelectDifficulty(EDifficulty::Easy);
    m_menu->SelectDifficulty(EDifficulty::Expert);
    EXPECT_EQ(m_menu->GetSelectedDifficulty(), EDifficulty::Expert);
    EXPECT_TRUE(m_menu->IsPlayUnlocked());
}

TEST_F(MenuTests, ScreenIsMainMenuAtStart)
{
    EXPECT_EQ(m_menu->GetCurrentScreen(), EScreen::MainMenu);
}

TEST_F(MenuTests, PlayWhileLockedStaysInMainMenu)
{
    m_menu->Play();
    EXPECT_EQ(m_menu->GetCurrentScreen(), EScreen::MainMenu);
}

TEST_F(MenuTests, PlayAfterSelectingADifficultyOpensTheGame)
{
    m_menu->SelectDifficulty(EDifficulty::Easy);
    m_menu->Play();
    EXPECT_EQ(m_menu->GetCurrentScreen(), EScreen::Game);
}

}
