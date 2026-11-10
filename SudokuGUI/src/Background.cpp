#include "Background.h"

#include "Theme.h"

#include <utility>

namespace sudoku::gui
{

namespace
{
constexpr sf::Angle kFullTurn = sf::degrees(360.f);

std::unique_ptr<sf::RectangleShape> CreateRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
    auto rectangle = std::make_unique<sf::RectangleShape>(size);
    rectangle->setPosition(position);
    rectangle->setFillColor(color);
    return rectangle;
}

std::unique_ptr<sf::CircleShape> CreateCenteredCircle(float radius, std::size_t pointCount)
{
    auto circle = std::make_unique<sf::CircleShape>(radius, pointCount);
    circle->setOrigin({radius, radius});
    return circle;
}

std::unique_ptr<sf::Shape> CreateRing(float radius, sf::Color color)
{
    auto ring = CreateCenteredCircle(radius, kRingPointCount);
    ring->setFillColor(sf::Color::Transparent);
    ring->setOutlineThickness(kDoodleOutlineThickness);
    ring->setOutlineColor(color);
    return ring;
}

std::unique_ptr<sf::Shape> CreateTriangle(float radius, sf::Color color)
{
    auto triangle = CreateCenteredCircle(radius, kTrianglePointCount);
    triangle->setFillColor(color);
    return triangle;
}

std::unique_ptr<sf::Shape> CreateStar(float radius, sf::Color color)
{
    const std::size_t cornerCount = kStarPointCount * 2;
    const sf::Angle cornerAngleStep = kFullTurn / static_cast<float>(cornerCount);
    auto star = std::make_unique<sf::ConvexShape>(cornerCount);
    for (std::size_t corner = 0; corner < cornerCount; ++corner)
    {
        const float cornerRadius = corner % 2 == 0 ? radius : radius * kStarInnerRadiusRatio;
        const sf::Angle angle = kStarStartAngle + cornerAngleStep * static_cast<float>(corner);
        star->setPoint(corner, sf::Vector2f(cornerRadius, angle));
    }
    star->setFillColor(color);
    return star;
}

std::unique_ptr<sf::Shape> CreateShape(const ShapeDoodle& doodle)
{
    if (doodle.shape == EDoodleShape::Ring)
    {
        return CreateRing(doodle.radius, doodle.color);
    }
    if (doodle.shape == EDoodleShape::Triangle)
    {
        return CreateTriangle(doodle.radius, doodle.color);
    }
    return CreateStar(doodle.radius, doodle.color);
}

std::unique_ptr<sf::Text> CreateDigit(const DigitDoodle& doodle, const sf::Font& font)
{
    auto digit = std::make_unique<sf::Text>(font, sf::String(doodle.digit), kDigitCharacterSize);
    digit->setFillColor(doodle.color);
    digit->setStyle(sf::Text::Bold);
    digit->setOrigin(digit->getLocalBounds().getCenter());
    return digit;
}

void PlaceDoodle(sf::Transformable& doodle, sf::Vector2f position, sf::Angle rotation)
{
    doodle.setPosition(position);
    doodle.setRotation(rotation);
}
}

Background::Background(sf::Vector2f size, const sf::Font& font)
{
    m_drawables.push_back(CreateRectangle(size, {}, kBackgroundColor));
    AddRuledLines(size);
    m_drawables.push_back(CreateRectangle({kMarginLineThickness, size.y}, {kMarginLineX, 0.f}, kMarginLineColor));
    AddShapeDoodles();
    AddDigitDoodles(font);
}

void Background::Draw(sf::RenderTarget& target) const
{
    for (const std::unique_ptr<sf::Drawable>& drawable : m_drawables)
    {
        target.draw(*drawable);
    }
}

void Background::AddRuledLines(sf::Vector2f size)
{
    for (float lineY = kFirstRuledLineY; lineY < size.y; lineY += kRuledLineSpacing)
    {
        m_drawables.push_back(CreateRectangle({size.x, kRuledLineThickness}, {0.f, lineY}, kRuledLineColor));
    }
}

void Background::AddShapeDoodles()
{
    for (const ShapeDoodle& doodle : kShapeDoodles)
    {
        std::unique_ptr<sf::Shape> shape = CreateShape(doodle);
        PlaceDoodle(*shape, doodle.position, doodle.rotation);
        m_drawables.push_back(std::move(shape));
    }
}

void Background::AddDigitDoodles(const sf::Font& font)
{
    for (const DigitDoodle& doodle : kDigitDoodles)
    {
        std::unique_ptr<sf::Text> digit = CreateDigit(doodle, font);
        PlaceDoodle(*digit, doodle.position, doodle.rotation);
        m_drawables.push_back(std::move(digit));
    }
}

}
