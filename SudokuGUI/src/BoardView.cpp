#include "BoardView.h"
#include "SudokuLogic/BoardConstants.h"
#include "Theme.h"
#include <array>
#include <cstddef>

namespace sudoku::gui
{
namespace
{
constexpr sf::Angle kQuarterTurn = sf::degrees(90.f);
constexpr sf::Angle kHalfTurn = sf::degrees(180.f);
constexpr std::size_t kCornerCount = 4;
} 

BoardView::BoardView(sf::Vector2f topLeft, float cellSize)
{
    InitializeBackground(topLeft);
    InitializeGrid(topLeft, cellSize);
}

void BoardView::Draw(sf::RenderTarget& target) const
{
    target.draw(m_shadow);
    target.draw(m_background);
    for (const auto& line : m_gridLines)
    {
        target.draw(line);
    }
}

void BoardView::InitializeBackground(sf::Vector2f topLeft)
{
    const std::size_t pointsPerCorner = kButtonCornerPointCount;
    const std::size_t totalPoints = pointsPerCorner * kCornerCount;

    m_background.setPointCount(totalPoints);
    m_shadow.setPointCount(totalPoints);

    const float radius = kBoardCornerRadius;
    const sf::Vector2f size{kBoardPixelSize, kBoardPixelSize};
    const std::array centers{sf::Vector2f(radius, radius), sf::Vector2f(size.x - radius, radius),
                             sf::Vector2f(size.x - radius, size.y - radius), sf::Vector2f(radius, size.y - radius)};

    std::size_t pointIndex = 0;
    for (std::size_t corner = 0; corner < kCornerCount; ++corner)
    {
        const sf::Angle startAngle = kHalfTurn + kQuarterTurn * static_cast<float>(corner);
        for (std::size_t pointInCorner = 0; pointInCorner < pointsPerCorner; ++pointInCorner)
        {
            const float progress = static_cast<float>(pointInCorner) / static_cast<float>(pointsPerCorner - 1);
            const sf::Vector2f offset(radius, startAngle + kQuarterTurn * progress);
            m_background.setPoint(pointIndex, centers[corner] + offset);
            m_shadow.setPoint(pointIndex, centers[corner] + offset);
            ++pointIndex;
        }
    }

    m_background.setPosition(topLeft);
    m_background.setFillColor(kBoardBackgroundColor);
    m_background.setOutlineColor(kInkColor);
    m_background.setOutlineThickness(kThickLineThickness);

    m_shadow.setPosition({topLeft.x + kBoardShadowOffset, topLeft.y + kBoardShadowOffset});
    m_shadow.setFillColor(kBoardShadowColor);
}

void BoardView::InitializeGrid(sf::Vector2f topLeft, float cellSize)
{
    const float boardSize = cellSize * static_cast<float>(kBoardSize);

    for (int lineIndex = 1; lineIndex < kBoardSize; ++lineIndex)
    {
        const float offset = static_cast<float>(lineIndex) * cellSize;
        const bool isThickLine = (lineIndex % kBoxSize == 0);
        const float thickness = isThickLine ? kThickLineThickness : kThinLineThickness;
        const float halfThickness = thickness / kHalf;

        sf::RectangleShape horizontalLine({boardSize, thickness});
        horizontalLine.setPosition({topLeft.x, topLeft.y + offset - halfThickness});
        horizontalLine.setFillColor(kInkColor);
        m_gridLines.push_back(horizontalLine);

        sf::RectangleShape verticalLine({thickness, boardSize});
        verticalLine.setPosition({topLeft.x + offset - halfThickness, topLeft.y});
        verticalLine.setFillColor(kInkColor);
        m_gridLines.push_back(verticalLine);
    }
}

} 
