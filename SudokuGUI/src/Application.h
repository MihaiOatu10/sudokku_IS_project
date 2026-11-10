#pragma once

#include "Background.h"

#include <SFML/Graphics.hpp>

namespace sudoku::gui
{

class Application
{
public:
    Application();

    void Run();

private:
    void HandleEvents();
    void Draw();

    sf::RenderWindow m_window;
    sf::Font m_font;
    Background m_background;
};

}
