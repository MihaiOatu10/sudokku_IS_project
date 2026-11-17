#pragma once

#include <SFML/Graphics.hpp>

#include <string_view>
#include <vector>

namespace sudoku::gui
{
class TitleText
{
  public:
    TitleText(const sf::Font& font, std::string_view text, unsigned characterSize, float letterSpacing);

    float GetWidth() const;
    void SetPosition(sf::Vector2f position);
    void CenterAbove(sf::Vector2f areaTopLeft, float areaWidth, float gap);
    void Draw(sf::RenderTarget& target) const;

  private:
    std::vector<sf::Text> m_letters;
    unsigned m_characterSize;
    float m_letterSpacing;
};
}
