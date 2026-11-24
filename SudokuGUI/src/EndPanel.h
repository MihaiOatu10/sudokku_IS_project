#pragma once

#include "Button.h"

#include "SudokuLogic/EGameState.h"

#include <SFML/Graphics.hpp>

#include <string_view>

namespace sudoku::gui
{
class EndPanel
{
  public:
    explicit EndPanel(const sf::Font& font);

    void HandleMouseMove(sf::Vector2f mousePosition);
    bool IsMenuClicked(sf::Vector2f position) const;
    void Draw(sf::RenderTarget& target, EGameState state) const;

  private:
    void DrawMessage(sf::RenderTarget& target, std::string_view message) const;

    const sf::Font& m_font;
    sf::ConvexShape m_panel;
    Button m_menuButton;
};
}
