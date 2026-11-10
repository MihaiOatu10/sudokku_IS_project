#include "Application.h"

namespace sudoku::gui
{

namespace
{
constexpr unsigned kWindowWidth = 1000;
constexpr unsigned kWindowHeight = 700;
constexpr unsigned kFrameRateLimit = 60;
const sf::Color kBackgroundColor{255, 248, 231};
}

Application::Application() : m_window(sf::VideoMode({kWindowWidth, kWindowHeight}), "Sudoku")
{
    m_window.setFramerateLimit(kFrameRateLimit);
}

void Application::Run()
{
    while (m_window.isOpen())
    {
        HandleEvents();
        Draw();
    }
}

void Application::HandleEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
    }
}

void Application::Draw()
{
    m_window.clear(kBackgroundColor);
    m_window.display();
}

}
