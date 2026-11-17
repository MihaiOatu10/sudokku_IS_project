#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace sudoku::gui
{
class NumberPad
{
  public:
    NumberPad(const sf::Font& font, sf::Vector2f topLeft);

    void HandleMouseMove(sf::Vector2f mousePosition);
    void Draw(sf::RenderTarget& target) const;

  private:
    std::vector<Button> m_buttons;
};
}
