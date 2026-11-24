#include "GameScreen.h"

#include "Theme.h"

#include "SudokuLogic/EDifficulty.h"

#include <string>

namespace sudoku::gui
{
GameScreen::GameScreen(const sf::Font& font)
    : m_font(font), m_boardView(font, GetBoardTopLeft()), m_numberPad(font, GetNumberPadTopLeft()),
      m_title(font, kTitleText, kSmallTitleFontSize, kSmallTitleSpacing)
{
    m_title.CenterAbove(GetNumberPadTopLeft(), kPadWidth, kTitlePadSpacing);
}

void GameScreen::ShowGame(IGame& game)
{
    m_game = &game;
    m_difficultyTitle.emplace(m_font, GetDifficultyName(game.GetDifficulty()), kDifficultyTitleFontSize,
                              kDifficultyTitleSpacing);
    m_difficultyTitle->CenterAbove(GetBoardTopLeft(), kBoardPixelSize, kDifficultyTitleBoardSpacing);
}

void GameScreen::Draw(sf::RenderTarget& target) const
{
    m_boardView.Draw(target, m_game);
    if (m_game)
    {
        m_boardView.DrawDigits(target, *m_game);
        DrawMistakes(target);
    }
    m_numberPad.Draw(target);
    m_title.Draw(target);
    if (m_difficultyTitle)
    {
        m_difficultyTitle->Draw(target);
    }
}

void GameScreen::HandleMouseMove(sf::Vector2f mousePosition)
{
    m_numberPad.HandleMouseMove(mousePosition);
}

void GameScreen::HandleClick(sf::Vector2f mousePosition)
{
    if (!m_game)
    {
        return;
    }

    if (const std::optional<CellPosition> cell = m_boardView.FindCellAt(mousePosition))
    {
        m_game->SelectCell(cell->row, cell->column);
        return;
    }
    if (const std::optional<int> value = m_numberPad.FindValueAt(mousePosition))
    {
        m_game->EnterValue(*value);
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

void GameScreen::DrawMistakes(sf::RenderTarget& target) const
{
    const std::string label =
        std::string(kMistakesPrefix) + std::to_string(m_game->GetMistakeCount()) + "/" + std::to_string(kMaxMistakes);
    sf::Text text(m_font, label, kMistakesFontSize);
    text.setFillColor(kInkColor);

    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.getCenter().x, bounds.position.y});

    const sf::Vector2f padTopLeft = GetNumberPadTopLeft();
    text.setPosition({padTopLeft.x + kPadWidth / kHalf, padTopLeft.y + kPadHeight + kMistakesPadSpacing});
    target.draw(text);
}
} 
