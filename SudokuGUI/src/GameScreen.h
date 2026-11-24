#pragma once

#include "BoardView.h"
#include "NumberPad.h"
#include "TitleText.h"

#include "SudokuLogic/IGame.h"

#include <SFML/Graphics.hpp>

namespace sudoku::gui
{
class GameScreen
{
  public:
    explicit GameScreen(const sf::Font& font);

    void Draw(sf::RenderTarget& target, const IGame& game) const;
    void HandleMouseMove(sf::Vector2f mousePosition);
    void HandleClick(sf::Vector2f mousePosition, IGame& game);

  private:
    sf::Vector2f GetBoardTopLeft() const;
    sf::Vector2f GetNumberPadTopLeft() const;
    void DrawDifficultyTitle(sf::RenderTarget& target, const IGame& game) const;
    void DrawMistakes(sf::RenderTarget& target, const IGame& game) const;

    const sf::Font& m_font;
    BoardView m_boardView;
    NumberPad m_numberPad;
    TitleText m_title;
};
} 
