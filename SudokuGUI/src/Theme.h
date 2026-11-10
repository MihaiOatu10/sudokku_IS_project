#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <cstddef>
#include <string_view>

#include "SudokuLogic/EDifficulty.h"

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

inline constexpr sf::Color kInkColor{70, 62, 95};
inline constexpr sf::Color kDisabledInkColor{160, 160, 165};
inline constexpr sf::Color kButtonColor = kPastelSky;
inline constexpr sf::Color kButtonSelectedColor = kPastelPeach;
inline constexpr sf::Color kButtonDisabledColor{220, 220, 222};

inline constexpr float kButtonCornerRadius = 18.f;
inline constexpr std::size_t kButtonCornerPointCount = 8;
inline constexpr float kButtonOutlineThickness = 4.f;
inline constexpr float kButtonSelectedOutlineThickness = 7.f;
inline constexpr unsigned kButtonCharacterSize = 32;
inline constexpr float kButtonHoverScale = 1.06f;
inline constexpr float kButtonHoverLightenRatio = 0.35f;
inline constexpr sf::Vector2f kTestButtonSize{220.f, 80.f};

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

inline constexpr std::array kAllDifficulties{EDifficulty::Easy, EDifficulty::Medium, EDifficulty::Hard, EDifficulty::Expert};

inline constexpr float kTitleFontSize = 80.f;
inline constexpr float kTitleOutlineThickness = 3.f;
inline constexpr float kTitleY = 50.f;
inline constexpr float kTitleSpacing = 60.f;

inline constexpr float kButtonWidth = 200.f;
inline constexpr float kButtonHeight = 50.f;
inline constexpr float kButtonSpacing = 20.f;
inline constexpr float kButtonStartY = 200.f;

inline constexpr sf::Color kTitleOutlineColor{50, 50, 50};

inline constexpr std::array kTitleColors{kPastelPink, kPastelSky, kPastelMint, kPastelPeach, kPastelLavender, kPastelPink};

inline constexpr std::array kTitleRotations{-10.f, 10.f, -10.f, 10.f, -10.f, 10.f};

inline constexpr std::string_view kTitleText = "SUDOKU";

inline constexpr float kPlayButtonWidth = 250.f;
inline constexpr float kPlayButtonHeight = 60.f;
inline constexpr float kPlayButtonMargin = 40.f;
inline constexpr float kPromptFontSize = 20.f;
inline constexpr float kPromptMargin = 15.f;

inline constexpr sf::Color kPlayButtonColor{152, 251, 152};
inline constexpr sf::Color kPromptTextColor{100, 100, 100};

inline constexpr std::string_view kPromptMessage = "Pick a level to start!";
}
