#pragma once
#include "BoardView.h"
#include <SFML/Graphics.hpp>

namespace sudoku::gui
{
class GameScreen
{
  public:
    GameScreen();

    void Draw(sf::RenderTarget& target) const;

  private:
    sf::Vector2f GetBoardTopLeft() const;
    BoardView m_boardView;
};
} 
