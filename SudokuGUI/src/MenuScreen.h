#pragma once
#include "Button.h"
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
    void InitializeTitle(const sf::Font& font);
    void InitializeDifficultyButtons(const sf::Font& font);
    std::string GetDifficultyName(EDifficulty difficulty) const;

    IMenu& m_menu;
    std::vector<sf::Text> m_titleLetters;
    std::vector<std::pair<EDifficulty, Button>> m_difficultyButtons;
};
} 
