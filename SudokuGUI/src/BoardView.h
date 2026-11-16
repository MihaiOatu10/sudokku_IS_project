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
    void InitializeBackground(sf::Vector2f topLeft);
    void InitializeGrid(sf::Vector2f topLeft, float cellSize);

    sf::ConvexShape m_background;
    sf::ConvexShape m_shadow;
    std::vector<sf::RectangleShape> m_gridLines;
};
} 
