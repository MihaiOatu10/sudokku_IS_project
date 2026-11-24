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

TEST_F(MenuTests, NoGameExistsBeforePlay)
{
    EXPECT_EQ(m_menu->GetGame(), nullptr);
}

TEST_F(MenuTests, PlayWhileLockedStaysInMainMenu)
{
    m_menu->Play();
    EXPECT_EQ(m_menu->GetCurrentScreen(), EScreen::MainMenu);
}

class MenuInGameTests : public MenuTests
{
protected:
    static constexpr EDifficulty kSelectedDifficulty = EDifficulty::Medium;
    static constexpr EDifficulty kOtherDifficulty = EDifficulty::Easy;

    MenuInGameTests()
    {
        m_menu->SelectDifficulty(kSelectedDifficulty);
        m_menu->Play();
    }

    void ExpectAGameOfDifficulty(EDifficulty difficulty) const
    {
        ASSERT_NE(m_menu->GetGame(), nullptr);
        EXPECT_EQ(m_menu->GetGame()->GetDifficulty(), difficulty);
    }
};

TEST_F(MenuInGameTests, PlayAfterSelectingADifficultyOpensTheGame)
{
    EXPECT_EQ(m_menu->GetCurrentScreen(), EScreen::Game);
}

TEST_F(MenuInGameTests, PlayCreatesAGameWithTheSelectedDifficulty)
{
    ExpectAGameOfDifficulty(kSelectedDifficulty);
}

TEST_F(MenuInGameTests, ReturningToTheMainMenuShowsTheMainMenu)
{
    m_menu->ReturnToMainMenu();
    EXPECT_EQ(m_menu->GetCurrentScreen(), EScreen::MainMenu);
}

TEST_F(MenuInGameTests, ReturningToTheMainMenuEndsTheGame)
{
    m_menu->ReturnToMainMenu();
    EXPECT_EQ(m_menu->GetGame(), nullptr);
}

TEST_F(MenuInGameTests, ReturningToTheMainMenuKeepsTheDifficultyAndPlayUnlocked)
{
    m_menu->ReturnToMainMenu();
    EXPECT_EQ(m_menu->GetSelectedDifficulty(), kSelectedDifficulty);
    EXPECT_TRUE(m_menu->IsPlayUnlocked());
}

TEST_F(MenuInGameTests, PlayAfterReturningToTheMainMenuCreatesANewGame)
{
    m_menu->ReturnToMainMenu();
    m_menu->SelectDifficulty(kOtherDifficulty);
    m_menu->Play();
    ExpectAGameOfDifficulty(kOtherDifficulty);
}

}
