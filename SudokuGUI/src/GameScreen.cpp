#include "GameScreen.h"
#include "Theme.h"

namespace sudoku::gui
{
GameScreen::GameScreen(const sf::Font& font)
    : m_boardView(GetBoardTopLeft(), kBoardCellSize), m_numberPad(font, GetNumberPadTopLeft())
{
}

void GameScreen::Draw(sf::RenderTarget& target) const
{
    m_boardView.Draw(target);
    m_numberPad.Draw(target);
}

sf::Vector2f GameScreen::GetBoardTopLeft() const
{
    return GetGroupTopLeft();
}

sf::Vector2f GameScreen::GetNumberPadTopLeft() const
{
    const sf::Vector2f boardTopLeft = GetBoardTopLeft();
    return {boardTopLeft.x + kBoardPixelSize + kPadBoardSpacing, boardTopLeft.y};
}

sf::Vector2f GameScreen::GetGroupTopLeft() const
{
    const float padWidth =(static_cast<float>(kPadColumns) * kPadButtonSize) + (static_cast<float>(kPadColumns - 1) * kPadButtonSpacing);

    const float totalWidth = kBoardPixelSize + kPadBoardSpacing + padWidth;

    return {(static_cast<float>(kWindowWidth) - totalWidth) / kHalf, (static_cast<float>(kWindowHeight) - kBoardPixelSize) / kHalf};
}

void GameScreen::HandleMouseMove(sf::Vector2f mousePosition)
{
    m_numberPad.HandleMouseMove(mousePosition);
}

} 
