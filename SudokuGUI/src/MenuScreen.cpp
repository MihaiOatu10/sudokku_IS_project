#include "MenuScreen.h"
#include "Theme.h"

namespace sudoku::gui
{
MenuScreen::MenuScreen(IMenu& menu, const sf::Font& font)
    : m_menu(menu), m_playButton(font, "Play", sf::Vector2f(static_cast<float>(kWindowWidth) / kHalf, GetPlayButtonY()),
                                 sf::Vector2f(kPlayButtonWidth, kPlayButtonHeight)),
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
    for (auto& [difficulty, button] : m_difficultyButtons)
    {
        button.UpdateHover(mousePosition);
    }
    m_playButton.UpdateHover(mousePosition);
}

void MenuScreen::HandleClick(sf::Vector2f mousePosition)
{
    for (auto& [difficulty, button] : m_difficultyButtons)
    {
        if (button.Contains(mousePosition))
        {
            m_menu.SelectDifficulty(difficulty);
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

    for (const auto& [difficulty, button] : m_difficultyButtons)
    {
        button.Draw(target);
    }

    m_playButton.Draw(target);

    if (!m_isPlayUnlocked)
    {
        target.draw(m_promptText);
    }
}

void MenuScreen::OnDifficultySelected(EDifficulty selectedDifficulty)
{
    for (auto& [difficulty, button] : m_difficultyButtons)
    {
        button.SetSelected(difficulty == selectedDifficulty);
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
    const float startX =
        (static_cast<float>(kWindowWidth) - (static_cast<float>(kTitleText.size()) * kTitleSpacing)) / kHalf;

    for (std::size_t letterIndex = 0; letterIndex < kTitleText.size(); ++letterIndex)
    {
        sf::Text letter(font, std::string(1, kTitleText[letterIndex]), static_cast<unsigned int>(kTitleFontSize));
        letter.setFillColor(kTitleColors[letterIndex % kTitleColors.size()]);
        letter.setOutlineColor(kTitleOutlineColor);
        letter.setOutlineThickness(kTitleOutlineThickness);
        letter.setRotation(sf::degrees(kTitleRotations[letterIndex % kTitleRotations.size()]));
        letter.setPosition({startX + (static_cast<float>(letterIndex) * kTitleSpacing), kTitleY});
        m_titleLetters.push_back(std::move(letter));
    }
}

void MenuScreen::InitializeDifficultyButtons(const sf::Font& font)
{
    float currentY = kButtonStartY;
    const float centerX = static_cast<float>(kWindowWidth) / kHalf;

    for (const EDifficulty difficulty : sudoku::kAllDifficulties)
    {
        Button button(font, std::string(sudoku::GetDifficultyName(difficulty)), sf::Vector2f(centerX, currentY),
                      sf::Vector2f(kButtonWidth, kButtonHeight));
        m_difficultyButtons.emplace_back(difficulty, std::move(button));
        currentY += kButtonHeight + kButtonSpacing;
    }
}

void MenuScreen::InitializePromptText()
{
    m_promptText.setFillColor(kPromptTextColor);

    const sf::FloatRect bounds = m_promptText.getLocalBounds();
    const float textX = (static_cast<float>(kWindowWidth) - bounds.size.x) / kHalf;
    const float centerY = GetPlayButtonY();
    const float textY = centerY + (kPlayButtonHeight / kHalf) + kPromptMargin;

    m_promptText.setPosition({textX, textY});
}

float MenuScreen::GetPlayButtonY() const
{
    return kButtonStartY + (static_cast<float>(sudoku::kAllDifficulties.size()) * (kButtonHeight + kButtonSpacing)) +
           kPlayButtonMargin;
}
} 
