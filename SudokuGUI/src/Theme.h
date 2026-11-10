#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <cstddef>
#include <string_view>

namespace sudoku::gui
{

inline constexpr unsigned kWindowWidth = 1000;
inline constexpr unsigned kWindowHeight = 700;

inline constexpr std::string_view kFontPath = "assets/fonts/Fredoka.ttf";

inline constexpr sf::Color kBackgroundColor{255, 248, 231};
inline constexpr sf::Color kRuledLineColor{200, 222, 245};
inline constexpr sf::Color kMarginLineColor{245, 160, 170};

inline constexpr sf::Color kPastelPink{255, 175, 200};
inline constexpr sf::Color kPastelMint{150, 220, 190};
inline constexpr sf::Color kPastelLavender{195, 175, 240};
inline constexpr sf::Color kPastelPeach{255, 195, 150};
inline constexpr sf::Color kPastelSky{145, 200, 245};

inline constexpr float kFirstRuledLineY = 90.f;
inline constexpr float kRuledLineSpacing = 32.f;
inline constexpr float kRuledLineThickness = 2.f;
inline constexpr float kMarginLineX = 80.f;
inline constexpr float kMarginLineThickness = 3.f;

inline constexpr float kDoodleOutlineThickness = 4.f;
inline constexpr std::size_t kRingPointCount = 30;
inline constexpr std::size_t kTrianglePointCount = 3;
inline constexpr std::size_t kStarPointCount = 5;
inline constexpr float kStarInnerRadiusRatio = 0.45f;
inline constexpr sf::Angle kStarStartAngle = sf::degrees(-90.f);
inline constexpr unsigned kDigitCharacterSize = 52;

enum class EDoodleShape
{
    Ring,
    Triangle,
    Star
};

struct ShapeDoodle
{
    EDoodleShape shape;
    sf::Vector2f position;
    float radius;
    sf::Angle rotation;
    sf::Color color;
};

struct DigitDoodle
{
    char digit;
    sf::Vector2f position;
    sf::Angle rotation;
    sf::Color color;
};

inline constexpr std::array kShapeDoodles{
    ShapeDoodle{EDoodleShape::Ring, {45.f, 45.f}, 16.f, sf::degrees(0.f), kPastelPink},
    ShapeDoodle{EDoodleShape::Star, {150.f, 38.f}, 20.f, sf::degrees(12.f), kPastelPeach},
    ShapeDoodle{EDoodleShape::Star, {790.f, 40.f}, 16.f, sf::degrees(-10.f), kPastelSky},
    ShapeDoodle{EDoodleShape::Triangle, {935.f, 75.f}, 24.f, sf::degrees(15.f), kPastelMint},
    ShapeDoodle{EDoodleShape::Ring, {955.f, 330.f}, 13.f, sf::degrees(0.f), kPastelLavender},
    ShapeDoodle{EDoodleShape::Star, {42.f, 370.f}, 18.f, sf::degrees(-8.f), kPastelPink},
    ShapeDoodle{EDoodleShape::Triangle, {40.f, 640.f}, 20.f, sf::degrees(-20.f), kPastelPeach},
    ShapeDoodle{EDoodleShape::Star, {905.f, 625.f}, 26.f, sf::degrees(20.f), kPastelLavender},
    ShapeDoodle{EDoodleShape::Ring, {560.f, 660.f}, 11.f, sf::degrees(0.f), kPastelMint},
};

inline constexpr std::array kDigitDoodles{
    DigitDoodle{'5', {40.f, 210.f}, sf::degrees(-14.f), kPastelMint},
    DigitDoodle{'1', {440.f, 38.f}, sf::degrees(-8.f), kPastelLavender},
    DigitDoodle{'7', {880.f, 200.f}, sf::degrees(12.f), kPastelPink},
    DigitDoodle{'9', {950.f, 500.f}, sf::degrees(16.f), kPastelPeach},
    DigitDoodle{'3', {130.f, 605.f}, sf::degrees(-12.f), kPastelSky},
    DigitDoodle{'2', {330.f, 660.f}, sf::degrees(9.f), kPastelPink},
};

}
