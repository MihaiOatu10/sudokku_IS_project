#include "Button.h"

#include "Theme.h"

#include <array>
#include <cstdint>
#include <limits>

namespace sudoku::gui
{

namespace
{
constexpr sf::Angle kQuarterTurn = sf::degrees(90.f);
constexpr std::array<sf::Vector2f, 4> kCornerDirections{{{1.f, 1.f}, {-1.f, 1.f}, {-1.f, -1.f}, {1.f, -1.f}}};
constexpr float kNormalScale = 1.f;
constexpr int kMaxColorChannel = std::numeric_limits<std::uint8_t>::max();

sf::ConvexShape CreateRoundedRectangle(sf::Vector2f size, float cornerRadius)
{
    const sf::Vector2f cornerCenterOffset = size / 2.f - sf::Vector2f(cornerRadius, cornerRadius);
    const sf::Angle pointAngleStep = kQuarterTurn / static_cast<float>(kButtonCornerPointCount - 1);
    sf::ConvexShape shape(kCornerDirections.size() * kButtonCornerPointCount);
    std::size_t pointIndex = 0;
    for (std::size_t corner = 0; corner < kCornerDirections.size(); ++corner)
    {
        const sf::Vector2f cornerCenter = cornerCenterOffset.componentWiseMul(kCornerDirections[corner]);
        const sf::Angle cornerStartAngle = kQuarterTurn * static_cast<float>(corner);
        for (std::size_t step = 0; step < kButtonCornerPointCount; ++step)
        {
            const sf::Angle angle = cornerStartAngle + pointAngleStep * static_cast<float>(step);
            shape.setPoint(pointIndex++, cornerCenter + sf::Vector2f(cornerRadius, angle));
        }
    }
    return shape;
}

std::uint8_t LightenChannel(std::uint8_t channel)
{
    const float distanceToWhite = static_cast<float>(kMaxColorChannel - channel);
    return static_cast<std::uint8_t>(static_cast<float>(channel) + distanceToWhite * kButtonHoverLightenRatio);
}

sf::Color Lighten(sf::Color color)
{
    return {LightenChannel(color.r), LightenChannel(color.g), LightenChannel(color.b), color.a};
}
}

Button::Button(const sf::Font& font, const std::string& label, sf::Vector2f center, sf::Vector2f size)
    : m_shape(CreateRoundedRectangle(size, kButtonCornerRadius)), m_label(font, label, kButtonCharacterSize),
      m_bounds(center - size / 2.f, size)
{
    m_shape.setPosition(center);
    m_label.setStyle(sf::Text::Bold);
    m_label.setOrigin(m_label.getLocalBounds().getCenter());
    m_label.setPosition(center);
    ApplyStyle();
}

void Button::SetEnabled(bool isEnabled)
{
    m_isEnabled = isEnabled;
    ApplyStyle();
}

void Button::SetSelected(bool isSelected)
{
    m_isSelected = isSelected;
    ApplyStyle();
}

bool Button::Contains(sf::Vector2f point) const
{
    return m_bounds.contains(point);
}

void Button::UpdateHover(sf::Vector2f mousePosition)
{
    m_isHovered = Contains(mousePosition);
    ApplyStyle();
}

void Button::Draw(sf::RenderTarget& target) const
{
    target.draw(m_shape);
    target.draw(m_label);
}

void Button::ApplyStyle()
{
    const bool isHighlighted = m_isEnabled && m_isHovered;
    const float scale = isHighlighted ? kButtonHoverScale : kNormalScale;
    const sf::Color baseFillColor = GetBaseFillColor();
    const sf::Color inkColor = m_isEnabled ? kInkColor : kDisabledInkColor;

    m_shape.setFillColor(isHighlighted ? Lighten(baseFillColor) : baseFillColor);
    m_shape.setOutlineColor(inkColor);
    m_shape.setOutlineThickness(m_isSelected ? kButtonSelectedOutlineThickness : kButtonOutlineThickness);
    m_shape.setScale({scale, scale});
    m_label.setFillColor(inkColor);
    m_label.setScale({scale, scale});
}

sf::Color Button::GetBaseFillColor() const
{
    if (!m_isEnabled)
    {
        return kButtonDisabledColor;
    }
    return m_isSelected ? kButtonSelectedColor : kButtonColor;
}

}
