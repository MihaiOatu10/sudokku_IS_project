#pragma once

#include "BoardView.h"
#include "NumberPad.h"
#include "TitleText.h"

#include "SudokuLogic/IGame.h"

#include <SFML/Graphics.hpp>

#include <optional>

namespace sudoku::gui
{
class GameScreen
{
  public:
    explicit GameScreen(const sf::Font& font);

    void ShowGame(IGame& game);
    void Draw(sf::RenderTarget& target) const;
    void HandleMouseMove(sf::Vector2f mousePosition);

    void HandleClick(sf::Vector2f mousePosition);

  private:
    sf::Vector2f GetBoardTopLeft() const;
    sf::Vector2f GetNumberPadTopLeft() const;

    const sf::Font& m_font;
    BoardView m_boardView;
    NumberPad m_numberPad;
    TitleText m_title;
    std::optional<TitleText> m_difficultyTitle;
    IGame* m_game = nullptr;
};
}
