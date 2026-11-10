#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

namespace sudoku::gui
{

class Background
{
public:
    Background(sf::Vector2f size, const sf::Font& font);

    void Draw(sf::RenderTarget& target) const;

private:
    void AddRuledLines(sf::Vector2f size);
    void AddShapeDoodles();
    void AddDigitDoodles(const sf::Font& font);

    std::vector<std::unique_ptr<sf::Drawable>> m_drawables;
};

}
