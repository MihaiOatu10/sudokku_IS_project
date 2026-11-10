#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace sudoku::gui
{

class Button
{
public:
    Button(const sf::Font& font, const std::string& label, sf::Vector2f center, sf::Vector2f size);

    void SetEnabled(bool isEnabled);
    void SetSelected(bool isSelected);

    bool Contains(sf::Vector2f point) const;
    void UpdateHover(sf::Vector2f mousePosition);

    void Draw(sf::RenderTarget& target) const;

private:
    void ApplyStyle();
    sf::Color GetBaseFillColor() const;

    sf::ConvexShape m_shape;
    sf::Text m_label;
    sf::FloatRect m_bounds;
    bool m_isEnabled = true;
    bool m_isSelected = false;
    bool m_isHovered = false;
};

}
