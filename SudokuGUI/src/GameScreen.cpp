#include "GameScreen.h"

#include "Theme.h"

#include "SudokuLogic/EDifficulty.h"

namespace sudoku::gui
{
GameScreen::GameScreen(const sf::Font& font)
    : m_font(font), m_boardView(font, GetBoardTopLeft()), m_numberPad(font, GetNumberPadTopLeft()),
      m_title(font, kTitleText, kSmallTitleFontSize, kSmallTitleSpacing)
{
    m_title.CenterAbove(GetNumberPadTopLeft(), kPadWidth, kTitlePadSpacing);
}

void GameScreen::ShowGame(const IGame& game)
{
    m_game = &game;
    m_difficultyTitle.emplace(m_font, GetDifficultyName(game.GetDifficulty()), kDifficultyTitleFontSize,
                              kDifficultyTitleSpacing);
    m_difficultyTitle->CenterAbove(GetBoardTopLeft(), kBoardPixelSize, kDifficultyTitleBoardSpacing);
}

void GameScreen::Draw(sf::RenderTarget& target) const
{
    m_boardView.Draw(target);
    if (m_game)
    {
        m_boardView.DrawDigits(target, *m_game);
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
}
