#include "BoardView.h"
#include "SudokuLogic/BoardConstants.h"
#include "Theme.h"
#include <array>
#include <string>

namespace sudoku::gui
{
namespace
{
constexpr sf::Angle kQuarterTurn = sf::degrees(90.f);
constexpr sf::Angle kHalfTurn = sf::degrees(180.f);
constexpr std::size_t kCornerCount = 4;
}

BoardView::BoardView(const sf::Font& font, sf::Vector2f topLeft, float cellSize)
    : m_font(font), m_topLeft(topLeft), m_cellSize(cellSize)
{
    InitializeBackground();
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

void BoardView::InitializeBackground()
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

    m_background.setPosition(m_topLeft);
    m_background.setFillColor(kBoardBackgroundColor);
    m_background.setOutlineColor(kInkColor);
    m_background.setOutlineThickness(kThickLineThickness);

    m_shadow.setPosition({m_topLeft.x + kBoardShadowOffset, m_topLeft.y + kBoardShadowOffset});
    m_shadow.setFillColor(kBoardShadowColor);
}

void BoardView::InitializeGrid()
{
    const float boardSize = m_cellSize * static_cast<float>(kBoardSize);

    for (std::size_t lineIndex = 1; lineIndex < kBoardSize; ++lineIndex)
    {
        const sf::Vector2f lineCorner = GetCellTopLeft(lineIndex, lineIndex);
        const bool isThickLine = (lineIndex % kBoxSize == 0);
        const float thickness = isThickLine ? kThickLineThickness : kThinLineThickness;
        const float halfThickness = thickness / kHalf;

        sf::RectangleShape horizontalLine({boardSize, thickness});
        horizontalLine.setPosition({m_topLeft.x, lineCorner.y - halfThickness});
        horizontalLine.setFillColor(kInkColor);
        m_gridLines.push_back(horizontalLine);

        sf::RectangleShape verticalLine({thickness, boardSize});
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
    const sf::Vector2f offset(static_cast<float>(column) * m_cellSize, static_cast<float>(row) * m_cellSize);
    return m_topLeft + offset;
}

sf::Vector2f BoardView::GetCellCenter(std::size_t row, std::size_t column) const
{
    const float halfCell = m_cellSize / kHalf;
    return GetCellTopLeft(row, column) + sf::Vector2f(halfCell, halfCell);
}
}
