#pragma once

#include "Theme.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <cstddef>

namespace sudoku::gui
{
inline constexpr sf::Angle kQuarterTurn = sf::degrees(90.f);
inline constexpr std::array<sf::Vector2f, 4> kCornerDirections{{{1.f, 1.f}, {-1.f, 1.f}, {-1.f, -1.f}, {1.f, -1.f}}};

inline sf::ConvexShape CreateRoundedRectangle(sf::Vector2f size, float cornerRadius)
{
    const sf::Vector2f cornerCenterOffset = size / kHalf - sf::Vector2f(cornerRadius, cornerRadius);
    const sf::Angle pointAngleStep = kQuarterTurn / static_cast<float>(kCornerPointCount - 1);
    sf::ConvexShape shape(kCornerDirections.size() * kCornerPointCount);
    std::size_t pointIndex = 0;
    for (std::size_t corner = 0; corner < kCornerDirections.size(); ++corner)
    {
        const sf::Vector2f cornerCenter = cornerCenterOffset.componentWiseMul(kCornerDirections[corner]);
        const sf::Angle cornerStartAngle = kQuarterTurn * static_cast<float>(corner);
        for (std::size_t step = 0; step < kCornerPointCount; ++step)
        {
            const sf::Angle angle = cornerStartAngle + pointAngleStep * static_cast<float>(step);
            shape.setPoint(pointIndex++, cornerCenter + sf::Vector2f(cornerRadius, angle));
        }
    }
    return shape;
}
}
