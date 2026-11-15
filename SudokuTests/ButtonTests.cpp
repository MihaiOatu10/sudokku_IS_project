#include "Button.h"

#include <gtest/gtest.h>

namespace sudoku::test
{

class ButtonTests : public ::testing::Test
{
protected:
    sf::Font m_font;
    gui::Button m_button{m_font, "Play", {100.f, 50.f}, {80.f, 40.f}};
};

TEST_F(ButtonTests, HoveringTheButtonMakesItBigger)
{
    m_button.UpdateHover({100.f, 50.f});
    EXPECT_GT(m_button.GetScale(), 1.f);
}

TEST_F(ButtonTests, ButtonIsNormalSizeWhenNotHovered)
{
    m_button.UpdateHover({300.f, 300.f});
    EXPECT_FLOAT_EQ(m_button.GetScale(), 1.f);
}

}
