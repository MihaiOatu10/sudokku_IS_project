#include "TitleText.h"

#include "Theme.h"

#include <cstddef>
#include <string>
#include <utility>

namespace sudoku::gui
{
TitleText::TitleText(const sf::Font& font, std::string_view text, unsigned characterSize, float letterSpacing)
    : m_characterSize(characterSize), m_letterSpacing(letterSpacing)
{
    for (std::size_t letterIndex = 0; letterIndex < text.size(); ++letterIndex)
    {
        sf::Text letter(font, std::string(1, text[letterIndex]), characterSize);
        letter.setFillColor(kTitleColors[letterIndex % kTitleColors.size()]);
        letter.setOutlineColor(kTitleOutlineColor);
        letter.setOutlineThickness(kTitleOutlineThickness);
        letter.setRotation(sf::degrees(kTitleRotations[letterIndex % kTitleRotations.size()]));
        m_letters.push_back(std::move(letter));
    }
}

float TitleText::GetWidth() const
{
    return static_cast<float>(m_letters.size()) * m_letterSpacing;
}

void TitleText::SetPosition(sf::Vector2f position)
{
    for (std::size_t letterIndex = 0; letterIndex < m_letters.size(); ++letterIndex)
    {
        const float letterX = position.x + (static_cast<float>(letterIndex) * m_letterSpacing);
        m_letters[letterIndex].setPosition({letterX, position.y});
    }
}

void TitleText::CenterAbove(sf::Vector2f areaTopLeft, float areaWidth, float gap)
{
    const float startX = areaTopLeft.x + ((areaWidth - GetWidth()) / kHalf) + (m_letterSpacing / kHalf);
    const float startY = areaTopLeft.y - gap - static_cast<float>(m_characterSize);
    SetPosition({startX, startY});
}

void TitleText::Draw(sf::RenderTarget& target) const
{
    for (const auto& letter : m_letters)
    {
        target.draw(letter);
    }
}
}
