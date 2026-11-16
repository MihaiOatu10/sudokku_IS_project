#include "BoardView.h"
#include "SudokuLogic/BoardConstants.h"
#include "Theme.h"
#include <utility>

namespace sudoku::gui
{
BoardView::BoardView(sf::Vector2f topLeft, float cellSize)
{
    const float boardPixelSize = static_cast<float>(kBoardSize) * cellSize;

    m_background.setSize({boardPixelSize, boardPixelSize});
    m_background.setPosition(topLeft);
    m_background.setFillColor(kBoardBackgroundColor);

    for (int lineIndex = 0; lineIndex <= kBoardSize; ++lineIndex)
    {
        const float offset = static_cast<float>(lineIndex) * cellSize;
        const bool isThickLine = (lineIndex % kBoxSize == 0);
        const float thickness = isThickLine ? kThickLineThickness : kThinLineThickness;
        const float halfThickness = thickness / kHalf;

        sf::RectangleShape horizontalLine({boardPixelSize + thickness, thickness});
        horizontalLine.setPosition({topLeft.x - halfThickness, topLeft.y + offset - halfThickness});
        horizontalLine.setFillColor(kInkColor);
        m_gridLines.push_back(std::move(horizontalLine));

        sf::RectangleShape verticalLine({thickness, boardPixelSize + thickness});
        verticalLine.setPosition({topLeft.x + offset - halfThickness, topLeft.y - halfThickness});
        verticalLine.setFillColor(kInkColor);
        m_gridLines.push_back(std::move(verticalLine));
    }
}

void BoardView::Draw(sf::RenderTarget& target) const
{
    target.draw(m_background);
    for (const auto& line : m_gridLines)
    {
        target.draw(line);
    }
}
} 
