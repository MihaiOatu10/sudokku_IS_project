#pragma once
#include "Background.h"
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
    void Render();
    void HandleMouseMoved(sf::Vector2f mousePosition);
    void HandleMouseButtonPressed(sf::Vector2f mousePosition);

    sf::RenderWindow m_window;
    sf::Font m_font;
    Background m_background;
    std::unique_ptr<IMenu> m_menu;
    MenuScreen m_menuScreen;
};
} 
