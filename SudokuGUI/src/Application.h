#pragma once

#include "Background.h"
#include "GameScreen.h"
#include "MenuScreen.h"

#include "SudokuLogic/IMenu.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace sudoku::gui
{
class Application
{
  public:
    Application();

    void Run();

  private:
    void ProcessEvents();
    void HandleEvent(const sf::Event& event);
    void HandleMouseMove(sf::Vector2f mousePosition);
    void HandleClick(sf::Vector2f mousePosition);
    void Render();

    bool IsMainMenuShown() const;
    bool IsGameShown() const;
    IGame& GetGame() const;

    sf::RenderWindow m_window;
    sf::Font m_font;
    Background m_background;
    std::unique_ptr<IMenu> m_menu;
    MenuScreen m_menuScreen;
    GameScreen m_gameScreen;
};
}
