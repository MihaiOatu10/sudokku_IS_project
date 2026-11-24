#include "Application.h"

#include "Theme.h"

#include <SFML/Window/Event.hpp>

#include <optional>
#include <stdexcept>
#include <string>

namespace sudoku::gui
{
namespace
{
sf::Font LoadFont()
{
    sf::Font font;
    if (!font.openFromFile(std::string(kFontPath)))
    {
        throw std::runtime_error("Could not load the font from " + std::string(kFontPath));
    }
    return font;
}
}

Application::Application()
    : m_window(sf::VideoMode({kWindowWidth, kWindowHeight}), std::string(kWindowTitle),
               sf::Style::Titlebar | sf::Style::Close),
      m_font(LoadFont()),
      m_background(kWindowSize, m_font),
      m_menu(IMenu::Produce()), m_menuScreen(*m_menu, m_font), m_gameScreen(*m_menu, m_font)
{
    m_window.setFramerateLimit(kFrameRateLimit);
}

void Application::Run()
{
    while (m_window.isOpen())
    {
        ProcessEvents();
        Render();
    }
}

void Application::ProcessEvents()
{
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        else
        {
            HandleEvent(*event);
        }
    }
}

void Application::HandleEvent(const sf::Event& event)
{
    if (const auto* mouseMove = event.getIf<sf::Event::MouseMoved>())
    {
        HandleMouseMove(m_window.mapPixelToCoords(mouseMove->position));
    }
    else if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButton->button == sf::Mouse::Button::Left)
        {
            HandleClick(m_window.mapPixelToCoords(mouseButton->position));
        }
    }
}

void Application::HandleMouseMove(sf::Vector2f mousePosition)
{
    if (IsMainMenuShown())
    {
        m_menuScreen.HandleMouseMove(mousePosition);
    }
    else if (IsGameShown())
    {
        m_gameScreen.HandleMouseMove(mousePosition, GetGame());
    }
}

void Application::HandleClick(sf::Vector2f mousePosition)
{
    if (IsMainMenuShown())
    {
        m_menuScreen.HandleClick(mousePosition);
    }
    else if (IsGameShown())
    {
        m_gameScreen.HandleClick(mousePosition, GetGame());
    }
}

void Application::Render()
{
    m_window.clear();
    m_background.Draw(m_window);
    if (IsMainMenuShown())
    {
        m_menuScreen.Draw(m_window);
    }
    else if (IsGameShown())
    {
        m_gameScreen.Draw(m_window, GetGame());
    }
    m_window.display();
}

bool Application::IsMainMenuShown() const
{
    return m_menu->GetCurrentScreen() == EScreen::MainMenu;
}

bool Application::IsGameShown() const
{
    return m_menu->GetCurrentScreen() == EScreen::Game;
}

IGame& Application::GetGame() const
{
    return *m_menu->GetGame();
}
}
