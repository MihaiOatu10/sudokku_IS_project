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

sf::Color GetDigitColor(ECellState state)
{
    switch (state)
    {
    case ECellState::Given:
        return kGivenDigitColor;
    case ECellState::Correct:
        return kCorrectDigitColor;
    case ECellState::Wrong:
        return kWrongDigitColor;
    case ECellState::Empty:
    default:
        return kInkColor;
    }
}
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

void BoardView::Draw(sf::RenderTarget& target, const IGame* game) const
{
    target.draw(m_shadow);
    target.draw(m_background);
    if (game)
    {
        DrawSelectedCell(target, *game);
    }
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

std::optional<CellPosition> BoardView::FindCellAt(sf::Vector2f position) const
{
    const sf::Vector2f boardTopLeft = GetCellTopLeft(0, 0);
    const sf::Vector2f relativePosition = position - boardTopLeft;

    if (relativePosition.x < 0.f || relativePosition.y < 0.f)
    {
        return std::nullopt;
    }

    const std::size_t column = static_cast<std::size_t>(relativePosition.x / kBoardCellSize);
    const std::size_t row = static_cast<std::size_t>(relativePosition.y / kBoardCellSize);

    if (row >= kBoardSize || column >= kBoardSize)
    {
        return std::nullopt;
    }

    return CellPosition{row, column};
}

void BoardView::DrawSelectedCell(sf::RenderTarget& target, const IGame& game) const
{
    for (std::size_t row = 0; row < kBoardSize; ++row)
    {
        for (std::size_t column = 0; column < kBoardSize; ++column)
        {
            if (game.IsCellSelected(row, column))
            {
                sf::RectangleShape highlight({kBoardCellSize, kBoardCellSize});
                highlight.setPosition(GetCellTopLeft(row, column));
                highlight.setFillColor(kSelectedCellColor);
                target.draw(highlight);
                return;
            }
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
        target.draw(CreateDigit(value, game.GetCellState(row, column), GetCellCenter(row, column)));
    }
}

sf::Text BoardView::CreateDigit(int value, ECellState state, sf::Vector2f center) const
{
    const bool isGiven = (state == ECellState::Given);
    sf::Text digit(m_font, std::to_string(value), isGiven ? kGivenDigitCharacterSize : kEnteredDigitCharacterSize);
    digit.setFillColor(GetDigitColor(state));
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
