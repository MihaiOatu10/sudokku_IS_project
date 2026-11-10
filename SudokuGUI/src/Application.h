#pragma once

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
};

}
