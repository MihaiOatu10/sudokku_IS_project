#include "BoardView.h"

#include "RoundedRectangle.h"
#include "SudokuLogic/BoardConstants.h"
#include "Theme.h"

#include <string>

namespace sudoku::gui
{
namespace
{
constexpr sf::Vector2f kBoardDimensions{kBoardPixelSize, kBoardPixelSize};
constexpr sf::Vector2f kShadowOffset{kBoardShadowOffset, kBoardShadowOffset};
}

BoardView::BoardView(const sf::Font& font, sf::Vector2f topLeft)
    : m_font(font), m_topLeft(topLeft), m_background(CreateRoundedRectangle(kBoardDimensions, kBoardCornerRadius)),
      m_shadow(m_background)
{
    const sf::Vector2f boardCenter = m_topLeft + kBoardDimensions / kHalf;

    m_background.setPosition(boardCenter);
    m_background.setFillColor(kBoardBackgroundColor);
    m_background.setOutlineColor(kInkColor);
    m_background.setOutlineThickness(kThickLineThickness);

    m_shadow.setPosition(boardCenter + kShadowOffset);
    m_shadow.setFillColor(kBoardShadowColor);

    InitializeGrid();
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

void BoardView::DrawDigits(sf::RenderTarget& target, const IGame& game) const
{
    for (std::size_t row = 0; row < kBoardSize; ++row)
    {
        for (std::size_t column = 0; column < kBoardSize; ++column)
        {
            DrawCell(target, game, row, column);
        }
    }
}

void BoardView::InitializeGrid()
{
    for (std::size_t lineIndex = 1; lineIndex < kBoardSize; ++lineIndex)
    {
        const sf::Vector2f lineCorner = GetCellTopLeft(lineIndex, lineIndex);
        const bool isThickLine = (lineIndex % kBoxSize == 0);
        const float thickness = isThickLine ? kThickLineThickness : kThinLineThickness;
        const float halfThickness = thickness / kHalf;

        sf::RectangleShape horizontalLine({kBoardPixelSize, thickness});
        horizontalLine.setPosition({m_topLeft.x, lineCorner.y - halfThickness});
        horizontalLine.setFillColor(kInkColor);
        m_gridLines.push_back(horizontalLine);

        sf::RectangleShape verticalLine({thickness, kBoardPixelSize});
        verticalLine.setPosition({lineCorner.x - halfThickness, m_topLeft.y});
        verticalLine.setFillColor(kInkColor);
        m_gridLines.push_back(verticalLine);
    }
}

void BoardView::DrawCell(sf::RenderTarget& target, const IGame& game, std::size_t row, std::size_t column) const
{
    const int value = game.GetCellValue(row, column);
    if (value != kEmptyValue)
    {
        target.draw(CreateDigit(value, game.IsCellGiven(row, column), GetCellCenter(row, column)));
    }
}

sf::Text BoardView::CreateDigit(int value, bool isGiven, sf::Vector2f center) const
{
    sf::Text digit(m_font, std::to_string(value), isGiven ? kGivenDigitCharacterSize : kEnteredDigitCharacterSize);
    digit.setFillColor(isGiven ? kInkColor : kEnteredDigitColor);
    digit.setStyle(isGiven ? sf::Text::Bold : sf::Text::Regular);
    digit.setOrigin(digit.getLocalBounds().getCenter());
    digit.setPosition(center);
    return digit;
}

sf::Vector2f BoardView::GetCellTopLeft(std::size_t row, std::size_t column) const
{
    const sf::Vector2f offset(static_cast<float>(column) * kBoardCellSize, static_cast<float>(row) * kBoardCellSize);
    return m_topLeft + offset;
}

sf::Vector2f BoardView::GetCellCenter(std::size_t row, std::size_t column) const
{
    constexpr float kHalfCell = kBoardCellSize / kHalf;
    return GetCellTopLeft(row, column) + sf::Vector2f(kHalfCell, kHalfCell);
}
}
