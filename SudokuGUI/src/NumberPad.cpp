#include "NumberPad.h"
#include "SudokuLogic/BoardConstants.h"
#include "Theme.h"
#include <string>
#include <utility>

namespace sudoku::gui
{
NumberPad::NumberPad(const sf::Font& font, sf::Vector2f topLeft)
{
    const sf::Vector2f buttonSize{kPadButtonSize, kPadButtonSize};
    const float step = kPadButtonSize + kPadButtonSpacing;
    const float halfSize = kPadButtonSize / kHalf;

    for (int value = kMinValue; value <= kMaxValue; ++value)
    {
        const int index = value - kMinValue;
        const int row = index / kPadColumns;
        const int column = index % kPadColumns;
        const sf::Vector2f position{topLeft.x + (static_cast<float>(column) * step) + halfSize, topLeft.y + (static_cast<float>(row) * step) + halfSize};
        m_buttons.emplace_back(font, std::to_string(value), position, buttonSize);
    }
}

void NumberPad::HandleMouseMove(sf::Vector2f mousePosition)
{
    for (auto& button : m_buttons)
        button.UpdateHover(mousePosition);
}

void NumberPad::Draw(sf::RenderTarget& target) const
{
    for (const auto& button : m_buttons)
        button.Draw(target);
}
} 
