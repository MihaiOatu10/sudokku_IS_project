#include "GameScreen.h"
#include "Theme.h"

namespace sudoku::gui
{
GameScreen::GameScreen() : m_boardView(GetBoardTopLeft(), kBoardCellSize) {}

void GameScreen::Draw(sf::RenderTarget& target) const
{
    m_boardView.Draw(target);
}

sf::Vector2f GameScreen::GetBoardTopLeft() const
{
    return {(static_cast<float>(kWindowWidth) - kBoardPixelSize) / kHalf,
            (static_cast<float>(kWindowHeight) - kBoardPixelSize) / kHalf};
}
} 
