#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace sudoku::gui
{
class BoardView
{
  public:
    BoardView(sf::Vector2f topLeft, float cellSize);

    void Draw(sf::RenderTarget& target) const;

  private:
    sf::RectangleShape m_background;
    std::vector<sf::RectangleShape> m_gridLines;
};
} 
