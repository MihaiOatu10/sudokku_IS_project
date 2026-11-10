#include "SudokuLogic/IMenu.h"
#include "mocks/MockMenuListener.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace sudoku::test
{

using ::testing::StrictMock;

class MenuListenerTests : public ::testing::Test
{
protected:
    MenuListenerTests()
    {
        m_menu->AddListener(&m_listener);
    }

    std::unique_ptr<IMenu> m_menu = IMenu::Produce();
    StrictMock<MockMenuListener> m_listener;
};

TEST_F(MenuListenerTests, FirstSelectionNotifiesDifficultyAndUnlocksPlay)
{
    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Hard));
    EXPECT_CALL(m_listener, OnPlayUnlocked());

    m_menu->SelectDifficulty(EDifficulty::Hard);
}

TEST_F(MenuListenerTests, ChangingTheDifficultyDoesNotUnlockPlayAgain)
{
    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Easy));
    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Expert));
    EXPECT_CALL(m_listener, OnPlayUnlocked()).Times(1);

    m_menu->SelectDifficulty(EDifficulty::Easy);
    m_menu->SelectDifficulty(EDifficulty::Expert);
}

TEST_F(MenuListenerTests, SelectingTheSameDifficultyAgainNotifiesNothing)
{
    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Medium)).Times(1);
    EXPECT_CALL(m_listener, OnPlayUnlocked()).Times(1);

    m_menu->SelectDifficulty(EDifficulty::Medium);
    m_menu->SelectDifficulty(EDifficulty::Medium);
}

TEST_F(MenuListenerTests, EveryListenerIsNotified)
{
    StrictMock<MockMenuListener> secondListener;
    m_menu->AddListener(&secondListener);

    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Easy));
    EXPECT_CALL(m_listener, OnPlayUnlocked());
    EXPECT_CALL(secondListener, OnDifficultySelected(EDifficulty::Easy));
    EXPECT_CALL(secondListener, OnPlayUnlocked());

    m_menu->SelectDifficulty(EDifficulty::Easy);
}

TEST_F(MenuListenerTests, AddingTheSameListenerTwiceNotifiesItOnce)
{
    m_menu->AddListener(&m_listener);

    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Easy)).Times(1);
    EXPECT_CALL(m_listener, OnPlayUnlocked()).Times(1);

    m_menu->SelectDifficulty(EDifficulty::Easy);
}

TEST_F(MenuListenerTests, RemovedListenerIsNotNotified)
{
    m_menu->RemoveListener(&m_listener);

    m_menu->SelectDifficulty(EDifficulty::Easy);
}

TEST_F(MenuListenerTests, AddingANullListenerIsIgnored)
{
    m_menu->AddListener(nullptr);

    EXPECT_CALL(m_listener, OnDifficultySelected(EDifficulty::Easy));
    EXPECT_CALL(m_listener, OnPlayUnlocked());

    m_menu->SelectDifficulty(EDifficulty::Easy);
}

}
