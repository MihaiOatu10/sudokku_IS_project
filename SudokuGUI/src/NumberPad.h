#pragma once
#include "Button.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <utility>
#include <vector>

namespace sudoku::gui
{
class NumberPad
{
  public:
    NumberPad(const sf::Font& font, sf::Vector2f topLeft);

    void HandleMouseMove(sf::Vector2f mousePosition);
    void Draw(sf::RenderTarget& target) const;
    std::optional<int> FindValueAt(sf::Vector2f position) const;

  private:
    std::vector<std::pair<int, Button>> m_buttons;
};
}
