#include "MenuScreen.h"
#include "Theme.h"

namespace sudoku::gui
{
MenuScreen::MenuScreen(IMenu& menu, const sf::Font& font)
    : m_menu(menu), m_playButton(font, "Play", sf::Vector2f(kWindowWidth / kHalf, GetPlayButtonY()),sf::Vector2f(kPlayButtonWidth, kPlayButtonHeight)),
      m_promptText(font, std::string(kPromptMessage), static_cast<unsigned int>(kPromptFontSize)),
      m_isPlayUnlocked(m_menu.IsPlayUnlocked())
{
    InitializeTitle(font);
    InitializeDifficultyButtons(font);
    m_playButton.SetEnabled(m_isPlayUnlocked);
    InitializePromptText();

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
    m_playButton.UpdateHover(mousePosition);
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

    if (m_playButton.Contains(mousePosition))
    {
        m_menu.Play();
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

    m_playButton.Draw(target);

    if (!m_isPlayUnlocked)
    {
        target.draw(m_promptText);
    }
}

void MenuScreen::OnDifficultySelected(EDifficulty difficulty)
{
    for (auto& pair : m_difficultyButtons)
    {
        pair.second.SetSelected(pair.first == difficulty);
    }
}

void MenuScreen::OnPlayUnlocked()
{
    m_isPlayUnlocked = true;
    m_playButton.SetEnabled(true);
}

void MenuScreen::OnScreenChanged(EScreen) {}

void MenuScreen::InitializeTitle(const sf::Font& font)
{
    const float startX = (kWindowWidth - (kTitleText.size() * kTitleSpacing)) / kHalf;

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
    const float centerX = kWindowWidth / kHalf;

    for (const EDifficulty difficulty : sudoku::kAllDifficulties)
    {
        Button btn(font, std::string(sudoku::GetDifficultyName(difficulty)), sf::Vector2f(centerX, currentY), sf::Vector2f(kButtonWidth, kButtonHeight));
        m_difficultyButtons.emplace_back(difficulty, std::move(btn));
        currentY += kButtonHeight + kButtonSpacing;
    }
}

void MenuScreen::InitializePromptText()
{
    m_promptText.setFillColor(kPromptTextColor);

    const sf::FloatRect bounds = m_promptText.getLocalBounds();
    const float textX = (kWindowWidth - bounds.size.x) / kHalf;
    const float centerY = GetPlayButtonY();
    const float textY = centerY + (kPlayButtonHeight / kHalf) + kPromptMargin;

    m_promptText.setPosition({textX, textY});
}

float MenuScreen::GetPlayButtonY() const
{
    return kButtonStartY + (sudoku::kAllDifficulties.size() * (kButtonHeight + kButtonSpacing)) + kPlayButtonMargin;
}
} 
