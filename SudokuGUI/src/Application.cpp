#include "Application.h"

#include "Theme.h"

#include <stdexcept>
#include <string>

namespace sudoku::gui
{

namespace
{
constexpr unsigned kFrameRateLimit = 60;

sf::Font LoadFont()
{
    sf::Font font;
    if (!font.openFromFile(kFontPath))
    {
        throw std::runtime_error("Could not load the font from " + std::string(kFontPath));
    }
    return font;
}
}

Application::Application()
    : m_window(sf::VideoMode({kWindowWidth, kWindowHeight}), "Sudoku"), m_font(LoadFont()),
      m_background(sf::Vector2f(m_window.getSize()), m_font),
      m_testButton(m_font, "Test", sf::Vector2f(m_window.getSize()) / 2.f, kTestButtonSize)
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
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            m_testButton.UpdateHover(m_window.mapPixelToCoords(mouseMoved->position));
        }
    }
}

void Application::Draw()
{
    m_window.clear();
    m_background.Draw(m_window);
    m_testButton.Draw(m_window);
    m_window.display();
}

}
