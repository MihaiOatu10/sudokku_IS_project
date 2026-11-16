#include "GameScreen.h"
#include "Theme.h"

#include <cstddef>
#include <string>
#include <utility>

namespace sudoku::gui
{
GameScreen::GameScreen(const sf::Font& font)
    : m_boardView(GetBoardTopLeft(), kBoardCellSize), m_numberPad(font, GetNumberPadTopLeft())
{
    InitializeTitle(font);
}

void GameScreen::Draw(sf::RenderTarget& target) const
{
    m_boardView.Draw(target);
    m_numberPad.Draw(target);
    for (const auto& letter : m_titleLetters)
    {
        target.draw(letter);
    }
}

void GameScreen::InitializeTitle(const sf::Font& font)
{
    const sf::Vector2f padPos = GetNumberPadTopLeft();
    const float titleWidth = static_cast<float>(kTitleText.size()) * kSmallTitleSpacing;
    const float startX = padPos.x + (kPadWidth - titleWidth) / kHalf + (kSmallTitleSpacing / kHalf);
    const float titleY = padPos.y - kTitlePadSpacing - static_cast<float>(kSmallTitleFontSize);

    for (std::size_t letterIndex = 0; letterIndex < kTitleText.size(); ++letterIndex)
    {
        sf::Text letter(font, std::string(1, kTitleText[letterIndex]), static_cast<unsigned int>(kSmallTitleFontSize));
        letter.setFillColor(kTitleColors[letterIndex % kTitleColors.size()]);
        letter.setOutlineColor(kTitleOutlineColor);
        letter.setOutlineThickness(kTitleOutlineThickness);
        letter.setRotation(sf::degrees(kTitleRotations[letterIndex % kTitleRotations.size()]));
        letter.setPosition({startX + (static_cast<float>(letterIndex) * kSmallTitleSpacing), titleY});
        m_titleLetters.push_back(std::move(letter));
    }
}

sf::Vector2f GameScreen::GetBoardTopLeft() const
{
    return GetGroupTopLeft();
}

sf::Vector2f GameScreen::GetNumberPadTopLeft() const
{
    const sf::Vector2f boardTopLeft = GetBoardTopLeft();
    return {boardTopLeft.x + kBoardPixelSize + kPadBoardSpacing,
            boardTopLeft.y + (kBoardPixelSize - kPadHeight) / kHalf};
}

sf::Vector2f GameScreen::GetGroupTopLeft() const
{
    const float totalWidth = kBoardPixelSize + kPadBoardSpacing + kPadWidth;

    return {(static_cast<float>(kWindowWidth) - totalWidth) / kHalf,
            (static_cast<float>(kWindowHeight) - kBoardPixelSize) / kHalf};
}

void GameScreen::HandleMouseMove(sf::Vector2f mousePosition)
{
    m_numberPad.HandleMouseMove(mousePosition);
}

} 
