#pragma once

#include "SudokuLogic/IGame.h"

#include <SFML/Graphics.hpp>

#include <cstddef>
#include <vector>

namespace sudoku::gui
{
class BoardView
{
  public:
    BoardView(const sf::Font& font, sf::Vector2f topLeft);

    void Draw(sf::RenderTarget& target) const;
    void DrawDigits(sf::RenderTarget& target, const IGame& game) const;

  private:
    void InitializeGrid();
    void DrawCell(sf::RenderTarget& target, const IGame& game, std::size_t row, std::size_t column) const;
    sf::Text CreateDigit(int value, bool isGiven, sf::Vector2f center) const;
    sf::Vector2f GetCellTopLeft(std::size_t row, std::size_t column) const;
    sf::Vector2f GetCellCenter(std::size_t row, std::size_t column) const;

    const sf::Font& m_font;
    sf::Vector2f m_topLeft;
    sf::ConvexShape m_background;
    sf::ConvexShape m_shadow;
    std::vector<sf::RectangleShape> m_gridLines;
};
}
