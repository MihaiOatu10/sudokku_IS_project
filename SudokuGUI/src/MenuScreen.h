#pragma once
#include "Button.h"
#include "TitleText.h"

#include "SudokuLogic/EDifficulty.h"
#include "SudokuLogic/EScreen.h"
#include "SudokuLogic/IMenu.h"
#include "SudokuLogic/IMenuListener.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <utility>
#include <vector>

namespace sudoku::gui
{
class MenuScreen : public IMenuListener
{
  public:
    MenuScreen(IMenu& menu, const sf::Font& font);
    ~MenuScreen() override;

    void HandleMouseMove(sf::Vector2f mousePosition);
    void HandleClick(sf::Vector2f mousePosition);
    void Draw(sf::RenderTarget& target) const;

    void OnDifficultySelected(EDifficulty difficulty) override;
    void OnPlayUnlocked() override;
    void OnScreenChanged(EScreen screen) override;

  private:
    void Refresh();
    void InitializeTitle();
    void InitializeDifficultyButtons(const sf::Font& font);
    void InitializePromptText();
    float GetPlayButtonY() const;

    IMenu& m_menu;
    TitleText m_title;
    std::vector<std::pair<EDifficulty, Button>> m_difficultyButtons;
    Button m_playButton;
    sf::Text m_promptText;
};
} 
