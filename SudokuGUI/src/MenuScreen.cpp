#include "MenuScreen.h"
#include "Theme.h"

namespace sudoku::gui
{
MenuScreen::MenuScreen(IMenu& menu, const sf::Font& font) : m_menu(menu)
{
    InitializeTitle(font);
    InitializeDifficultyButtons(font);
    m_menu.AddListener(this);
}

MenuScreen::~MenuScreen()
{
    m_menu.RemoveListener(this);
}

void MenuScreen::HandleMouseMove(sf::Vector2f mousePosition)
{
    for (auto& pair : m_difficultyButtons)
    {
        pair.second.UpdateHover(mousePosition);
    }
}

void MenuScreen::HandleClick(sf::Vector2f mousePosition)
{
    for (auto& pair : m_difficultyButtons)
    {
        if (pair.second.Contains(mousePosition))
        {
            m_menu.SelectDifficulty(pair.first);
        }
    }
}

void MenuScreen::Draw(sf::RenderTarget& target) const
{
    for (const auto& letter : m_titleLetters)
    {
        target.draw(letter);
    }

    for (const auto& pair : m_difficultyButtons)
    {
        pair.second.Draw(target);
    }
}

void MenuScreen::OnDifficultySelected(EDifficulty difficulty)
{
    for (auto& pair : m_difficultyButtons)
    {
        pair.second.SetSelected(pair.first == difficulty);
    }
}

void MenuScreen::OnPlayUnlocked() {}

void MenuScreen::OnScreenChanged(EScreen screen) {}

void MenuScreen::InitializeTitle(const sf::Font& font)
{
    const float startX = (kWindowWidth - (kTitleText.size() * kTitleSpacing)) / 2.0f;

    for (std::size_t i = 0; i < kTitleText.size(); ++i)
    {
        sf::Text letter(font, std::string(1, kTitleText[i]), static_cast<unsigned int>(kTitleFontSize));
        letter.setFillColor(kTitleColors[i % kTitleColors.size()]);
        letter.setOutlineColor(kTitleOutlineColor);
        letter.setOutlineThickness(kTitleOutlineThickness);
        letter.setRotation(sf::degrees(kTitleRotations[i % kTitleRotations.size()]));
        letter.setPosition({startX + (i * kTitleSpacing), kTitleY});
        m_titleLetters.push_back(std::move(letter));
    }
}

void MenuScreen::InitializeDifficultyButtons(const sf::Font& font)
{
    float currentY = kButtonStartY;
    const float centerX = kWindowWidth / 2.0f;

    for (const EDifficulty difficulty : kAllDifficulties)
    {
        Button btn(font, GetDifficultyName(difficulty), {centerX, currentY}, {kButtonWidth, kButtonHeight});
        m_difficultyButtons.emplace_back(difficulty, std::move(btn));
        currentY += kButtonHeight + kButtonSpacing;
    }
}

std::string MenuScreen::GetDifficultyName(EDifficulty difficulty) const
{
    switch (difficulty)
    {
    case EDifficulty::Easy:
        return "Easy";
    case EDifficulty::Medium:
        return "Medium";
    case EDifficulty::Hard:
        return "Hard";
    case EDifficulty::Expert:
        return "Expert";
    default:
        return "";
    }
}
} 
