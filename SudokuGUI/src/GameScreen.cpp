#include "GameScreen.h"

#include "Theme.h"

#include "SudokuLogic/EDifficulty.h"

#include <optional>
#include <string>

namespace sudoku::gui
{
GameScreen::GameScreen(const sf::Font& font)
    : m_font(font), m_boardView(font, GetBoardTopLeft()), m_numberPad(font, GetNumberPadTopLeft()),
      m_title(font, kTitleText, kSmallTitleFontSize, kSmallTitleSpacing)
{
    m_title.CenterAbove(GetNumberPadTopLeft(), kPadWidth, kTitlePadSpacing);
}

void GameScreen::Draw(sf::RenderTarget& target, const IGame& game) const
{
    m_boardView.Draw(target, game);
    DrawMistakes(target, game);
    m_numberPad.Draw(target);
    m_title.Draw(target);
    DrawDifficultyTitle(target, game);
}

void GameScreen::HandleMouseMove(sf::Vector2f mousePosition)
{
    m_numberPad.HandleMouseMove(mousePosition);
}

void GameScreen::HandleClick(sf::Vector2f mousePosition, IGame& game)
{
    if (const std::optional<CellPosition> cell = m_boardView.FindCellAt(mousePosition))
    {
        game.SelectCell(cell->row, cell->column);
        return;
    }
    if (const std::optional<int> value = m_numberPad.FindValueAt(mousePosition))
    {
        game.EnterValue(*value);
    }
}

sf::Vector2f GameScreen::GetNumberPadTopLeft() const
{
    const sf::Vector2f boardTopLeft = GetBoardTopLeft();
    return {boardTopLeft.x + kBoardPixelSize + kPadBoardSpacing,
            boardTopLeft.y + (kBoardPixelSize - kPadHeight) / kHalf};
}

sf::Vector2f GameScreen::GetBoardTopLeft() const
{
    const float totalWidth = kBoardPixelSize + kPadBoardSpacing + kPadWidth;

    return {(static_cast<float>(kWindowWidth) - totalWidth) / kHalf,
            (static_cast<float>(kWindowHeight) - kBoardPixelSize) / kHalf};
}

void GameScreen::DrawDifficultyTitle(sf::RenderTarget& target, const IGame& game) const
{
    TitleText difficultyTitle(m_font, GetDifficultyName(game.GetDifficulty()), kDifficultyTitleFontSize,
                              kDifficultyTitleSpacing);
    difficultyTitle.CenterAbove(GetBoardTopLeft(), kBoardPixelSize, kDifficultyTitleBoardSpacing);
    difficultyTitle.Draw(target);
}

void GameScreen::DrawMistakes(sf::RenderTarget& target, const IGame& game) const
{
    const std::string label =
        std::string(kMistakesPrefix) + std::to_string(game.GetMistakeCount()) + "/" + std::to_string(kMaxMistakes);
    sf::Text text(m_font, label, kMistakesFontSize);
    text.setFillColor(kInkColor);

    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.getCenter().x, bounds.position.y});

    const sf::Vector2f padTopLeft = GetNumberPadTopLeft();
    text.setPosition({padTopLeft.x + kPadWidth / kHalf, padTopLeft.y + kPadHeight + kMistakesPadSpacing});
    target.draw(text);
}
} 
