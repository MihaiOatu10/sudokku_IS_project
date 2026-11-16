#pragma once
#include "BoardView.h"
#include "NumberPad.h"
#include <SFML/Graphics.hpp>

#include <vector>

namespace sudoku::gui
{
class GameScreen
{
  public:
    explicit GameScreen(const sf::Font& font);

    void Draw(sf::RenderTarget& target) const;
    void HandleMouseMove(sf::Vector2f mousePosition);

  private:
    sf::Vector2f GetBoardTopLeft() const;
    sf::Vector2f GetNumberPadTopLeft() const;
    sf::Vector2f GetGroupTopLeft() const;
    void InitializeTitle(const sf::Font& font);

    BoardView m_boardView;
    NumberPad m_numberPad;
    std::vector<sf::Text> m_titleLetters;
};
} 
